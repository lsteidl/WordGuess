#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char word[64]; // holds word retrieved from file
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
    srand(time(NULL));            // seed with time
    index = (rand() % 58108) + 1; // 1-58109
    printf("%d\n", index);        // display chosen number
    // loop through file to find corresponding word
    for (int i = 0; i <= index; i++)
    {
        fscanf(file, "%s", word);
    }
    printf("Chosen word is: %s\n", word);
    int length = strlen(word);
    printf("Length: %d\n", length);

    char hidden[length]; // holds "hidden word"
    for (int i = 0; i <= length; i++)
    {
        hidden[i] = '*';
        // mark end of string
        if (i == length)
        {
            hidden[i] = '\0';
        }
    }
    printf("%s\n", hidden);

    // get user guess input
    //char *line = NULL;
    char letter = '\0';
    printf("Enter letter guess:  ");
    scanf("%c", &letter); // reads user input
    printf("input is %c\n", letter);
    
}