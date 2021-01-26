//70分//Clear vers
/*
Week 16 Question 1

Description

數迴是一個我非常喜歡的益智遊戲，數迴詳細的規則請參考以下的網站

https://zh.puzzle-loop.com/

這個學期的最後一個作業請各位同學寫一個程式來解數迴
如果能夠設計一個資料結構用來儲存這個遊戲，並解釋你打算如何用這樣的結構嘗試解決遊戲，那你可以拿到70分
如果能夠寫一個程式用你設計的資料結構，自行設計輸入輸出格式，嘗試解開5 X 5的普通難度但是沒有成功，那你可以拿到80分
如果能夠寫一個程式用你設計的資料結構，自行設計輸入輸出格式，解開5 X 5的普通難度，那你可以拿到95分
如果能夠寫一個程式用你設計的資料結構，自行設計輸入輸出格式，解開5 X 5的困難難度，那你可以拿到100分
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define wall 9
#define dot 8

void main()
{
    char maps[13][13];
    for (int i = 0; i < 13; i++)
        for (int j = 0; j < 13; j++)
            maps[i][j] = 32;
            
    for (int i = 0; i < 13; i++)
    {
        maps[0][i] = wall;
        maps[i][0] = wall;
        maps[i][12] = wall;
        maps[12][i] = wall;
    }

    for (int i = 1; i <= 11; i += 2)
    {
        for (int j = 1; j <= 11; j += 2)
            maps[i][j] = dot;
    }

    char tmp[5];
    for (int i = 1; i <= 5; i++)
    {
        gets(tmp);
        maps[2 * i][2] = tmp[0];
        //printf("%c\n", tmp[0]);
        //printf("maps:%c\n", maps[2 * i][2]);
        maps[2 * i][4] = tmp[1];
        maps[2 * i][6] = tmp[2];
        maps[2 * i][8] = tmp[3];
        maps[2 * i][10] = tmp[4];
    }

    printf("\n=================tmp=======================================\n");
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            if (maps[i][j] == 32)
                printf("+");
            else if (maps[i][j] == wall)
                printf("#");
            else if (maps[i][j] == dot)
                printf(".");
            else if (maps[i][j] >= 48 && maps[i][j] <= 57)
                printf("%c", maps[i][j]);
            else
                printf("!");
        }
        printf("\n");
    }
    printf("\n========================================================\n");

}
