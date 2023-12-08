#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<string.h>

#define MAX_COUNT 20

#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define UP 72

#define MAPSIZE 22 // 신규
#define SNAKELENGTH 17

int snakemain();

typedef struct _coord {
    int x;
    int y;
} coord;

typedef struct _listNode {
    coord data;
    struct _listNode* link;
} listNode;

// 연결 리스트의 변수들을 정의하는 공간이다. 현재는 뱀의 길이 정보를 정의하고 있다.
typedef struct _linkedList {
    int snakeLength;
    struct _listNode* link;
} linkedList;

typedef struct _body
{
    int x;
    int y;
}Body;

typedef struct _component
{
    int x;
    int y;
}Component;

Component food;
Component block;

typedef struct _sanctuary {
    int xArray[3];
    int yArray[3];
} Sanctuary;

Sanctuary sanctuary[20];

typedef struct _logic
{
    bool Up;
    bool Down;
    bool Right;
    bool Left;
}Logic;
Logic l;

linkedList* snakeList;

bool plusChecker;
int blockCount = 0;
static int snakeScore = 0;
int bestSnakeScore;
Component blockArray[30] = { {0, 0} };

int map[MAPSIZE][MAPSIZE] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

linkedList* createList(); // 연결 리스트 생성 함수
void add(linkedList* list, coord value); // 연결 리스트에 노드를 추가하는 함수
bool printList(linkedList* list); // 연결 리스트 전체를 출력하는 함수
void freeList(linkedList* list); // 연결 리스트의 모든 노드들을 free하는 함수
void delLast(linkedList* list); // 마지막 노드를 제거하는 함수
void insert0(linkedList* list, coord value); // 맨 앞(index 0)에 노드를 추가하는 함수
coord getCoord(linkedList* list, int index); // 지정된 index의 좌표를 얻어오는 함수
void insertLast(linkedList* list, coord value); // 맨 뒤에 노드를 추가하는 함수

void Map();
void Init();
void MoveCoor();
int choiceGame(int mode);

void Delete();
void Output();
void Move();
void BlockOutput(int diff, int diff2);
void putInSanctuary(Component block); // 장애물이 생성될 수 없는 공간, 장애물을 포함한 3*3을 생성한다.
bool isInSanctuary(Component block); // 장애물이 sanctuary에 있는지 check. 있으면 true, 없으면 false
bool isInSnake(Component block); // 장애물이 snake의 좌표에 존재하는지 check. 있으면 true, 없으면 false
void printSanctuary(Component block, bool toggle); // sanctuary를 화면에 출력해보는 함수
bool isInBlockArray(Component block); // block이 blockArray 내에 존재하는지 check.
bool isAtFood(Component block, Component food);

void FoodOutput();
void Eat();
int CanEatFood();
void BodyPlus();
void Score();
void textColor(int colorNum);

void GameOver();
void AfterGame();
void GameExplain(int score);

void gotoxy(int x, int y);
void CursorView(char show);//커서숨기기

void mainInterface();
void gotoxy(int x, int y);
void CursorView(char show); //커서숨기기
void textColor(int colorNum);
void chooseGame();

