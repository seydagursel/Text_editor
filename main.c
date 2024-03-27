#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curses.h>
#include "textbuffer.c"

int main(int argc, char *argv[]) {
	int ht, wd;
	char *filename;
	char choice;
	char line[40];

	initscr();
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	getmaxyx(stdscr, ht, wd);

	/* HELP MENU */
	attron(COLOR_PAIR(1));
	mvprintw(ht/2 - 5, wd/2 - 10, "WELCOME TO MYEDITOR!");  //mvprintw() = move() + printw()
	attroff(COLOR_PAIR(1));
	refresh();

	attron(COLOR_PAIR(2));
	mvprintw(ht/2 - 3, wd/2 - 10, "w: move cursor up"   );
	mvprintw(ht/2 - 2, wd/2 - 10, "z: move cursor down" );
	mvprintw(ht/2 - 1, wd/2 - 10, "I: insert"           );
	mvprintw(ht/2 - 0, wd/2 - 10, "D: delete"           );
	mvprintw(ht/2 + 1, wd/2 - 10, "S: save"             );
	mvprintw(ht/2 + 2, wd/2 - 10, "X: exit"             );
	attroff(COLOR_PAIR(2));

	attron(COLOR_PAIR(1));
	mvprintw(ht/2 + 4, wd/2 -10, "window size: %3d x %3d",wd,ht);
	mvprintw(ht/2 + 6, wd/2 - 10, "press any key to continue...");
	attroff(COLOR_PAIR(1));

	move(0,0);
	refresh();
	getch();
	clear();

	filename  = argv[1];
	//call edit()
	edit(filename);
	refresh();

	choice = getch();

	while(choice != 'X')
	{

		switch(choice)
		{
			case 'w': {
				noecho();
				if (cursor_position > 0) {
					move(--cursor_position,x);
					//cursor_position--;
				}
				refresh();
				break;
			}
			case 'z': {
				noecho();
				if (cursor_position <= 26) {
					move(cursor_position+1,x);
					cursor_position++;
				}
				refresh();
				break;
			}
			case 'I': {
				noecho();
				scanw("%s",line);
				insert(line);
				break;
			}
			case 'D': {
				noecho();
				delete();
				break;
			}
			case 'S': {
				noecho();
				save(filename);
				break;
			}
			default:
				echo();
		}
		
		choice = getch();
	}

	endwin();
	return 0;
}