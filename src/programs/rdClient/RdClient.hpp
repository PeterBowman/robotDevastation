// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __ROBOT_DEVASTATION_HPP__
#define __ROBOT_DEVASTATION_HPP__

#include <yarp/os/Network.h>
#include <yarp/os/RFModule.h>

#include "RdInputBase.hpp"

#include "ExecutionThread.hpp"

#define DEFAULT_WATCHDOG    5       // [s]

namespace rdclient{

/**
 * @ingroup rdClient
 * @brief The main \ref rdClient program class, implemented as a slow watchdog class that also launches an \ref ExecutionThread.
 */
class RdClient : public yarp::os::RFModule {

    public:
        /**
         * Constructor of this slow watchdog thread.
         */
        RdClient();

        /**
         * Configure the module, pass a ResourceFinder object to the module.
         *
         * @param rf a previously initialized ResourceFinder
         * @return true/false upon success/failure
         */
        virtual bool configure(yarp::os::ResourceFinder &rf);

    protected:

        /**
         * When your module wants to stop, return false.  The module's actual
         * work could be done during this call, or it could just check the
         * state of a thread running in the background.
         *
         * @return true if module should continue
        */
        virtual bool updateModule();

        /** Closing rutines. */
        virtual bool interruptModule();
        
        /** Tell YARP the period of this slow watchdog thread. */
        virtual double getPeriod();


        /** Will be returned through getPeriod() [s]. */
        double watchdog;

        /** An instance of the main periodical fast thread. */
        ExecutionThread executionThread;

        /** Input */
        rdlib::RdInputBase* rdInputPtr;

        /** Screen */
        //RdScreen rdScreen;

        /** Robot */
        //RdRobot rdRobot;
        
};

} //rdclient

#endif  // __ROBOT_DEVASTATION_HPP__

