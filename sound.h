#ifndef SOUND_H
#define SOUND_H
#include <windows.h>
#include <iostream>

using namespace std;


void playSound(const char* soundFile) {
    size_t len = strlen(soundFile) + 1;
    wchar_t* wSoundFile = new wchar_t[len];
    mbstowcs(wSoundFile, soundFile, len);

    if (PlaySoundW(wSoundFile, NULL, SND_FILENAME | SND_ASYNC)) {
        std::wcout << L"Playing sound: " << wSoundFile << std::endl;
    } else {
        std::wcerr << L"Failed to play sound: " << wSoundFile << std::endl;
    }

    delete[] wSoundFile; 

}

#endif

