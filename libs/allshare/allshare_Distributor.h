#pragma once
#include <functional>
#include <unordered_map>
#include <QObject>
#include "allshare_Subscriber.h"

#define GCC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)

namespace allshare {

class Distributor
{
    typedef QObject Base;

    template<class T>
    using Func = std::function<void(T*)>;

public:
    static Distributor & instance()
    {
        static Distributor inst;
        return inst;
    }

    template <typename T>
    static void subscribe(Subscriber<T> * subscriber)
    {
        for (auto obj : objects())
        {
            T * t = dynamic_cast<T*>(obj);
            if (t)
                subscriber->add(t);
        }
        sender<T>()->add(subscriber);
    }

    template <typename T>
    static void unsubscribe(Subscriber<T> * subscriber)
    {
        sender<T>()->remove(subscriber);
    }

    template <typename T>
    static int subscribe(Func<T> && subscriber)
    {
        for (auto obj : objects())
        {
            T * t = dynamic_cast<T*>(obj);
            if (t)
                subscriber(t);
        }
        return funcSender<T>()->add(std::forward<Func<T>>(subscriber));
    }

    template <typename T>
    static void unsubscribe(int funcIndex)
    {
        funcSender<T>()->remove(funcIndex);
    }

    template <class T, class Tag = T>
    static T * get()
    {
        static T * t{nullptr};

        if (!t)
        {
            t = new T();
            objects().push_back(t);
            for (auto sender : senders())
            {
                sender->send(t);
            }
        }
        return t;
    }

private:
    struct ISender
    {
        virtual ~ISender() {}
        virtual void send(Base * object) const = 0;
    };

    template <class T>
    struct Sender : public ISender
    {
        void send(T * object) const
        {
            for (auto sub : subscribers)
            {
                sub->add(object);
            }
        }

        void send(Base * object) const override
        {
            T * t = dynamic_cast<T*>(object);
            if (t)
            {
                send(t);
            }
        }


        void add(Subscriber<T> * sub)
        {
            auto search = std::find(subscribers.begin(), subscribers.end(), sub);
            if (search == subscribers.end())
                subscribers.push_back(sub);
        }

        void remove(Subscriber<T> * sub)
        {
            auto search = std::find(subscribers.begin(), subscribers.end(), sub);
            if (search != subscribers.end())
                subscribers.erase(search);
        }

    private:
        std::vector<Subscriber<T>*> subscribers;
    };

    template <class T>
    struct FuncSender : public ISender
    {
        void send(T * object) const
        {
            for (auto foo : functions)
            {
                foo.second(object);
            }
        }

        void send(Base * object) const override
        {
            T * t = dynamic_cast<T*>(object);
            if (t)
            {
                send(t);
            }
        }

        int add(Func<T> && foo)
        {
            static int key = 0;
#if GCC_VERSION >= 40800
            functions.emplace(key, foo);
#else
            functions.insert(std::make_pair(key, foo));
#endif
            return key++;
        }

        void remove(int index)
        {
            functions.erase(index);
        }

    private:
        std::unordered_map<int,Func<T>> functions;
    };


    template<typename T>
    static inline Sender<T> * sender()
    {
        static Sender<T> * sndr{nullptr};
        if (!sndr)
        {
            sndr = new Sender<T>();
            senders().push_back(sndr);
        }
        return sndr;
    }

    template<typename T>
    static inline FuncSender<T> * funcSender()
    {
        static FuncSender<T> * sndr{nullptr};
        if (!sndr)
        {
            sndr = new FuncSender<T>();
            senders().push_back(sndr);
        }
        return sndr;
    }
    static inline std::vector<Base*> & objects()
    {
        static std::vector<Base*> objs;
        return objs;
    }

    static inline std::vector<ISender*> & senders()
    {
        static std::vector<ISender*> sndrs;
        return sndrs;
    }

    Distributor() = default;
};

template <class T>
void Subscriber<T>::subscribe()
{
    Distributor::subscribe<T>(this);
}

template <class T>
void Subscriber<T>::unsubscribe()
{
    Distributor::unsubscribe<T>(this);
}

}
