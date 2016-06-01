#include <signal.h>
#include <fstream>
#include "../headers/includes.h"
#include "../headers/CommonUtils.h"

SnailColony* colony = nullptr;
Grass* grass = nullptr;
Map* map = nullptr;
StatusBar* statusBar = nullptr;

bool resizeEvent = false;

void resizeSignal(int signal)
{
	resizeEvent = true;
}

void resizeObjects()
{
	endwin();
	refresh();
	int lines = 0, columns = 0;
	int height = 0, width = 0;
	getmaxyx(stdscr, lines, columns);
	width = columns - 2;
	height = lines - 2 - CommonUtils::statusBarHeight;
	
	if(width >= 3 && height >= 3)
	{
		map->resize(width, height);
		statusBar->resize(width,
						  CommonUtils::statusBarHeight,
						  1,
						  height + 1);
		wclear(stdscr);
		wborder(stdscr, '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0');
		refresh();
	}
	resizeEvent = false;
}

void* keys(void* arg)
{
	while(*static_cast<bool*>(arg))
	{
		char c = getchar();
		switch(c)
		{
			case 'q':
				*static_cast<bool*>(arg) = false;
				break;
			case '+':
				colony->add();
				break;
			case '-':
				colony->remove();
				break;
			case ' ':
				grass->toggleRaining();
				break;
			case '*':
				grass->setGrowthChancePercentage(grass->getGrowthChancePercentage() + 1.0);
				break;
			case '/':
				grass->setGrowthChancePercentage(grass->getGrowthChancePercentage() - 1.0);
				break;
			default:
				break;
		}
	}
	return nullptr;
}

int main(int argc, char** argv)
{
	if(CommonUtils::initLibrary())
	{
		if(CommonUtils::initWindows(map, statusBar))
		{
			grass = new Grass(map->getHeight() - 2, map->getWidth() - 2);
			colony = new SnailColony();
			colony->setGrass(grass);
			map->setColony(colony);
			map->setGrass(grass);
			statusBar->setColony(colony);
			statusBar->setGrass(grass);

			map->getColony()->add();

			refresh();

			bool run = true;
			pthread_t keysThread;
			pthread_create(&keysThread, nullptr, keys, static_cast<void*>(&run));

			unsigned i = 0, j = 0;

			signal(SIGWINCH, resizeSignal);
			while(run)
			{
				if(resizeEvent)
					resizeObjects();

				++i;
				++j;
				if(i == 10)
				{
					map->growMap();
					i = 0;
				}
				usleep(100000);
				map->reprint();
				statusBar->refreshStatus();
			}
			signal(SIGWINCH, SIG_DFL);
		}

		if(nullptr != map)
		{
			delete map;
			map = nullptr;
		}

		if(nullptr != grass)
		{
			delete grass;
			grass = nullptr;
		}

		if(nullptr != colony)
		{
			delete colony;
			colony = nullptr;
		}

		if(nullptr != statusBar)
		{
			delete statusBar;
			statusBar = nullptr;
		}
	}
	endwin();
	return 0;
}
