// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RdManagerDefault.hpp"

namespace rdlib{

/************************************************************************/

bool RdManagerDefault::shoot() {
    return rdRobotBasePtr->shoot();
}

/************************************************************************/

RdManagerDefault::RdManagerDefault() {

}

/************************************************************************/

RdManagerDefault::~RdManagerDefault() {
}

/************************************************************************/

} //rdlib
