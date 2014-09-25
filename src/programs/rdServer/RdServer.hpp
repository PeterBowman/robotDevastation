// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __RD_SERVER_HPP__
#define __RD_SERVER_HPP__

#include <yarp/os/RFModule.h>
#include <yarp/os/RpcServer.h>

#include <map>

#include "RdUtils.hpp"
#include "RdRpcResponder.hpp"

#define DEFAULT_WATCHDOG    1.0       // [s]


namespace rd{

/**
 * @ingroup rdServer
 * @brief The main \ref rdServer program class.
 */
class RdServer : public yarp::os::RFModule
{

    public:
        /**
         * Run the program.
         *
         * @return true/false upon success/failure
         */
        bool configure(yarp::os::ResourceFinder &rf);

    protected:
        bool interruptModule();
        double getPeriod();
        bool updateModule();

        /** Watchdog period [s]. */
        double watchdog;

        int serverStatus;

        std::map <int, RdPlayer> players;

        yarp::os::RpcServer rpcServer;
        RdRpcResponder rdRpcResponder;
        yarp::os::Port rdBroadcast;
};

} //rd

#endif  // __RD_SERVER_HPP__

