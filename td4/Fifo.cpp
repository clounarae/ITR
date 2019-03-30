#include "Fifo.h"



Fifo::Fifo(void)
{
    
}

Fifo::~Fifo()
{
    
}


void Fifo::push(T element)
{
    Mutex::Lock lock(m_mutex);
    m_queue.push(element);
}

T Fifo::pop(void)
{
    
}

T Fifo::pop(double timeout_ms) throw EmptyException
{
    
}
