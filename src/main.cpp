#include "../headers/includes.h"
#include "../headers/CommonUtils.h"
#include "../headers/SnailColony.h"

int main(int argc, char** argv)
{

	if(CommonUtils::initLibrary())
	{
//		getchar();
		Map map;
//		SnailColony colony;
		StatusBar statusBar;

		if(CommonUtils::initWindows(map, statusBar))
		{

//			mvprintw(1, 1, "%d, %d", map.getHeight(), map.getWidth());
//			mvprintw(2, 1, "%d, %d", statusBar.getHeight(), statusBar.getWidth());
//			wrefresh(stdscr);
			map.getColony().add();
			map.getColony().add();
			map.getColony().add();
			map.getColony().add();
			refresh();

//			for(unsigned i = 0; i < 10000; i++)
			unsigned i = 0;
			while(true)
			{
				++i;
				if(i == 10)
				{
					map.growMap();
					i = 0;
				}
				usleep(100000);
				map.reprint();
			}
//			sleep(2);
//			getchar();

		}

	}
	endwin();
	return 0;
}