int main() {
    while (1) {
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
        if (selectGame == 1) {
            system("cls");
            BBmain();
        }
        else if (selectGame == 2) {
            system("cls");
            CNSQuizmain();
        }
        else if (selectGame == 3) {
            system("cls");
            snakemain();
        }
    }
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

int choose() {
    textColor(4);
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
    textColor(15);

    textColor(6);
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

    textColor(10);
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

    textColor(9);
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

    textColor(13);
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
    textColor(15);


    int st_intro_x = 40;
    int st_intro_y = 19;
    int st_choose_x = 49;
    int st_choose_y = 20;
    int stage;
    gotoxy(st_intro_x, st_intro_y);
    printf("1:튜토리얼   2:쉬움   3:보통   4:어려움");
    gotoxy(st_choose_x, st_choose_y);
    printf("난이도를 선택하세요:");
    scanf_s("%d", &stage);
    system("cls");
    return stage;
}

void BBwall() {
    textColor(9);//파란색
    for (int i = 0; i < 41; i++) {
        printf("■");
    }
    textColor(15);
    printf("\n");
    for (int i = 0; i < 25; i++) {
        printf("|");
        for (int i = 0; i < 39; i++) {
            printf(" ");
        }
        printf("|\n");


    }
    textColor(10);//초록색
    for (int i = 0; i < 41; i++) {
        printf("■");
    }
    textColor(15);

}

void quizwall() {
    textColor(9);//파란색
    gotoxy(15, 4);
    for (int i = 0; i < 91; i++) {
        printf("■");
    }
    textColor(15);
    int k = 5;
    for (int i = 0; i < 20; i++) {
        gotoxy(15, k++);
        printf("|");
        for (int i = 0; i < 89; i++) {
            printf(" ");
        }
        printf("|\n");


    }
    gotoxy(15, 24);
    textColor(10);//초록색
    for (int i = 0; i < 91; i++) {
        printf("■");
    }
    textColor(15);

}

int BBmain() {
    int stage = choose();
    BBwall();
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
    int count = 1;
    int block[7][40] = { 0, }; //블록 존재 여부 확인
    int bx = 0, by = 0; //블록 좌표 변수 선언
    int score = 0; //점수 변수 선언
    int flag = 0;
    int check = 0;
    FILE* fp;
    int highscore;
    char num[100];
    int scocount = 0;
    fopen_s(&fp, "BBScore.txt", "r");
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
        highscore = (num[0] - '0') * 10 + num[1] - '0';
    }

    if (scocount - 1 == 2) {
        highscore = (num[0] - '0') * 100 + (num[1] - '0') * 10 + num[2] - '0';
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
    else if (stage == 2) {
        for (int by = 0; by < 3; by++) {
            if (by == 0) {
                textColor(12);//red
            }
            if (by == 1) {
                textColor(6);//Dark yellow
            }
            if (by == 2) {
                textColor(10);//green
            }
            for (int bx = 1; bx < 39; bx++) {
                block[by][bx] = 1;
                gotoxy(bx + 1, by + 1);
                printf("▣");
            }
            textColor(15);//White
        }
    }
    else if (stage == 3) {
        for (int by = 0; by < 5; by++) {
            if (by == 0) {
                textColor(12);//red
            }
            if (by == 1) {
                textColor(6);//Dark yellow
            }
            if (by == 2) {
                textColor(10);//green
            }
            if (by == 3) {
                textColor(9);//blue
            }
            if (by == 4) {
                textColor(13);//purple
            }
            for (int bx = 1; bx < 39; bx++) {
                block[by][bx] = 1;
                gotoxy(bx + 1, by + 1);
                printf("▣");
            }
            textColor(15);//White
        }
    }
    else if (stage == 4) {
        for (int by = 0; by < 7; by++) {
            if (by == 0) {
                textColor(12);//red
            }
            if (by == 1) {
                textColor(6);//Dark yellow
            }
            if (by == 2) {
                textColor(10);//green
            }
            if (by == 3) {
                textColor(9);//blue
            }
            if (by == 4) {
                textColor(13);//purple
            }
            if (by == 5) {
                textColor(8);//dark gray
            }
            if (by == 6) {
                textColor(15);//White
            }
            for (int bx = 1; bx < 39; bx++) {
                block[by][bx] = 1;
                gotoxy(bx + 1, by + 1);
                printf("▣");
            }
            textColor(15);//White
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
    while (1) {
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

     
        if (GetAsyncKeyState(VK_LEFT) & 0x8000 && bar1_x!=1) { // 막대 왼쪽으로 이동
            bar1_x--;
            bar2_x--;
            bar3_x--;
            bar4_x--;
            bar5_x--;
            bar6_x--;
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && bar6_x!=39) { // 막대 오른쪽으로 이동
            bar1_x++;
            bar2_x++;
            bar3_x++;
            bar4_x++;
            bar5_x++;
            bar6_x++;
        }

        gotoxy(x, y);
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
        gotoxy(50, 2);
        printf("점수: %d", score);

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

        if (x == 1 || x == 38) {//특정 x좌표에서 이동방향 반대로 바꾸기
            dx = -dx;
        }
        if (y == 1) {//특정 y좌표에서 이동방향 반대로 바꾸기
            dy = -dy;
        }
        if (y == 25) {//공이 바닥에 닿으면 게임종료
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
                if (block[by][bx] == 1) {
                    flag = 1;
                }
            }
        }
        if (flag == 0) {
            check = 1;
            break;
        }
    }
    system("cls");
    if (score > highscore) {
        highscore = score;
    }
    fopen_s(&fp, "BBScore.txt", "w");
    fprintf(fp, "%d", highscore);
    fclose(fp);
    system("cls");
    if (check == 0) {
        gotoxy(55, 10);
        printf(" GAME OVER ");
    }
    else if (check == 1) {
        gotoxy(57, 10);
        printf(" CLEAR ");
    }
    gotoxy(50, 12);
    printf("최고점수:%d  현재점수:%d", highscore, score);
    gotoxy(50, 14);
    printf("메인메뉴:1 게임종료:2");
    gotoxy(55, 20);
    printf("선택하세요: ");
    scanf_s("%d", &n);
    system("cls");

    if (n == 1) return 0;
    else if (n == 2) exit(0);


}

int CNSQuizmain(void) {
    getchar();
    quizwall();
    int score = 0;
    int data[MAX_COUNT];
    int i, sub_i;
    srand((unsigned int)time(NULL));

    for (i = 0; i < MAX_COUNT; i++) {
        data[i] = rand() % MAX_COUNT;
        for (sub_i = 0; sub_i < i; sub_i++) {
            if (data[i] == data[sub_i]) {
                i--;
                break;
            }
        }
    }
    char ans[20][24] = { "서울", "도쿄", "베이징", "워싱턴", "로마", "파리", "베를린", "아테네",
    "리스본", "마드리드", "seven", "baddie", "이미 슬픈 사랑", "사랑은 늘 도망가", "hype boy",
    "omg", "next level", "fast forward", "좋니", "오래된 노래" };
    char quiz[20][200] = { "한국","일본", "중국", "미국", "이탈리아",
    "프랑스", "독일", "그리스", "포르투갈", "스페인",
    "Weight of thee world on your shoulders I'll kiss your waist and ease your mind",
    "Imma baddie baddie baddie Pretty little risky baddie",
    "떠나는 그대여 울지 말아요 슬퍼 말아요 내가 단념할게요 마음 편히 가시도록",
    "사랑아 왜 도망가 수줍은 아이처럼",
    "Cause I know what you like boy You're my chemical hype boy",
    "Oh my oh my God 예상했어 나",
    "I see the NU EVO. 적대적인 고난과 슬픔은",
    "How many lovers do I go through to find you How many how many how many",
    "이제 괜찮니 너무 힘들었잖아 우리 그 마무리가",
    "오래전에 함께듣던 노래가 거리에서 내게 우연히 들려온것처럼" };
    char input[24] = { "" };
    int n, cnt = 0;
    char ch;
    int reset = 0;

    i = 0;
    gotoxy(93, 5);
    printf("점수:%d", score);

    while (cnt < 10) {
        cnt++;
        if (reset == 0) {
            gotoxy(16, 8);
            for (int k = 0; k < 88; k++) {
                printf(" ");
            }
            gotoxy(16, 14);
            for (int k = 0; k < 88; k++) {
                printf(" ");
            }

            gotoxy(16, 17);
            for (int k = 0; k < 88; k++) {
                printf(" ");
            }

            int xCoor = 58 - strlen(quiz[data[i]]) / 2;
            gotoxy(xCoor, 8);
            printf("문제: %s\n", quiz[data[i]]);
            gotoxy(50, 14);
            printf("답: ");
            gotoxy(53, 14);
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strcmp(ans[data[i]], input) == 0) {
                gotoxy(55, 17);
                printf("맞았습니다.\n");
                score = score + 10;
            }
            else {
                gotoxy(55, 17);
                printf("틀렸습니다.\n");
            }
            gotoxy(93, 5);
            printf("점수:%d", score);


            i++;
            gotoxy(55, 18);

            ch = getchar();

            if (ch == '\n') {
                reset = 0;
            }
        }

    }
    system("cls");

    gotoxy(55, 12);
    printf("최종점수:%d", score);
    gotoxy(50, 14);
    printf("메인메뉴:1 게임종료:2");
    gotoxy(55, 20);
    printf("선택하세요: ");
    scanf_s("%d", &n);
    system("cls");
    if (n == 1) {
        return 0;
    }
    else if (n == 2) {
        exit(0);
    }
}

linkedList* createList(void) { //
    linkedList* list = (linkedList*)malloc(sizeof(linkedList));

    list->link = NULL;
    list->snakeLength = 0;

    return list;
}

void add(linkedList* list, coord value) { //
    listNode* newNode = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 동적 할당
    if (!newNode) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = value; // 새로운 노드의 데이터 설정
    newNode->link = NULL;  // 새로운 노드의 링크 초기화

    // 헤드부터 시작해서 맨 끝까지 이동
    if (list->link == NULL) { // 리스트에 노드가 없을 때
        list->link = newNode;
        list->snakeLength += 1;
    }
    else { // 
        listNode* current = list->link;
        while (current) {
            if (current->link == NULL) break;
            current = current->link;
        }
        // 맨 끝에 새로운 노드 추가
        current->link = newNode;
        list->snakeLength += 1;
    }
}

// 연결 리스트 출력 함수
bool printList(linkedList* list) {
    // 헤드부터 시작해서 맨 끝까지 이동
    if (list->link == NULL) { // 노드가 1개일 때
        return false;
    }
    else { // 노드가 2개 이상일 때
        listNode* current = list->link;
        while (current) {
            printf("(%d, %d) ", current->data.x, current->data.y);
            current = current->link;
        }
        printf("\n");
    }
}

// 연결 리스트 메모리 해제 함수
void freeList(linkedList* list) {
    if (list->link == NULL) {
        free(list);
    }
    else {
        listNode* current = list->link;
        while (current) {
            listNode* temp = current;
            current = current->link;
            free(temp);
        }
        free(list);
    }
}

// 연결 리스트 마지막 노드 삭제 함수
void delLast(linkedList* list) {
    if (list->link == NULL) {
        fprintf(stderr, "리스트가 비어있습니다.\n");
    }
    else if (list->link->link == NULL) {
        free(list->link);
        list->link = NULL;
        list->snakeLength = 0;
    }
    else {
        listNode* current = list->link;
        while (current->link && current->link->link) {
            current = current->link;
        }
        free(current->link);
        current->link = NULL;
        list->snakeLength -= 1;
    }
}

void insert0(linkedList* list, coord value) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 동적 할당
    if (!newNode) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = value; // 새로운 노드의 데이터 설정
    newNode->link = NULL;  // 새로운 노드의 링크 초기화

    // 헤드부터 시작해서 맨 끝까지 이동
    if (list->link == NULL) { // 노드가 1개일 때(head->link부터 출발하는 이유는 head는 null이 될 수 없기 때문이다.)
        list->link = newNode;
        list->snakeLength += 1;
    }
    else { // 노드가 2개 이상일 때 
        listNode* tempNode = (listNode*)malloc(sizeof(listNode));
        tempNode = list->link;
        list->link = newNode;
        newNode->link = tempNode;
        list->snakeLength += 1;
    }
}

