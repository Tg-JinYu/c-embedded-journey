#include <stdio.h>
#include "linked_list.h"

int main() {
    list_node_t *head = NULL;
    list_init(&head);
    
    printf("=== 测试开始 ===\n\n");

    // 1. 测试尾插和打印
    student_t s1 = {1, "张三"};
    student_t s2 = {2, "李四"};
    student_t s3 = {3, "王五"};
    
    list_insert_tail(&head, s1);
    list_insert_tail(&head, s2);
    list_insert_tail(&head, s3);
    
    printf("1. 尾插3个节点后: \n");
    list_print(head);
    
    // 2. 测试查找
    printf("\n2. 查找 id=2 的学生: ");
    list_node_t *find_node = list_find_node(head, 2);
    if (find_node) printf("找到了，名字是 %s\n", find_node->data.name);
    else printf("没找到\n");

    // 3. 测试删除中间节点
    printf("\n3. 删除 id=2 的节点后: \n");
    list_delete_node(&head, 2);
    list_print(head);

    // 4. 测试删除头节点
    printf("\n4. 删除头节点 id=1 后: \n");
    list_delete_node(&head, 1);
    list_print(head);

    // 5. 测试删除不存在的节点
    printf("\n5. 尝试删除不存在的 id=99: \n");
    list_delete_node(&head, 99);

    // 6. 销毁链表
    printf("\n6. 销毁链表...\n");
    list_free(&head);
    if (head == NULL) {
        printf("链表已彻底清空，head 已置为 NULL！\n");
    }

    printf("\n=== 测试结束 ===\n");
    return 0;
}