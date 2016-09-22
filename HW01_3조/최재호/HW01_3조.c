/*
 * HW01_3��.c
 *
 *  Created on: 2016. 9. 21.
 *      Author: Choi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define pi 1024				//�ҷ��� text�� ���� ���ڿ��� ��������

typedef struct node {		//Linked List�� ���� �ڱ���������ü ����
	int num;
	char *word;
	struct node *next;
} NODE;

typedef NODE *NODEptr;		//�ڱ���������ü�� �������� ����

void search(NODEptr *);		//���ϴ� ���ڿ� �˻�

int main() {

	FILE *fp = fopen("C:\\abc.txt", "r");	//������ �б� �������� �ҷ��´�.
	char sentence[pi];						//�ҷ��� ������ ���ڿ��� ���� ����
	char *sent;								//���� ������ �ڸ� ���ڿ��� ���� ����
	char *context = NULL;
	int i = 1;								//�ڸ� ���ڿ��� ����
	sent = (char *)malloc(sizeof(char));

	NODEptr startptr = NULL;				//Linked List�� ���ۺκ� ����

	if (fp != NULL) {
		while( !feof(fp) ){					//�ҷ��� ������ �̸� �����ص� ������ �ִ´�.
			fgets(sentence, sizeof(sentence), fp);
		}
	}
	else {
		printf("error\n");					//fp�� NULL�̶�� ���� �ε� ����
	}

	printf("�ҷ��� ���� = C:\\abc.txt""\n");

	sent = strtok(sentence, " ");	//Linked List�� ���ۺκ��� ���� �켱 �ڸ�

	while (sent != NULL) {
		NODEptr newptr, previousptr, currentptr;
		newptr = malloc(sizeof(NODE));

		if (newptr != NULL) {			//newptr�� null�� �ƴҶ�
			newptr->num = i;			//newptr�� ���� ����
			newptr->word = sent;		//newptr�� null�̶��
			newptr->next = NULL;		//�޸𸮺������� ������ �ȵȰ�

			previousptr = NULL;
			currentptr = startptr;		//currentptr�� ���������� ���� sptr�� �ִ´�


			//�������� ����
			while (currentptr != NULL && i > currentptr->num) {		//Linked List�� ���� �� text�� ���ۺκ��� ������ �ǰ�
				previousptr = currentptr;							//text�� ���� Linked List�� ���ۺκ��� �ȴ�.
				currentptr = currentptr->next;						//Linked List�� ������ �� ��°���� ������ ���� �Է��Ͽ� ������������ ����
			}

			if (previousptr == NULL) {		//�������� ������ �̿��Ͽ� newptr�� ������ ��ũ�帮��Ʈ �ȿ� ����
				newptr->next = startptr;	//��, currentptr�� ��ũ�帮��Ʈ�� �������϶�, �������� ���Ļ� �������϶�
				startptr = newptr;			//newptr�� ���ο� ������ sptr�� �Ѵ�.
			}
			else {							//�������� ���ķ� ������ ��ġ�� �����Ͽ�
				previousptr->next = newptr;	//�տ� ���� ���� ��� ���̿� ����
				newptr->next = currentptr;
			}
			sent = strtok(NULL, " ");	//���� Linked List�� ���� �߶� �д�.
		}
		else
			printf("Error : %s not inserted. No memory available. \n", sent);
		i++;								//���� ���ڿ��� �� ��°���� ���
	}

	search(&startptr);						//���ڿ� �˻�

	printf("\n		-END-\n\n");

	fclose(fp);								//�ҷ��� ��Ʈ���� �ݴ´�.
	system("pause");
	return 0;
}

//���ڿ� �˻�
void search(NODEptr  *sptr) {
	printf("\nã����� �ܾ��� �Է��Ͻʽÿ�. : ");
	NODEptr previousptr, currentptr, tempptr;
	tempptr = *sptr;

	char *sword;
	int i = 0;								//ã�� ���� ���ڿ��� �ݺ� Ƚ�� üũ
	sword = (char *)malloc(sizeof(char) * 100);
	scanf("%s", sword);	printf("\n");

	while (tempptr != NULL) {				//Linked List�� ���� �� ���� �� Node ��
		if (strncmp(sword, tempptr->word,sizeof(sword)) == 0) {		//���縦 ����Ͽ� ã����� ���ڿ��� ���̸�ŭ�� ��
			printf("%d��° �ܾ� : %s\n", tempptr->num, tempptr->word);
			i++;							//ã�� ���� ���ڿ��� �ݺ� Ƚ�� üũ
		}

		tempptr = tempptr->next;
	}

	if( i != 0 ){
		printf("\n'%s' �ܾ %d�� �˻��Ǿ����ϴ�.\n", sword, i);
	}
	else{
		printf("\n'%s' �ܾ�� �ش� ���Ͽ� �������� �ʽ��ϴ�.\n",sword);
	}

	free(sword);
}