coord getCoord(linkedList* list, int index) {
    listNode* current = list;
    int start = 0;
    while (current && start <= index) {
        if (current->link == NULL) break;
        current = current->link;
        start += 1;
    }
    return current->data;
}

void insertLast(linkedList* list, coord value) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode));

    if (!newNode) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = value; // 새로운 노드의 데이터 설정
    newNode->link = NULL;  // 새로운 노드의 링크 초기화

    if (list->link == NULL) {
        list->link = newNode;
        list->snakeLength += 1;
    }
    else {
        listNode* current = list->link;
        while (current->link) {
            current = current->link;
        }
        current->link = newNode;
        list->snakeLength += 1;
    }
}

void Map()
{
    for (int i = 0; i < MAPSIZE; i++)
    {
        for (int j = 0; j < MAPSIZE; j++)
        {
            if (map[i][j] == 1)
                printf("▣ ");
            else
                printf("  ");
        }
        printf("\n");
    }
}

void Init()
{
    l.Up = false;
    l.Down = false;
    l.Right = false;
    l.Left = false;

    snakeList = createList();

    coord body1 = { 14, 14 };
    coord body2 = { 12, 14 };
    coord body3 = { 10, 14 };

    add(snakeList, body1);
    add(snakeList, body2);
    add(snakeList, body3);

    plusChecker = false;
}

