#include <stdio.h>
#include <string.h>

size_t my_strlen(const char *ch){
    const char *p = ch;
    while(*p != '\0'){
        p++;
    }

    return (size_t) (p - ch);
}

int main(){
    const char *ch = "Hello World!";
    size_t t1 = strlen(ch);
    size_t t2 = my_strlen(ch);

    printf("标准库： %zu\n",t1);
    printf("手写库： %zu\n",t2);
}