#include "data_structures/dqueue.h"
#include "input.h"
#include <stdio.h>
#include <sys/types.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

static void move_back(WINDOW * win,int spaces){
	int y,x;
	getyx(win,y,x);
	int my,mx;
	getmaxyx(win,my,mx);
	x -= spaces;
	if(x < 0){
		x *= -1;
		int rows = (x / mx) + 1;
		x = mx - (x % mx);
		y -= rows;
		if(y < 0){
			y = 0;
			x = 0;
		}
	}
	wmove(win,y,x);
}
static void move_forward(WINDOW * win,int spaces){
	int y,x;
	getyx(win,y,x);
	int my,mx;
	getmaxyx(win,my,mx);
	x += spaces;
	if(x >= mx){
		int rows = (x / mx);
		x = (x % mx);
		y += rows;
		if(y >= my){
			y = my - 1;
			x = mx - 1;
		}
	}
	wmove(win,y,x);
}

//variables here
char * head;
char * path;
char * end;
WINDOW * selected_win;
int history_range;
int history_index;

void get_input(){
	new_buffer(default_buffer_size);
	//gets input
	wprintw(selected_win,"%s%s%s",head,path,end);
	int prompt_start_y,prompt_start_x;
	getyx(selected_win,prompt_start_y,prompt_start_x);
	while(1){
		if(listen()){
			//non-printable character
			if(keycode == '\n'){
				move_forward(selected_win,strlen(&buffer[buffer_index]));
				wprintw(selected_win,"\n");
				break;
			}
			else if(keycode == KEY_LEFT){
				if(buffer_index){
					buffer_index--;
					move_back(selected_win,1);
				}
			}
			else if(keycode == KEY_RIGHT){
				if(buffer[buffer_index]){
					buffer_index++;
					move_forward(selected_win,1);
				}
			}
			else if(keycode == KEY_UP){
				if(history_index >= 0){
					wmove(selected_win,prompt_start_y,prompt_start_x);
					int i,s;
					s = strlen(buffer);
					for(i = 0; i < s; i++){
						addch(' ');
					}
					wmove(selected_win,prompt_start_y,prompt_start_x);
					free(buffer);
					history_index -= 1;
					if(history_index < 0){
						history_index = history_range - 1;
					}
					buffer = buffer_cpy(dqueue_get(history_index,history));
					wprintw(selected_win,"%s",buffer);
					
				}
			}
			else if(keycode == KEY_DOWN){
				if(history_index >= 0){
					wmove(selected_win,prompt_start_y,prompt_start_x);
					int i,s;
					s = strlen(buffer);
					for(i = 0; i < s; i++){
						addch(' ');
					}
					wmove(selected_win,prompt_start_y,prompt_start_x);
					free(buffer);
					history_index += 1;
					if(history_index >= history_range){
						history_index = 0;
					}
					buffer = buffer_cpy(dqueue_get(history_index,history));
					wprintw(selected_win,"%s",buffer);
					
				}
			}
			else if(keycode == KEY_BACKSPACE){
				if(backspace()){
					move_back(selected_win,1);
				}
				int y,x;
				getyx(selected_win,y,x);
				wprintw(selected_win,"%s ",&buffer[buffer_index]);
				wmove(selected_win,y,x);
			}
			else if(keycode == EOF){
				wprintw(selected_win,"EOF, exiting");
				endwin();
				exit(0);
			}
		}
		else{
			//printable characters	
			buffer_add(key);
			int y,x;
			wprintw(selected_win,"%c",buffer[buffer_index-1]);
			getyx(selected_win,y,x);
			wprintw(selected_win,"%s",&buffer[buffer_index]);
			move(y,x);
		}
		wrefresh(selected_win);
	}
	//puts input into history
	push_input_dqueue(buffer, history);
	//updates history_range and histroy_index
	if(history->dqueue[0] && history->dqueue[1]){
		history_range = history_size;
	}
	else{
		history_range++;
		if(history_range >= history_size){
			history_range = history_size;
		}
	}
	history_index = history_range;
	//makes a copy of the input and parses it
	
	//writes to variables
}
struct parsed_input{
	int commands_size;
	char ** commands;
	char * symbols;
	int * place;
};
struct parsed_input * parse(char * str){
	struct parsed_input * output =(struct parsed_input *)malloc(sizeof(struct parsed_input));
	int i;
	output->commands_size = 0;
	output->commands = (char **)malloc(sizeof(char *));
	output->commands[output->commands_size++] = str;
	for(i = 0; str[i]; i++){
		if(str[i] == ';'){
			if(str[i+1]){
				output->commands_size += 1;
				output->commands = (char **)realloc(output->commands,sizeof(char *) * output->commands_size);
				output->commands[output->commands_size - 1] = &str[i + 1];
			}
			str[i] = '\0';
		}
	}
	output->symbols = (char *)calloc(sizeof(char),output->commands_size);
	output->place = (int *)calloc(sizeof(int),output->commands_size);
	for(i = 0; i < output->commands_size; i++){
		int ii;
		int len = strlen(output->commands[i]);
		for(ii = 0; ii < len; ii++){
			if(output->commands[i][ii] == '>' || output->commands[i][ii] == '<' || output->commands[i][ii] == '|'){
				output->symbols[i] = output->commands[i][ii];
				output->place[i] = ii;
			}
		}
	}
	output->symbols[i] = '\0';
	return output;
}

int execute(int index, struct parsed_input * parsed){ 
//return 0 if child finished
// 1 if exit has been called
// 2 if its the parent process
	return 2;
}

int display_output(){

}

int main(){
	input_init(20,10);
	selected_win = stdscr;
	history_index = -1;
	history_range = 0;
	head = "TERM:";
	//remember to actually set path
	path = "";
	end = "$ ";
	while(1){
		//gets input and handles basic terminal interfacing
		get_input();
		char * str = buffer_cpy(buffer);
		//parses the string
		int i;
		struct parsed_input * parsed = parse(str);
		for(i = 0; i < parsed->commands_size; i++){
			//forks and executes the process
			int end = execute(i,parsed);	
			if(end == 0){
				return 0;
			}
			else if(end == 1){
				endwin();
				return 0;
			}
			else if(end == 2){
				display_output();
			}
		}
		for(i = 0; i < parsed->commands_size; i++){
			free(parsed->commands[i]);
		}
		free(buffer);
		free(parsed->commands);
		free(parsed->symbols);
		free(parsed->place);
		free(parsed);
	}
	endwin();
	return 0;
}
