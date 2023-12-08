#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

void mainInterface();
void gotoxy(int x, int y);
void CursorView(char show); //커서숨기기
void textColor(int colorNum);
void chooseGame();

int main() {
    int selectGame;
    mainInterface(15);
    chooseGame(16, 30);
    gotoxy(42, 25);
    printf("플레이할 게임을 선택하세요: ");
    do {
        gotoxy(70, 25);
        printf("        ");
        gotoxy(70, 25);
        scanf_s("%d", &selectGame);
        if (selectGame == 0) return 0;
    } while (!((selectGame == 1) || (selectGame == 2) || (selectGame == 3)));

    return 0;
}

void mainInterface(int mainInterfaceCoor) {
    //textColor(4);
    gotoxy(mainInterfaceCoor, 5);
    printf("          ■■");
    gotoxy(mainInterfaceCoor, 6);
    printf("■■■■■■■■  ■■");
    gotoxy(mainInterfaceCoor, 7);
    printf("■■    ■■  ■■");
    gotoxy(mainInterfaceCoor, 8);
    printf("■■    ■■  ■■");
    gotoxy(mainInterfaceCoor, 9);
    printf("■■    ■■  ■■");
    gotoxy(mainInterfaceCoor, 10);
    printf("■■    ■■  ■■");
    gotoxy(mainInterfaceCoor, 11);
    printf("■■■■■■■■  ■■");
    gotoxy(mainInterfaceCoor, 12);
    printf("          ■■");
    gotoxy(mainInterfaceCoor, 13);
    printf("          ■■");

    //textColor(6);
    gotoxy(mainInterfaceCoor + 15, 5);
    printf("         ■■");
    gotoxy(mainInterfaceCoor + 15, 6);
    printf("■■       ■■");
    gotoxy(mainInterfaceCoor + 15, 7);
    printf("■■       ■■");
    gotoxy(mainInterfaceCoor + 15, 8);
    printf("■■       ■■");
    gotoxy(mainInterfaceCoor + 15, 9);
    printf("■■       ■■");
    gotoxy(mainInterfaceCoor + 15, 10);
    printf("■■       ■■");
    gotoxy(mainInterfaceCoor + 15, 11);
    printf("■■■■■■■  ■■");
    gotoxy(mainInterfaceCoor + 15, 12);
    printf("         ■■");
    gotoxy(mainInterfaceCoor + 15, 13);
    printf("         ■■");

    //textColor(10);
    gotoxy(mainInterfaceCoor + 29, 5);
    printf("         ■ ■");
    gotoxy(mainInterfaceCoor + 29, 6);
    printf("■■■■■■■  ■ ■");
    gotoxy(mainInterfaceCoor + 29, 7);
    printf("    ■■   ■ ■");
    gotoxy(mainInterfaceCoor + 29, 8);
    printf("   ■■  ■■■ ■");
    gotoxy(mainInterfaceCoor + 29, 9);
    printf("  ■■     ■ ■");
    gotoxy(mainInterfaceCoor + 29, 10);
    printf(" ■■      ■ ■");
    gotoxy(mainInterfaceCoor + 29, 11);
    printf("■■       ■ ■");
    gotoxy(mainInterfaceCoor + 29, 12);
    printf("         ■ ■");
    gotoxy(mainInterfaceCoor + 29, 13);
    printf("         ■ ■");

    //textColor(9);
    gotoxy(mainInterfaceCoor + 44, 5);
    printf("         ■■");
    gotoxy(mainInterfaceCoor + 44, 6);
    printf("  ■■■    ■■");
    gotoxy(mainInterfaceCoor + 44, 7);
    printf(" ■   ■   ■■");
    gotoxy(mainInterfaceCoor + 44, 8);
    printf("■■   ■■  ■■");
    gotoxy(mainInterfaceCoor + 44, 9);
    printf(" ■   ■   ■■");
    gotoxy(mainInterfaceCoor + 44, 10);
    printf("  ■■■    ■■");
    gotoxy(mainInterfaceCoor + 44, 11);
    printf("     ■■■■■ ");
    gotoxy(mainInterfaceCoor + 44, 12);
    printf("     ■   ■ ");
    gotoxy(mainInterfaceCoor + 44, 13);
    printf("     ■■■■■ ");

    //textColor(13);
    gotoxy(mainInterfaceCoor + 58, 5);
    printf(" ■■■■    ■■");
    gotoxy(mainInterfaceCoor + 58, 6);
    printf("■■■■■■   ■■");
    gotoxy(mainInterfaceCoor + 58, 7);
    printf("   ■■    ■■");
    gotoxy(mainInterfaceCoor + 58, 8);
    printf("  ■■■  ■■■■");
    gotoxy(mainInterfaceCoor + 58, 9);
    printf(" ■■ ■■   ■■");
    gotoxy(mainInterfaceCoor + 58, 10);
    printf("■■   ■■  ■■");
    gotoxy(mainInterfaceCoor + 58, 11);
    printf("   ■■");
    gotoxy(mainInterfaceCoor + 58, 12);
    printf("   ■■");
    gotoxy(mainInterfaceCoor + 58, 13);
    printf("   ■■■■■■■■");

    //textColor(14);
    gotoxy(mainInterfaceCoor + 72, 5);
    printf(" ■■■■■■■■");
    gotoxy(mainInterfaceCoor + 72, 6);
    printf("       ■■");
    gotoxy(mainInterfaceCoor + 72, 7);
    printf("       ■■");
    gotoxy(mainInterfaceCoor + 72, 8);
    printf("       ■■");
    gotoxy(mainInterfaceCoor + 72, 9);
    printf("■■■■■■■■■■");
    gotoxy(mainInterfaceCoor + 72, 10);
    printf("     ■■   ");
    gotoxy(mainInterfaceCoor + 72, 11);
    printf(" ■■■■■■■■");
    gotoxy(mainInterfaceCoor + 72, 12);
    printf("       ■■");
    gotoxy(mainInterfaceCoor + 72, 13);
    printf("       ■■");

    textColor(15);
}

void chooseGame(int mainInterfaceCoor, int coorX) {
    gotoxy(mainInterfaceCoor + coorX, 17);
    printf("▶ 1. 벽돌깨기");
    gotoxy(mainInterfaceCoor + coorX, 19);
    printf("▶ 2. 수도 및 노래 맞추기");
    gotoxy(mainInterfaceCoor + coorX, 21);
    printf("▶ 3. 뱀 게임");
}

void gotoxy(int x, int y)
{
    COORD Pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void CursorView(char show)//커서숨기기
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
void textColor(int colorNum) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}
