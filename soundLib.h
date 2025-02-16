#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <tchar.h>
// Links the windows multi media library as a dynamic library
#pragma comment(lib, "winmm.lib")

void laugh(){
    // Unicode version of play sound
    PlaySoundW(L"crazy.wav", NULL, SND_FILENAME | SND_ASYNC);
    // Allows sound to play out
    Sleep(5000);
}
