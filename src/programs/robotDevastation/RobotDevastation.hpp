// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __ROBOT_DEVASTATION_HPP__
#define __ROBOT_DEVASTATION_HPP__

#include <yarp/os/RFModule.h>

#include "RdUtils.hpp"
#include "SDLAudioManager.hpp" //-- Should be AudioManager.hpp
#include "RdMentalMap.hpp"
#include "RdInputManager.hpp"
#include "RdSDLInputManager.hpp"
#include "RdInputEventListener.hpp"
#include "RdYarpNetworkManager.hpp"
#include "RdRobotManager.hpp"
#include "RdYarpRobotManager.hpp"
#include "RdMockupRobotManager.hpp"
#include "StateMachine.hpp"
#include "RdImageManager.hpp"
#include "RdYarpImageManager.hpp"
#include "RdMockupImageManager.hpp"
#include "RdProcessorImageEventListener.hpp"

//-- Game FSM
#include "StateMachine.hpp"
#include "StateMachineBuilder.hpp"
#include "InitState.hpp"
#include "GameState.hpp"
#include "DeadState.hpp"

namespace rd
{

/**
 * @ingroup robotDevastation
 * @brief The parent Robot Devastation class of the \ref robotDevastation program.
 */
class RobotDevastation : public yarp::os::RFModule
{
    public:
        /** Called on initialization. */
        virtual bool configure(yarp::os::ResourceFinder &rf);

    private:
        FiniteStateMachine * gameFSM;

        RdInputManager *  inputManager;
        AudioManager * audioManager;
        RdMentalMap * mentalMap;
        RdNetworkManager * networkManager;
        RdRobotManager * robotManager;
        FiniteStateMachine * stateMachine;
        RdImageManager * imageManager;

        bool interruptModule();
        double getPeriod();
        bool updateModule();

        bool initSound(yarp::os::ResourceFinder &rf);
        FiniteStateMachine* initGameFSM();
        bool cleanup();
};

}  // namespace rd

#endif  // __ROBOT_DEVASTATION_HPP__

