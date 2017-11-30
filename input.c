#include <stdio.h>
#include <stdlib.h>

int main(){
	char *str;
    printf (" enter a string of any length, whitespace is OK: ");
    while(1){
		scanf ("%ms", &str);
    	printf ("\n str: %s\n\n", str);
		printf("%c\n",str[0]);
		
		if(0){
			printf("before break\n");
			break;
			printf("after break\n");
		}
		printf("before free\n");
		free(str);
		printf("after free\n");
	}
    return 0;
}
