#ifndef MODIFY_CLASSES_H
#define MODIFY_CLASSES_H

#include "SFML/Graphics.hpp"

namespace ModifyClasses
{
	using namespace sf;

	class MainWindow : public RenderWindow
	{
	private:

		Mutex* mutexForActive = nullptr;

		bool isBusy = false;

	public:
		MainWindow() : RenderWindow()
		{

		}
		MainWindow(VideoMode mode, const String& title, Uint32 style = Style::Default, const ContextSettings& settings = ContextSettings()) :
			RenderWindow(mode, title, style, settings)
		{
			mutexForActive = new Mutex();
		}

		~MainWindow()
		{
			if (mutexForActive)
				delete mutexForActive;
			mutexForActive = nullptr;
		}

		bool setActiveSafe(bool const& _active)
		{
			mutexForActive->lock();

			if (_active) // if u wona take the window..
			{
				if (isBusy)	// and if it already taked...
				{
					mutexForActive->unlock();
					return false;	// gtfo
				}
				
				// if it free ..
				isBusy = true;
				this->setActive(true); // take it
				mutexForActive->unlock();
				return true;
			}
			else
			{
				isBusy = false;
				this->setActive(_active);
				mutexForActive->unlock();
				return true;
			}

			mutexForActive->unlock();
			return true;
		}


	private:


	};


}



#endif // !MODIFY_CLASSES_H

