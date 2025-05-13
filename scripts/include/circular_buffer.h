#pragma once
#include "template.h"
#include <cstdint>
#include <vector>

namespace Tmpl8
{
    // The CircularBuffer helps us gather past information from the player to pass it to the AI Copy.
    // We are interested in getting the previous position to follow the player and correct previous rotation for the draw.
    struct PlayerState {
        vec2 position;
        float rotation_acceleration = 0.0f;
    };

    class CircularBuffer {
    public:
        // Define a buffer that will be used to store the data, the tail to read it, the head 
        // to write it and a timer that determines the delay between the read and write.
        std::vector<PlayerState> buf;
        int tail;
        int head;
        float timer;

        CircularBuffer();

        // Functions to handle the circular buffer.
        void reset();
        void incrementTail();
        void add(vec2& item, float angle);
        PlayerState read();

    private:
        const size_t BUFFER_SIZE = 720; // Expecting a maximum size of 3 seconds * 240 frames for a fixed size of the buffer 
                                        // that will allow us to store all the previous state of the player for a given of time.
    };
}
