#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include <stddef.h>

typedef struct{
    uint8_t *buffer;//指针指向存放数据的数组——此处用uint8-t，保证整数大小为1字节（1字节 = 8字）
    size_t capacity;//缓冲区的总大小
    size_t count;   //记录当前存了多少字节
    size_t head;    //读指针位置
    size_t tail;    //写指针位置
}ring_buffer_t;

//初始化队列
int rb_init(ring_buffer_t *rb,uint8_t *buffer,size_t capacity);

//判空和判满
int rb_is_empty(const ring_buffer_t *rb);
int rb_is_full(const ring_buffer_t *rb);

//写入数据
int rb_write(ring_buffer_t *rb,uint8_t data);

//读取数据
int rb_read(ring_buffer_t *rb,uint8_t *data);

#endif