#include <stdio.h>
#include <string.h>

void *my_memcpy(void *dest,const void *src,size_t n){
    if(n == 0 || dest == src)return dest;
    
    char *pDest = (char *)dest;//转化为char指针，使数据一字节一字节地输入
    const char *pSrc = (const char *)src;//原理同上
    for(size_t i = 0;i < n;i++){
        *pDest = *pSrc;//可简化为*pDest++ = *pSrc++;
        pDest++;
        pSrc++;
    }
    
    return dest;
}

int main() {
    // 测试 1：拷贝字符数组
    char src1[] = "Hello";
    char dest1_std[20] = {0};
    char dest1_my[20] = {0};

    memcpy(dest1_std, src1, 5);
    dest1_std[5] = '\0';
    my_memcpy(dest1_my, src1, 5);
    dest1_my[5] = '\0';
    printf("字符拷贝:\n");
    printf("  标准库: %s\n", dest1_std);
    printf("  手写库: %s\n", dest1_my);
    printf("  是否一致: %s\n\n", strcmp(dest1_std, dest1_my) == 0 ? "✅" : "❌");

    // 测试 2：拷贝整数数组（整体）
    int src2[3] = {1, 2, 3};
    int dest2_std[3] = {0};
    int dest2_my[3] = {0};

    memcpy(dest2_std, src2, sizeof(src2));
    my_memcpy(dest2_my, src2, sizeof(src2));
    printf("整数拷贝:\n");
    printf("  标准库: %d, %d, %d\n", dest2_std[0], dest2_std[1], dest2_std[2]);
    printf("  手写库: %d, %d, %d\n", dest2_my[0], dest2_my[1], dest2_my[2]);
    printf("  是否一致: %s\n\n",
           (dest2_std[0] == dest2_my[0] &&
            dest2_std[1] == dest2_my[1] &&
            dest2_std[2] == dest2_my[2]) ? "✅" : "❌");

    // 测试 3：部分拷贝（只拷贝前两个整数）
    int dest3_std[3] = {0};
    int dest3_my[3] = {0};

    memcpy(dest3_std, src2, 2 * sizeof(int));
    my_memcpy(dest3_my, src2, 2 * sizeof(int));
    printf("部分拷贝:\n");
    printf("  标准库: %d, %d, %d\n", dest3_std[0], dest3_std[1], dest3_std[2]);
    printf("  手写库: %d, %d, %d\n", dest3_my[0], dest3_my[1], dest3_my[2]);
    printf("  是否一致: %s\n",
           (dest3_std[0] == dest3_my[0] &&
            dest3_std[1] == dest3_my[1] &&
            dest3_std[2] == dest3_my[2]) ? "✅" : "❌");

    return 0;
}