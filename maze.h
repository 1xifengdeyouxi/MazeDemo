#ifndef MAZE_H
#define MAZE_H

#include "base.h"
#include "stkpas.h"

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

// �����Թ�һ���н���Թ�
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

    // ���̶����Թ����Ƶ�������Թ�����
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j] = mazeOne[i][j];
        }
    }
}

// �����Թ������н���Թ�
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

    // ���̶����Թ����Ƶ�������Թ�����
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j] = mazeTwo[i][j];
        }
    }
}

// �����Թ������޽���Թ�����·��
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

    // ���̶����Թ����Ƶ�������Թ�����
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j] = mazeThree[i][j];
        }
    }
}



// ��ӡ�Թ��ĺ������ò�ͬ��ɫ��ʾͨ·���ϰ�����·�����·��
void printMaze(int maze[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (maze[i][j] == 0) {

                printf("\033[47m  \033[0m"); // ��ɫС���飨��·��
            }
            else if (maze[i][j] == 1) {
                printf("\033[41m  \033[0m"); // ��ɫС���飨�ϰ���
            }
            else if (maze[i][j] == 2) {
                printf("\033[42m  \033[0m"); // ��ɫС���飨���·����
            }
            else if (maze[i][j] == 3) {
                printf("\033[44m  \033[0m"); // ��ɫС���飨ͨ·��
            }
            if (j < SIZE - 1) {
                printf("|"); // ʹ������ '|' ��Ϊ���
            }
        }
        printf("\n");

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

// ȫ������������¼����ͨ·�ڵ㣬��ʼֵΪ0����ʾ�ýڵ㲻��ͨ·
int allPaths[SIZE][SIZE] = { 0 };

//ȫ�ֱ�����¼һ���ж��ٸ�ͨ·
int numPaths = 0;

// �ݹ���ݷ�Ѱ������·��
void findPaths(int maze[SIZE][SIZE], Stack* path, int x, int y, int endX, int endY, int pathLength) {
    // ��������յ㣬���·��
    if (x == endX && y == endY) {
        numPaths++;
        printf("ͨ·: ");
        printStack(path);

        // ��¼��ǰ·���ϵ����нڵ㵽 allPaths ����
        Node* current = path->top;
        while (current) {
            allPaths[current->x][current->y] = 1; // �������Ľڵ���Ϊ1����ʾ��ͨ·
            current = current->next;
        }

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


// ����������·���ĺ���
void markShortestPath(int maze[SIZE][SIZE]) {
    Node* current = bestPath.top;
    while (current) {
        maze[current->x][current->y] = 2; // �����·�����Ϊ 2����ɫ��
        current = current->next;
    }
}


// ���Թ��н�����ͨ·��Ϊ��ɫ
void markAllPaths(int maze[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (allPaths[i][j] == 1) {
                maze[i][j] = 3; // ��ͨ·���Ϊ 3����ɫ��
            }
        }
    }
}


// ���÷���״̬��ͨ·����
void resetMazeState() {
    memset(visited, 0, sizeof(visited));  // ��շ�������
    memset(allPaths, 0, sizeof(allPaths)); // �������ͨ·����
    initStack(&bestPath);  // ������·��ջ
    minPathLength = SIZE * SIZE + 1;  // �������·������
    numPaths = 0;//���ù��м���ͨ·
}

// ��ӡ������·������ʾ���·��
void printAllPathsAndShortest(int maze[SIZE][SIZE]) {
    Stack path;
    initStack(&path);
    initStack(&bestPath);

    resetMazeState();  // ���÷���״̬��ͨ·����

    visited[0][0] = 1;  // ������Ϊ�ѷ���
    push(&path, 0, 0);  // �����ѹ��·��ջ

    // ��ʼѰ�����д���㵽�յ��·��
    findPaths(maze, &path, 0, 0, SIZE - 1, SIZE - 1, 1);

    //����ԭ�����Թ�
    int temp_maze[SIZE][SIZE] = { 0 };
    // ʹ��Ƕ��ѭ����������
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp_maze[i][j] = maze[i][j];
        }
    }
    //�����е�ͨ·��Ϊ��ɫ
    markAllPaths(maze);



    // ������·��
    if (!isEmpty(&bestPath)) {
        printf("���ͨ·: ");
        printStack(&bestPath);

        //�������·��
        printf("\n���Թ�����ͨ·��%d", numPaths);
        printf("\n���Թ�����ͨ·Ϊ��\n");
        printMaze(maze);         // ��ӡ��������ͨ·���Թ�


        markShortestPath(temp_maze);  // ������·��
        printf("\n���Թ����ͨ·Ϊ��\n");
        printMaze(temp_maze);         // ��ӡ�������·�����Թ�
    }
    else {
        printf("���Թ���ͨ·\n");
    }
}


#endif // MAZE_H