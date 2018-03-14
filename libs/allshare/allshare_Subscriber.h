#pragma once

namespace allshare {

template <typename T>
struct Subscriber
{
    virtual ~Subscriber()
    {
        unsubscribe();
    }

    virtual void add(T * t) = 0;
    virtual void remove(T * t) {}
    void subscribe();
    void unsubscribe();
};

}
