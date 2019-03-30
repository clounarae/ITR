<<<<<<< Updated upstream
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
=======
#include "Thread.h"

void incr(unsigned int nLoops, double* pCounter)
{
    while(nLoops--)
        *pCounter += 1.;
}

void exB(int argc, char* argv[])
{
    double counter = 0.;
    struct timespec debut, fin, duree ;
    
    clock_gettime(CLOCK_REALTIME, &debut);
    incr(std::atoi(argv[1]), &counter);
    clock_gettime(CLOCK_REALTIME, &fin);
    duree = fin - debut;
    std::cout << "Durée d'execution: " << timespec_to_ms(duree) << ".\n";
>>>>>>> Stashed changes
}
