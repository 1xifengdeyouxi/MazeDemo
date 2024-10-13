#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"


//����˵�
void MazeMenu() {
    printf("\n========================================\n");
    printf("           �������������:\n");
    printf("========================================\n");
    printf("   [1] ѡ���Թ�һ\n");
    printf("   [2] ѡ���Թ���\n");
    printf("   [3] ѡ���Թ���\n");
    printf("   [4] �������\n");
    printf("   [5] �˳�����\n");
    printf("========================================\n");
    printf("��������ѡ�� (1-5): ");
}


int main() {
    int maze[SIZE][SIZE];  // �����Թ�����
    int choice;

    while (1) {
        MazeMenu();
        scanf_s("%d", &choice);
        getchar();  // ������뻺��

        switch (choice) {
        case 1: {
            generateMazeOne(maze);  // �����Թ�һ
            printf("�Թ�һ:\n");
            printMaze(maze);  // ��ӡ�Թ�һ
            printAllPathsAndShortest(maze);
            break;
        }
        case 2: {
            generateMazeTwo(maze);  // �����Թ���
            printf("�Թ���:\n");
            printMaze(maze);  // ��ӡ�Թ���
            printAllPathsAndShortest(maze);
            break;
        }
        case 3: {
            generateMazeThree(maze);  // �����Թ���
            printf("�Թ��� (�޽�):\n");
            printMaze(maze);  // ��ӡ�Թ���
            printAllPathsAndShortest(maze);
            break;
        }
        case 4: {
            generateMaze(maze, 0.65);  // ��������Թ�
            printf("��������Թ�:\n");
            printMaze(maze);  // ��ӡ������ɵ��Թ�
            printAllPathsAndShortest(maze);
            break;
        }
        case 5: {
            printf("�˳�����\n");
            return 0;  // �˳�����
        }
        default:
            printf("�����д���");
            break;
        }

        printf("�����������... ...\n");
        getch(); // �ȴ��û����������
    }
}
