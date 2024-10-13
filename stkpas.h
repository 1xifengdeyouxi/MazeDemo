#ifndef STKPAS_H
#define STKPAS_H

#include "base.h"
#include <stdlib.h>

// 链栈的节点定义，用于存储路径中的每个位置的坐标
typedef struct Node {
    int x, y;           // 迷宫中的位置坐标 (x, y)
    struct Node* next;  // 指向下一个节点的指针
} Node;

// 栈的定义，栈使用链表实现
typedef struct {
    Node* top;  // 指向栈顶的指针
} Stack;

// 初始化栈，将栈顶指针设置为NULL
void initStack(Stack* s) {
    s->top = NULL;
}

// 判断栈是否为空，栈顶为NULL则为空
int isEmpty(Stack* s) {
    return s->top == NULL;
}

// 压栈操作，创建新节点并将其放入栈顶
void push(Stack* s, int x, int y) {
    Node* node = (Node*)malloc(sizeof(Node)); // 动态分配内存创建新节点
    node->x = x;   // 存储当前位置的 x 坐标
    node->y = y;   // 存储当前位置的 y 坐标
    node->next = s->top;  // 新节点指向当前的栈顶
    s->top = node;        // 栈顶移动到新节点
}

// 弹栈操作，将栈顶的节点移除并释放内存
void pop(Stack* s) {
    if (!isEmpty(s)) {           // 先判断栈是否为空
        Node* temp = s->top;     // 临时保存栈顶节点
        s->top = s->top->next;   // 栈顶指向下一个节点
        free(temp);              // 释放被弹出的节点
    }
}

// 打印栈中的路径，逆序打印出路径的每个坐标
void printStack(Stack* s) {
    Node* current = s->top;
    Stack tempStack;  // 临时栈，用来逆序存储当前路径
    initStack(&tempStack);
    // 将当前栈内容压入临时栈中，逆序存储
    while (current) {
        push(&tempStack, current->x, current->y);
        current = current->next;
    }
    // 从临时栈中弹出并打印路径
    current = tempStack.top;
    while (current) {
        if (current->next != NULL) {
            printf("(%d, %d) -> ", current->x, current->y);  // 使用箭头连接路径
        }
        else {
            printf("(%d, %d)", current->x, current->y);  // 打印最后一个节点
        }
        current = current->next;
    }
    printf("\n");  // 完成路径打印后换行
}

// 复制栈内容，将源栈中的内容复制到目标栈中
void copyStack(Stack* dest, Stack* src) {
    Node* current = src->top;
    Stack tempStack;
    initStack(&tempStack);

    // 将源栈内容逆序存入临时栈
    while (current) {
        push(&tempStack, current->x, current->y);
        current = current->next;
    }

    // 将临时栈内容再复制到目标栈，以保持顺序
    current = tempStack.top;
    while (current) {
        push(dest, current->x, current->y);
        current = current->next;
    }
}

#endif // STKPAS_H