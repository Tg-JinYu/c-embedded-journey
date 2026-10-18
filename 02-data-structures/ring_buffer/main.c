#include <stdio.h>
#include "ring_buffer.h" 

int main() {
    // 1. 准备底层物理空间（容量为 5）
    uint8_t memory[5];
    
    // 2. 定义并初始化环形缓冲区
    ring_buffer_t rb;
    rb_init(&rb, memory, 5);
    
    printf("=== 测试开始 ===\n\n");

    // --- 场景 1：尝试读空缓冲区 ---
    printf("1. 尝试读空缓冲区:\n");
    uint8_t temp_data = 0;
    if (rb_read(&rb, &temp_data) == -1) {
        printf("读取失败（预料之中）\n\n");
    }

    // --- 场景 2：写入 3 个数据，读取 1 个 ---
    printf("2. 连续写入 'A', 'B', 'C':\n");
    rb_write(&rb, 'A');
    rb_write(&rb, 'B');
    rb_write(&rb, 'C');
    printf("当前缓存数量: %zu\n", rb.count); // 应该是 3
    
    rb_read(&rb, &temp_data);
    printf("读取了一个数据: %c (应为 A)\n", temp_data);
    printf("当前缓存数量: %zu\n\n", rb.count); // 应该是 2 (B, C)

    // --- 场景 3：触发绕圈（核心难点） ---
    printf("3. 触发绕圈测试:\n");
    // 现在 B 和 C 占着前面的位置，我们继续塞，直到塞满（容量5）
    printf("继续写入 'D', 'E', 'F', 'G' (会塞满):\n");
    rb_write(&rb, 'D');
    rb_write(&rb, 'E');
    rb_write(&rb, 'F');
    rb_write(&rb, 'G'); // 到这里应该满了，因为有 B,C,D,E,F 五个数据
    rb_write(&rb, 'H'); // 这个应该会触发“满”的错误

    // 读取 3 个数据，把前面的位置腾出来
    printf("连续读取 3 个数据: ");
    for(int i = 0; i < 3; i++) {
        rb_read(&rb, &temp_data);
        printf("%c ", temp_data);
    }
    printf("(应为 B C D)\n");

    // 现在 head 已经跑到中间了，tail 在末尾。我们继续写，触发 tail 绕回数组头部
    printf("再写入 'X', 'Y' (触发 tail 绕回开头):\n");
    rb_write(&rb, 'X'); // 此时 tail 会回到数组下标 0 的位置
    rb_write(&rb, 'Y'); 

    // 把剩下的全读出来，看顺序对不对
    printf("把剩余数据全读出: ");
    while (rb_read(&rb, &temp_data) == 0) {
        printf("%c ", temp_data);
    }
    printf("(应为 E F X Y)\n\n");

    printf("=== 测试结束 ===\n");
    return 0;
}