#include "circular_buffer.h"

namespace Tmpl8
{
    CircularBuffer::CircularBuffer() :
        timer(3.0f),
        buf(std::vector<PlayerState>{}),
        head(0),
        tail(0)
    {
        buf.resize(720);
    }

    void CircularBuffer::incrementTail() {
        tail = (tail == 720 - 1) ? 0 : tail + 1;
    }

    void CircularBuffer::add(vec2& item, float angle) {
        buf[head] = { item, angle };
        head = (head == 720 - 1) ? 0 : head + 1;
    }

    PlayerState CircularBuffer::read() {
        PlayerState item = buf[tail];
        incrementTail();
        return item;
    }

    void CircularBuffer::reset() {
        head = 0;
        tail = 0;
        buf.clear();
        buf.resize(720);
    }
}
