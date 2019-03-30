#ifndef __TD4_FIFO_H
#define __TD4_FIFO_H

#include <queue>
#include <exception>

#include "Mutex.h"


template<typename T>
class Fifo
{
public:
    Fifo(void){};
    ~Fifo(){};

    void push(T element)
    {
        Mutex::Lock lock(m_mutex);
        m_queue.push(element);
    };
    T pop(void){};
    T pop(double timeout_ms) throw EmptyException {};

private:
    Mutex           m_mutex;
    std::queue<T>   m_queue;

public:
    class EmptyException : public std::exception {
    public:
        EmptyException(){} noexcept;
        ~EmptyException(){};
        virtual const char* what() {
            return "Queue : empty !";
        } const noexcept;
    };
};

#endif  //__TD4_FIFO_H
