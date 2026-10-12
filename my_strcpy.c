#include <stdio.h>
#include <string.h>

char *my_strcpy(char *result,const char *ch){
    if (result == NULL || ch == NULL) return NULL;
    
    char *p = result;//使p指向result的内存空间，这样*p改变，result对应的空间内容也会变。

    while(*ch != '\0'){
        *p = *ch;//让p指向的内存地址的内容变为ch指向的内存的内容
        p++;
        ch++;
    }
    *p = '\0';
    return result;
}

int main(){
    const char *ch = "Hello";
    char temp1[20],temp2[20];
    printf("原字符串为：%s\n",ch);

    strcpy(temp1,ch);
    printf("标准库输出：%s\n",temp1);

    my_strcpy(temp2,ch);
    printf("手写库输出：%s\n",temp2);

    return 0;
}