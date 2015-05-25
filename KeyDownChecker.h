//KeyDownChecker.h
#include "DxLib.h"

class KeyDownChecker
{
private:
	int Buf[256];
	char StateBuf[256];

	KeyDownChecker();
	bool GetKeyDown(int KeyCode);
	bool GetKey(int KeyCode);

public:
	static KeyDownChecker* GetInstance();
	void CheckKeyState();
	static bool GetKeyDownState(int KeyCode);
	static bool GetKeyState(int KeyCode);
};