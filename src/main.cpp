#include <pthread.h>
#include <ncurses.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv)
{

	if(NULL != initscr())
	{
		WINDOW * win = NULL;
		cbreak();
		refresh();
		int height = 10;
		int width = 10;
		int lines, columns;
		getmaxyx(stdscr, lines, columns);
		height = lines;
		width = columns;

		int starty = (lines - height) / 2;     /* Obliczanie środkowej pozycji */
		int startx = (columns - width) / 2;

//		win = newwin(lines, width, starty, startx);
//		box(win, '-' , '|');
//		wprintw(win, "Hello World");
		wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');
		wrefresh(stdscr);
//		mvprintw(10, 10, "%d", win);

		refresh();
		sleep(2);
//		getchar();
	}
	endwin();
	return 0;
}
