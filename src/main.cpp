#include "../headers/includes.h"
#include "../headers/CommonUtils.h"
#include "../headers/SnailColony.h"

SnailColony* colony = nullptr;
Grass* grass = nullptr;

void* keys(void* arg)
{
	while(true)
	{
		char c = getchar();
		switch(c)
		{
			case 'q':
				*static_cast<bool*>(arg) = false;
				return nullptr;
			case '+':
				colony->add();
				break;
			case '-':
				colony->remove();
				break;
			case ' ':
				// TODO: deszcz
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
}

int main(int argc, char** argv)
{

	if(CommonUtils::initLibrary())
	{
//		getchar();
		Map* map = nullptr;
		StatusBar* statusBar = nullptr;

		if(CommonUtils::initWindows(map, statusBar))
		{
			grass = new Grass(map->getHeight() - 2, map->getWidth() - 2);
			colony = new SnailColony();
			colony->setGrass(grass);
			map->setColony(colony);
			map->setGrass(grass);
			statusBar->setColony(colony);
			statusBar->setGrass(grass);
//			statusBar->start();
//			mvprintw(1, 1, "%d, %d", map.getHeight(), map.getWidth());
//			mvprintw(2, 1, "%d, %d", statusBar.getHeight(), statusBar.getWidth());
//			wrefresh(stdscr);
			for(int i = 0; i < 5; i++)
			{
				map->getColony()->add();
			}

			refresh();

			bool run = true;
			pthread_t keysThread;
			pthread_create(&keysThread, nullptr, keys, static_cast<void*>(&run));

//			for(unsigned i = 0; i < 10000; i++)
			unsigned i = 0;
			while(run)
			{
				++i;
				if(i == 10)
				{
					map->growMap();
					i = 0;
				}
				usleep(100000);
				map->reprint();
				statusBar->refreshStatus();
			}
//			sleep(2);
//			getchar();

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
