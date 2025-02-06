#pragma once
#include "IETThread.h"

class IWorkerAction;
class IFinishedTask;

class PoolWorkerThread : public IETThread

{
public:
	PoolWorkerThread(int id, IFinishedTask* task);
	~PoolWorkerThread();

private:
	void run() override;

public:
	void assignTask(IWorkerAction* action);
	int getThreadID();

private:
	int id = 0;
	IWorkerAction* action;
	IFinishedTask* finishedTask;
};

