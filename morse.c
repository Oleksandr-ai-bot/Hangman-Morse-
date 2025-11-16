#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "morse.h"

void text_to_morse(const char text[], char output[]){
    const char* morse_alphabet[26] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
        "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
        "..-", "...-", ".--", "-..-", "-.--", "--.."
    };

    const char* morse_digits[10] = {
        "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
    };

    int k = 0;
    for(int i = 0; text[i] != '\0'; i++){
        char c = toupper(text[i]);

        if(c >= 'A' && c <= 'Z'){
            const char* morse = morse_alphabet[c - 'A'];
            for(int j = 0; morse[j] != '\0'; j++){
                output[k++] = morse[j];
            }
            if(text[i+1] != '\0'){
                output[k++] = ' ';
            }
        } else if(c >= '0' && c <= '9'){
            const char* morse = morse_digits[c - '0'];
            for(int j = 0; morse[j] != '\0'; j++){
                output[k++] = morse[j];
            }
            if(text[i+1] != '\0'){
                output[k++] = ' ';
            }
        }
    }
    output[k] = '\0';
}

void morse_to_text(const char morse[], char output[]){
    const char* morse_alphabet[26] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
        "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
        "..-", "...-", ".--", "-..-", "-.--", "--.."
    };

    const char* morse_digits[10] = {
        "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
    };

    char token[10];
    int token_idx = 0;
    int output_idx = 0;

    for(int i = 0; morse[i] != '\0'; i++){
        if(morse[i] == ' '){
            if(token_idx > 0){
                token[token_idx] = '\0';

                int found = 0;
                for(int j = 0; j < 26; j++){
                    if(strcmp(token, morse_alphabet[j]) == 0){
                        output[output_idx++] = 'A' + j;
                        found = 1;
                        break;
                    }
                }

                if(!found){
                    for(int j = 0; j < 10; j++){
                        if(strcmp(token, morse_digits[j]) == 0){
                            output[output_idx++] = '0' + j;
                            break;
                        }
                    }
                }

                token_idx = 0;
            }
        } else {
            token[token_idx++] = morse[i];
        }
    }

    if(token_idx > 0){
        token[token_idx] = '\0';

        int found = 0;
        for(int j = 0; j < 26; j++){
            if(strcmp(token, morse_alphabet[j]) == 0){
                output[output_idx++] = 'A' + j;
                found = 1;
                break;
            }
        }

        if(!found){
            for(int j = 0; j < 10; j++){
                if(strcmp(token, morse_digits[j]) == 0){
                    output[output_idx++] = '0' + j;
                    break;
                }
            }
        }
    }

    output[output_idx] = '\0';
}

int is_morse_code_valid(const char morse[]){
    const char* morse_alphabet[26] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
        "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
        "..-", "...-", ".--", "-..-", "-.--", "--.."
    };

    const char* morse_digits[10] = {
        "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
    };

    char token[10];
    int token_idx = 0;

    for(int i = 0; morse[i] != '\0'; i++){
        if(morse[i] == ' '){
            if(token_idx > 0){
                token[token_idx] = '\0';

                int found = 0;
                for(int j = 0; j < 26; j++){
                    if(strcmp(token, morse_alphabet[j]) == 0){
                        found = 1;
                        break;
                    }
                }

                if(!found){
                    for(int j = 0; j < 10; j++){
                        if(strcmp(token, morse_digits[j]) == 0){
                            found = 1;
                            break;
                        }
                    }
                }

                if(!found){
                    return 0;
                }

                token_idx = 0;
            }
        } else if(morse[i] == '.' || morse[i] == '-'){
            token[token_idx++] = morse[i];
        } else {
            return 0;
        }
    }

    if(token_idx > 0){
        token[token_idx] = '\0';

        int found = 0;
        for(int j = 0; j < 26; j++){
            if(strcmp(token, morse_alphabet[j]) == 0){
                found = 1;
                break;
            }
        }

        if(!found){
            for(int j = 0; j < 10; j++){
                if(strcmp(token, morse_digits[j]) == 0){
                    found = 1;
                    break;
                }
            }
        }

        if(!found){
            return 0;
        }
    }

    return 1;
}
