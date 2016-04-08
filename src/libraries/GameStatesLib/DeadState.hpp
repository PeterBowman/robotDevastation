// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __DEAD_STATE_HPP__
#define __DEAD_STATE_HPP__

#include "State.hpp"
#include "StateDirector.hpp"
#include "RdUtils.hpp"
#include "Hub.hpp"
#include "RdYarpNetworkManager.hpp"
#include "DeadScreen.hpp"


namespace rd{

/**
* @ingroup GameStatesLib
*
* @brief Game Dead State
* Behavior:
*  - Waits for 10 seconds showing dead screen
*  - Then, it enables input:
*      - When user presses enter, respawns the robot and goes to game state again
*      - When user presses q, logout the game
*/
class DeadState : public State, public ManagerHub, public RdInputEventListener
{
public:
    //DeadState();
    DeadState(RdNetworkManager * networkManager, RdImageManager * imageManager,
              RdInputManager * inputManager, RdMentalMap * mentalMap,
              RdRobotManager * robotManager, AudioManager * audioManager);
    virtual ~DeadState();
    virtual bool setup();
    virtual bool loop();
    virtual bool cleanup();

    //! @brief Returns the internal variable value as condition evaluation result
    virtual int evaluateConditions();

    static const int RESPAWN_SELECTED;
    static const int EXIT_SELECTED;

    //-- RdInputEventListener interface:
    virtual bool onKeyDown(RdKey k);
    virtual bool onKeyUp(RdKey k);

protected:
    DeadState screen;
    int last_transition; //-- Stores the transition that triggered the cleanup
};
}
#endif // __DEAD_STATE_HPP__
