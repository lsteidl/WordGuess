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
// print loss statistics
void print_loss(char* word){
    printf("-------------------------\n");
    printf("You Lose! Try Again.\n");
    printf("Correct word: %s\n", word);
    printf("-------------------------\n");
}

// prints history of past guesses
void print_past(char* past){
    int length = strlen(past);
    //printf("Previous Wrong Guesses: ");
    // loop through each past input
    for(int i = 0; i < length; i++){
        // handle final punctuation
        if(i < (length - 1)){
            printf("%c, ", past[i]);
        }
        else{ 
            // print last char
            printf("%c\n", past[i]);
        }
    }
    if(length == 0){
       printf("\n"); 
    }
}
// prints hidden word in easy to view format
void print_hidden(char* hidden){
    int length = strlen(hidden);
    // print updated word
    // print word with spacing
    // print border line of varying length
    for(int i = 0; i < length; i++){
        printf("--");
        if(i == (length - 1)){
            printf("\n");
        }
    }
    // print word with spaces
    for(int i = 0; i < length; i++){
        printf("%c ", hidden[i]);
    }
    // print border line of varying length
    for(int i = 0; i < length; i++){
        if(i == 0){
            printf("\n");
        }
        printf("--");
        if(i == (length - 1)){
            printf("\n");
        }
    }
}
int repeat_guess(char* letter, char* past, char* past_right){
    int length_wrong = strlen(past);
    int length_right = strlen(past_right);
    int repeat = 0; // false until repeat is discovered
    for(int i = 0; i < length_wrong; i++){
        if(past[i] == *letter){
            repeat = 1;
        }
    }
    for(int i = 0; i < length_right; i++){
        if(past_right[i] == *letter){
            repeat = 1;
        }
    }
    return repeat;
}
// handles user letter guess, 
//updates num_correct, num_wrong and hidden word
int guess(char* hidden, char* word, char* letter, int *length, int *correct_guesses,
            int *num_correct, int *num_wrong, int *max_wrong, char* past, char* past_right){
    int match = 0; // false unless guess is a match
    for(int i = 0; i < *length; i++){
        if(repeat_guess(letter, past, past_right)){
            printf("\nYou already guessed %c", *letter);
            match = -1;
            break; // stop searching for matches
        }
        if(word[i] == *letter){
            match = 1;
            hidden[i] = *letter;
            *num_correct += 1; // increment correct count
        }
    }
    if(match == 0){
        past[*num_wrong] = *letter; // add letter to list of past wrong guesses
        past[(*num_wrong)+1] = '\0'; // mark end 
        *num_wrong += 1; // increment wrong count
        printf("\nWrong!");
        
    }
    else if(match == 1){
        past_right[*correct_guesses] = *letter; // add letter to list of past right
        past_right[(*correct_guesses)+1] = '\0'; // mark end
        *correct_guesses += 1;
        printf("\nCorrect!");
    }
    printf(" - %d incorrect guesses left\n", *max_wrong-*num_wrong);
    // print updated word
    print_hidden(hidden);
    // print updated wrong guesses
    printf("Previous Wrong Guesses: ");
    print_past(past);
    //print update correct guesses
    printf("Previous Correct Guesses: ");
    print_past(past_right);
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
    int correct_guesses = 0; // correct guesses made
    int num_correct = 0; // correct letters found
    int num_wrong = 0; // total wrong guesses
    char past[64]; // holds past incorrect guesses
    past[0] = '\0'; // avoid unexpected array values 
    char past_right[64]; // holds past correct guesses
    past_right[0] = '\0'; // avoid unecpected values
    char letter = '\0'; // make room for user char guess
    // repeatedly prompt user for guess input
    while(( max_wrong > num_wrong ) && ( num_correct < length ) ){
        printf("Enter letter guess:  ");
        letter = '\0';
        scanf("%c", &letter); // reads user input
        guess(hidden, word, &letter, &length, &correct_guesses, &num_correct, &num_wrong, &max_wrong, past, past_right);
        while ( getchar() != '\n' ); // clear ENTER key from buffer
    }

    // handle game termination
    if(max_wrong == num_wrong){
        // losing game
        print_loss(word);
    }
    else{
        // winning game
        printf("max wrong == %d, num_wrong == %d\n", max_wrong, num_wrong);
        printf("You Win. Congratulations!\n");

    }
    


}

