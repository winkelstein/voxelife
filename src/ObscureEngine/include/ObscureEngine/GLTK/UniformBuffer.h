#pragma once
#include "GLObject.h"

namespace ObscureEngine
{
    namespace gltk
    {
        template <typename _Ty>
        class UniformBuffer : public glObject
        {
        public:
            UniformBuffer();
            ~UniformBuffer();

        public:
            void data(const _Ty *data);

            void bind_base(const unsigned int base) const;

        public:
            void bind() override;
            void unbind() override;
        };
    }
}

template <typename _Ty>
inline ObscureEngine::gltk::UniformBuffer<_Ty>::UniformBuffer()
{
    glGenBuffers(1, &this->handler);
    glBindBuffer(GL_UNIFORM_BUFFER, this->handler);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(_Ty), nullptr, GL_DYNAMIC_DRAW);
}

template <typename _Ty>
inline ObscureEngine::gltk::UniformBuffer<_Ty>::~UniformBuffer()
{
    glDeleteBuffers(1, &this->handler);
}

template <typename _Ty>
inline void ObscureEngine::gltk::UniformBuffer<_Ty>::data(const _Ty *data)
{
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(_Ty), data);
}

template <typename _Ty>
inline void ObscureEngine::gltk::UniformBuffer<_Ty>::bind_base(const unsigned int base) const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, base, this->handler);
}

template <typename _Ty>
inline void ObscureEngine::gltk::UniformBuffer<_Ty>::bind()
{
    if (!this->_check_is_binded())
    {
        this->_bind();
        glBindBuffer(GL_UNIFORM_BUFFER, this->handler);
    }
}

template <typename _Ty>
inline void ObscureEngine::gltk::UniformBuffer<_Ty>::unbind()
{
    if (this->_check_is_binded())
    {
        this->_unbind();
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
}