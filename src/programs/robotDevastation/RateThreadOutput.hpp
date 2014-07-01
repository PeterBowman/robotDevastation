// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __RATE_THREAD_OUTPUT_HPP__
#define __RATE_THREAD_OUTPUT_HPP__

#include <yarp/os/RFModule.h>
#include <yarp/os/Module.h>
#include <yarp/os/Network.h>
#include <yarp/os/Port.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/RateThread.h>

#include <yarp/sig/all.h>

#define DEFAULT_RATE_MS 20

namespace rd
{

class RateThreadOutput : public yarp::os::RateThread {
    private:
        //BufferedPort<ImageOf<PixelRgb> > *pInImg;
        //BufferedPort<ImageOf<PixelRgb> > *pOutImg;  // for testing
        //Port *pOutPort;
        //


    public:
        RateThreadOutput() : RateThread(DEFAULT_RATE_MS) {}

        //void setInImg(BufferedPort<ImageOf<PixelRgb> > * _pInImg);
        //void setOutImg(BufferedPort<ImageOf<PixelRgb> > * _pOutImg);
        //void setOutPort(Port *_pOutPort);
        void init(yarp::os::ResourceFinder &rf);
        void run();  // The periodical function
};

}  // namespace rd

#endif  // __RATE_THREAD_OUTPUT_HPP__

