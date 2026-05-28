#include <stdio.h>
#include <stdlib.h>
#include "create_passwords.h"
#include "data_types.h"


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

record_list* add_password(record_list* head){
    char password[PASSWORD_MAX_LEN + 1];
    char service_name[SERVICE_MAX_LEN + 1];

    printf("Введите название сервиса: ");
    scanf("%100s", service_name);
    printf("Введите пароль: ");
    scanf("%100s", password);

    head = add_record(service_name, password, head);
    return head;
}

record_list* delete_password(record_list* head){
    char service_name[SERVICE_MAX_LEN + 1];
    printf("Введите имя сервиса в удаляемой записи: ");
    scanf("%100s", service_name);

    head = delete_record(service_name, head);
    return head;
}

void save_list(record_list* head){
    char file_name[100];
    printf("Введите имя файла, в который нужно сохранить: ");

    scanf("%100s", file_name);
    save_in_file(head, file_name);
}

record_list* load_list(record_list* head){
    char file_name[100];
    printf("Введите имя файла, из которого нужно загрузить: ");
    scanf("%100s", file_name);

    record_list* data = load_records(file_name), *cur = head;

    if (!cur){
        return data;
    }
    while(cur->next){
        cur = cur->next;
    }
    cur->next = data;
    return head;
}

void menu(){
    printf("1 - создать пароль из чисел какой-то длины\n");
    printf("2 - создать пароль из дат\n");
    printf("3 - проверить пароль на надёжность\n");
    printf("4 - добавить запись с паролем\n");
    printf("5 - удалить запись с паролем\n");
    printf("6 - сохранить список паролей в файл\n");
    printf("7 - загрузить из файла список паролей\n");
    printf("8 - показать меню\n");
    printf("9 - показать весь список паролей\n");
    printf("10 - выйти из программы\n\n");
}

int main(){
    printf("====================================\n");
    printf("          %s\n", "Оператор паролей");
    printf("====================================\n");
    printf("%20s\n", "Меню");
    menu();

    int option;
    record_list* head = NULL;

    while (1){

        printf("\nВведите опцию: ");
        if (scanf("%d", &option) != 1) {
            printf("Ошибка: введите число\n");
            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');


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
                head = add_password(head);
                break;
            case 5:
                head = delete_password(head);
                break;
            case 6:
                save_list(head);
                break;
            case 7:
                head = load_list(head);
                break;
            case 8:
                menu();
                break;
            case 9:
                print_all_records(head);
                break;
            case 10:
                printf("До свидания\n");
                return 0;
            default:
                printf("Некорректный выбор опции\n\n");
                menu();
                break;
        }
    }
    
    return 0;
}