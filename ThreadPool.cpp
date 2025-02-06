#include "ThreadPool.h"
#include "PoolWorkerThread.h"

ThreadPool::ThreadPool(String name, int numWorkers)
{
	this->name = name;
	this->numWorkers = numWorkers;

	for (int i = 0; i < this->numWorkers; i++) {
		this->inactiveThreads.push(new PoolWorkerThread(i, this));
	}
}

ThreadPool::~ThreadPool()
{
	this->stopScheduler();
	this->activeThreads.clear();
	while (this->inactiveThreads.empty() == false) {
		this->inactiveThreads.pop();
	}
}

void ThreadPool::startScheduler()
{
	this->running = true;
	this->start();
}

void ThreadPool::stopScheduler()
{
	this->running = false;
}

void ThreadPool::scheduleTask(IWorkerAction* action)
{
	this->pendingActions.push(action);
}

void ThreadPool::run()
{
	while (this->running) {
		if (this->pendingActions.empty() == false) {
			if (this->inactiveThreads.empty() == false) {
				//Schedule Task
				PoolWorkerThread* workerThread = this->inactiveThreads.front();
				this->inactiveThreads.pop();
				this->activeThreads[workerThread->getThreadID()] = workerThread;

				workerThread->assignTask(this->pendingActions.front());
				workerThread->start();
				this->pendingActions.pop();

				std::cout << "worker thread #" << workerThread->getThreadID() << " was assigned a task." << std::endl;
			}

			else
				std::cout << "No More Available Worker Threads" << std::endl;
		}

		else 
			std::cout << "No Actions Scheduled" << std::endl;
	}
}

void ThreadPool::onFinished(int threadID)
{
	if (this->activeThreads[threadID] != nullptr) {
		delete this->activeThreads[threadID];
		this->activeThreads.erase(threadID);

		this->inactiveThreads.push(new PoolWorkerThread(threadID, this));
	}
}
