#pragma once
#include "template.h"
#include <cstdint>
#include <vector>

namespace Tmpl8
{
    struct PlayerState {
        vec2 position;
        float rotation_acceleration = 0.0f;
    };

    class CircularBuffer {
    public:
        std::vector<PlayerState> buf;
        uint64_t head;
        uint64_t tail;
        float timer;

        CircularBuffer();

        void reset();
        void incrementTail();

        void add(vec2& item, float angle);
        PlayerState read();
    private:
        const size_t BUFFER_SIZE = 720; // Expecting a maximum size of 3 seconds * 240 frames for a fixed size of the buffer 
                                        // that will allow us to store all the previous state of the player for a given of time.
    };
}
