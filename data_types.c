#include "data_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSWORD_MAX_LEN 100
#define SERVICE_MAX_LEN 100

static void* xmalloc(size_t size){
    void* result = malloc(size);
    if (!result){
        printf("Ошибка при выделении памяти");
        exit(EXIT_FAILURE);
    }
    return result;
}

static void free_record_list(record_list* cur){
    if (!cur) return;
    if(cur->value){
        free(cur->value->password);
        free(cur->value->service_name);
        free(cur->value);
    }
    free(cur);
}

static record_list* create_record(const char* service_name, const char* password){
    record_list* new_node = xmalloc(sizeof(record_list));
    record* new_record = xmalloc(sizeof(record));

    new_record->password = xmalloc(sizeof(char) * (PASSWORD_MAX_LEN + 1));
    new_record->service_name = xmalloc(sizeof(char) * (SERVICE_MAX_LEN + 1));

    strncpy(new_record->password, password, PASSWORD_MAX_LEN);
    new_record->password[PASSWORD_MAX_LEN] = '\0';

    strncpy(new_record->service_name, service_name, SERVICE_MAX_LEN);
    new_record->service_name[SERVICE_MAX_LEN] = '\0';

    new_node->value = new_record;
    new_node->next = NULL;
    
    return new_node;
}

record_list* get_record(const char* service_name, record_list* head){
    while (head){
        if (strcmp(head->value->service_name, service_name) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

record_list* add_record(const char* service_name, const char* password, record_list* head){
    record_list* new_node = create_record(service_name, password);

    new_node->next = head;
    return new_node;
}

record_list* delete_record(const char* service_name, record_list* head){
    if (!head) return NULL;

    if (strcmp(head->value->service_name, service_name) == 0){
        record_list* new_head = head->next;
        free_record_list(head);
        return new_head;
    }

    record_list* cur = head;

    while (cur->next){
        if (strcmp(cur->next->value->service_name,service_name) == 0){
            record_list* tmp = cur->next;
            cur->next = cur->next->next;
    
            free_record_list(tmp);
            break;
        }
        cur = cur->next;
    }
    return head;
}

void print_all_records(record_list* head){
    if (!head){
        printf("Записи отсутствуют\n");
        return;
    }
    printf("Вывод всех записей:\n");
    while (head){
        printf("Имя сервиса: %s\n", head->value->service_name);
        printf("Пароль: %s\n\n", head->value->password);
        head = head->next;
    }
}

void save_in_file(record_list* head, const char* name){
    FILE* f = fopen(name, "w");
    if (!f){
        printf("Нет файла в текущей директории\n");
        return;
    }
    
    while(head){
        fprintf(f, "service_name: %s\npassword: %s\n\n", head->value->service_name, head->value->password);
        head = head->next;
    }
    fclose(f);

    printf("Сохранение прошло успешно");
}

record_list* load_records(const char* name){
    FILE* f = fopen(name, "r");
    if (!f){
        printf("Нет файла в текущей директории\n");
        return NULL;
    }

    record_list* head = NULL;
    char service_name[SERVICE_MAX_LEN + 1];
    char password[PASSWORD_MAX_LEN + 1];
    char line[256];
    
    while (fgets(line, sizeof(line), f)) {
        // Ищем строку с service_name
        if (strncmp(line, "service_name: ", 14) == 0) {
            
            char *name_start = line + 14;
            name_start[strcspn(name_start, "\n")] = '\0';
            strncpy(service_name, name_start, SERVICE_MAX_LEN);
            service_name[SERVICE_MAX_LEN] = '\0';
            
            if (fgets(line, sizeof(line), f)) {
                if (strncmp(line, "password: ", 10) == 0) {
                    char *pass_start = line + 10;
                    pass_start[strcspn(pass_start, "\n")] = '\0';
                    strncpy(password, pass_start, PASSWORD_MAX_LEN);
                    password[PASSWORD_MAX_LEN] = '\0';
                    
                    head = add_record(service_name, password, head);
                    
                    fgets(line, sizeof(line), f);
                }
            }
        }
    }
    
    fclose(f);
    printf("Загрузка завершена\n");
    return head;
}