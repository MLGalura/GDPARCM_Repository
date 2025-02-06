#include "PoolWorkerThread.h"
#include "IWorkerAction.h"
#include "ThreadPool.h"

PoolWorkerThread::PoolWorkerThread(int id, IFinishedTask* task)
{
	this->id = id;
	this->finishedTask = task;
}

PoolWorkerThread::~PoolWorkerThread()
{
}

void PoolWorkerThread::run()
{
	this->action->onStartTask();
	this->finishedTask->onFinished(this->id);
}

void PoolWorkerThread::assignTask(IWorkerAction* action)
{
	this->action = action;
}

int PoolWorkerThread::getThreadID()
{
	return this->id;
}
