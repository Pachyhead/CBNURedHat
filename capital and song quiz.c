#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define MAX_COUNT 20

void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

void gotoxy(int x, int y) {//원하는 x,y좌표로 이동시키는 함수
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void wall() {
	textcolor(9);//파란색
	gotoxy(15, 4);
	for (int i = 0; i < 91; i++) {
		printf("■");
	}
	textcolor(15);
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
	textcolor(10);//초록색
	for (int i = 0; i < 91; i++) {
		printf("■");
	}
	textcolor(15);

}
int main(void) {
	wall();
	int score=0;
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
	"omg", "next level", "fast forward", "좋니", "오래된 노래"};
	char quiz[20][200] = {"한국","일본", "중국", "미국", "이탈리아", 
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
	"오래전에 함께듣던 노래가 거리에서 내게 우연히 들려온것처럼"};
	char input[24] = {""};
	int n, cnt=0;
	char ch;
	int reset = 0;
	
	i = 0;
    gotoxy(80, 5);
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


			gotoxy(16, 8);
			printf("문제:%s\n", quiz[data[i]]);
			gotoxy(50, 14);
			printf("답:");
			gotoxy(53, 14);
			fgets(input, sizeof(input), stdin);
			input[strcspn(input, "\n")] = '\0';
			if (strcmp(ans[data[i]], input) == 0) {
				gotoxy(55,17);
				printf("맞았습니다.\n");
				score = score + 10;
			}
			else {
				gotoxy(55, 17);
				printf("틀렸습니다.\n");
			}
			gotoxy(80, 5);
			printf("점수:%d", score);			


			i++;
			gotoxy(55,18 );
			
			ch = getchar();

			if (ch == '\n') {
				reset = 0;
			}
		}
		
	}
	return 0;
}