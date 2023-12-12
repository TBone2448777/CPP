/**
 * Examples of reading and writing files. 
 * 
*/
#include <stdio.h>

int main() 
{
    FILE * infile;
    FILE * outfile;
    char buffer[1024];

    outfile = fopen("test.txt", "w");
    if(outfile != NULL) {
	    fputs("Hello files!", outfile);
	    fclose(outfile);
    }

    infile = fopen("test.txt", "r");
    if (infile != NULL) {
        while (fscanf(infile, "%s", buffer) != EOF)  {
            printf("From file: %s\n", buffer);
        }
        fclose(infile);
    }
}