#include <pthread.h>
#include <ncurses.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{

	if(NULL != initscr())
	{
		WINDOW * win = NULL;
		cbreak();
		int lines, columns;
		getmaxyx(stdscr, lines, columns);
		win = newwin(10, 10, 10, 10);
		box(win, '-' , '|');
//		wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
		wrefresh(win);
		mvprintw(10, 10, "%d", win);

		refresh();
		getchar();
	}
	endwin();
	return 0;
}
