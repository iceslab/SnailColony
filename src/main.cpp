#include "../headers/includes.h"
#include "../headers/CommonUtils.h"
#include "../headers/SnailColony.h"

int main(int argc, char** argv)
{

	if(CommonUtils::initLibrary())
	{
//		getchar();
		Map* map = nullptr;
		Grass* grass = nullptr;
		SnailColony* colony = nullptr;
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

//			for(unsigned i = 0; i < 10000; i++)
			unsigned i = 0;
			while(true)
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

		if(nullptr != statusBar)
		{
			delete statusBar;
			statusBar = nullptr;
		}
	}
	endwin();
	return 0;
}
