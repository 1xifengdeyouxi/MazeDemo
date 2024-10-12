#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 7 // 定义迷宫的大小（7×7）

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

// 随机生成迷宫，pathProbability 控制通路生成的概率
void generateMaze(int maze[SIZE][SIZE], float pathProbability) {
    srand(time(0));  // 使用当前时间设置随机种子
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // 根据概率生成通路（0）或障碍（1）
            maze[i][j] = (rand() / (float)RAND_MAX) < pathProbability ? 0 : 1;
        }
    }
    // 强制设置起点和终点为通路
    maze[0][0] = 0;
    maze[SIZE - 1][SIZE - 1] = 0;
    // 确保起点和终点的周围有通路，增加可通行的概率
    maze[0][1] = 0;
    maze[1][0] = 0;
    maze[SIZE - 1][SIZE - 2] = 0;
    maze[SIZE - 2][SIZE - 1] = 0;
}

// 打印迷宫的函数，用不同颜色显示通路和障碍
void printMaze(int maze[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        // 打印迷宫的方块行
        for (int j = 0; j < SIZE; j++) {
            if (maze[i][j] == 0) {
                printf("\033[44m  \033[0m"); // 蓝色小方块（通路）
            }
            else {
                printf("\033[41m  \033[0m"); // 红色小方块（障碍）
            }
            if (j < SIZE - 1) {
                printf("|"); // 使用竖线 '|' 作为间隔
            }
        }
        printf("\n");

        // 打印分隔线，保持视觉上行与行之间的分隔
        if (i < SIZE - 1) {
            for (int j = 0; j < SIZE; j++) {
                printf("--");  // 每个方块下面打印 '--' 表示分隔线
                if (j < SIZE - 1) {
                    printf("+");  // 使用加号 '+' 分隔横向线
                }
            }
            printf("\n");
        }
    }
}

// 四个方向的移动向量（右、下、左、上）
int directions[4][2] = { {0,  1}, {1,  0}, {0,  -1}, {-1, 0} };

// 记录迷宫中每个位置是否访问过
int visited[SIZE][SIZE] = { 0 };

// 用来记录最短路径的栈
Stack bestPath;

// 记录最短路径的长度，初始值设置为一个较大的值
int minPathLength = SIZE * SIZE + 1;

// 递归回溯法寻找所有路径
void findPaths(int maze[SIZE][SIZE], Stack* path, int x, int y, int endX, int endY, int pathLength) {
    // 如果到达终点，输出路径
    if (x == endX && y == endY) {
        printf("通路: ");
        printStack(path);

        // 更新最短路径
        if (pathLength < minPathLength) {
            minPathLength = pathLength;
            while (!isEmpty(&bestPath)) {
                pop(&bestPath);  // 清空最短路径栈
            }
            copyStack(&bestPath, path);  // 将当前路径复制到最短路径栈
        }
        return;
    }

    // 尝试四个方向移动
    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];

        // 检查新位置是否在迷宫内、是否是通路且未访问过
        if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE && maze[newX][newY] == 0 && !visited[newX][newY]) {
            visited[newX][newY] = 1;   // 标记当前位置为已访问
            push(path, newX, newY);    // 将新位置压入路径栈
            findPaths(maze, path, newX, newY, endX, endY, pathLength + 1);  // 递归搜索
            pop(path);  // 回溯：移除刚才加入的路径节点
            visited[newX][newY] = 0;   // 取消访问标记，便于其他路径探索
        }
    }
}

int main() {
    int maze[SIZE][SIZE];  // 定义迷宫数组
    generateMaze(maze, 0.6);  // 随机生成迷宫，通路的概率
    printf("随机生成迷宫:\n");
    printMaze(maze);  // 打印生成的迷宫

    Stack path;
    initStack(&path);
    initStack(&bestPath);

    visited[0][0] = 1;  // 标记起点为已访问
    push(&path, 0, 0);  // 将起点压入路径栈

    // 开始寻找所有从起点到终点的路径
    findPaths(maze, &path, 0, 0, SIZE - 1, SIZE - 1, 1);

    // 输出最短路径
    if (!isEmpty(&bestPath)) {
        printf("最短通路: ");
        printStack(&bestPath);
    }
    else {
        printf("该迷宫无通路\n");
    }

    return 0;
}
