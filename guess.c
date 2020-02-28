#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int guess(char* hidden, char* word, char* letter, int *length, int *num_correct){
    int match = 0; // false unless guess is a match
    for(int i = 0; i < *length; i++){
        if(word[i] == *letter){
            match = 1;
            hidden[i] = *letter;
            *num_correct += 1;
        }
    }
    if(!match){
        printf("Wrong!\n");
    }
    else{
        printf("Correct!\n");
    }
    printf("----------------\n");
    printf("%s\n",hidden); 
    printf("----------------\n");
    // return 0 if solved
    if(*num_correct == *length){
        return 0;
    }
    // return 1 if all blanks have been guessed
    else{
        return 1;
    }
    
}
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
    int index; //  chosen random index
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

    //char *hidden = NULL; // holds "hidden word"
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
    int num_correct = 0;
    int num_guesses = 0;
    int max_guesses = 3;
    char letter = '\0';
    // first user guess input
    while(max_guesses != num_guesses){
        printf("Enter letter guess:  ");
        letter = '\0';
        scanf("%c", &letter); // reads user input
        printf("input is %c\n", letter);
        guess(hidden, word, &letter, &length, &num_correct);
        while ( getchar() != '\n' ); // clear ENTER key from buffer
    }
    // while( guess(hidden, word, &letter, &length, &num_correct) ){
    //     printf("Enter letter guess:  ");
    //     scanf("%c", &letter); // reads user input
    //     printf("input is %c\n", letter);
    // }
        
    


}

