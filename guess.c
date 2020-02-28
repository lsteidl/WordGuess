#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    char c[64]; // holds word retrieved from file
    // open file for reading
    FILE *file;
    if ((file = fopen("wordlist.txt", "r")) == NULL)
    {
        printf("Error opening file. wordlist.txt must be in current folder");
        // program exits if file cannot be opened
        exit(1);
    }
    // choose random number, used to select word
    // choose index 1-58109
    int index;
    srand ( time(NULL) ); // seed with time
    index = (rand() % 58108) + 1; // 1-58109
    printf("%d\n",index); // display chosen number
    // loop through file to find corresponding word
    for(int i = 0; i <= index; i++){
        fscanf(file, "%s", c);
       // printf("%s", c);
    }

}