#include <stdio.h>
#include <stdlib.h>

int main(){
	char *str;
    printf (" enter a string of any length, whitespace is OK: ");
    while(!feof(stdin)){
		scanf ("%ms", &str);
    	printf ("\n str: %s\n\n", str);
		free(str);	
	}
    return 0;
}
