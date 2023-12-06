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
    textcolor(4);
    gotoxy(27, 5);
    printf("■■■■■  ");
    gotoxy(27, 6);
    printf("■■    ■■  ");
    gotoxy(27, 7);
    printf("■■    ■■  ");
    gotoxy(27, 8);
    printf("■■■■■  ");
    gotoxy(27, 9);
    printf("■■    ■■  ");
    gotoxy(27, 10);
    printf("■■    ■■  ");
    gotoxy(27, 11);
    printf("■■■■■  ");
    textcolor(15);

    textcolor(6);
    gotoxy(40, 5);
    printf("■■");
    gotoxy(40, 6);
    printf("■■");
    gotoxy(40, 7);
    printf("■■");
    gotoxy(40, 8);
    printf("■■");
    gotoxy(40, 9);
    printf("■■");
    gotoxy(40, 10);
    printf("■■");
    gotoxy(40, 11);
    printf("■■■■■■■■");

    textcolor(10);
    gotoxy(52, 5);
    printf("  ■■■■■■■  ");
    gotoxy(52, 6);
    printf(" ■       ■");
    gotoxy(52, 7);
    printf("■■       ■■");
    gotoxy(52, 8);
    printf("■■       ■■");
    gotoxy(52, 9);
    printf("■■       ■■");
    gotoxy(52, 10);
    printf(" ■       ■");
    gotoxy(52, 11);
    printf("  ■■■■■■■");

    textcolor(9);
    gotoxy(67, 5);
    printf("  ■■■■■■■  ");
    gotoxy(67, 6);
    printf(" ■       ■");
    gotoxy(67, 7);
    printf("■■       ");
    gotoxy(67, 8);
    printf("■■       ");
    gotoxy(67, 9);
    printf("■■       ■■");
    gotoxy(67, 10);
    printf(" ■       ■");
    gotoxy(67, 11);
    printf("  ■■■■■■■");

    textcolor(13);
    gotoxy(82, 5);
    printf("■■       ■■");
    gotoxy(82, 6);
    printf("■■     ■■");
    gotoxy(82, 7);
    printf("■■   ■■ ");
    gotoxy(82, 8);
    printf("■■■■■  ");
    gotoxy(82, 9);
    printf("■■   ■■");
    gotoxy(82, 10);
    printf("■■     ■■");
    gotoxy(82, 11);
    printf("■■       ■■");
    textcolor(15);


    int st_intro_x=40;
    int st_intro_y=19;
    int st_choose_x=49;
    int st_choose_y=20;
    int stage;
    gotoxy(st_intro_x, st_intro_y);
    printf("1:튜토리얼   2:쉬움   3:보통   4:어려움");
    gotoxy(st_choose_x, st_choose_y);
    printf("난이도를 선택하세요:");
    scanf_s("%d", &stage);
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
    int n;
    int x = 18;  // 공의 초기 x 좌표
    int y = 20;  // 공의 초기 y 좌표
    int dx = 1; // 공을 오른쪽으로 이동시킴
    int dy = 1; // 공을 아래쪽으로 이동시킴
    int bar1_x = 17; //왼쪽 막대 초기 x 좌표
    int bar1_y = 23; //왼쪽 막대 초기 y 좌표
    int bar2_x = 18;
    int bar2_y = 23;
    int bar3_x = 19;
    int bar3_y = 23;
    int bar4_x = 20;//오른쪽 막대 초기 x좌표
    int bar4_y = 23;//오른쪽 막대 초기 y좌표
    int bar5_x = 21;
    int bar5_y = 23;
    int bar6_x = 22;
    int bar6_y = 23;
    int counttime;
    int count=1;
    int block[7][40] = {0,}; //블록 존재 여부 확인
    int bx = 0, by = 0; //블록 좌표 변수 선언
    int score = 0; //점수 변수 선언
    int flag = 0;
    int check = 0;
    FILE *fp;
    int highscore;
    char num[100];
    int scocount=0;
    fopen_s(&fp, "score.txt", "r");
    if (fp == NULL) {
        printf("파일 열기 실패");
        return 1;
        }

    // fscanf_s 함수를 호출할 때 "%c" 서식 지정자를 사용하고,
    // num 변수의 주소와 sizeof(num)을 인수로 전달합니다.
    while (fscanf_s(fp, "%c", &num[scocount++]) != EOF);
    scocount = scocount - 1;
    if (scocount - 1 == 0) {
        highscore = num[0] - '0';
    }

    if (scocount - 1 == 1) {
        highscore = (num[0] - '0')*10+num[1]-'0';
    }

    if (scocount - 1 == 2) {
        highscore = (num[0] - '0') * 100 + (num[1] - '0')*10+num[2]-'0';
    }
    gotoxy(50, 3);
    printf("최고점수:%d", highscore);

    fclose(fp);
    if (stage == 1) {
        for (bx = 5; bx < 8; bx++) {
            by = 0;
            block[by][bx] = 1;
            gotoxy(bx + 1, by + 1);
            printf("▣");
        }
        for (bx = 32; bx < 35; bx++) {
            by = 0;
            block[by][bx] = 1;
            gotoxy(bx + 1, by + 1);
            printf("▣");
        }
    }
    else if (stage==2){
        for( int by = 0; by < 3; by++){
        if (by == 0) {
            textcolor(12);//red
            }
        if (by == 1) {
            textcolor(6);//Dark yellow
            }
        if (by == 2) {
            textcolor(10);//green
            }
        for (int bx = 1; bx < 39; bx++) {
            block[by][bx] = 1;
            gotoxy(bx + 1, by + 1);
            printf("▣");
            }
        textcolor(15);//White
        }
    }
    else if (stage==3){
        for( int by = 0; by < 5; by++){
        if (by == 0) {
            textcolor(12);//red
            }
        if (by == 1) {
            textcolor(6);//Dark yellow
            }
        if (by == 2) {
            textcolor(10);//green
            }
        if (by == 3) {
            textcolor(9);//blue
            }
        if (by == 4) {
            textcolor(13);//purple
            }
        for (int bx = 1; bx < 39; bx++) {
            block[by][bx] = 1;
            gotoxy(bx + 1, by + 1);
            printf("▣");
            }
        textcolor(15);//White
        }
    }
    else if (stage==4){
        for( int by = 0; by < 7; by++){
        if (by == 0) {
            textcolor(12);//red
            }
        if (by == 1) {
            textcolor(6);//Dark yellow
            }
        if (by == 2) {
            textcolor(10);//green
            }
        if (by == 3) {
            textcolor(9);//blue
            }
        if (by == 4) {
            textcolor(13);//purple
            }
        if (by == 5) {
            textcolor(8);//dark gray
            }
        if (by == 6) {
            textcolor(15);//White
            }
        for (int bx = 1; bx < 39; bx++) {
            block[by][bx] = 1;
            gotoxy(bx + 1, by + 1);
            printf("▣");
            }
        textcolor(15);//White
        }
    }

    if (stage == 1) {
        counttime = 600;
    }
    if (stage == 2) {
        counttime = 300;
    }
    else if (stage == 3) {
        counttime = 180;
    }

    else if (stage == 4) {
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
        gotoxy(bar5_x, bar5_y);
        printf(" ");
        gotoxy(bar6_x, bar6_y);
        printf(" ");
        
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) { // 막대 왼쪽으로 이동
            bar1_x--;
            bar2_x--;
            bar3_x--;
            bar4_x--;
            bar5_x--;
            bar6_x--;
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { // 막대 오른쪽으로 이동
            bar1_x++;
            bar2_x++;
            bar3_x++;
            bar4_x++;
            bar5_x++;
            bar6_x++;
        }

        gotoxy(x,y);
        printf("  ");//이전 공의 위치 지우기

        if (count % 20 == 0) {
            counttime -= 1;
        }

        if (counttime == 0) {
            break;
        }

        for (by = 0; by < 7; by++) { //블록과 공이 충돌 시 블록 삭제
            for (bx = 1; bx < 39; bx++) {
                if (block[by][bx] != 0) {
                    if (x == bx + 1 && y == by + 2) {
                        if (x < 37) x++;//반복되지 않게 수정
                        dy = 1;
                        block[by][bx] = 0;
                        gotoxy(bx + 1, by + 1);
                        printf(" ");
                        if (bx > 1) {
                            block[by][bx - 1] = 0;
                            gotoxy(bx, by + 1);
                            printf(" ");
                        }
                        if (bx < 38) {
                            block[by][bx + 1] = 0;
                            gotoxy(bx + 2, by + 1);
                            printf(" ");
                        }
                        score++;
                        break;
                    }
                }
            }
        }

        gotoxy(50, 1);
        printf("%d초", counttime);
        

        x += dx;//공의 좌표 바꾸기
        y += dy;

        gotoxy(x, y);
        printf("■");//위치에 따라 공 출력
        gotoxy(bar1_x, bar1_y);
        printf("O");//위치에 따라 왼쪽 막대 출력
        gotoxy(bar2_x, bar2_y);
        printf("O");
        gotoxy(bar3_x, bar3_y);
        printf("O");
        gotoxy(bar4_x, bar4_y);//위치에 따라 오른쪽 막대 출력
        printf("O");
        gotoxy(bar5_x, bar5_y);
        printf("O");
        gotoxy(bar6_x, bar6_y);
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
        if (x == bar1_x - 1 && y == bar1_y) {
            dx = -1;
            dy = -1;
            }
        if (x == bar1_x && y == bar1_y) {
            dx = -1;
            dy = -1;
            }
        if (x == bar2_x && y == bar2_y) {
            dx = -1;
            dy = -1;
            }
        if (x == bar3_x && y == bar3_y) {
            dx = -1;
            dy = -1;
            }
        if (x == bar4_x && y == bar4_y) {
            dx = 1;
            dy = -1;
            }
        if (x == bar5_x && y == bar5_y) {
            dx = 1;
            dy = -1;
            }
        if (x == bar6_x && y == bar6_y) {
            dx = 1;
            dy = -1;
            }
        if (x == bar6_x + 1 && y == bar6_y) {
            dx = 1;
            dy = -1;
            }
        if (x == bar1_x - 1 && y == bar1_y - 1) {//공이 왼쪽 막대에 닿으면 왼쪽으로 보내기
        dx = -1;
        dy = -1;
        }
        if (x == bar1_x && y == bar1_y - 1) {//공이 왼쪽 막대에 닿으면 왼쪽으로 보내기
        dx = -1;
        dy = -1;
        }
        if (x == bar2_x && y == bar2_y - 1) {
            dx = -1;
            dy = -1;
            }
        if (x == bar3_x && y == bar3_y - 1) {//공이 왼쪽 막대에 닿으면 왼쪽으로 보내기
        dx = -1;
        dy = -1;
        }
        if (x == bar4_x && y == bar4_y - 1) {
            dx = 1;
            dy = -1;
            }
        if (x == bar5_x && y == bar5_y - 1) {//공이 왼쪽 막대에 닿으면 왼쪽으로 보내기
        dx = 1;
        dy = -1;
        }
        if (x == bar6_x && y == bar6_y - 1) {
            dx = 1;
            dy = -1;
            }
        if (x == bar6_x + 1 && y == bar6_y - 1) {
            dx = 1;
            dy = -1;
            }
        count++;
        flag = 0;
        for (by = 0; by < 7; by++) {
            for (bx = 1; bx < 39; bx++) {
                if (block[by][bx]==1) {
                    flag = 1;
                }
            }
        }
        if (flag == 0) {
            check =1;
            break;
        }
    }
    system("cls");
     if (score > highscore) {
            highscore = score;
    }
    fopen_s(&fp, "score.txt", "w");
    fprintf(fp, "%d", highscore);
    fclose(fp);
    system("cls");
    if(check == 0){
        gotoxy(55, 10);
        printf(" GAME OVER ");
    }
    else if(check==1){
        gotoxy(57, 10);
        printf(" CLEAR ");
    }
    gotoxy(50, 12);
    printf("최고점수:%d  현재점수:%d",highscore,score);
    gotoxy(50, 14);
    printf("메인메뉴:1 게임종료:2");
    gotoxy(55, 20);
    printf("선택하세요: ");
    scanf_s("%d", &n);
}