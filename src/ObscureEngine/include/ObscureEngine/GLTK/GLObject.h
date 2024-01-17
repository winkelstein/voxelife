#pragma once
#include <GL/glew.h>

namespace ObscureEngine
{
    namespace gltk
    {
        class glObject
        {
        private:
            bool isBinded = false;

        protected:
            GLuint handler;

        protected:
            inline bool _checkIsBinded() const { return this->isBinded; }
            void _bind() { this->isBinded = true; }
            void _unbind() { this->isBinded = false; }

        public:
            virtual void bind() = 0;
            virtual void unbind() = 0;
        };
    }
}