#ifndef OBSERVER_H
#define OBSERVER_H

#include <cstdint>
#include <assert.h>
#include <list>
#include <functional>

const std::uint8_t MAX_OBSERVERS = 32; 


struct Emitter
{
    using Callback = std::function<void(void)>;
    Callback callback;

    void connect(Callback callback)
    {
        this->callback = callback;
    }

    virtual ~Emitter(){}

    virtual void Emmit()
    {
        this->callback();
    }
};

struct Signal
{
private:
    std::list<Emitter*> observers;

public:

    void AddEmitter(Emitter* observer)
    {
        assert(this->observers.size() != MAX_OBSERVERS-1 && "Observer limit exceded");

        this->observers.push_back(observer);        
    }

    void RemoveEmitter(Emitter* observer)
    {
        assert(this->observers.size() != 0 && "Nothing to remove");
        this->observers.remove(observer);     
    }

    void Notify()
    {
        for(auto observer : this->observers)
        {
            observer->Emmit();
        }
    }
};

#endif //OBSERVER_H