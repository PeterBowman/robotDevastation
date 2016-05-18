// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __RD_NETWORK_MANAGER_HPP__
#define __RD_NETWORK_MANAGER_HPP__

#include <map>

#include "RdUtils.hpp"
#include "RdPlayer.hpp"
#include "RdNetworkEventListener.hpp"
#include "RdMentalMapEventListener.hpp"

namespace rd{

/**
 * @ingroup rd_libraries
 *
 * \defgroup RdNetworkLib
 *
 * @brief The RdNetworkLib library contains everything related to the communications with the RobotDevastation network
 */

/**
 * @ingroup RdNetworkLib
 *
 * @brief Manages the communications between the user and the RobotDevastation network
 *
 * RdNetworkManager is a <a href="http://en.wikipedia.org/wiki/Singleton_pattern">singleton text</a> (only
 * one instance of this object can exist, that is is shared by all the users). To use this
 * class, we first get the reference to the RdNetworkManager with getNetworkManager() and then we
 * access the manager with that reference.
 *
 * When the program finishes, the RdNetworkManager can be deallocated using destroyNetworkManager().
 *
 * Network events are broadcasted to the registered <a href="http://en.wikipedia.org/wiki/Observer_pattern">listeners</a>,
 * along with the data relevant to the event triggered (i.e. data that just arrived)
 *
 */
class RdNetworkManager: public RdMentalMapEventListener
{
    public:
        //------------------------------ Construction & destruction ---------------------------------------------------//
        /**
         * @brief Get a reference to the RdNetworkManager
         * @return By default, if no id is specified, this will return a reference to the first
         * RdImageManager that it can find in the registry, or NULL if no RdNetworkManager was registered.
         */
       static rd::RdNetworkManager *getNetworkManager();

        /**
         * @brief Get a reference to the RdNetworkManager
         * @return The RdNetworkManager registered with the given id, NULL if the id is not found in
         * the registry.
         */
        static rd::RdNetworkManager *getNetworkManager(std::string id);

        //! @brief Deallocate all the registered RdNetworkManager
        static bool destroyNetworkManager();

        virtual ~RdNetworkManager();


        //------------------------------ Manager Startup & Halting ----------------------------------------------------//
        /**
         * @brief Start the network manager
         *
         * This function is supposed to be called after RdNetworkManager configuration.
         */
        virtual bool start() = 0;

        //! @brief Stop the network manager
        virtual bool stop() = 0;


        //------------------------------ Configuration & Listeners ----------------------------------------------------//
        //! @brief Adds a RdInputEventListener to the list of observers to be notified of events
        bool addNetworkEventListener( RdNetworkEventListener * listener );

        //! @brief Unregisters all the RdInputEventListener stored
        bool removeNetworkEventListeners();

        //! @brief Configures a parameter with a value
        virtual bool configure(std::string parameter, RdPlayer value);



        //-- Network API
        //--------------------------------------------------------------------------------------------
        //! @brief Communicate to the network that a player has been hit by the user
        virtual bool sendPlayerHit(RdPlayer player, int damage) = 0;

        //! @brief Log the user into the network
        virtual bool login() = 0;

        //! @brief Log the user out of the network
        virtual bool logout() = 0;

        //-- MentalMap listener API
        //-------------------------------------------------------------------------------------------
        //! @brief Implementation of RdMentalMapEventListener interface
        bool onTargetHit(rd::RdTarget target, rd::RdPlayer player, rd::RdWeapon weapon);


protected:
        /**
         * @brief This function allows subclasses to install their unique instances in the singleton register to be
         * selected later by the user
         */
        static bool Register(RdNetworkManager *manager, std::string id);

        //! @brief Observers registered to be notified of network events
        std::vector<RdNetworkEventListener *> listeners;


    private:
        //! \brief Stores the unique instance of the RdInputManager
        static RdNetworkManager * networkManagerInstance;

        //! \brief Stores the id of the current unique instance used
        static std::string currentId;

        //! \brief Stores all the RdImageManager that have been registered
        static std::map< std::string, RdNetworkManager * > networkManagerRegistry;


};

}

#endif //-- __RD_NETWORK_MANAGER_HPP__
