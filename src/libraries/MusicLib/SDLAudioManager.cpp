
#include "SDLAudioManager.hpp"

//-- This is very important:
rd::SDLAudioManager * rd::SDLAudioManager::uniqueInstance = NULL;
const std::string rd::SDLAudioManager::id = "SDL";

//-- C++ forces us to initialize constants here:
const int rd::SDLAudioManager::MUSIC = 0;
const int rd::SDLAudioManager::FX = 1;

rd::SDLAudioManager::SDLAudioManager()
{
    if(SDL_Init(SDL_INIT_AUDIO)==-1)
        RD_ERROR("SDL Audio subsystem could not be initialized!\n");

    if(Mix_OpenAudio(22050, AUDIO_S16, 2, 4096)==-1)
        RD_ERROR("AudioMixer could not be opened!\n");
}


bool rd::SDLAudioManager::load(const std::string &music_filepath, const std::string &id, const int &type)
{
    if(type == MUSIC)
      {
        Mix_Music* pMusic = Mix_LoadMUS(music_filepath.c_str());

        if(pMusic == 0)
        {
            RD_ERROR( "Error loading file: \"%s\": %s\n", music_filepath.c_str(), Mix_GetError());
            return false;
        }

        music_sounds[id] = pMusic;
        return true;
      }
      else if(type == FX)
      {
        Mix_Chunk* pChunk = Mix_LoadWAV(music_filepath.c_str());
        if(pChunk == 0)
        {
            RD_ERROR( "Error loading file: \"%s\": %s\n", music_filepath.c_str(), Mix_GetError());
            return false;
        }

        fx_sounds[id] = pChunk;
        return true;
      }
      return false;
}

bool rd::SDLAudioManager::playMusic(const std::string &id, int loop)
{
    if (Mix_PlayMusic(music_sounds[id], loop) == -1)
    {
        RD_ERROR( "Error playing sound \"%s\"\n", id.c_str());
        return false;
    }

    return true;
}

bool rd::SDLAudioManager::playSound(const std::string &id, int loop)
{
    if( Mix_PlayChannel(-1, fx_sounds[id], loop) == -1 )
    {
        RD_ERROR( "Error playing sound \"%s\"\n", id.c_str());
        return false;
    }

    return true;
}

bool rd::SDLAudioManager::stopMusic()
{
    if ( Mix_PlayingMusic() )
        if(Mix_HaltMusic() == -1)
        {
            RD_ERROR( "Error stopping music\n");
            return false;
        }

    return true;
}

bool rd::SDLAudioManager::start()
{
    return true;
}

bool rd::SDLAudioManager::stop()
{
    Mix_CloseAudio();
    return true;
}

bool rd::SDLAudioManager::RegisterManager()
{
    if (uniqueInstance == NULL)
    {
        uniqueInstance = new SDLAudioManager();
    }

    return Register( uniqueInstance, id);
}

rd::SDLAudioManager::~SDLAudioManager()
{
    //-- Stop this manager
    this->stop();
    uniqueInstance = NULL;
}
