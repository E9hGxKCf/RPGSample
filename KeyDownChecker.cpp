//KeyDownChecker.cpp
#include "KeyDownChecker.h"

KeyDownChecker::KeyDownChecker()
{
	ZeroMemory(Buf, sizeof(char) * 256);
	ZeroMemory(StateBuf, sizeof(char) * 256);
}

bool KeyDownChecker::GetKeyDown(int KeyCode)
{
	return(Buf[KeyCode] == 1 ? true : false);
}

bool KeyDownChecker::GetKey(int KeyCode)
{
	return(Buf[KeyCode] > 0 ? true : false);
}

KeyDownChecker* KeyDownChecker::GetInstance()
{
	static KeyDownChecker Checker;
	return&Checker;
}

void KeyDownChecker::CheckKeyState()
{
	GetHitKeyStateAll(StateBuf);
	for (int i = 0; i < 256; i++)
	{
		if (StateBuf[i] == 1)
			Buf[i]++;
		else
			Buf[i] = 0;
	}
}

bool KeyDownChecker::GetKeyDownState(int KeyCode)
{
	return GetInstance()->GetKeyDown(KeyCode);
}

bool KeyDownChecker::GetKeyState(int KeyCode)
{
	return GetInstance()->GetKey(KeyCode);
}