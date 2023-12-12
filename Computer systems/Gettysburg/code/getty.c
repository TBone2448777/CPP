#include <stdio.h>

int isNumber(char chosen){
    char nums[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0'};
    for (int i = 0; i < 10; i++){
        if (chosen == nums[i]){
            return 1;
        }
    }
    return 0;
}

int main(int argc, char * argv[]){
    if (argc != 2){
        printf("Usage: program requires 1 parameter.\nYou provided %d.\n", argc-1);
        return 0;
    } else{
        FILE *infile;
        infile = fopen(argv[1], "r");
        FILE *outfile;
        outfile = fopen("gba_formatted.txt", "w");
        if (infile != NULL){
            char buffer[1024];
            int pCount = 0;
            while(fscanf(infile, "%s", buffer) != EOF){
                if (isNumber(buffer[0]) == 1){
                    pCount++;
                }
            }
            fprintf(outfile, "%d", pCount);
            fclose(infile);
            infile = fopen(argv[1], "r");
            while(fscanf(infile, "%s", buffer) != EOF){
                if (isNumber(buffer[0]) == 1){
                    fprintf(outfile, "\n\t");
                } else{
                    fprintf(outfile, "%s ", buffer);
                }
            }
            fprintf(outfile, "\n");
            fclose(infile);
            fclose(outfile);
            printf("Text sent to output file.");
        } else {
            printf("File not found.");
        }
        printf("\n");
        return 0;
    }
}