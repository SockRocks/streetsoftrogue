#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <tchar.h>
#pragma comment(lib, "winmm.lib")

void laugh(){
    PlaySoundW(L"crazy.wav", NULL, SND_FILENAME | SND_ASYNC);
    Sleep(5000);
}