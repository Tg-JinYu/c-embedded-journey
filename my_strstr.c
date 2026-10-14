#include <stdio.h>
#include <string.h>

char *my_strstr(const char *p1,const char *p2){
    if(*p2 == '\0') return (char *)p1;
    
    const char *p1_start = p1;  //用于帮助p1回溯到检测前的位置
    const char *p2_start = p2;
    while(*p1_start != '\0'){
        p1 = p1_start;          //令p1指回到检测子串之前的位置
        p2 = p2_start;          //让p2指回到原本子串的开头
        while(*p2 == *p1 && *p1 !='\0' && *p2 != '\0'){
            p1++;
            p2++;
            if(*p2 == '\0'){
                return (char *)p1_start;    //返回首次找到子串时的地址
            }
        }
        p1_start++;
    }
    return NULL;
}

void test(const char *str1, const char *str2) {
    printf("主串: \"%s\", 子串: \"%s\"\n", str1, str2);
    char *std_res = strstr(str1, str2);
    char *my_res = my_strstr(str1, str2);

    printf("标准库: ");
    if (std_res) printf("找到，下标: %ld\n", std_res - str1); else printf("未找到 (NULL)\n");

    printf("手写库: ");
    if (my_res) printf("找到，下标: %ld\n", my_res - str1); else printf("未找到 (NULL)\n");

    printf("----------------------------------------\n");
}

int main() {
    test("hello world", "world");      // 普通查找
    test("hello world", "guet");       // 找不到
    test("hello", "");                 // 空子串
    test("", "a");                     // 主串为空
    test("aaaab", "aab");              // 重叠匹配
    test("hello world", "world");      // 结尾查找
    return 0;
}