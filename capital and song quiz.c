#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define MAX_COUNT 20
int main(viod) {
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
	"Weight of thee world on your shoulders\nI'll kiss your waist and ease your mind",
	"Imma baddie baddie baddie\nPretty little risky baddie",
	"떠나는 그대여 울지 말아요 슬퍼 말아요\n내가 단념할게요 마음 편히 가시도록",
	"사랑아 왜 도망가\n수줍은 아이처럼",
	"Cause I know what you like boy\nYou're my chemical hype boy",
	"Oh my oh my God\n예상했어 나",
	"I see the NU EVO.\n적대적인 고난과 슬픔은",
	"How many lovers do I go through to find you\nHow many how many how many",
	"이제 괜찮니 너무 힘들었잖아\n우리 그 마무리가",
	"오래전에 함께듣던 노래가\n거리에서 내게 우연히 들려온것처럼"};
	char input[24] = {""};
	int n, cnt=0;

	i=0;

	while(cnt<10) {
		cnt++;
		n = rand() % 20;
		printf("%s\n", quiz[data[i]]);
        fgets(input, sizeof(input), stdin);
		input[strcspn(input, "\n")] = '\0';
		if (strcmp(ans[data[i]], input) == 0) {
			printf("맞았습니다.\n");
		}
		else {
			printf("틀렸습니다.\n");
		}
		i++;
	}
	return 0;
}