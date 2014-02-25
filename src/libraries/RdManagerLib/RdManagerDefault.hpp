// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __RD_MANAGER_DEFAULT_HPP__
#define __RD_MANAGER_DEFAULT_HPP__

#include "RdManagerBase.hpp"
#include <semaphore.h>
#include <vector>
#include <utility>
#include <pthread.h>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>


namespace rdlib{

/**
 * @ingroup RdManagerLib
 *
 * @brief Implements a default manager for Robot Devastation.
 */
class RdManagerDefault : public RdManagerBase {
    public:
        RdManagerDefault();

        virtual bool start();
        virtual bool quit();

        virtual bool shoot();

        static void * processImageThread( void * This);
        bool processImage();

        static bool toggleHeadTrackWrapper( void * This);
        bool toggleHeadTrack();
        bool trackHead( int index); //-- Index is the source image that is being processed

        void setProcessSemaphores(sem_t * processSemaphores);
        void setDisplaySemaphores(sem_t * displaySemaphores);

    protected:
        sem_t * processSemaphores;
        sem_t * displaySemaphores;
        pthread_t processImage_thread;
};

} //rdlib

#endif  // __RD_MANAGER_DEFAULT_HPP__

