#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"


//输入菜单
void MazeMenu() {
    printf("\n========================================\n");
    printf("           请输入操作类型:\n");
    printf("========================================\n");
    printf("   [1] 选择迷宫一\n");
    printf("   [2] 选择迷宫二\n");
    printf("   [3] 选择迷宫三\n");
    printf("   [4] 随机生成\n");
    printf("   [5] 退出程序\n");
    printf("========================================\n");
    printf("输入您的选择 (1-5): ");
}


int main() {
    int maze[SIZE][SIZE];  // 定义迷宫数组
    int choice;

    while (1) {
        MazeMenu();
        scanf_s("%d", &choice);
        getchar();  // 清除输入缓存

        switch (choice) {
        case 1: {
            generateMazeOne(maze);  // 生成迷宫一
            printf("迷宫一:\n");
            printMaze(maze);  // 打印迷宫一
            printAllPathsAndShortest(maze);
            break;
        }
        case 2: {
            generateMazeTwo(maze);  // 生成迷宫二
            printf("迷宫二:\n");
            printMaze(maze);  // 打印迷宫二
            printAllPathsAndShortest(maze);
            break;
        }
        case 3: {
            generateMazeThree(maze);  // 生成迷宫三
            printf("迷宫三 (无解):\n");
            printMaze(maze);  // 打印迷宫三
            printAllPathsAndShortest(maze);
            break;
        }
        case 4: {
            generateMaze(maze, 0.65);  // 随机生成迷宫
            printf("随机生成迷宫:\n");
            printMaze(maze);  // 打印随机生成的迷宫
            printAllPathsAndShortest(maze);
            break;
        }
        case 5: {
            printf("退出程序\n");
            return 0;  // 退出程序
        }
        default:
            printf("输入有错误");
            break;
        }

        printf("按任意键继续... ...\n");
        getch(); // 等待用户按下任意键
    }
}