void MoveCoor()
{
    if (l.Up == true)
    {
        coord temp = getCoord(snakeList, 0);
        temp.y--;
        insert0(snakeList, temp);
        if (plusChecker) plusChecker = false;
        else delLast(snakeList);
    }

    if (l.Down == true)
    {
        coord temp = getCoord(snakeList, 0);
        temp.y++;
        insert0(snakeList, temp);
        if (plusChecker) plusChecker = false;
        else delLast(snakeList);
    }

    if (l.Right == true)
    {
        coord temp = getCoord(snakeList, 0);
        temp.x += 2;
        insert0(snakeList, temp);
        if (plusChecker) plusChecker = false;
        else delLast(snakeList);
    }

    if (l.Left == true)
    {
        coord temp = getCoord(snakeList, 0);
        temp.x -= 2;
        insert0(snakeList, temp);
        if (plusChecker) plusChecker = false;
        else delLast(snakeList);
    }
}

void Delete()
{
    int length = snakeList->snakeLength;
    coord temp;

    for (int i = 0; i < length; i++) {
        temp = getCoord(snakeList, i);
        gotoxy(temp.x, temp.y);
        printf("  ");
    }
}

void Output()
{
    int length = snakeList->snakeLength;
    coord temp;

    for (int i = 0; i < length; i++) {
        temp = getCoord(snakeList, i);
        gotoxy(temp.x, temp.y);

        if (i == 0) { // 머리부분의 색깔을 dark yellow로 출력
            textColor(6);
            printf("■");
            textColor(15);
        }
        else printf("■");
    }
}

