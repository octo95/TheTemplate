#pragma once
#include "template.h"
#include <cstdint> 
#include <vector>

namespace Tmpl8
{
    class CircularBuffer {
    public:
        std::vector<vec2> buf;
        uint64_t head;
        uint64_t tail;
        float timer;

        CircularBuffer();

        void reset();
        void incrementTail();

        void add(float deltaTime, vec2& item);
        vec2 read();
    private:
        const size_t BUFFER_SIZE = 720;
    };
}