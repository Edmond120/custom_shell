#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "data_structures/dqueue.h"
#include "input.h"

void input_init(int b_size, int h_size){
	history = input_dqueue_init(h_size);
	history_size = h_size;
	new_buffer(b_size);
	default_buffer_size = b_size;
}

void new_buffer(int b_size){
	buffer_size = b_size;
	buffer = (char *)malloc(sizeof(char) * b_size);
	buffer_index = 0;
}

//inserts a new character to the buffer at buffer_index and increases it by 1
static void insert_char(char new_char){
	buffer[buffer_index++] = new_char;
}

//shifts everything starting from buffer_index to the right, expands buffer if needed
static void buffer_shift_right(){
	int i;
	char temp = buffer[buffer_index];
	char temp2;
	for(i = buffer_index; temp; i++){
		temp2 = buffer[i];
		buffer[i] = temp;
		temp = temp2;
	}
	if(i >= buffer_size){
		buffer = (char *)realloc(buffer,buffer_size * 2);
		buffer_size *= 2;
	}
	buffer[i] = temp;
}

//shifts everything starting from buffer_index to the left, overwritting the character in buffer_index
static void buffer_shift_left(){

}

void buffer_add(char new_char){
	if(buffer[buffer_index]){
		buffer_shift_right();
		insert_char(new_char);
	}
	else{
		if(buffer_index < buffer_size - 1){
			insert_char(new_char);
			buffer[buffer_index] = '\0';
		}
		else{
			char * str = (char *)realloc(buffer,buffer_size * 2);
			if(str){
				buffer = str;
				buffer_size *= 2;
				insert_char(new_char);
				buffer[buffer_index] = '\0';
			}
			else{
				printf("------------------------------------------------------------\n");
				printf("oh no, it seems that realloc ACTUALLY failed\n");
				printf("I never expected this to happen, and only wrote\n");
				printf("this as a joke and because I like to hear keyboard clicks\n");
				printf("but.........................................................\n");
				printf("¯\\_(o.0)_/¯\n");
				printf("------------------------------------------------------------\n");
			}
		}
	}
}

//for testing purposes
int main(){
	new_buffer(10);
	int i;
	for(i = 0; i < 5; i++){
		buffer[i] = i + 97;
	}
	printf("%s\n",buffer);
	for(i = 0; i < 5;i++){
		printf("shift right\n");
		buffer_shift_right();
		printf("%s\n",buffer);
	}
	printf("buffer size: %d\n",buffer_size);
	return 0;
}
