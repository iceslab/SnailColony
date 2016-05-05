#include "../headers/CommonUtils.h"
#include "../headers/Map.h"

int main(int argc, char** argv)
{

	if(initLibrary())
	{
//		wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');
		wborder(stdscr, '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0');
		wrefresh(stdscr);

		int height = 10;
		int width = 10;
		int lines, columns;

		getmaxyx(stdscr, lines, columns);
//		height = lines;
//		width = columns;

		int startY = (lines - height) / 2;     /* Obliczanie środkowej pozycji */
		int startX = (columns - width) / 2;

		refresh();

		Map map(height, width, startX, startY);

		refresh();
		sleep(2);
//		getchar();
	}
	endwin();
	return 0;
}
