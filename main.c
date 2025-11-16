#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hangman.h"
#include "morse.h"

int main(){
    srand(time(NULL));

    char secret[20];
    if(get_word(secret) == 0){
        hangman(secret);
    }

    return 0;
}
