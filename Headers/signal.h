#ifndef SIGNAL_H
#define SIGNAL_H

#include <cstdint>
#include <assert.h>
#include <list>
#include <functional>
#include <memory>

const std::uint8_t MAX_OBSERVERS = 32; 


template<typename returnT, class... Args>
struct Connection
{
    typedef std::function<returnT(Args...)> Callback;

    Connection(Callback callback)
    : callback(callback), isConnected(true)
    {}

    void operator()(Args... args)
    {
        if(isConnected && callback)
        {
            callback(args...);
        }
    }

    bool connected()
    {
        return isConnected;
    }

    void disconnect()
    {
        isConnected = false;
        callback = nullptr;
    }

    Callback callback;
    bool isConnected;
};


template<typename returnT, typename... Args>
struct Signal
{
    typedef std::function<returnT(Args...)> Callback;
    typedef Connection<returnT, Args...> _Connection;

    void Connect(Callback callback)
    {
        observers.push_back(std::shared_ptr<_Connection>(new _Connection(callback)));
    }

    void Disconnect(Callback callback)
    {
        //observers.erase(callback);
        //TODO implement erasing mechanism.
    }

    void Emmit(Args... args)
    {
        for(auto& observer : observers)
        {
            observer.get()->callback(args...);
        }
    }

private:
    std::list<std::shared_ptr<_Connection>> observers;

};



/* struct Observer
{
    using Callback = std::function<void(void)>;
    Callback callback;

    void connect(Callback callback)
    {
        this->callback = callback;
    }

    virtual ~Observer(){}

    virtual void Observe()
    {
        this->callback();
    }
};

struct Signal
{
private:
    std::list<std::shared_ptr<Observer>> observers;

public:

    void Connect(std::shared_ptr<Observer> observer)
    {
        assert(this->observers.size() != MAX_OBSERVERS-1 && "Observer limit exceded");

        this->observers.push_back(observer);        
    }

    void Disconnect(std::shared_ptr<Observer> observer)
    {
        assert(this->observers.size() != 0 && "Nothing to remove");
        this->observers.remove(observer);     
    }

    void Notify()
    {
        for(auto observer : this->observers)
        {
            observer->Observe();
        }
    }
}; */



#endif //OBSERVER_H