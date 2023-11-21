#include <stdio.h>
#include <stdlib.h>

typedef struct _coord {
    int x;
    int y;
} coord;

typedef struct _listNode {
    coord data;
	struct _listNode* link;
} listNode;

// 헤드 노드는 클래스의 멤버변수를 저장하는 공간과 같은 역할을 한다. 뱀의 길이와 같은 변수들을 이곳에 정의해두고 활용할 수 있다.
typedef struct _headNode {
    coord data;
	int snakeLength;
	struct _listNode* link;
} headNode;

void add(headNode* head, coord value) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 동적 할당
    if (!newNode) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = value; // 새로운 노드의 데이터 설정
    newNode->link = NULL;  // 새로운 노드의 링크 초기화

    // 헤드부터 시작해서 맨 끝까지 이동
    if (head->link == NULL) { // 노드가 1개일 때(head->link부터 출발하는 이유는 head는 null이 될 수 없기 때문이다.)
        head->link = newNode;
        head->snakeLength += 1;
    }
    else { // 노드가 2개 이상일 때 
        listNode* current = head->link; 
        while (current) {
            if (current->link == NULL) break;
            current = current->link;
        }
        // 맨 끝에 새로운 노드 추가
        current->link = newNode;
        head->snakeLength += 1;
    }
}

// 연결 리스트 출력 함수
void printList(headNode* head) {
    // 헤드부터 시작해서 맨 끝까지 이동
    if (head->link == NULL) { // 노드가 1개일 때
        printf("(%d, %d) ", head->data.x, head->data.y);
    }
    else { // 노드가 2개 이상일 때
        listNode* current = head->link;
        printf("(%d, %d) ", head->data.x, head->data.y);
        while (current) {
            printf("(%d, %d) ", current->data.x, current->data.y);
            current = current->link;
        }
        printf("\n");
    }
}

// 연결 리스트 메모리 해제 함수
void freeList(headNode* head) {
    if (head->link == NULL) {
        free(head);
    }
    else {
        listNode* current = head->link;
        while (current) {
            listNode* temp = current;
            current = current->link;
            free(temp);
        }
        free(head);
    }
}

// 연결 리스트 마지막 노드 삭제 함수
void delLast(headNode* head) {
    if (head->link == NULL) {
        free(head); // 게임오버(나중에 수정할 것)
    }
    else {
        listNode* current = head->link;
        while (current) {
            if (current->link->link == NULL) {
                current->link = NULL;
                head->snakeLength -= 1;
            }
            current = current->link;
        }
    }
}

/*
int main(void) {
    headNode *h1 = (headNode *)malloc(sizeof(headNode));
    coord temp = { 10, 20 };
    h1->data = temp;
    h1->link = NULL;
    h1->snakeLength = 1; //뱀의 길이는 1로 초기화 해주어야 한다.

    coord temp1 = { 20, 30 };

    add(h1, temp1);
    add(h1, temp1);
    add(h1, temp1);
    add(h1, temp1);
    add(h1, temp1);
    add(h1, temp1);

    printList(h1);
    printf("%d\n", h1->snakeLength);

    delLast(h1);

    printList(h1);
    printf("%d", h1->snakeLength);

    freeList(h1);

	return 0;
}
*/
