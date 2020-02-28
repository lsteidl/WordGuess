#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void print_hidden(char* hidden){
    // print updated word
    printf("----------------\n");
    printf("%s\n",hidden); 
    printf("----------------\n");
}
int guess(char* hidden, char* word, char* letter, int *length, int *num_correct, int *num_wrong){
    int match = 0; // false unless guess is a match
    for(int i = 0; i < *length; i++){
        if(word[i] == *letter){
            match = 1;
            hidden[i] = *letter;
            *num_correct += 1; // increment correct count
        }
    }
    if(!match){
        *num_wrong += 1; // increment wrong count
        printf("Wrong!\n");
    }
    else{
        printf("Correct!\n");
    }
    // print updated word
    print_hidden(hidden);
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

    char hidden[length]; // holds "hidden word"
    // fill hidden word with blanks
    for (int i = 0; i <= length; i++)
    {
        hidden[i] = '*';
        // mark end of string
        if (i == length)
        {
            hidden[i] = '\0';
        }
    }
    print_hidden(hidden); // display hidden word
    int num_correct = 0; // correct guesses
    int num_wrong = 0; // total wrong guesses
    int max_guesses = 3; // max wrong guesses
    char letter = '\0';
    // repeatedly prompt user for guess input
    while(( max_guesses > num_wrong ) && ( num_correct < length ) ){
        printf("Enter letter guess:  ");
        letter = '\0';
        scanf("%c", &letter); // reads user input
        printf("input is %c\n", letter);
        guess(hidden, word, &letter, &length, &num_correct, &num_wrong);
        while ( getchar() != '\n' ); // clear ENTER key from buffer
    }

    // handle game termination
    if(max_guesses == num_wrong){
        // losing game
        printf("You Lose! Try Again.\n");
    }
    else{
        // winning game
        printf("You Win! Congratulations\n");

    }
    


}

