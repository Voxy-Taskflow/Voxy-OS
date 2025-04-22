#include <strings.h>

int strings_equal(const char* a, const char* b){
    while (*a && *b)
    {
        if(*a != *b)return 0;
        a++;
        b++;
    }
    return *a == *b;
}

int strlen(const char* a){
    int len = 0;
    while (*a ++) len++;
    return len;
}
void strcpy(char* dest, const char* src){
    while (*src){
        *dest++ = *src++;
        *dest = '\0';
    }
}
void strcat(char* dest, const char* src){
    while(*dest) dest++;
    while(*src){
        *dest++ = *src++;
    }
    *dest = '\0';
}