#ifndef _TEXT_PLAYER_H_
#define _TEXT_PLAYER_H_
#include <vector>
#include <string>
#include <iostream>
#include <windows.h>
#include <Mmsystem.h>

#pragma comment(lib, "Winmm.lib")

class TextPlayer {
  public:
    static void play(std::vector<std::string>& vec) {
        for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
            std::string comm = "play msc/" + *it + ".mp3 wait"; //声音太短听不到声音，至少为一秒钟
            // mciSendStringA(comm.c_str(), 0, 0, 0);
            Sleep(800);
        }
    }
};

#endif // !_TEXT_PLAYER_H_
