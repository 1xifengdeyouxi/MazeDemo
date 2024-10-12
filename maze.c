#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 7 // �����Թ��Ĵ�С��7��7��

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

// ��������Թ���pathProbability ����ͨ·���ɵĸ���
void generateMaze(int maze[SIZE][SIZE], float pathProbability) {
    srand(time(0));  // ʹ�õ�ǰʱ�������������
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // ���ݸ�������ͨ·��0�����ϰ���1��
            maze[i][j] = (rand() / (float)RAND_MAX) < pathProbability ? 0 : 1;
        }
    }
    // ǿ�����������յ�Ϊͨ·
    maze[0][0] = 0;
    maze[SIZE - 1][SIZE - 1] = 0;
    // ȷ�������յ����Χ��ͨ·�����ӿ�ͨ�еĸ���
    maze[0][1] = 0;
    maze[1][0] = 0;
    maze[SIZE - 1][SIZE - 2] = 0;
    maze[SIZE - 2][SIZE - 1] = 0;
}

// ��ӡ�Թ��ĺ������ò�ͬ��ɫ��ʾͨ·���ϰ�
void printMaze(int maze[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        // ��ӡ�Թ��ķ�����
        for (int j = 0; j < SIZE; j++) {
            if (maze[i][j] == 0) {
                printf("\033[44m  \033[0m"); // ��ɫС���飨ͨ·��
            }
            else {
                printf("\033[41m  \033[0m"); // ��ɫС���飨�ϰ���
            }
            if (j < SIZE - 1) {
                printf("|"); // ʹ������ '|' ��Ϊ���
            }
        }
        printf("\n");

        // ��ӡ�ָ��ߣ������Ӿ���������֮��ķָ�
        if (i < SIZE - 1) {
            for (int j = 0; j < SIZE; j++) {
                printf("--");  // ÿ�����������ӡ '--' ��ʾ�ָ���
                if (j < SIZE - 1) {
                    printf("+");  // ʹ�üӺ� '+' �ָ�������
                }
            }
            printf("\n");
        }
    }
}

// �ĸ�������ƶ��������ҡ��¡����ϣ�
int directions[4][2] = { {0,  1}, {1,  0}, {0,  -1}, {-1, 0} };

// ��¼�Թ���ÿ��λ���Ƿ���ʹ�
int visited[SIZE][SIZE] = { 0 };

// ������¼���·����ջ
Stack bestPath;

// ��¼���·���ĳ��ȣ���ʼֵ����Ϊһ���ϴ��ֵ
int minPathLength = SIZE * SIZE + 1;

// �ݹ���ݷ�Ѱ������·��
void findPaths(int maze[SIZE][SIZE], Stack* path, int x, int y, int endX, int endY, int pathLength) {
    // ��������յ㣬���·��
    if (x == endX && y == endY) {
        printf("ͨ·: ");
        printStack(path);

        // �������·��
        if (pathLength < minPathLength) {
            minPathLength = pathLength;
            while (!isEmpty(&bestPath)) {
                pop(&bestPath);  // ������·��ջ
            }
            copyStack(&bestPath, path);  // ����ǰ·�����Ƶ����·��ջ
        }
        return;
    }

    // �����ĸ������ƶ�
    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];

        // �����λ���Ƿ����Թ��ڡ��Ƿ���ͨ·��δ���ʹ�
        if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE && maze[newX][newY] == 0 && !visited[newX][newY]) {
            visited[newX][newY] = 1;   // ��ǵ�ǰλ��Ϊ�ѷ���
            push(path, newX, newY);    // ����λ��ѹ��·��ջ
            findPaths(maze, path, newX, newY, endX, endY, pathLength + 1);  // �ݹ�����
            pop(path);  // ���ݣ��Ƴ��ղż����·���ڵ�
            visited[newX][newY] = 0;   // ȡ�����ʱ�ǣ���������·��̽��
        }
    }
}

int main() {
    int maze[SIZE][SIZE];  // �����Թ�����
    generateMaze(maze, 0.6);  // ��������Թ���ͨ·�ĸ���
    printf("��������Թ�:\n");
    printMaze(maze);  // ��ӡ���ɵ��Թ�

    Stack path;
    initStack(&path);
    initStack(&bestPath);

    visited[0][0] = 1;  // ������Ϊ�ѷ���
    push(&path, 0, 0);  // �����ѹ��·��ջ

    // ��ʼѰ�����д���㵽�յ��·��
    findPaths(maze, &path, 0, 0, SIZE - 1, SIZE - 1, 1);

    // ������·��
    if (!isEmpty(&bestPath)) {
        printf("���ͨ·: ");
        printStack(&bestPath);
    }
    else {
        printf("���Թ���ͨ·\n");
    }

    return 0;
}
