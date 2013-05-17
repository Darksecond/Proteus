#pragma once

namespace stl
{
    class freelist
    {
        freelist* next;
    public:
        inline freelist();
        
        inline void* pop();
        inline void push(void* ptr);
    };
    
    inline freelist::freelist() : next(nullptr)
    {
    }
    
    inline void* freelist::pop()
    {
        if(next == nullptr)
            return nullptr;
        
        freelist* head = next;
        next = head->next;
        
        return head;
    }
    
    inline void freelist::push(void* ptr)
    {
        //TODO assert ptr not null
        
        freelist* head = static_cast<freelist*>(ptr);
        head->next = next;
        next = head;
    }
};