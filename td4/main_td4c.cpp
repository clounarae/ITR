/** main_td4c.cpp
 * Test for the Semaphore class, as follow:
 * - tasks that give tokens
 * - tasks that consume tokens
 * -> check that every token has been consummed.
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
	TaskGiver(Semaphore & semaphore, int nbr) : m_semaphore(semaphore), m_nbr(nbr) {};
	virtual ~TaskGiver(){};
protected:
	virtual void run(void){
		for(int i = 0 ; i < m_nbr ; i++)
			m_semaphore.give();
	};
private:
	Semaphore & m_semaphore;
	int m_nbr;
};

class TaskConsumer : public Thread
{
public:
	TaskConsumer(Semaphore & semaphore, int nbr) : m_semaphore(semaphore), m_nbr(nbr) {};
	virtual ~TaskConsumer(){};
protected:
	virtual void run(void){
		for(int i = 0 ; i < m_nbr ; i++)
			m_semaphore.take();
	};
private:
	Semaphore & m_semaphore;
	int m_nbr;
};




int main(int argc, char * argv[])
{
	Semaphore semaphore;
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
		threadsGivers[i] = new TaskGiver(semaphore, nbrConsumers);
	for(int i = 0 ; i < nbrConsumers ; i++)
		threadsConsumers[i] = new TaskConsumer(semaphore, nbrGivers);

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
	
	// Check if there is a token left
	std::cout << "Test done.\n";
	std::cout << "Result : ";
	if(semaphore.take(0.))
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
