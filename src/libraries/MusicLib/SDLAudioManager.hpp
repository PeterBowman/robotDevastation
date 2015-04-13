// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __SDL_AUDIO_MANAGER_HPP__
#define __SDL_AUDIO_MANAGER_HPP__

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <iostream>
#include <map>

#include "RdMacros.hpp"
#include "AudioManager.hpp"

namespace rd{

/**
 * @ingroup RdMusicLib
 *
 * @brief Music and sound effects manager using SDL libraries
 *
 */
class SDLAudioManager : public AudioManager
{
    public:
        //---------------- Audio-related Stuff ----------------------------------------------------------------------//
        /**
         * @brief Loads an audio file, assigning it a string as identifier
         * @param music_filepath Path to the file to be loaded
         * @param id String that will identify the audio loaded
         * @param type Can take a value of MUSIC or FX depending if the audio is to be loaded as game music or
         * sound effect
         * @return True if sound was loaded successfully, false otherwise
         */
        bool load( const std::string& music_filepath, const std::string& id, const int& type);

        //! @brief Plays a music/sound effect file previously loaded
        bool play(const std::string &id, int loop);

        /**
         * @brief Stops the music being played currently
         * @return False if the music could not be stopped
         */
        bool stopMusic();


        //---------------- Manager Stuff ----------------------------------------------------------------------//
        virtual bool start();
        virtual bool stop();

        /**
         * @brief Register this manager in the RdImageManager registry so that can be used
         *
         * It ensures that only one manager of this type is created (unique instance)
         */
        static bool RegisterManager();

        //! @brief Destructor. Used to reset the local static reference after destroying this manager
        ~SDLAudioManager();


        //! @brief String that identifies this manager
        static const std::string id;


    private:
        /**
         * @brief Constructor
         *
         * Constructor for this class is private, since the singleton can only be instantiated once,
         * and the instantiation is done at the getAudioManager() method
         */
        SDLAudioManager();

        //! \brief Stores the unique instance of the RdAudioManager
        static SDLAudioManager * uniqueInstance;

        //! \brief Dictionary for the sound effects
        std::map<std::string, Mix_Chunk*> fx_sounds;

        //! \brief Dictionary for the music tracks
        std::map<std::string, Mix_Music*> music_sounds;

};

}

#endif //-- __SDL_AUDIO_MANAGER_HPP__