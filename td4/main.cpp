#include <iostream>

#include "Semaphore.h"
#include "Thread.h"
#include "Mutex.h"
#include "Fifo.h"




int main(int argc, char * argv[])
{
//    Thread thread;
    Mutex mutex;
    Semaphore semaphore;
    Fifo<int> fifo;
    
    std::cout << "Hello, world !\n";
    
    return 0;
}
