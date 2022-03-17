#ifndef TASK_H
#define TASK_H

#include <thread>
#include <functional>
#include <SFML/Graphics.hpp>

namespace ThreadTasks
{
	
	class Tasks 
	{
	private:

		int id = 0;

		bool taskIsCompleted = false;

		sf::Thread* thisTaskThread = nullptr;

		

	public:

		Tasks();

		template <typename T, typename U, class C>
		Tasks(std::function<T(C*, U)> _func, C* _classPtr, U _arg);

		~Tasks();

		void startTask();
		
		void join();
		
		void terminate();
		

		// 
		template <typename T, typename U, class C>
		void setFunc(std::function<T(C*, U)> f, C* _classPtr, U _arg)
		{
			if (thisTaskThread)
				delete thisTaskThread;

			thisTaskThread = new sf::Thread([&]
				{
					f(_classPtr, _arg);
					taskIsCompleted = true;
				});

			
		}
		template <typename T, class C>
		void setFunc(std::function<T(C*)> f, C* _classPtr)
		{
			if (thisTaskThread)
				delete thisTaskThread;

			thisTaskThread = new sf::Thread([&]
				{
					f(_classPtr);
					taskIsCompleted = true;
				});

		}

		template <typename T>
		void setFunc(const T& _lambda)
		{
			if (thisTaskThread)
				delete thisTaskThread;

			thisTaskThread = new sf::Thread([&]
				{
					_lambda();
					taskIsCompleted = true;
				});
		}

		bool isComplited() const { return taskIsCompleted; }

		int getID() const { return id; }

	private:


	};

}


#endif // ! TASK_H

