#pragma once
#include "Core.h"
#include "Window.h"

namespace ObscureEngine
{
    namespace WS
    {
        class Event
        {
        public:
            friend class Window;

        public:
            enum class EventType
            {
                // Mouse events
                LeftMouseButtonPressed,
                LeftMouseButtonReleased,
                RightMouseButtonPressed,
                RightMouseButtonReleased,
                MiddleMouseButtonPressed,
                MiddleMouseButtonReleased,
                WheelMouseScrolled,
                MouseMoved,

                // Window events
                WindowResized,
                WindowClosed,
                WindowCreated,

                // Keyboard events
                KeyPressed,
                KeyReleased
            };

        private:
            EventType m_type;
            /*Window *m_window;*/

        public:
            /*inline EventType type() const { return; }
            inline char symbol() const { return; }
            inline uint32_t key() const { return; }
            inline uint8_t wheel() const { return; }
            inline Size window_size() const { return; }
            inline Window *window() const { return this->m_window; }*/
        };
    }
}