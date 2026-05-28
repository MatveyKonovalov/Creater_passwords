#ifndef DATA_TYPES
#define DATA_TYPES

/*Структуры для сохранения записи в файл*/
typedef struct Record{
    char* service_name;
    char* password;
} record;

typedef struct Record_List{
    record* value;
    struct Record_List* next;
} record_list;

/*Функции для работы со списками*/
record_list* get_record(const char* service_name, record_list* head);
record_list* add_record(const char* service_name, const char* password, record_list* head);
record_list* delete_record(const char* service_name, record_list* head);
void print_all_records(record_list* head);

/*Работа с файлами*/
record_list* load_records(const char* name);
void save_in_file(record_list* head, const char* name);

#endif