void Move(int diff, int diff2)
{
    int Time = 150;
    while (1)
    {
        Sleep(Time);
        Delete();
        MoveCoor();
        Output();
        Eat();
        BlockOutput(diff, diff2);
        GameOver();
        if (_kbhit())
            break;
    }
}

void BodyPlus()
{
    plusChecker = true;
}

int CanEatFood() {
    int count;
    count = 0;

    if (food.x == 1 || food.x == (MAPSIZE - 2) * 2) count++;
    if (food.y == 1 || food.y == MAPSIZE - 2) count++;

    for (int i = 0; i < strlen(blockArray); i++) {
        if (blockArray[i].x == food.x && blockArray[i].y + 1 == food.y) { count++; }
        if (blockArray[i].x == food.x && blockArray[i].y - 1 == food.y) { count++; }
        if (blockArray[i].x + 2 == food.x && blockArray[i].y == food.y) { count++; }
        if (blockArray[i].x - 2 == food.x && blockArray[i].y == food.y) { count++; }
    }

    if (count > 2) {
        return 0;
    }
    else return 1;
}

void FoodOutput() {
    int length = snakeList->snakeLength;
    int playing;
    srand(time(NULL));

    food.x = (rand() % (MAPSIZE - 2) + 1) * 2;
    food.y = rand() % (MAPSIZE - 2) + 1;
    playing = CanEatFood();

    if (playing) {
        for (int i = 0; i < length; i++) {
            coord forTemp = getCoord(snakeList, i);
            if (forTemp.x == food.x && forTemp.y == food.y) {
                food.x = (rand() % (MAPSIZE - 2) + 1) * 2;
                food.y = rand() % (MAPSIZE - 2) + 1;
            }
        }

        gotoxy(food.x, food.y);
        textColor(14);
        printf("★");
        textColor(15);
    }
    else {
        FoodOutput();
    }
}

void Eat()
{
    coord temp = getCoord(snakeList, 0);
    if (temp.x == food.x && temp.y == food.y)
    {
        Score();
        BodyPlus();
        FoodOutput();
    }
}

void BlockOutput(int diff, int diff2)
{
    if (diff == 0) return 0;
    int ranCase;
    Component block = { 0,0 }; // 장애물 정의

    ranCase = rand() % diff; // 중요
    gotoxy(30, 29);
    printf("ranCase : %d ", ranCase);
    printf("blockCount : %d", blockCount);

    if (ranCase == 0 && blockCount < diff2) {
        do {
            block.x = (rand() % 18 + 1) * 2;
            block.y = rand() % 18 + 1;
        } while (isInSnake(block) || isInSanctuary(block) || isAtFood(block, food));

        putInSanctuary(block);
        printSanctuary(block, false); // sanctuary를 화면에 표시할지 true, false를 통해 선택

        gotoxy(block.x, block.y);
        textColor(12);
        printf("▣");
        textColor(15);
        blockArray[blockCount].x = block.x;
        blockArray[blockCount].y = block.y;
        blockCount += 1;
    }
}

