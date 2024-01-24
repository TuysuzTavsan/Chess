#ifndef PTR_H
#define PTR_H

class Ref{
private:
    unsigned int count; //Reference count

public:    

    Ref() 
    : count(0)
    {}

    ~Ref()
    {}

    void AddRef()
    {
        //Increment the reference count
        this->count++;
    }

    int Release()    
    {
        //Decrement the reference count and return
        return --this->count;
    }
};

template <typename T>
class SoftPtr
{
private:
    T* pData; //Pointer to data
    Ref * reference; //Reference count

public:

    SoftPtr()
    : pData(nullptr), reference(0)
    {
        //Create new reference and increment by 1.
        this->reference = new Ref();
        this->reference->AddRef();
    }

    SoftPtr(T* pValue)
    : pData(pValue), reference(0)
    {
        //Create new reference and increment by 1.
        this->reference = new Ref();
        this->reference->AddRef();
    }
    
    //Copy constructor
    SoftPtr(const SoftPtr<T>& sp)
    : pData(sp.pData), reference(sp.reference)
    {
        //Copy and increment the reference
        this->reference->AddRef();
    }

    //Destructor
    ~SoftPtr()
    {
        //Decrement the reference count by 1.
        //If reference count == 0 delete data.
        if(this->reference->Release() == 0)
        {
            delete this->pData;
            delete this->reference;
        }
    }

    T& operator* ()
    {
        return *this->pData;
    }

    T* operator-> ()
    {
        return this->pData;
    }

    //Assignment operator overload
    SoftPtr<T>& operator = (const SoftPtr<T>& sp)
    {
        if (this != &sp) //Avoid self assigment
        {
            //Decrement the old reference count and delete old data if 0
            if(this->reference->Release() == 0)
            {
                delete this->pData;
                delete this->reference;
            }

            //Copy and increment by 1.
            this->pData = sp.pData;
            this->reference =  sp.reference;
            this->reference->AddRef();
        }
        return *this;
    };

    T* getP()
    {
        return this->pData;
    }

    T& getVal()
    {
        return *this->pData;
    }

};

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ HARD PTR @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@q


template <class T>
class HardPtr
{
    T* ptr; //Actual pointer

public:

    //Constructor
    explicit HardPtr(T* p = nullptr) : ptr(p) {}

    //Destructor
    ~HardPtr()
    {
        delete this->ptr;
    }

    //Copy constructor is prohibited.
    HardPtr (const HardPtr&) = delete;

    //Assignment operator overload
    HardPtr<T>& operator=(const HardPtr<T>& other)
    {
        if (this != other)
        {
            this->ptr = std::move(other.ptr);
            other.ptr = nullptr;
        }
        
        return *this;
    }

    //Move constructor
    HardPtr (HardPtr&& other) noexcept : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    //Move assignment operator
    HardPtr& operator=(HardPtr&& other) noexcept
    {
        if (this != &other)
        {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    //Dereference operator overload.
    T& operator*()
    {
        return *this->ptr;
    }

    //Arrow operator overload.
    T* operator->()
    {
        return this->ptr;
    }

    //Bool operator
    explicit operator bool() const noexcept
    {
        return this->ptr != nullptr;
    }

    T* getP()
    {
        return this->ptr;
    }

};

template<class T>
class HardPtr<T[]>
{
    T* ptr; //Actual pointer

public:

    //Constructor
    explicit HardPtr(T* p = nullptr) : ptr(p) {}

    //Destructor
    ~HardPtr()
    {
        delete[] this->ptr;
    }

    //Copy constructor is prohibited.
    HardPtr (const HardPtr&) = delete;

    //Assignment operator overload
    HardPtr<T[]>& operator=(const HardPtr<T[]>& other)
    {
        if (this != other)
        {
            this->ptr = std::move(other.ptr);
            other.ptr = nullptr;
        }
        
        return *this;
    }

    //Move constructor
    HardPtr (HardPtr&& other) noexcept : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    //Move assignment operator
    HardPtr& operator=(HardPtr&& other) noexcept
    {
        if (this != &other)
        {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    //Dereference operator overload.
    T& operator*()
    {
        return *this->ptr;
    }

    //Arrow operator overload.
    T* operator->()
    {
        return this->ptr;
    }

    //Bool operator
    explicit operator bool() const noexcept
    {
        return this->ptr != nullptr;
    }

    T* getP()
    {
        return this->ptr;
    }

};

#endif //PTR_H