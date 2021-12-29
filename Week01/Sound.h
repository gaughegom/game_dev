#pragma once
#ifndef _SOUND_H
#define _SOUND_H

#include <dsound.h>
#include <unordered_map>

struct SWaveHeaderFile
{
	char chunkId[4];
	unsigned long chunkSize;
	char format[4];
	char subChunkId[4];
	unsigned long subChunkSize;
	unsigned short audioFormat;
	unsigned short numChannels;
	unsigned long sampleRate;
	unsigned long bytesPerSecond;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
	char dataChunkId[4];
	unsigned long dataSize;
};

class CSound {
private:
	static CSound* __instance;

	IDirectSound8* l_ptrDirectSound8;
	IDirectSoundBuffer* l_ptrDirectSoundBuffer;
	std::unordered_map<std::string, IDirectSoundBuffer8*> l_soundBuffers;


	bool InitDirectSound(HWND hWnd);
	bool LoadWaveFile(char* fileName, std::string soundName);


public:
	CSound(HWND hWnd);

	~CSound();

	bool Init(HWND hWnd);
	bool PlayWaveFile(std::string soundName);

	static CSound* GetInstance();
};


#endif // !_SOUND_H
