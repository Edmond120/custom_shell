#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

//works but not the best way to get input
char * old_input(){
	char * str;
	scanf("%ms", &str);
	return str;
}
int main(){//main does not belong here, it is only used for bug testing
	//printf("%s\n",old_input());
}
