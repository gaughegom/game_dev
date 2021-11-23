#include "InputHandler.h"

CInputHandler* CInputHandler::__instance = nullptr;

CInputHandler::CInputHandler()
{
}

CInputHandler::CInputHandler(HWND hWnd, LPKEYEVENTHANDLER keyHandler)
{
	this->hWnd = hWnd;
	this->keyHandler = keyHandler;
}

void CInputHandler::SetHandleWindow(HWND hWnd)
{
	this->hWnd = hWnd;
}

void CInputHandler::SetKeyHandler(LPKEYEVENTHANDLER handler)
{
	this->keyHandler = handler;
}

void CInputHandler::InitKeyboard()
{
	HRESULT
		hr = DirectInput8Create
		(
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&di, NULL
		);

	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DirectInput8Create failed!\n");
		return;
	}

	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] CreateDevice failed!\n");
		return;
	}

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = didv->SetDataFormat(&c_dfDIKeyboard);

	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
}

void CInputHandler::ProcessKeyboard()
{
	HRESULT hResult;

	// Collect all key states first
	hResult = this->didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hResult))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hResult == DIERR_INPUTLOST) || (hResult == DIERR_NOTACQUIRED))
		{
			HRESULT h = this->didv->Acquire();
			if (h == DI_OK)
			{
				DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hResult);
			return;
		}
	}

	this->keyHandler->KeyState((BYTE*)&keyStates);


	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hResult = this->didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), this->keyEvents, &dwElements, 0);
	if (FAILED(hResult))
	{
		DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hResult);
		return;
	}

	this->presses.clear();

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = this->keyEvents[i].dwOfs;
		int KeyState = this->keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0) {
			this->presses.push_back(KeyCode);
			this->keyHandler->OnKeyDown(KeyCode);
		}
		else
			this->keyHandler->OnKeyUp(KeyCode);
	}
}

int CInputHandler::IsKeyDown(int keyCode)
{
	return (this->keyStates[keyCode] & 0x80) > 0;
}

int CInputHandler::OnKeyDown(int keyCode)
{
	for (int press : this->presses)
	{
		if (press == keyCode) return true;
	}
	return false;
}

CInputHandler* CInputHandler::GetInstance()
{
	if (__instance == nullptr) {
		__instance = new CInputHandler();
	}
	return __instance;
}
