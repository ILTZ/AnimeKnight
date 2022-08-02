#include "Tasks.h"

//

using namespace ThreadTasks;

Tasks::Tasks()
{

}

template <typename T, typename U, class C>
Tasks::Tasks(std::function<T(C*, U)> _func, C* _classPtr, U _arg)
{
	setFunc(_func, _classPtr, _arg);
}



Tasks::~Tasks()
{
	if (thisTaskThread)
	{
		delete thisTaskThread;
	}
}


void Tasks::startTask()
{
	if (thisTaskThread)
	{
		thisTaskThread->launch();
	}
}

void Tasks::join()
{
	if (thisTaskThread)
	{
		thisTaskThread->wait();
	}
}

void Tasks::terminate()
{
	if (thisTaskThread)
	{
		thisTaskThread->terminate();
	}
}