/*
 * HW01_3조.c
 *
 *  Created on: 2016. 9. 21.
 *      Author: Choi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define pi 1024				//불러온 text를 담을 문자열의 길이지정

typedef struct node {		//Linked List를 위한 자기참조구조체 생성
	int num;
	char *word;
	struct node *next;
} NODE;

typedef NODE *NODEptr;		//자기참조구조체의 포인터형 선언

void search(NODEptr *);		//원하는 문자열 검색

int main() {

	FILE *fp = fopen("C:\\abc.txt", "r");	//파일을 읽기 형식으로 불러온다.
	char sentence[pi];						//불러온 파일의 문자열을 담을 공간
	char *sent;								//띄어쓰기 단위로 자른 문자열을 넣을 공간
	char *context = NULL;
	int i = 1;								//자른 문자열의 순번
	sent = (char *)malloc(sizeof(char));

	NODEptr startptr = NULL;				//Linked List의 시작부분 선언

	if (fp != NULL) {
		while( !feof(fp) ){					//불러온 파일을 미리 선언해둔 공간에 넣는다.
			fgets(sentence, sizeof(sentence), fp);
		}
	}
	else {
		printf("error\n");					//fp가 NULL이라면 파일 로드 실패
	}

	printf("불러온 파일 = C:\\abc.txt""\n");

	sent = strtok(sentence, " ");	//Linked List의 시작부분을 위해 우선 자름

	while (sent != NULL) {
		NODEptr newptr, previousptr, currentptr;
		newptr = malloc(sizeof(NODE));

		if (newptr != NULL) {			//newptr이 null이 아닐때
			newptr->num = i;			//newptr에 값을 대입
			newptr->word = sent;		//newptr이 null이라면
			newptr->next = NULL;		//메모리부족으로 생성이 안된것

			previousptr = NULL;
			currentptr = startptr;		//currentptr에 시작점으로 정한 sptr을 넣는다


			//오름차순 정렬
			while (currentptr != NULL && i > currentptr->num) {		//Linked List로 엮을 때 text의 시작부분이 꼬리가 되고
				previousptr = currentptr;							//text의 끝이 Linked List의 시작부분이 된다.
				currentptr = currentptr->next;						//Linked List로 엮을때 몇 번째인지 정보를 같이 입력하여 오름차순으로 정렬
			}

			if (previousptr == NULL) {		//오름차순 정렬을 이용하여 newptr을 구성된 링크드리스트 안에 대입
				newptr->next = startptr;	//즉, currentptr이 링크드리스트의 시작점일때, 오름차순 정렬상 최하위일때
				startptr = newptr;			//newptr을 새로운 시작점 sptr로 한다.
			}
			else {							//오름차순 정렬로 삽입할 위치를 선정하여
				previousptr->next = newptr;	//앞에 노드와 현재 노드 사이에 삽입
				newptr->next = currentptr;
			}
			sent = strtok(NULL, " ");	//다음 Linked List를 위해 잘라 둔다.
		}
		else
			printf("Error : %s not inserted. No memory available. \n", sent);
		i++;								//넣은 문자열이 몇 번째인지 기록
	}

	search(&startptr);						//문자열 검색

	printf("\n		-END-\n\n");

	fclose(fp);								//불러온 스트림을 닫는다.
	system("pause");
	return 0;
}

//문자열 검색
void search(NODEptr  *sptr) {
	printf("\n찾고싶은 단어을 입력하십시오. : ");
	NODEptr previousptr, currentptr, tempptr;
	tempptr = *sptr;

	char *sword;
	int i = 0;								//찾고 싶은 문자열의 반복 횟수 체크
	sword = (char *)malloc(sizeof(char) * 100);
	scanf("%s", sword);	printf("\n");

	while (tempptr != NULL) {				//Linked List가 끝날 때 까지 각 Node 비교
		if (strncmp(sword, tempptr->word,sizeof(sword)) == 0) {		//조사를 고려하여 찾고싶은 문자열의 길이만큼만 비교
			printf("%d번째 단어 : %s\n", tempptr->num, tempptr->word);
			i++;							//찾고 싶은 문자열의 반복 횟수 체크
		}

		tempptr = tempptr->next;
	}

	if( i != 0 ){
		printf("\n'%s' 단어가 %d번 검색되었습니다.\n", sword, i);
	}
	else{
		printf("\n'%s' 단어는 해당 파일에 존재하지 않습니다.\n",sword);
	}

	free(sword);
}
