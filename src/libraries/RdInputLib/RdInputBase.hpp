// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __RD_INPUT_BASE_HPP__
#define __RD_INPUT_BASE_HPP__

#include <iostream>
#include "RdManagerBase.hpp"

/**
 * @ingroup rd_libraries
 *
 * \defgroup RdInputLib
 *
 * @brief The RdInputLib library contains the \ref RdInputBase class and some inherited implementations.
 */

namespace rdlib{

class RdManagerBase;
class RdRobotBase;

/**
 * @ingroup RdInputLib
 *
 * @brief An abstract base class for Robot Devastation inputs (keyboard, xpad...).
 *
 */
class RdInputBase {
    public:
        /** A quit rutine.
         * @return true if the object was quit successfully.
         */
        virtual bool quit() = 0;

        void setRdManagerBasePtr(RdManagerBase* rdManagerBasePtr ) {
            this->rdManagerBasePtr = rdManagerBasePtr;
        }

    protected:
        RdManagerBase* rdManagerBasePtr;
};

} //rdlib

#endif  // __RD_INPUT_BASE_HPP__

