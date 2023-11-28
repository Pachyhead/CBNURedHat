#include <stdio.h>
#include <windows.h>

void textcolor(int colorNum) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

void gotoxy(int x, int y) {//원하는 x,y좌표로 이동시키는 함수
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
 
int choose(){
    int st_intro_x=45;
    int st_intro_y=10;
    int st_choose_x=49;
    int st_choose_y=20;
    int stage;
    gotoxy(st_intro_x, st_intro_y);
    printf("1:쉬움   2:보통   3:어려움");
    gotoxy(st_choose_x, st_choose_y);
    printf("난이도를 선택하세요:");
    scanf("%d", &stage);
    system("cls");
    return stage;
}

void wall(){
    textcolor(9);//파란색
    for (int i = 0; i < 41; i++) {
        printf("■");
    }
    textcolor(15);
    printf("\n");
    for (int i = 0; i < 25; i++) {
        printf("|");
        for (int i = 0; i < 39; i++) {
            printf(" ");
        }
        printf("|\n");


    }
    textcolor(10);//초록색
    for (int i = 0; i < 41; i++) {
        printf("■");
    }
    textcolor(15);
}
int main(){
    int stage=choose();
    wall();
    int x = 18;  // 공의 초기 x 좌표
    int y = 20;  // 공의 초기 y 좌표
    int dx = 1; // 공을 오른쪽으로 이동시킴
    int dy = 1; // 공을 아래쪽으로 이동시킴
    int bar1_x = 18; //왼쪽 막대 초기 x 좌표
    int bar1_y = 23; //왼쪽 막대 초기 y 좌표
    int bar2_x = 19;
    int bar2_y = 23;
    int bar3_x = 20; //오른쪽 막대 초기 x 좌표
    int bar3_y = 23; //오른쪽 막대 초기 y 좌표
    int bar4_x = 21;
    int bar4_y = 23;
    int counttime;
    int count=1;
    int block[7][40]; //블록 존재 여부 확인
    int bx = 0, by = 0; //블록 좌표 변수 선언
    int score = 0; //점수 변수 선언
    for (int by = 0; by < 7; by++) {     //블록 설치
        for (int bx = 1; bx < 39; bx++) {
            block[by][bx] = 1;
            gotoxy(bx + 1, by + 1);
            printf("▣");
        }
    }
    if (stage == 1) {
        counttime = 300;
    }
    else if (stage == 2) {
        counttime = 180;
    }

    else if (stage == 3) {
        counttime = 60;
    }
    while(1){
        gotoxy(bar1_x, bar1_y);
        printf(" ");
        gotoxy(bar2_x, bar2_y);
        printf(" ");
        gotoxy(bar3_x, bar3_y);
        printf(" ");
        gotoxy(bar4_x, bar4_y);
        printf(" ");
        
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

        gotoxy(x,y);
        printf("  ");//이전 공의 위치 지우기

        if (count % 20 == 0) {
            counttime -= 1;
        }

        if (counttime == 0) {
            break;
        }
        for (by = 0;by < 7;by++) { //블록과 공이 충돌 시 블록 삭제
            for (bx = 1; bx < 39; bx++) {
                if (block[by][bx] != 0) {
                    if (x == bx + 1 && y == by + 1) {
                        if (x < 37) x++;//반복되지 않게 수정
                        dy = 1;
                        block[by][bx] = 0;
                        gotoxy(bx + 1, by + 1);
                        printf(" ");
                        score++;
                        break;
                    }
                }
            }
        }
        gotoxy(50, 1);
        printf("%d초", counttime);
        gotoxy(50, 2);
        printf("score:%d", score);

        

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
        Sleep(50);//공이 이동하는 속도 조절

        if(x==1||x==38){//특정 x좌표에서 이동방향 반대로 바꾸기
            dx=-dx;
        }
        if(y==1){//특정 y좌표에서 이동방향 반대로 바꾸기
            dy=-dy;
        }
        if(y==25){//공이 바닥에 닿으면 게임종료
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
        count++;
    }
    system("cls");
    printf("게임종료");
}