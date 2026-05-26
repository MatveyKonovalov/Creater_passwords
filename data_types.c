#include "data_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSWORD_MAX_LEN 25
#define SERVICE_MAX_LEN 25

static void* xmalloc(int size){
    void* result = malloc(size);
    if (!result){
        printf("Memory error");
        exit(1);
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
    record_list* new_node = (record_list*) xmalloc(sizeof(record_list));
    record* new_record = (record* ) xmalloc(sizeof(record));

    new_record->password = (char*) xmalloc(sizeof(char) * (PASSWORD_MAX_LEN + 1));
    new_record->service_name = (char*) xmalloc(sizeof(char) * (SERVICE_MAX_LEN + 1));

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
        if (cur->next && strcmp(cur->next->value->service_name,service_name) == 0){
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