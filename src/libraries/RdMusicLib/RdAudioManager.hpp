// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __RD_AUDIO_MANAGER_HPP__
#define __RD_AUDIO_MANAGER_HPP__

#include "RdMacros.hpp"
#include <iostream>
#include <map>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"


namespace rd{

class RdAudioManager
{
    public:

        RdAudioManager();
        ~RdAudioManager();
        bool destroy();

        static const int MUSIC = 0;
        static const int FX = 1;

        bool load( const std::string& music_filepath, const std::string& id, const int& type);
        bool playMusic(const std::string& id, int loop);
        bool playSound(const std::string& id, int loop);
        bool stopMusic();

    private:
        std::map<std::string, Mix_Chunk*> fx_sounds;
        std::map<std::string, Mix_Music*> music_sounds;

};

}

#endif //-- __RD_AUDIO_MANAGER_HPP__