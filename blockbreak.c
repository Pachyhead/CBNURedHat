#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y) {//원하는 x,y좌표로 이동시키는 함수
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
 
int main(){
    int x = 1;  // 공의 초기 x 좌표
    int y = 1;  // 공의 초기 y 좌표
   

}