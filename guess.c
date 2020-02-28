#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// displays menu to screen
void print_menu(){
    printf("Select Difficulty...\n");
    printf("1) Easy\n"); // 8 wrong
    printf("2) Medium\n"); // 5 wrong
    printf("3) Hard\n"); // 2 wrong
    printf(">> ");
}
// prints history of past guesses
void print_past(char* past){
    int length = strlen(past);
    // loop through each past input
    for(int i = 0; i < length; i++){
        // handle final punctuation
        if(i < (length - 1)){
            printf("%c, ", past[i]);
        }
        else{
            printf("%c", past[i]);
        }
    }
}
// prints hidden word in easy to view format
void print_hidden(char* hidden){
    // print updated word
    printf("----------------\n");
    printf("%s\n",hidden); 
    printf("----------------\n");
}
// handles user letter guess, 
//updates num_correct, num_wrong and hidden word
int guess(char* hidden, char* word, char* letter, int *length, int *num_correct, int *num_wrong, int *max_wrong, char* past){
    int match = 0; // false unless guess is a match
    for(int i = 0; i < *length; i++){
        if(word[i] == *letter){
            match = 1;
            hidden[i] = *letter;
            *num_correct += 1; // increment correct count
        }
    }
    if(!match){
        past[*num_wrong] = *letter; // add letter to list of past wrong guesses
        past[(*num_wrong)+1] = '\0'; // mark end 
        *num_wrong += 1; // increment wrong count
        printf("Wrong!");
        
    }
    else{
        printf("Correct!");
    }
    printf(" - %d incorrect guesses left\n", *max_wrong-*num_wrong);
    // print updated word
    print_hidden(hidden);
    // print updated wrong guesses
    print_past(past);
    // return 0 if solved
    if(*num_correct == *length){
        return 0;
    }
    // return 1 if all blanks have been guessed
    else{
        return 1;
    }
}
// word guess game
int main(int argc, char *argv[])
{
    char word[64]; // holds word retrieved from file
    // Game Setup
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
    // prompt user for difficulty level
    print_menu(); // display menu
    int max_wrong = 5; // max wrong guesses
    int level = 0; // holds chosen difficulty 
    // get user input
    scanf("%d", &level); // reads user input
    while ( getchar() != '\n' ); // clear ENTER key from buffer
    if(level == 1){
        printf("You chose Easy. 8 Wrong guesses allowed.\n");
        max_wrong = 8;
    }
    else if(level == 2){
        printf("You chose Medium. 5 Wrong guesses allowed.\n");
        max_wrong = 5;
    }
    else if(level == 3){
        printf("You chose Hard. 2 Wrong guesses allowed.\n");
        max_wrong = 2;
    }

    print_hidden(hidden); // display hidden word
    int num_correct = 0; // correct guesses
    int num_wrong = 0; // total wrong guesses
    char past[64]; // holds past incorrect guesses
    char letter = '\0'; // make room for user char guess
    // repeatedly prompt user for guess input
    while(( max_wrong > num_wrong ) && ( num_correct < length ) ){
        printf("Enter letter guess:  ");
        letter = '\0';
        scanf("%c", &letter); // reads user input
        guess(hidden, word, &letter, &length, &num_correct, &num_wrong, &max_wrong, past);
        while ( getchar() != '\n' ); // clear ENTER key from buffer
    }

    // handle game termination
    if(max_wrong == num_wrong){
        // losing game
        printf("You Lose! Try Again.\n");
    }
    else{
        // winning game
        printf("You Win. Congratulations!\n");

    }
    


}

