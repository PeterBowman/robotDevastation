#ifndef _RD_MOCK_NETWORK_EVENT_LISTENER_HPP_
#define _RD_MOCK_NETWORK_EVENT_LISTENER_HPP_

#include "NetworkEventListener.hpp"

namespace rd {
/**
 * @brief Dummy NetworkEventListener used for testing
 *
 * The required pure virtual members are left with their function body empty.
 *
 * This mock object allows to access the received data and has a counter of
 * the incoming messages received
 *
 */

class MockNetworkEventListener : public NetworkEventListener
{
    public:
        MockNetworkEventListener();

        virtual bool onDataArrived(std::vector<Player> players);

        int getDataArrived();
        void resetDataArrived();

        std::vector<Player> getStoredPlayers();


    private:
        int data_arrived;
        std::vector<Player> stored_players;
};



}

#endif // _RD_MOCK_NETWORK_EVENT_LISTENER_HPP_
