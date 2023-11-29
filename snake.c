#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define UP 72

#define MAPWIDTH 20
#define MAPHEIGHT 20
#define SNAKELENGTH 17

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

int i, j, mode = 0;

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

int map[20][20] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
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
int choiceGame();
void consorClear();

void Delete();
void Output();
void Move();
void BlockOutput();

void FoodOutput();
void Eat();
void BodyPlus();
void Score();
void Clear();

void GameOver();
void GameExplain();

void gotoxy(int x, int y);
void CursorView(char show);//커서숨기기

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
    for (i = 0; i < MAPHEIGHT; i++)
    {
        for (j = 0; j < MAPWIDTH; j++)
        {
            if (map[i][j] == 1)
                printf("▣");
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
        printf("■");
    }
}

void Move(int diff)
{
    int Time = 150;
    while (1)
    {
        Sleep(Time);
        Delete();
        MoveCoor();
        Output();
        Eat();
        
        BlockOutput(diff);
        GameOver();
        if (_kbhit())
            break;
    }
}

void BodyPlus()
{
    plusChecker = true;
}

Component sanctuary[9];

void FoodOutput() {
    int length = snakeList->snakeLength;

    srand(time(NULL));

    food.x = (rand() % 18 + 1) * 2;
    food.y = rand() % 18 + 1;

    for (i = 1; i <= 3; i++) { // food 주변 좌표 123/456/789 순이다.
        for (j = 1; j <= 3; j++) {
            sanctuary[i * j - 1].x = food.x + (i - 2);
            sanctuary[i * j - 1].y = food.y + (j - 2);
        }
    }

    for (int i = 0; i < length; i++) {
        coord forTemp = getCoord(snakeList, i);
        if (forTemp.x == food.x && forTemp.y == food.y) {
            food.x = (rand() % 18 + 1) * 2;
            food.y = rand() % 18 + 1;
            for (i = 1; i <= 3; i++) { // food 주변 좌표 123/456/789 순이다.
                for (j = 1; j <= 3; j++) {
                    sanctuary[i * j - 1].x = food.x + (i - 2);
                    sanctuary[i * j - 1].y = food.y + (j - 2);
                }
            }
        }
    }

    gotoxy(food.x, food.y);
    printf("♥");
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

int blockCount = 0;
Component blockArray[20] = { {0, 0} };

void BlockOutput(int diff)
{
    int ranCase;
    int length = snakeList->snakeLength;

    ranCase = rand() % diff;
    gotoxy(30, 30);
    printf("ranCase : %d ", ranCase);
    printf("blockCount : %d", blockCount);

    if (ranCase == 0 && blockCount < 20) {
        block.x = (rand() % 18 + 1) * 2;
        block.y = rand() % 18 + 1;

        for (int i = 0; i < length; i++) {
            coord forTemp = getCoord(snakeList, i);

            if (forTemp.x == block.x && forTemp.y == block.y)
            {
                block.x = (rand() % 18 + 1) * 2;
                block.y = rand() % 18 + 1;
            }
        }

        gotoxy(block.x, block.y);
        printf("▣");
        blockArray[blockCount].x = block.x;
        blockArray[blockCount].y = block.y;
        blockCount += 1;
    }
}

void Score()
{
    static int score = 0;
    score += 1;
    gotoxy(0, 20);
    printf("점수 : %d", score);
    if (score == 20)
        Clear();
}

void GameOver()
{
    coord temp = getCoord(snakeList, 0);
    int length = snakeList->snakeLength;

    if (temp.x >= 38 || temp.x <= 0)
    {
        system("cls");
        printf("게임 오버");
        exit(0);
    }

    if (temp.y >= 19 || temp.y <= 0)
    {
        system("cls");
        printf("게임 오버");
        exit(0);
    }

    for (int i = 0; i < 20; i++)
    {
        if (temp.x == blockArray[i].x && temp.y == blockArray[i].y)
        {
            system("cls");
            printf("게임 오버");
            exit(0);
        }
    }

    for (int i = 1; i < length; i++) {
        coord forTemp = getCoord(snakeList, i);

        if (temp.x == forTemp.x && temp.y == forTemp.y) {
            system("cls");
            printf("게임 오버");
            exit(0);
        }
    }
}

void GameExplain()
{
    gotoxy(50, 8);
    puts("▶ 방향키: 이동");

    gotoxy(50, 10);
    puts("▶ 시작하려면 오른쪽 방향키를 누르세요");

    gotoxy(50, 12);
    puts("▶ 머리가 몸이나 벽에 닿을시 게임오버입니다");

    gotoxy(50, 14);
    puts("▶ ♥를 먹으면 뱀의 길이가 늘어나고 점수가 1점 추가됩니다");

    gotoxy(50, 16);
    puts("▶ 종료하려면 q를 누르세요");

    gotoxy(50, 16);
    puts("▶ 20점을 넘으면 클리어입니다");
}

void Clear()
{
    system("cls");
    printf("클리어");
    exit(0);
}

int choiceGame() {
    int playing = 1;
    while (playing) {
        gotoxy(25, 10);
        printf("■■■■■   ■      ■       ■       ■    ■  ■■■■■");
        gotoxy(25, 11);
        printf("■           ■■    ■     ■  ■     ■  ■    ■");
        gotoxy(25, 12);
        printf("■■■■■   ■  ■  ■   ■■■■■   ■■      ■■■■■");
        gotoxy(25, 13);
        printf("        ■   ■    ■■   ■      ■   ■  ■    ■");
        gotoxy(25, 14);
        printf("■■■■■   ■      ■   ■      ■   ■    ■  ■■■■■   Game");
        gotoxy(90, 17);
        printf("1. easy mode");
        gotoxy(90, 18);
        printf("2. nomal mode");
        gotoxy(90, 19);
        printf("3. hard mode");
        gotoxy(50, 25);
        printf("choice mode num: ");
        gotoxy(67, 25);
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
    return mode;
}

void consorClear() {
    for (int i = 10; i < 15; i++) {
        gotoxy(25, i);
        printf("                                                                    ");
    }
    for (int i = 17; i < 20; i++) {
        gotoxy(90, i);
        printf("             ");
    }
    gotoxy(50, 25);
    printf("                  ");
    gotoxy(44, 26);
    printf("                               ");
    gotoxy(0, 0);
}

int main()
{
    int key;
    int select;
    choiceGame();
    consorClear();
    printf("select: ");
    scanf_s("%d", &select);
    system("cls");

    Map();
    CursorView(0);
    Init();
    Output();
    FoodOutput();
    coord temp = getCoord(snakeList, 0);

    while (1)
    {
        GameExplain();

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
                Move(select);
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
                Move(select);
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
                Move(select);
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
                Move(select);
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