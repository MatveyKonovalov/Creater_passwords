#ifndef CREATE_PASSWORD
#define CREATE_PASSWORD


#define PASSWORD_MAX_LEN 100
#define SERVICE_MAX_LEN 100

void password_digit(int len, char* name);
void password_data(char* name);
int check_password(char *password);

typedef struct Node{
    int digit;
    int lower;
    int upper;
    int zn;
} password_an;

#endif