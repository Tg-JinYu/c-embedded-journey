#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct{
    int id;
    char name[20];
}student_t;

typedef struct list_node{
    student_t data;
    struct list_node *next;
}list_node_t;

//初始化链表
void list_init(list_node_t **head);

//创建新节点
list_node_t *list_create_node(student_t data);

//尾部插入
void list_insert_tail(list_node_t **head,student_t data);

//按照学号找节点
list_node_t *list_find_node(list_node_t *head,int id);

//删除对应学号的节点
void list_delete_node(list_node_t **head,int id);

//打印所有节点信息
void list_print(list_node_t *head);

//销毁链表
void list_free(list_node_t **head);

#endif