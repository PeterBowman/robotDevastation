#include "YarpStateDirector.hpp"


const int rd::YarpStateDirector::DEFAULT_RATE_MS = 100;

rd::YarpStateDirector::YarpStateDirector(rd::State *state) : StateDirector(state), RateThread(DEFAULT_RATE_MS)
{

}

bool rd::YarpStateDirector::Start()
{
    RD_DEBUG("Starting StateDirector for id %s\n", state->getStateId().c_str());
    active = true;
    state->setup();

    return yarp::os::RateThread::start();
}

bool rd::YarpStateDirector::Stop()
{
    RD_DEBUG("Stopping StateDirector for id %s\n", state->getStateId().c_str());

    active = false;

    yarp::os::RateThread::askToStop();
    yarp::os::RateThread::stop();

    state->cleanup();

    return true;
}

void rd::YarpStateDirector::run()
{
    //RD_DEBUG("Entering loop in StateDirector with id %s\n", state->getStateId().c_str());
    state->loop();
    int condition = state->evaluateConditions();

    if (nextStates.find(condition) != nextStates.end())
    {
        this->Stop();
        nextStates.find(condition)->second->Start();
    }

}
