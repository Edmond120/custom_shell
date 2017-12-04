#include "data_structures/dqueue.h"
#include "input.h"
#include  <stdio.h>
#include  <sys/types.h>
#include  <ncurses.h>

void move_back(WINDOW * win,int spaces){
	int y,x;
	getyx(win,y,x);
	move(y,x - spaces);
}
void move_foward(WINDOW * win,int spaces){

}

int main(){
	input_init(20,10);
	move(0,10);
	move_foward(stdscr,5);
	getch();
	move_back(stdscr,5);
	refresh();
	getch();
	endwin();
	return 0;
}
