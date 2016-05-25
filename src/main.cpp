#include "../headers/includes.h"
#include "../headers/CommonUtils.h"
#include "../headers/SnailColony.h"

SnailColony* colony = nullptr;

void* keys(void* arg)
{
	while(true)
	{
		char c = getchar();
		bool revived = false;
		switch(c)
		{
			case 'q':
				*static_cast<bool*>(arg) = false;
				return nullptr;
			case '+':
				// Nie zadziala bo watek juz wyszedl z petli
				for(unsigned i = 0; i < colony->getColonySize(); i++)
				{
					if(DEAD == colony->getSnail(i)->getState())
					{
						colony->getSnail(i)->setState(ALIVE);
						revived = true;
						break;
					}
				}

				if(!revived)
				{
					colony->add();
				}

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
//		getchar();
		Map* map = nullptr;
		Grass* grass = nullptr;
		StatusBar* statusBar = nullptr;

		if(CommonUtils::initWindows(map, statusBar))
		{
			grass = new Grass(map->getHeight() - 2, map->getWidth() - 2);
			colony = new SnailColony();
			colony->setGrass(grass);
			map->setColony(colony);
			map->setGrass(grass);
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
				if(i == 30)
				{
					map->growMap();
					i = 0;
				}
				usleep(100000);
				map->reprint();
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
