// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __RD_NETWORK_EVENT_LISTENER_HPP__
#define __RD_NETWORK_EVENT_LISTENER_HPP__

#include <vector>
#include "RdPlayer.hpp"

namespace rd{

class RdNetworkEventListener
{
    public:
        virtual bool onDataArrived(RdPlayer player) = 0;
        virtual bool onDataArrived(std::vector<RdPlayer> players) = 0;
};

}

#endif //-- __RD_NETWORK_EVENT_LISTENER_HPP__