#include "Sound.h"
#include "Util.h"

CSound* CSound::__instance = nullptr;

CSound::CSound(HWND hWnd)
{
	this->l_ptrDirectSound8 = 0;
	this->l_ptrDirectSoundBuffer = 0;
	bool result = this->InitDirectSound(hWnd);
	if (!result) {
		DebugOut(L"[ERROR] Failed InitDirectSound\n");
	}
}

CSound::~CSound()
{
	for (auto &sound : this->l_soundBuffers) {
		if (sound.second) {
			sound.second->Release();
			sound.second = nullptr;
		}
	}

	if (this->l_ptrDirectSoundBuffer) this->l_ptrDirectSoundBuffer->Release();
	this->l_ptrDirectSoundBuffer = nullptr;

	if (this->l_ptrDirectSound8) this->l_ptrDirectSound8->Release();
	this->l_ptrDirectSound8 = nullptr;
}

bool CSound::InitDirectSound(HWND hWnd)
{
	HRESULT result;
	DSBUFFERDESC bufferDesc{};
	WAVEFORMATEX waveFormat{};

	// Initialize the direct sound interface pointer for the default sound device.
	result = DirectSoundCreate8(NULL, &l_ptrDirectSound8, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Set the cooperative level to priority so the format of the primary sound buffer can be modified.
	result = l_ptrDirectSound8->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);
	if (FAILED(result))
	{
		return false;
	}

	// Setup the primary buffer description.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Get control of the primary sound buffer on the default sound device.
	result = l_ptrDirectSound8->CreateSoundBuffer(&bufferDesc, &l_ptrDirectSoundBuffer, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Setup the format of the primary sound bufffer.
	// In this case it is a .WAV file recorded at 44,100 samples per second in 16-bit stereo (cd audio format).
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// Set the primary buffer to be the wave format specified.
	result = l_ptrDirectSoundBuffer->SetFormat(&waveFormat);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool CSound::LoadWaveFile(char* fileName, std::string soundName)
{
	int error;
	FILE* ptrFile;
	unsigned int count;
	IWaveHeaderFile waveFileHeader;
	WAVEFORMATEX waveFormat{};
	DSBUFFERDESC bufferDesc{};
	HRESULT result;
	IDirectSoundBuffer* ptrTmpSoundBuffer;
	unsigned char* ptrWaveData;
	unsigned char* ptrBuffer = nullptr;
	unsigned long bufferSize = 0;

	// Open the wave file in binary.
	error = fopen_s(&ptrFile, fileName, "rb");
	if (error != 0)
	{
		return false;
	}

	// Read in the wave file header.
	count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, ptrFile);
	if (count != 1)
	{
		return false;
	}

	// Check that the chunk ID is the RIFF format.
	if ((waveFileHeader.chunkId[0] != 'R') || (waveFileHeader.chunkId[1] != 'I') ||
		(waveFileHeader.chunkId[2] != 'F') || (waveFileHeader.chunkId[3] != 'F'))
	{
		return false;
	}

	// Check that the file format is the WAVE format.
	if ((waveFileHeader.format[0] != 'W') || (waveFileHeader.format[1] != 'A') ||
		(waveFileHeader.format[2] != 'V') || (waveFileHeader.format[3] != 'E'))
	{
		return false;
	}

	// Check that the sub chunk ID is the fmt format.
	if ((waveFileHeader.subChunkId[0] != 'f') || (waveFileHeader.subChunkId[1] != 'm') ||
		(waveFileHeader.subChunkId[2] != 't') || (waveFileHeader.subChunkId[3] != ' '))
	{
		return false;
	}

	// Check that the audio format is WAVE_FORMAT_PCM.
	if (waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
	{
		return false;
	}

	// Check that the wave file was recorded in stereo format.
	if (waveFileHeader.numChannels != 2)
	{
		return false;
	}

	// Check that the wave file was recorded at a sample rate of 44.1 KHz.
	if (waveFileHeader.sampleRate != 44100)
	{
		return false;
	}

	// Ensure that the wave file was recorded in 16 bit format.
	if (waveFileHeader.bitsPerSample != 16)
	{
		return false;
	}

	// Check for the data chunk header.
	if ((waveFileHeader.dataChunkId[0] != 'd') || (waveFileHeader.dataChunkId[1] != 'a') ||
		(waveFileHeader.dataChunkId[2] != 't') || (waveFileHeader.dataChunkId[3] != 'a'))
	{
		return false;
	}

	// Set the wave format of secondary buffer that this wave file will be loaded onto.
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// Set the buffer description of the secondary sound buffer that the wave file will be loaded onto.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	IDirectSoundBuffer8* secondaryBuffer = 0;
	IDirectSoundBuffer8** pSecondaryBuffer = &secondaryBuffer;

	// Create a temporary sound buffer with the specific buffer settings.
	result = l_ptrDirectSound8->CreateSoundBuffer(&bufferDesc, &ptrTmpSoundBuffer, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Test the buffer format against the direct sound 8 interface and create the secondary buffer.
	result = ptrTmpSoundBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*pSecondaryBuffer);
	if (FAILED(result))
	{
		DebugOut(L"[ERROR] Can not create secondary buffer\n");
		return false;
	}

	// Release the temporary buffer.
	ptrTmpSoundBuffer->Release();
	ptrTmpSoundBuffer = 0;

	// Move to the beginning of the wave data which starts at the end of the data chunk header.
	fseek(ptrFile, sizeof(IWaveHeaderFile), SEEK_SET);

	// Create a temporary buffer to hold the wave file data.
	ptrWaveData = new unsigned char[waveFileHeader.dataSize];
	if (!ptrWaveData)
	{
		return false;
	}

	// Read in the wave file data into the newly created buffer.
	count = fread(ptrWaveData, 1, waveFileHeader.dataSize, ptrFile);
	if (count != waveFileHeader.dataSize)
	{
		return false;
	}

	// Close the file once done reading.
	error = fclose(ptrFile);
	if (error != 0)
	{
		return false;
	}

	// Lock the secondary buffer to write wave data into it.
	result = (*pSecondaryBuffer)->Lock(0, waveFileHeader.dataSize, (void**)&ptrBuffer, (DWORD*)&bufferSize, NULL, 0, 0);
	if (FAILED(result))
	{
		return false;
	}

	// Copy the wave data into the buffer.
	memcpy(ptrBuffer, ptrWaveData, waveFileHeader.dataSize);

	// Unlock the secondary buffer after the data has been written to it.
	result = (*pSecondaryBuffer)->Unlock((void*)ptrBuffer, bufferSize, NULL, 0);
	if (FAILED(result))
	{
		return false;
	}

	// Release the wave data since it was copied into the secondary buffer.
	delete[] ptrWaveData;
	ptrWaveData = 0;

	// Set volume of the buffer to 100%.
	(*pSecondaryBuffer)->SetVolume(DSBVOLUME_MAX);

	//m_soundBufferList[soundname] = secondaryBuffer;
	l_soundBuffers.insert(std::make_pair(soundName, secondaryBuffer));

	DebugOut(L"[INFO] Loading sound file: %s has been loaded successfully\n", ToWSTR(fileName).c_str());

	return true;
}

bool CSound::Init(HWND hWnd)
{
	bool result;

	result = LoadWaveFile((char*)"sounds/BossDie.wav", "bossDie");
	result = LoadWaveFile((char*)"sounds/EnemyDie.wav", "enemyDie");
	result = LoadWaveFile((char*)"sounds/EnemyOnDamaged.wav", "enemyTakeDamage");
	result = LoadWaveFile((char*)"sounds/EnterBossRoom.wav", "enterBossRoom");
	result = LoadWaveFile((char*)"sounds/JasonBullet.wav", "jasonBullet");
	result = LoadWaveFile((char*)"sounds/JasonDie.wav", "jasonDie");
	result = LoadWaveFile((char*)"sounds/JasonJump.wav", "jasonJump");
	result = LoadWaveFile((char*)"sounds/JasonOnDamaged.wav", "jasonTakeDamage");
	result = LoadWaveFile((char*)"sounds/PickItemUp.wav", "useItem");
	result = LoadWaveFile((char*)"sounds/ScrollingMapJump.wav", "outdoorMapJump");
	result = LoadWaveFile((char*)"sounds/SophiaBullet.wav", "sophiaBullet");
	result = LoadWaveFile((char*)"sounds/SophiaDie.wav", "sophiaDie");
	result = LoadWaveFile((char*)"sounds/BulletExplosion.wav", "bulletDestroy");
	result = LoadWaveFile((char*)"sounds/SwitchCharacter.wav", "switchCharacter");

	if (!result) {
		DebugOut(L"[ERROR] Failed to load one LoadWaveFile\n");
		return false;
	}

	return true;
}

bool CSound::PlayWaveFile(std::string soundName)
{
	std::unordered_map<std::string, IDirectSoundBuffer8*> ::iterator itSound;
	itSound = this->l_soundBuffers.find(soundName);

	itSound->second->Stop();
	itSound->second->SetCurrentPosition(0);
	itSound->second->Play(0, 0, 0);

	return true;

}

CSound* CSound::GetInstance(HWND hWnd)
{
	if (__instance == nullptr) {
		__instance = new CSound(hWnd);
	}

	return __instance;
}
