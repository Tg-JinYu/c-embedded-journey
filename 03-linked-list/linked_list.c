#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

void list_init(list_node_t **head){
    *head = NULL;//让头指针指向空，让它有所指向，不被判定为野指针
}

list_node_t *list_create_node(student_t data){
    list_node_t *new_node = (list_node_t *)malloc(sizeof(list_node_t));

    if(new_node == NULL) return NULL;//内存满了，创建失败

    new_node->data = data;

    new_node->next =NULL;

    return new_node;//返回的是该节点的地址
}

void list_insert_tail(list_node_t **head,student_t data){
    list_node_t *new_node = list_create_node(data);
    if(*head == NULL){
        *head = new_node;
        return;
    }

    list_node_t *p = *head;
    while(p->next != NULL){
        p = p->next;
    }

    p->next = new_node;
}

list_node_t *list_find_node(list_node_t *head,int id){
    if(head == NULL) return NULL;
    list_node_t *p = head;

    while(p->data.id != id && p->next != NULL){
        p = p->next;
    }
    if(p->data.id == id) return p;
    
    printf("未找到对应节点！");
    return NULL;
}

void list_delete_node(list_node_t **head,int id){
    if(*head == NULL){ 
        printf("空链表无法进行删除操作！");
        return;//传入空链表直接终止
    }
    list_node_t *prev = NULL;
    list_node_t *curr = *head;

    while(curr->next != NULL && curr->data.id != id){
        prev = curr;
        curr = curr->next;
    }

    if(curr->next == NULL && curr->data.id != id){ 
        printf("未找到对应节点，删除失败！");
        return;
    }
    if(curr == *head){
        *head = curr->next;
        free(curr);
        return;
    }

    prev->next = curr->next;
    free(curr);
}

void list_print(list_node_t *head){
    if(head == NULL){
        printf("链表为空！");
        return;
    }
    
    list_node_t *p = head;

    while(p->next != NULL){
        printf(" id:%d,学生名字：%s ->\n",p->data.id,p->data.name);
        p = p->next;
    }
    printf(" id:%d,学生名字：%s",p->data.id,p->data.name);
}

void list_free(list_node_t **head){
    if(*head == NULL) return;
    
    list_node_t *p = *head;

    while(p != NULL){
        list_node_t *curr = p->next;
        free(p);
        p = curr;
    }
    *head = NULL;
}