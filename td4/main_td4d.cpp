/** main_td4d.cpp
 * Test for the Fifo class
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

#include "Semaphore.h"
#include "Thread.h"
#include "Mutex.h"
#include "Fifo.h"


class TaskGiver : public Thread
{
public:
    TaskGiver(Fifo<int> & fifo, int nbr, int id) : m_fifo(fifo), m_nbr(nbr), m_taskId(id) {};
    ~TaskGiver(){};
protected:
    virtual void run(void){
        for(int i = 0 ; i < m_nbr ; i++)
            m_fifo.push(i + m_taskId * m_nbr);
    };
private:
    Fifo<int> & m_fifo;
    int m_nbr;
    int m_taskId;
};

class TaskConsumer : public Thread
{
public:
    TaskConsumer(Fifo<int> & fifo, int nbr, std::vector<bool> & table, Mutex & mutex) :
        m_fifo(fifo), m_nbr(nbr), m_table(table), m_mutex(mutex) {};
    ~TaskConsumer(){};
protected:
    virtual void run(void){
        for(int i = 0 ; i < m_nbr ; i++)
        {
            int item = 0;
            item = m_fifo.pop();
            Mutex::Lock lock(m_mutex);
            if(m_table.at(item))
                std::cout << "Error : number " << item << " Had already been recovered.\n";
            m_table.at(item) = true;
        }
    };
private:
    Fifo<int> & m_fifo;
    int m_nbr;
    std::vector<bool> & m_table;
    Mutex & m_mutex;
};




int main(int argc, char * argv[])
{
    Fifo<int> fifo;
    std::vector<bool> table;    // Table to check if the number was poped
    Mutex mutex;                // Mutex to protect table access
    std::vector<Thread *> threadsGivers;
    std::vector<Thread *> threadsConsumers;
    int nbrGivers = 0;
    int nbrConsumers = 0;

    std::cout << "Starting test_semaphore.cpp\n\n";

    // Read the arguments
    if(argc != 3)
    {
        std::cout << "Argument error : was expecting 2 numbers.\n";
        return -1;
    }
    nbrGivers = std::stoi(argv[1]);
    nbrConsumers = std::stoi(argv[2]);

    // Create the tasks
    threadsGivers.resize(nbrGivers, nullptr);
    threadsConsumers.resize(nbrConsumers, nullptr);
    for(int i = 0 ; i < nbrGivers ; i++)
        threadsGivers[i] = new TaskGiver(fifo, nbrConsumers, i);
    for(int i = 0 ; i < nbrConsumers ; i++)
        threadsConsumers[i] = new TaskConsumer(fifo, nbrGivers, table, mutex);
    table.resize(nbrGivers * nbrConsumers, false);

    std::cout << "Starting test (" << nbrGivers * nbrConsumers << " iterations)...\n";

    // Start the tasks
    for(int i = 0 ; i < nbrGivers ; i++)
        threadsGivers[i]->start();
    for(int i = 0 ; i < nbrConsumers ; i++)
        threadsConsumers[i]->start();

    std::cout << "All thread started, waiting for them to finish ...\n";
    // Wait for the tasks to end
    for(int i = 0 ; i < nbrGivers ; i++)
        threadsGivers[i]->join();
    for(int i = 0 ; i < nbrConsumers ; i++)
        threadsConsumers[i]->join();
    
    // Check if every position has been filled
    std::cout << "Test done, checking ...\n";
    bool result = true;
    for(int i = 0 ; i < nbrGivers * nbrConsumers ; i++)
        if(!table[i])
        {
            std::cout << "Missing number " << i << ".\n";
            result = false;
        }
    std::cout << "Result : ";
    if(!result)
        std::cout << "failed.\n";
    else
        std::cout << "success.\n";

    for(int i = 0 ; i < nbrGivers ; i++)
        delete threadsGivers[i];
    for(int i = 0 ; i < nbrConsumers ; i++)
        delete threadsConsumers[i];

    std::cout << "\ntest_semaphore.cpp finished.\n\n";

    return 0;
}
