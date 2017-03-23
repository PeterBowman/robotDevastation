// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __MOCK_INPUT_EVENT_LISTENER_HPP__
#define __MOCK_INPUT_EVENT_LISTENER_HPP__

#include "InputEventListener.hpp"

namespace rd{

/**
 * @ingroup InputLib
 *
 * @brief Mock object that receives and stores key presses, mainly for testing purposes
 */
class MockInputEventListener : public InputEventListener
{
    public:
        MockInputEventListener();

        virtual bool onKeyDown( const Key & k );
        virtual bool onKeyUp( const Key & k );
        virtual bool onWindowEvent( const WindowEvent & event );

        int getNumKeyDownPresses();
        int getNumKeyUpPresses();
        int getNumWindowEvents();

        bool clear();

        std::vector<Key> getStoredKeyUpPresses();
        std::vector<Key> getStoredKeyDownPresses();
        std::vector<WindowEvent> getStoredWindowEvents();

    private:
        int num_keydown_presses;
        std::vector<Key> stored_keydown_presses;

        int num_keyup_presses;
        std::vector<Key> stored_keyup_presses;

        int num_window_events;
        std::vector<WindowEvent> stored_window_events;

};
}
#endif // __MOCK_INPUT_EVENT_LISTENER_HPP__
