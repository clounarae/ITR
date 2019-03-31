#ifndef __TD4_FIFO_H
#define __TD4_FIFO_H

#include <queue>
#include <exception>

#include "Mutex.h"


template<typename T>
class Fifo
{
public:
    class EmptyException : public std::exception {
    public:
        EmptyException() noexcept {};
        ~EmptyException(){};
        virtual const char* what() const noexcept{
            return "Queue : empty !";
        };
    };

public:
    Fifo(void){};
    ~Fifo(){};

    void push(T element)
    {
        Mutex::Lock lock(m_mutex);
        m_queue.push(element);
    };
    T pop(void)
    {
        Mutex::Lock lock(m_mutex);
        while(m_queue.empty())
            lock.wait();
        T ret = m_queue.front();
        m_queue.pop();
        return ret;
    };
    T pop(double timeout_ms) throw(EmptyException)
    {
        Mutex::Lock lock(m_mutex);
        while(m_queue.empty())
            if(!lock.wait(0.))
                throw EmptyException();
        T ret = m_queue.front();
        m_queue.pop();
        return ret;
    };

private:
    Mutex           m_mutex;
    std::queue<T>   m_queue;

};

#endif  //__TD4_FIFO_H
