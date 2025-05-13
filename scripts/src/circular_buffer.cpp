#include "../include/circular_buffer.h"

namespace Tmpl8
{
    // +-------------------------------------------------------------------------------------------------------------------------+
    // The circular buffer is being used for the AI Copy.
    // The AI copies the player's position and angular acceleration from a desired previous state. 
    // To do so we use a circular buffer as it allows us to read and write in different locations. 
    // The tail will allow us to read the previous player's state and the head to write it on the AI to set its state later.
    // +-------------------------------------------------------------------------------------------------------------------------+

    // CircularBuffer implementation inspired by https://www.geeksforgeeks.org/implement-circular-buffer-using-std-vector-in-cpp/.

    CircularBuffer::CircularBuffer() :
        timer(0.0f),
        buf(std::vector<PlayerState>{}),
        head(0),
        tail(0)
    {
        buf.resize(BUFFER_SIZE);
    }

    // Increment the tail to let us later read. The position is the fixed size of the buffer - 1 since the size count starts from 1 and the index from 0.
    void CircularBuffer::incrementTail() 
    {
        if (tail == BUFFER_SIZE - 1)
        {
            tail = 0;
        }
        else 
        {
            tail++;
        }
    }

    // Following the same logic for the head, we increment it and it will allow us to add elements by writing them.
    void CircularBuffer::add(vec2& item, float angle) 
    {
        buf[head] = { item, angle };
        if (head == BUFFER_SIZE - 1) 
        {
            head = 0;
        }
        else 
        {
            head++;
        }

    }

    // Read the position and angle of the player (type PlayerState) by reading the current position of the tail.
    PlayerState CircularBuffer::read() 
    {
        PlayerState item = buf[tail];
        incrementTail();
        return item;
    }

    // Reset the circular buffer by setting back the head and tail to 0. 
    // Once the buffer is cleared we need to assign its fixed size again or else it's going to be 0 after a clear.
    void CircularBuffer::reset() 
    {
        head = 0;
        tail = 0;
        buf.clear();            
        buf.resize(BUFFER_SIZE);
    }
}
