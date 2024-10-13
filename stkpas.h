#ifndef STKPAS_H
#define STKPAS_H

#include "base.h"
#include <stdlib.h>

// ��ջ�Ľڵ㶨�壬���ڴ洢·���е�ÿ��λ�õ�����
typedef struct Node {
    int x, y;           // �Թ��е�λ������ (x, y)
    struct Node* next;  // ָ����һ���ڵ��ָ��
} Node;

// ջ�Ķ��壬ջʹ������ʵ��
typedef struct {
    Node* top;  // ָ��ջ����ָ��
} Stack;

// ��ʼ��ջ����ջ��ָ������ΪNULL
void initStack(Stack* s) {
    s->top = NULL;
}

// �ж�ջ�Ƿ�Ϊ�գ�ջ��ΪNULL��Ϊ��
int isEmpty(Stack* s) {
    return s->top == NULL;
}

// ѹջ�����������½ڵ㲢�������ջ��
void push(Stack* s, int x, int y) {
    Node* node = (Node*)malloc(sizeof(Node)); // ��̬�����ڴ洴���½ڵ�
    node->x = x;   // �洢��ǰλ�õ� x ����
    node->y = y;   // �洢��ǰλ�õ� y ����
    node->next = s->top;  // �½ڵ�ָ��ǰ��ջ��
    s->top = node;        // ջ���ƶ����½ڵ�
}

// ��ջ��������ջ���Ľڵ��Ƴ����ͷ��ڴ�
void pop(Stack* s) {
    if (!isEmpty(s)) {           // ���ж�ջ�Ƿ�Ϊ��
        Node* temp = s->top;     // ��ʱ����ջ���ڵ�
        s->top = s->top->next;   // ջ��ָ����һ���ڵ�
        free(temp);              // �ͷű������Ľڵ�
    }
}

// ��ӡջ�е�·���������ӡ��·����ÿ������
void printStack(Stack* s) {
    Node* current = s->top;
    Stack tempStack;  // ��ʱջ����������洢��ǰ·��
    initStack(&tempStack);
    // ����ǰջ����ѹ����ʱջ�У�����洢
    while (current) {
        push(&tempStack, current->x, current->y);
        current = current->next;
    }
    // ����ʱջ�е�������ӡ·��
    current = tempStack.top;
    while (current) {
        if (current->next != NULL) {
            printf("(%d, %d) -> ", current->x, current->y);  // ʹ�ü�ͷ����·��
        }
        else {
            printf("(%d, %d)", current->x, current->y);  // ��ӡ���һ���ڵ�
        }
        current = current->next;
    }
    printf("\n");  // ���·����ӡ����
}

// ����ջ���ݣ���Դջ�е����ݸ��Ƶ�Ŀ��ջ��
void copyStack(Stack* dest, Stack* src) {
    Node* current = src->top;
    Stack tempStack;
    initStack(&tempStack);

    // ��Դջ�������������ʱջ
    while (current) {
        push(&tempStack, current->x, current->y);
        current = current->next;
    }

    // ����ʱջ�����ٸ��Ƶ�Ŀ��ջ���Ա���˳��
    current = tempStack.top;
    while (current) {
        push(dest, current->x, current->y);
        current = current->next;
    }
}

#endif // STKPAS_H