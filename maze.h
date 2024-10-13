#ifndef MAZE_H
#define MAZE_H

#include "base.h"
#include "stkpas.h"

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

// 生成迷宫一：有解的迷宫
void generateMazeOne(int maze[SIZE][SIZE]) {
    int mazeOne[SIZE][SIZE] = {
        {0, 1, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0, 0, 0},
        {1, 1, 0, 0, 1, 1, 1},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0}
    };

    // 将固定的迷宫复制到传入的迷宫数组
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j] = mazeOne[i][j];
        }
    }
}

// 生成迷宫二：有解的迷宫
void generateMazeTwo(int maze[SIZE][SIZE]) {
    int mazeTwo[SIZE][SIZE] = {
        {0, 0, 1, 0, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 0},
        {1, 0, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0},
        {1, 1, 0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0, 0, 0}
    };

    // 将固定的迷宫复制到传入的迷宫数组
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j] = mazeTwo[i][j];
        }
    }
}

// 生成迷宫三：无解的迷宫（死路）
void generateMazeThree(int maze[SIZE][SIZE]) {
    int mazeThree[SIZE][SIZE] = {
        {0, 1, 1, 0, 0, 1, 1},
        {0, 0, 0, 1, 0, 1, 1},
        {1, 0, 0, 0, 0, 1, 1},
        {1, 0, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 1, 1},
        {1, 0, 1, 1, 0, 1, 0},
        {1, 1, 0, 0, 1, 0, 0}
    };

    // 将固定的迷宫复制到传入的迷宫数组
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j] = mazeThree[i][j];
        }
    }
}



// 打印迷宫的函数，用不同颜色显示通路、障碍、死路、最短路径
void printMaze(int maze[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (maze[i][j] == 0) {

                printf("\033[47m  \033[0m"); // 白色小方块（死路）
            }
            else if (maze[i][j] == 1) {
                printf("\033[41m  \033[0m"); // 红色小方块（障碍）
            }
            else if (maze[i][j] == 2) {
                printf("\033[42m  \033[0m"); // 绿色小方块（最短路径）
            }
            else if (maze[i][j] == 3) {
                printf("\033[44m  \033[0m"); // 蓝色小方块（通路）
            }
            if (j < SIZE - 1) {
                printf("|"); // 使用竖线 '|' 作为间隔
            }
        }
        printf("\n");

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

// 全局数组用来记录所有通路节点，初始值为0，表示该节点不是通路
int allPaths[SIZE][SIZE] = { 0 };

//全局变量记录一共有多少个通路
int numPaths = 0;

// 递归回溯法寻找所有路径
void findPaths(int maze[SIZE][SIZE], Stack* path, int x, int y, int endX, int endY, int pathLength) {
    // 如果到达终点，输出路径
    if (x == endX && y == endY) {
        numPaths++;
        printf("通路: ");
        printStack(path);

        // 记录当前路径上的所有节点到 allPaths 数组
        Node* current = path->top;
        while (current) {
            allPaths[current->x][current->y] = 1; // 将经过的节点标记为1，表示是通路
            current = current->next;
        }

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


// 用来标记最短路径的函数
void markShortestPath(int maze[SIZE][SIZE]) {
    Node* current = bestPath.top;
    while (current) {
        maze[current->x][current->y] = 2; // 将最短路径标记为 2（绿色）
        current = current->next;
    }
}


// 在迷宫中将所有通路变为蓝色
void markAllPaths(int maze[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (allPaths[i][j] == 1) {
                maze[i][j] = 3; // 将通路标记为 3（蓝色）
            }
        }
    }
}


// 重置访问状态和通路数组
void resetMazeState() {
    memset(visited, 0, sizeof(visited));  // 清空访问数组
    memset(allPaths, 0, sizeof(allPaths)); // 清空所有通路数组
    initStack(&bestPath);  // 清空最短路径栈
    minPathLength = SIZE * SIZE + 1;  // 重置最短路径长度
    numPaths = 0;//重置共有几条通路
}

// 打印出所有路径并显示最短路径
void printAllPathsAndShortest(int maze[SIZE][SIZE]) {
    Stack path;
    initStack(&path);
    initStack(&bestPath);

    resetMazeState();  // 重置访问状态和通路数组

    visited[0][0] = 1;  // 标记起点为已访问
    push(&path, 0, 0);  // 将起点压入路径栈

    // 开始寻找所有从起点到终点的路径
    findPaths(maze, &path, 0, 0, SIZE - 1, SIZE - 1, 1);

    //保存原来的迷宫
    int temp_maze[SIZE][SIZE] = { 0 };
    // 使用嵌套循环保存数组
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp_maze[i][j] = maze[i][j];
        }
    }
    //将所有的通路变为蓝色
    markAllPaths(maze);



    // 输出最短路径
    if (!isEmpty(&bestPath)) {
        printf("最短通路: ");
        printStack(&bestPath);

        //输出所有路径
        printf("\n该迷宫共有通路：%d", numPaths);
        printf("\n该迷宫所有通路为：\n");
        printMaze(maze);         // 打印包含所有通路的迷宫


        markShortestPath(temp_maze);  // 标记最短路径
        printf("\n该迷宫最短通路为：\n");
        printMaze(temp_maze);         // 打印包含最短路径的迷宫
    }
    else {
        printf("该迷宫无通路\n");
    }
}


#endif // MAZE_H