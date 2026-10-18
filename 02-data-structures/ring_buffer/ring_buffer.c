#include <stdio.h>
#include "ring_buffer.h"

//成功返回0，失败返回-1
int rb_init(ring_buffer_t *rb,uint8_t *buffer,size_t capacity){
    if(rb == NULL || buffer == NULL ||capacity == 0){
        return -1;
    }
    rb->buffer = buffer;
    rb->capacity = capacity;

    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;

    return 0;
}

int rb_is_empty(const ring_buffer_t *rb){
    return (rb->count == 0);
}

int rb_is_full(const ring_buffer_t *rb){
    return (rb->count == rb->capacity);
}

int rb_write(ring_buffer_t *rb,uint8_t data){
    if(rb_is_full(rb)){
        printf("缓冲区已满！\n");
        return -1;
    }

    rb->buffer[rb->tail] = data;
    rb->tail = (rb->tail+1) % rb->capacity; //加1后取模，满足绕圈要求
    rb->count++;

    return 0;
}

int rb_read(ring_buffer_t *rb,uint8_t *data){
    if(rb_is_empty(rb)){
        printf("缓冲区为空！");
        return -1;
    }

    *data = rb->buffer[rb->head];
    rb->head = (rb->head + 1) % rb->capacity;
    rb->count--;
    return 0;
}