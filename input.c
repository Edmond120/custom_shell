#include <stdio.h>
#include <stdlib.h>

int main(){
	char *str = NULL;
    printf (" enter a string of any length, whitespace is OK: ");
    scanf ("%m[^\n]%*c", &str);
    printf ("\n str: %s\n\n", str);
	scanf ("%m[^\n]%*c", &str);
	printf ("\n str: %s\n\n", str);
    if (str) free (str);
    return 0;
}