void putInSanctuary(Component block) { // 장애물이 생성될 수 없는 공간, 장애물을 포함한 3*3을 생성한다.
    for (int x = 0; x < 3; x++) {
        sanctuary[blockCount].xArray[x] = block.x + 2 * (x - 1); // block의 x좌표를 포함한 3칸의 좌표를 저장
    }
    for (int y = 0; y < 3; y++) {
        sanctuary[blockCount].yArray[y] = block.y + (y - 1); // block의 y좌표를 포함한 3칸의 좌표를 저장
    }
}

bool isInSanctuary(Component block) { // 장애물이 sanctuary에 있는지 check. 있으면 true, 없으면 false
    bool xChecker = false;

    for (int count = 0; count <= blockCount; count++) {
        for (int x = 0; x < 3; x++) {
            if (block.x == sanctuary[count].xArray[x]) {
                xChecker = true; // block의 x좌표가 sanctuary내에 존재하는지 check
                break;
            }
            else xChecker = false;
        }
        if (xChecker) {
            for (int y = 0; y < 3; y++) {
                if (block.y == sanctuary[count].yArray[y]) return true; // block의 y좌표마저 sanctuary내에 존재한다면 return true
            }
        }
    }
    return false; // 위의 조건문에 안 걸리면, 없다는 의미이므로 return false
}

bool isInSnake(Component block) { // 장애물이 snake에 있는지 check. 있으면 true, 없으면 false
    int length = snakeList->snakeLength;

    for (int i = 0; i < length; i++) {
        coord forTemp = getCoord(snakeList, i);
        if (forTemp.x == block.x && forTemp.y == block.y) return true;
    }
    return false;
}

void printSanctuary(Component block, bool toggle) {
    if (toggle) {
        for (int count = 0; count <= blockCount; count++) {
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    int tempX = sanctuary[count].xArray[x];
                    int tempY = sanctuary[count].yArray[y];
                    Component tempBlock = { tempX, tempY };
                    if (!isInBlockArray(tempBlock)) {
                        gotoxy(tempX, tempY);
                        printf("●");
                    }
                }
            }
        }
    }
}

bool isInBlockArray(Component block) {
    for (int count = 0; count < blockCount; count++) {
        if (block.x == blockArray[count].x && block.y == blockArray[count].y) {
            return true;
        }
    }
    return false;
}

bool isAtFood(Component block, Component food) { // new
    if (block.x == food.x && block.y == food.y) return true;
    else return false;
}

void Score()
{
    snakeScore += 1;
    if (snakeScore == 20)
        AfterGame();
}

void GameOver()
{
    coord temp = getCoord(snakeList, 0);
    int length = snakeList->snakeLength;

    if (temp.x >= (MAPSIZE - 1) * 2 || temp.x <= 0)
    {
        system("cls");
        printf("게임 오버");
        AfterGame();
    }

    if (temp.y >= MAPSIZE - 1 || temp.y <= 0)
    {
        system("cls");
        printf("게임 오버");
        AfterGame();
    }

    for (int i = 0; i < 20; i++)
    {
        if (temp.x == blockArray[i].x && temp.y == blockArray[i].y)
        {
            system("cls");
            printf("게임 오버");
            AfterGame();
        }
    }

    for (int i = 1; i < length; i++) {
        coord forTemp = getCoord(snakeList, i);

        if (temp.x == forTemp.x && temp.y == forTemp.y) {
            system("cls");
            printf("게임 오버");
            AfterGame();
        }
    }
}

void AfterGame() {
    system("cls");
    int n;
    FILE* scoreFile;
    if (snakeScore > bestSnakeScore) {
        fopen_s(&scoreFile, "data.txt", "w");
        printf_s(scoreFile, "%d", snakeScore);
        fclose(scoreFile);
    }
    if (snakeScore == 20) {
        gotoxy(57, 10);
        printf(" CLEAR ");
    }
    else {
        gotoxy(55, 10);
        printf(" GAME OVER ");
    }

    gotoxy(50, 12);
    printf("최고점수:%d  현재점수:%d", bestSnakeScore, snakeScore);
    gotoxy(50, 14);
    printf("메인메뉴:1 게임종료:2");
    gotoxy(55, 20);
    printf("선택하세요: ");
    scanf_s("%d", &n);
    exit(0);
}

