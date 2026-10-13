#include <stdio.h>
#include <string.h>

int my_strcmp(const char *str1,const char *str2){
    while(*str1 && (*str1 == *str2)){//前半部分的判断是防止两者相同时陷入死循环，后半部分足以应对大部分情况
        str1++;
        str2++;
    }

    return (*str1 - *str2);//返回两者指向的字符的ASCII值的差值
}

int main(){
    const char *str1 = "apple";
    const char *str2 = "apple";
    printf("两段字符串分别为：%s,%s\n",str1,str2);

    printf("以下是标准库输出：\n");
    if(strcmp(str1,str2)==0){
        printf("两者相等。\n");
    }else if(strcmp(str1,str2)<0){
        printf("str1 小于 str2。\n");
    }else{
        printf("str1 大于 str2。\n");
    }

    printf("以下是手写库输出：\n");
    if(my_strcmp(str1,str2)==0){
        printf("两者相等。\n");
    }else if(my_strcmp(str1,str2)<0){
        printf("str1 小于 str2。\n");
    }else{
        printf("str1 大于 str2。\n");
    }

    return 0;
}