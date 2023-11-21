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
    int bar1_x = 18; //왼쪽 막대 초기 x 좌표
    int bar1_y = 45; //왼쪽 막대 초기 y 좌표
    int bar2_x = 19;
    int bar2_y = 45;
    int bar3_x = 20; //오른쪽 막대 초기 x 좌표
    int bar3_y = 45; //오른쪽 막대 초기 y 좌표
    int bar4_x = 21;
    int bar4_y = 45;

    system("mode con cols=40 lines=50"); // 콘솔 창 크기 설정

    while(1){
        gotoxy(x,y);
        printf("  ");//이전 공의 위치 지우기
        x += dx;//공의 좌표 바꾸기
        y += dy;

        gotoxy(x, y);
        printf("■");//위치에 따라 공 출력
        gotoxy(bar1_x, bar1_y);
        printf("O");//위치에 따라 왼쪽 막대 출력
        gotoxy(bar2_x, bar2_y);
        printf("O");
        gotoxy(bar3_x, bar3_y);
        printf("O");//위치에 따라 오른쪽 막대 출력
        gotoxy(bar4_x, bar4_y);
        printf("O");
        Sleep(100);//공이 이동하는 속도 조절

        if(x==1||x==39){//특정 x좌표에서 이동방향 반대로 바꾸기
            dx=-dx;
        }
        if(y==1){//특정 y좌표에서 이동방향 반대로 바꾸기
            dy=-dy;
        }
        if(y==49){//공이 바닥에 닿으면 게임종료
            break;
        }
        if (x == bar1_x && y == bar1_y-1) {//공이 왼쪽 막대에 닿으면 왼쪽으로 보내기
            dx = -1;
            dy = -1;
        }
        if (x == bar2_x && y == bar2_y-1) {
            dx = -1;
            dy = -1;
        }
        if (x == bar3_x && y == bar3_y - 1) {//공이 왼쪽 막대에 닿으면 왼쪽으로 보내기
            dx = 1;
            dy = -1;
        }
        if (x == bar4_x && y == bar4_y - 1) {
            dx = 1;
            dy = -1;
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) { // 막대 왼쪽으로 이동
            bar1_x--;
            bar2_x--;
            bar3_x--;
            bar4_x--;
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { // 막대 오른쪽으로 이동
            bar1_x++;
            bar2_x++;
            bar3_x++;
            bar4_x++;
        }
    }
    system("cls");
    printf("게임종료");
}