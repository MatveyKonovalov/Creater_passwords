#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "create_passwords.h"

void password_digit(int len, char* name){
    FILE* f = fopen(name, "w");
    if (!f) return;

    for(long int i = 0; i < (long int) pow(10, len); ++i){
        fprintf(f, "%0*ld\n", len, i);
    }
    fclose(f);
}

void password_data(char* name){
    //"30.06.2007"
    FILE* f = fopen(name, "w");
    if (!f) return;

    for (int year = 2026; year >= 0; --year){
        for (int month = 1; month <= 12; ++month){
            for (int day = 1; day <= 31; ++day){
                fprintf(f, "%02d.%02d.%04d\n", day, month, year);
            }
        }
    }
}

int check_password(char *password){
    if (!password) return 0;
    password_an data = {0, 0, 0, 0};

    int criter = 3;
    int cnt = 0;
    int i = 0;
    while(password[i] != '\0'){
        char b = password[i];
        if (isalpha(b)){
            if (isupper(b)){
                data.upper++;
            } else{
                data.lower++;
            }
        } else if(isdigit(b)){
            data.digit++;
        } else{
            data.zn ++;
        }
        i ++;
        cnt ++;
    }
    
    int sm = (data.digit > 0) + (data.lower > 0) + (data.upper > 0) + (data.zn > 0);
    if (sm >= criter && cnt >= 8){
        //printf("%d %d\n", sm, cnt);
        return 1;
    } else{
        return 0;
    }

}