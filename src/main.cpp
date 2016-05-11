#include "../headers/includes.h"
#include "../headers/CommonUtils.h"
#include "../headers/SnailColony.h"

int main(int argc, char** argv)
{

	if(CommonUtils::initLibrary())
	{
		Map map;
		SnailColony colony;
		StatusBar statusBar;

		if(CommonUtils::initWindows(map, statusBar))
		{

//			mvprintw(1, 1, "%d, %d", map.getHeight(), map.getWidth());
//			mvprintw(2, 1, "%d, %d", statusBar.getHeight(), statusBar.getWidth());
//			wrefresh(stdscr);
			refresh();

			for(unsigned i = 0; i < 10; i++)
			{
				map.growMap();
				sleep(1);
			}
//			sleep(2);
			getchar();

		}

	}
	endwin();
	return 0;
}
