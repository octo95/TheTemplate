#include "circular_buffer.h"

namespace Tmpl8
{
    CircularBuffer::CircularBuffer() :
        timer(3.0f),
        buf(std::vector<PlayerState>{}),
        head(0),
        tail(0)
    {
        buf.resize(BUFFER_SIZE);
    }

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

    PlayerState CircularBuffer::read() 
    {
        PlayerState item = buf[tail];
        incrementTail();
        return item;
    }

    void CircularBuffer::reset() 
    {
        head = 0;
        tail = 0;
        buf.clear();
        buf.resize(BUFFER_SIZE);
    }
}
