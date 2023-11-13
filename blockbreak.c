#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y) {//원하는 x,y좌표로 이동시키는 함수
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
 
int main(){
    int x = 1;  // 공의 초기 x 좌표
    int y = 1;  // 공의 초기 y 좌표
    int dx = 1; // 공을 오른쪽으로 이동시킴
    int dy = 1; // 공을 아래쪽으로 이동시킴

    while(1){
        gotoxy(x, y);//공의 이전위치 지우기
        printf(" ");

        x += dx;//공의 좌표 바꾸기
        y += dy;

        gotoxy(x, y);
        printf("■");//위치에 따라 공 출력

        Sleep(100);//공이 이동하는 속도 조절
    }
}