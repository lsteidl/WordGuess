#include <stdio.h>

int main(char *argc, char *argv[])
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
    index = 12;
    // loop through file to find corresponding word
    for(int i = 0; i <= index; i++){
        fscanf(file, "%s", c);
        printf("%s", c);
    }
}