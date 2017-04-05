// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __RD_PROCESSOR_IMAGE_EVENT_LISTENER_HPP__
#define __RD_PROCESSOR_IMAGE_EVENT_LISTENER_HPP__

#include <math.h>  //-- Just for fabs to make it a bit failproof.

#include <stddef.h> //-- Just for NULL
#include <zbar.h>

#include "ImageManager.hpp"
#include "Macros.hpp"
#include "MentalMap.hpp"

namespace rd
{

/**
 * @brief ProcessorImageEventListener used for processing
 *
 * This object allows to access the received image and has a counter of
 * the incoming images received
 *
 */
class ProcessorImageEventListener : public ImageEventListener
{
    public:
        ProcessorImageEventListener();
        ~ProcessorImageEventListener();

        virtual bool onImageArrived( ImageManager * manager );


    private:
        bool isInteger(std::string s);
        Image received_image;

        int cameraWidth;
        int cameraHeight;
        bool cameraInitialized;
        unsigned char* rimage;

        zbar::ImageScanner scanner;

        MentalMap* mentalMap;
};

}  // namespace rd

#endif  // __RD_PROCESSOR_IMAGE_EVENT_LISTENER_HPP__