#include <stdio.h>
#include <string.h>

char *my_strcat(char *dest,const char *src){
    char *p = dest;
    while(*p != '\0'){
        p++;
    }
    while(*src != '\0'){
        *p = *src;
        p++;
        src++;
    }
    *p = '\0';

    return dest;
}

int main() {
    char dest1[50] = "Hello, "; 
    char dest2[50] = "Hello, "; 
    char src[] = "World!";

    printf("拼接前 dest: %s\n", dest1);
    printf("拼接前 src: %s\n", src);

    strcat(dest1, src);
    printf("标准库拼接后 dest: %s\n", dest1);
    my_strcat(dest2,src);
    printf("手写库拼接后 dest: %s\n", dest2);

    return 0;
}