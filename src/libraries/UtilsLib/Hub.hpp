
// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __MANAGER_HUB_HPP__
#define __MANAGER_HUB_HPP__

#include "ImageManager.hpp"
#include "InputManager.hpp"
#include "Key.hpp"
#include "MentalMap.hpp"
#include "Weapon.hpp"
#include "NetworkManager.hpp"
#include "RobotManager.hpp"
#include "AudioManager.hpp"
#include "ScreenManager.hpp"

namespace rd{

/**
 * @ingroup Utils
 *
 * @brief A classs to interface all the robot devastation managers
 *
 */
class ManagerHub
{
    public:
    ManagerHub();

    ManagerHub(NetworkManager * networkManager, ImageManager * imageManager,
               InputManager * inputManager, MentalMap * mentalMap,
               RobotManager * robotManager, AudioManager * audioManager,
               ScreenManager * screenManager);

        bool setNetworkManager(NetworkManager * networkManager);
        bool setImageManager(ImageManager * imageManager);
        bool setInputManager(InputManager * inputManager);
        bool setMentalMap(MentalMap * mentalMap);
        bool setRobotManager(RobotManager * robotManager);
        bool setAudioManager(AudioManager * audioManager);
        bool setScreenManager(ScreenManager * screenManager);

   protected:
        //-- Pointers to everything important in the game:
        NetworkManager * networkManager;
        ImageManager * imageManager;
        InputManager * inputManager;
        MentalMap * mentalMap;
        RobotManager * robotManager;
        AudioManager * audioManager;
        ScreenManager * screenManager;
};





}

#endif //-- __MANAGER_HUB_HPP__
