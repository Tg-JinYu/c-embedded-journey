#include <stdio.h>
#include <string.h>

void *my_memmove(void *dest,const void *src,size_t n){
    if(n == 0 || dest == src)return dest;
    char *pDest = (char *)dest;
    const char *pSrc = (const char *)src;//初始化指针
    if(pDest < pSrc){//若dest的地址在src的左边，则正序拷贝
        for(size_t i = 0;i < n ; i++){
            *pDest++ = *pSrc++;
        }
    }else{//若在右侧,则重新给两个指针赋值到指定拷贝的地址处，倒序拷贝
        pDest = (char *)dest + n-1;//这里就可以直接赋值了，注意别加*。
        pSrc = (const char *)src + n-1;//注：char *变量可以赋值给const char *,但是反过来不行。
        for(size_t i = 0;i < n ; i++){
            *pDest-- = *pSrc--;
        }
    }

    return dest;
}

//打印数组内容，方便观察
void print_arr(const char *label, const char *arr, int len) {
    printf("%s: ", label);
    for (int i = 0; i < len; i++) {
        printf("%c", arr[i]);
    }
    printf("\n");
}

int main() {
    // ========================
    // 测试 1：非重叠区域拷贝
    // ========================
    printf("=== 测试 1：非重叠拷贝 ===\n");
    char src1[] = "HelloWorld";
    char dest1_std[20] = {0};
    char dest1_my[20] = {0};

    memmove(dest1_std, src1, 10);
    my_memmove(dest1_my, src1, 10);

    printf("标准库: %s\n", dest1_std);
    printf("手写库: %s\n", dest1_my);
    printf("是否一致: %s\n\n", strcmp(dest1_std, dest1_my) == 0 ? "✅" : "❌");

    // ========================
    // 测试 2：内存重叠——dest > src（需要从右往左拷贝）
    // 这是 memmove 与 memcpy 的核心区别！
    // ========================
    printf("=== 测试 2：重叠 (dest > src) ===\n");
    char s1_std[] = "hello";
    char s1_my[]  = "hello";

    // 把 s[0]~s[3] 拷到 s[1]~s[4]
    // 正确结果应该是 "hhell"（往右拷贝时如果不小心会变成 "hhhhh" 之类）
    memmove(s1_std + 1, s1_std, 4);
    my_memmove(s1_my + 1, s1_my, 4);

    printf("标准库: %s\n", s1_std);
    printf("手写库: %s\n", s1_my);
    printf("是否一致: %s\n\n", strcmp(s1_std, s1_my) == 0 ? "✅" : "❌");

    // ========================
    // 测试 3：内存重叠——dest < src（从左往右拷贝即可）
    // ========================
    printf("=== 测试 3：重叠 (dest < src) ===\n");
    char s2_std[] = "hello";
    char s2_my[]  = "hello";

    // 把 s[1]~s[4] 拷到 s[0]~s[3]
    // 正确结果应该是 "elllo"
    memmove(s2_std, s2_std + 1, 4);
    my_memmove(s2_my, s2_my + 1, 4);

    printf("标准库: %s\n", s2_std);
    printf("手写库: %s\n", s2_my);
    printf("是否一致: %s\n\n", strcmp(s2_std, s2_my) == 0 ? "✅" : "❌");

    // ========================
    // 测试 4：n = 0（零字节拷贝）
    // ========================
    printf("=== 测试 4：n = 0 ===\n");
    char s3_std[] = "hello";
    char s3_my[]  = "hello";

    memmove(s3_std, s3_std + 1, 0);
    my_memmove(s3_my, s3_my + 1, 0);

    printf("标准库: %s\n", s3_std);
    printf("手写库: %s\n", s3_my);
    printf("是否一致: %s\n\n", strcmp(s3_std, s3_my) == 0 ? "✅" : "❌");

    // ========================
    // 测试 5：dest == src（自己拷自己）
    // ========================
    printf("=== 测试 5：dest == src ===\n");
    char s4_std[] = "hello";
    char s4_my[]  = "hello";

    memmove(s4_std, s4_std, 5);
    my_memmove(s4_my, s4_my, 5);

    printf("标准库: %s\n", s4_std);
    printf("手写库: %s\n", s4_my);
    printf("是否一致: %s\n\n", strcmp(s4_std, s4_my) == 0 ? "✅" : "❌");

    // ========================
    // 测试 6：整数数组重叠（验证 void * 的通用性）
    // ========================
    printf("=== 测试 6：整数数组重叠 ===\n");
    int arr_std[5] = {1, 2, 3, 4, 5};
    int arr_my[5]  = {1, 2, 3, 4, 5};

    // 把前 3 个整数搬到后 3 个位置（重叠，dest > src）
    memmove(arr_std + 2, arr_std, 3 * sizeof(int));
    my_memmove(arr_my + 2, arr_my, 3 * sizeof(int));

    printf("标准库: ");
    for (int i = 0; i < 5; i++) printf("%d ", arr_std[i]);
    printf("\n手写库: ");
    for (int i = 0; i < 5; i++) printf("%d ", arr_my[i]);
    printf("\n");

    int ok = 1;
    for (int i = 0; i < 5; i++) {
        if (arr_std[i] != arr_my[i]) { ok = 0; break; }
    }
    printf("是否一致: %s\n", ok ? "✅" : "❌");

    return 0;
}