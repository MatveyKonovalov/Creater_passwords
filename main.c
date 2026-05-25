#include <stdio.h>
#include "create_passwords.h"
#include <stdlib.h>

void get_password_digit(){
    int d;
    printf("Введите количество чисел в пароле: ");
    scanf("%d", &d);

    char filename[100];
    sprintf(filename, "digit_password_%d.txt", d);
    password_digit(d, filename);
    printf("Сохранено в файл digit_password_%d.txt\n\n", d);
}
void get_data(){
    password_data("input_data.txt");
    printf("Готово\n\n");
}

void check_my_password(){
    char *s = (char*) malloc(sizeof(char) * 100);
    for (int i = 0; i < 100; ++i)
        s[i] = '\0';
    printf("Введите ваш пароль: ");
    scanf("%s", s);

    int ans = check_password(s);
    free(s);
    switch (ans){
        case 1:
            printf("Пароль надёжный\n\n");
            break;
        case 0:
            printf("Пароль не надёжный\n\n");
            break;
    }
}
void menu(){
    printf("1 - создать пароль из чисел какой-то длины\n");
    printf("2 - создать пароль из дат\n");
    printf("3 - проверить пароль на надёжность\n");
    printf("4 - показать меню\n");
    printf("5 - выйти из программы\n\n");
}
int main(){
    printf("====================================\n");
    printf("          %s\n", "Оператор паролей");
    printf("====================================\n");
    printf("%20s\n", "Меню");
    menu();

    int option;
    printf("Введите опцию: ");
    scanf("%d", &option);

    while (1){
        switch(option){
            case 1:
                get_password_digit();
                break;
            case 2:
                get_data();
                break;
            case 3:
                check_my_password();
                break;
            case 4:
                menu();
                break;
            case 5:
                printf("До свидания\n");
                return 0;
            default:
                printf("Некорректный выбор опции\n\n");
                menu();
                break;
        }
        printf("Введите следующую опцию: ");
        scanf("%d", &option);
    }
    
    return 0;
}