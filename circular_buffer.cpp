#include "circular_buffer.h"

namespace Tmpl8
{
    CircularBuffer::CircularBuffer() :
        timer(3.0f),
        buf(std::vector<vec2>{}),
        head(0),
        tail(0)
    {
        buf.resize(720);
    }

    void CircularBuffer::incrementTail() {
        tail = (tail == 720 - 1) ? 0 : tail + 1;
    }

    void CircularBuffer::add(float deltaTime, vec2& item) {
        buf[head] = item;
        head = (head == 720 - 1) ? 0 : head + 1;
    }

    vec2 CircularBuffer::read() {
        vec2 item = buf[tail];
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