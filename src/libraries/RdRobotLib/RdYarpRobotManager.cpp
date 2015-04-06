// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RdYarpRobotManager.hpp"

namespace rd{

bool RdYarpRobotManager::moveForward(int velocity) {
    double velocities[] = {2000,1000};
    vel->velocityMove(velocities);
    return true;
}

bool RdYarpRobotManager::moveBackwards(int velocity) {
    double velocities[] = {1000,2000};
    vel->velocityMove(velocities);
    return true;
}

bool RdYarpRobotManager::turnLeft(int velocity) {
    double velocities[] = {1000,1000};
    vel->velocityMove(velocities);
    return true;
}

bool RdYarpRobotManager::turnRight(int velocity) {
    double velocities[] = {2000,2000};
    vel->velocityMove(velocities);
    return true;
}

bool RdYarpRobotManager::stopMovement() {
    vel->stop();
    return true;
}

bool RdYarpRobotManager::tiltUp(int velocity) {
    return true;
}

bool RdYarpRobotManager::tiltDown(int velocity) {
    return true;
}

bool RdYarpRobotManager::panLeft(int velocity) {
    return true;
}

bool RdYarpRobotManager::panRight(int velocity) {
    return true;
}
        
bool RdYarpRobotManager::connect()  {

    std::string line("(on /");
    line += robotName;
    line += ") (as launcher) (cmd \"sudo launchRd1Yarp --device pwmbot --name /";
    line += robotName;
    line += " --gpios 17 27\")";
    yarp::os::Property yarpRunOptions;
    yarpRunOptions.fromString(line);
    int ret = yarp::os::Run::client(yarpRunOptions);
    if (ret != 0)
    {
        RD_ERROR("Could not start robot launch on robot side.\n");
        return false;
    }
    RD_SUCCESS("Started robot launch on robot side.\n");

    std::string local_s("/robotDevastation/");
    local_s += robotName;

    std::string remote_s("/");
    remote_s += robotName;

    yarp::os::Property robotOptions;
    robotOptions.put("device","remote_controlboard");
    robotOptions.put("local", local_s );
    robotOptions.put("remote", remote_s );

    int tries = 0;
    while(tries++ < 10)
    {
        if( !! robotDevice.isValid() )
            break;
        RD_DEBUG("Wait to connect to remote robot, try %d...\n",tries);
        yarp::os::Time::delay(0.5);
        robotDevice.open(robotOptions);
    }

    if (tries == 11)
    {
        RD_ERROR("Timeout on connect to remote robot!\n");
        return false;
    }

    RD_SUCCESS("Connected to remote robot.\n");

    if(! robotDevice.view(vel) )
    {
        RD_ERROR("Could not aquire robot motor velocity interface.\n");
        return false;
    }
    RD_SUCCESS("Acquired robot motor velocity interface.\n");

    return true;
}

bool RdYarpRobotManager::disconnect()  {
    robotDevice.close();
    return true;
}

bool RdYarpRobotManager::test()  {
    return true;
}

bool RdYarpRobotManager::ping()  {
    return true;
}

void RdYarpRobotManager::onDestroy(){
    return;
}

} //rd
