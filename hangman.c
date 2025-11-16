#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include "hangman.h"


int get_word(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}

int is_word_guessed(const char secret[], const char letters_guessed[]){
    for(int i = 0; secret[i] != '\0'; i++){
        int found = 0;
        for(int j = 0; letters_guessed[j] != '\0'; j++){
            if(secret[i] == letters_guessed[j]){
                found = 1;
                break;
            }
        }
        if(!found){
            return 0;
        }
    }
    return 1;
}

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]){
    int k = 0;
    for(int i = 0; secret[i] != '\0'; i++){
        int found = 0;
        for(int j = 0; letters_guessed[j] != '\0'; j++){
            if(secret[i] == letters_guessed[j]){
                found = 1;
                break;
            }
        }
        if(found){
            guessed_word[k++] = secret[i];
        } else {
            guessed_word[k++] = '_';
        }
    }
    guessed_word[k] = '\0';
}

void get_available_letters(const char letters_guessed[], char available_letters[]){
    int k = 0;
    for(char c = 'a'; c <= 'z'; c++){
        int found = 0;
        for(int j = 0; letters_guessed[j] != '\0'; j++){
            if(c == letters_guessed[j]){
                found = 1;
                break;
            }
        }
        if(!found){
            available_letters[k++] = c;
        }
    }
    available_letters[k] = '\0';
}

void hangman(const char secret[]){
    int guesses_left = 8;
    char letters_guessed[100] = "";
    int letters_count = 0;

    printf("Welcome to the game, Hangman!\n");
    printf("I am thinking of a word that is %ld letters long.\n", strlen(secret));

    while(guesses_left > 0){
        printf("-------------\n");
        printf("You have %d guesses left.\n", guesses_left);

        char available[27];
        get_available_letters(letters_guessed, available);
        printf("Available letters: %s\n", available);

        printf("Please guess a letter: ");
        char input[100];
        scanf("%s", input);

        if(strlen(input) > 1){
            char lower_input[100];
            for(int i = 0; input[i] != '\0'; i++){
                lower_input[i] = tolower(input[i]);
            }
            lower_input[strlen(input)] = '\0';

            if(strcmp(lower_input, secret) == 0){
                printf("Congratulations, you won!\n");
                return;
            } else {
                printf("Sorry, bad guess. The word was %s.\n", secret);
                return;
            }
        }

        char letter = input[0];

        if(!isalpha(letter)){
            printf("Oops! '%c' is not a valid letter: ", letter);
            char guessed[100];
            get_guessed_word(secret, letters_guessed, guessed);
            for(int i = 0; guessed[i] != '\0'; i++){
                printf("%c", guessed[i]);
                if(guessed[i+1] != '\0'){
                    printf(" ");
                }
            }
            printf("\n");
            continue;
        }

        letter = tolower(letter);

        int already_guessed = 0;
        for(int i = 0; i < letters_count; i++){
            if(letters_guessed[i] == letter){
                already_guessed = 1;
                break;
            }
        }

        if(already_guessed){
            printf("Oops! You've already guessed that letter: ");
            char guessed[100];
            get_guessed_word(secret, letters_guessed, guessed);
            for(int i = 0; guessed[i] != '\0'; i++){
                printf("%c", guessed[i]);
                if(guessed[i+1] != '\0'){
                    printf(" ");
                }
            }
            printf("\n");
            continue;
        }

        letters_guessed[letters_count++] = letter;
        letters_guessed[letters_count] = '\0';

        int letter_in_word = 0;
        for(int i = 0; secret[i] != '\0'; i++){
            if(secret[i] == letter){
                letter_in_word = 1;
                break;
            }
        }

        char guessed[100];
        get_guessed_word(secret, letters_guessed, guessed);

        if(letter_in_word){
            printf("Good guess: ");
        } else {
            printf("Oops! That letter is not in my word: ");
            guesses_left--;
        }

        for(int i = 0; guessed[i] != '\0'; i++){
            printf("%c", guessed[i]);
            if(guessed[i+1] != '\0'){
                printf(" ");
            }
        }
        printf("\n");

        if(is_word_guessed(secret, letters_guessed)){
            printf("-------------\n");
            printf("Congratulations, you won!\n");
            return;
        }
    }

    printf("Sorry, you ran out of guesses. The word was %s.\n", secret);
}