void GameExplain(int score)
{
    gotoxy(50, 4);
    printf("▶ 점수 : %d", snakeScore);

    gotoxy(50, 6);
    printf("▶ 최고 점수:  %d", score);

    gotoxy(50, 8);
    puts("▶ 방향키: 이동");

    gotoxy(50, 10);
    puts("▶ 시작하려면 오른쪽 방향키를 누르세요");

    gotoxy(50, 12);
    puts("▶ 머리가 몸이나 벽에 닿을시 게임오버입니다");

    gotoxy(50, 14);
    puts("▶ ★를 먹으면 뱀의 길이가 늘어나고 점수가 1점 추가됩니다");

    gotoxy(50, 16);
    puts("▶ 종료하려면 q를 누르세요");

    gotoxy(50, 18);
    puts("▶ 20점을 넘으면 클리어입니다");
}

int choiceGame(int mode) {
    int playing = 1;
    int xCoor = 35;
    while (playing) {
        textColor(14);
        gotoxy(xCoor, 10);
        printf("■■■■■■   ■     ■      ■      ■    ■  ■■■■■");
        gotoxy(xCoor, 11);
        printf("■        ■ ■   ■     ■ ■     ■  ■    ■");
        gotoxy(xCoor, 12);
        printf("■■■■■■   ■  ■  ■    ■■■■■    ■■      ■■■■■");
        gotoxy(xCoor, 13);
        printf("     ■   ■   ■ ■   ■     ■   ■  ■    ■");
        gotoxy(xCoor, 14);
        printf("■■■■■■   ■     ■   ■     ■   ■    ■  ■■■■■   Game");
        textColor(15);
        gotoxy(xCoor + 15, 20);
        printf("1. easy mode");
        gotoxy(xCoor + 15, 21);
        printf("2. nomal mode");
        gotoxy(xCoor + 15, 22);
        printf("3. hard mode");

        gotoxy(xCoor + 15, 25);
        printf("choice mode: ");
        gotoxy(xCoor + 28, 25);
        scanf_s("%d", &mode);
        if (mode < 0 || mode  > 3) {
            gotoxy(67, 25);
            printf("       ");
            gotoxy(44, 26);
            printf("1~3 사이에 숫자를 입력해주세요.");
            continue;
        }
        if (mode != 0) playing = 0;
    }
    system("cls");
    return mode;
}

int snakemain()
{
    int key, mode = 0;
    int select, select2 = 30;
    FILE* scoreFile;
    fopen_s(&scoreFile, "SnakeScore.txt", "r");
    fscanf_s(scoreFile, "%d", &bestSnakeScore);
    fclose(scoreFile);

    mode = choiceGame(mode);
    if (mode == 1) { select = 0; select2 = 0; }
    else if (mode == 2) { select = 7; select2 = 20; }
    else if (mode == 3) { select = 7; select2 = 30; }

    Map();
    CursorView(0);
    Init();
    Output();
    FoodOutput();
    coord temp = getCoord(snakeList, 0);

    while (1)
    {
        GameExplain(bestSnakeScore);

        if (_kbhit())
        {
            key = _getch();

            if (key == 'q')
                break;

            switch (key)
            {
            case UP:
                if (l.Down == true)
                    l.Up = false;
                else
                {
                    l.Up = true;
                    l.Down = false;
                    l.Right = false;
                    l.Left = false;
                }
                Move(select, select2);
                break;
            case DOWN:
                if (l.Up == true)
                    l.Down = false;
                else
                {
                    l.Down = true;
                    l.Up = false;
                    l.Right = false;
                    l.Left = false;
                }
                Move(select, select2);
                break;
            case LEFT:
                if (l.Right == true)
                    l.Left = false;
                else
                {
                    l.Left = true;
                    l.Down = false;
                    l.Right = false;
                    l.Up = false;
                }
                Move(select, select2);
                break;
            case RIGHT:
                if (l.Left == true)
                    l.Right = false;
                else
                {
                    l.Right = true;
                    l.Down = false;
                    l.Up = false;
                    l.Left = false;
                }
                Move(select, select2);
                break;
            case 1:
                Sleep(10000);
                break;
            default:
                break;
            }
        }
    }
    return 0;
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
