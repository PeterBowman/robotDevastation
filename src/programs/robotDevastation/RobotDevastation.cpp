// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RobotDevastation.hpp"

bool rd::RobotDevastation::configure(yarp::os::ResourceFinder &rf)
{

    //printf("--------------------------------------------------------------\n");
    if (rf.check("help")) {
        printf("RobotDevastation options:\n");
        printf("\t--help (this help)\t--from [file.ini]\t--context [path]\n");
        // Do not exit: let last layer exit so we get help from the complete chain.
    }
    printf("RobotDevastation using no additional special options.\n");

    rateThreadOutput.setInImg(&inImg);
    
    rateThreadOutput.init(rf);

    //-----------------OPEN LOCAL PORTS------------//
    inImg.open("/img:i");
    
    return true;
}

double rd::RobotDevastation::getPeriod()
{
    return 2.0;  // Fixed, in seconds, the slow thread that calls updateModule below
}

bool rd::RobotDevastation::updateModule()
{
    printf("RobotDevastation alive...\n");
    return true;
}

bool rd::RobotDevastation::interruptModule() {
    printf("RobotDevastation closing...\n");
    inImg.interrupt();
    inImg.close();
    return true;
}

