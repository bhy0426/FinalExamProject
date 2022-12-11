
///////////////////////////////////////////////////////////
// 
// 2022-12-10 Sat                                        
// <�н�ƮǪƮ �������� �޴����� �� ������ϱ� ó�� ���α׷�>
// '������ġ Ű����ũ'
// 
// ���� - ���Ͽ�, ����, ��γ�
// 
///////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
// ��ũ�� ��� ����, ����ü ����, �������� ���ǰ� ����ִ� ������� header.h
#include "header.h"

// ����� ���� �Լ� ����
void printMenu(const selectedMenu* cart);
void add(selectedMenu* cart, const selectedMenu(*menuLog)[MAX_COL]);
void cancel(selectedMenu* cart);
void quit(FILE* fp, const selectedMenu *cart, selectedMenu (*menuLog)[MAX_COL]);
void reset(selectedMenu* cart);
void printCart(const selectedMenu* cart);
void recommend(int maxNum, const selectedMenu(*menuLog)[MAX_COL]);
void initiate(FILE* fp, int* maxNum, selectedMenu *cart,selectedMenu(*menuLog)[MAX_COL]);

// 1. main()
// - �޴��� �����ְ� ���� �۾��� ���� �����ϴ� ���� ȭ��
int main(void)
{
	// ���� ���� ���� & �ʱ�ȭ
	FILE* fp;
	int numMain = 0;
	int maxNum = 0;
	selectedMenu cart[MAX_LIST];
	selectedMenu menuLog[MAX_ROW][MAX_COL];

	// �ʱ�ȭ �۾�
	// menu_log.txt ������ ����
	fp = fopen("menu_log.txt", "r+");
	if (fp == NULL)
	{
		printf("���� ���� ����");
		exit(1);
	}
	// ���Ͽ� �ִ� �����͸� menuLog�� �������� ���� ���� count�� maxNum�� ����
	initiate(fp, &maxNum, cart, menuLog);

	while (1)
	{	
		// menuLog�� �������� ������ ���� ���� �� �޴��� ���
		recommend(maxNum, menuLog);
		printMenu(cart, menuLog);
		scanf("%d", &numMain);
		switch (numMain)
		{
		case 0: 
			reset(cart); // �� �ݾװ� cart ����ü �迭 �ʱ�ȭ
			break;
		case 1:
			add(cart, menuLog); // �޴� �߰�
			break;
		case 2:
			cancel(cart); // �޴� ���
			break;
		case 3:
			quit(fp, cart, menuLog); // cart�� ��� �޴� ��� 
			break;
		}
		// �ܼ� ȭ�� �����
		system("cls"); 
	}
	return 0;
}

// 2. printMenu()
// - �޴��� ���
void printMenu(const selectedMenu *cart, const selectedMenu(*menuLog)[MAX_COL])
{

	for (int r = 0; r < MAX_ROW; r += 2)
	{
		// menuList�� 2���� �迭���� �̿��ؼ�
		// [0][0] ~ [0][2]\t[1][0] ~ [1][2]
		// [2][0] ~ [2][2]\t[3][0] ~ [3][2]
		// �̷������� ���
		if (r == 0)
			printf("<��Ʈ�޴�>\t\t\t<���Ÿ޴�>\n");
		else if (r == 2)
			printf("<����Ʈ�޴�>\t\t\t<����޴�>\n");
		for (int c = 0; c < MAX_COL; c++)
			printf("%d %20s %5d\t%d %20s %5d\n", menuLog[r][c].menu->num, menuLog[r][c].menu->name, menuLog[r][c].menu->cost, menuLog[r + 1][c].menu->num, menuLog[r + 1][c].menu->name, menuLog[r + 1][c].menu->cost);

		printf("\n");
	}
	printCart(cart); // cart�� ��� �޴� ���
	printf("������ �Ѿ� :       %d\n\n", result);
	printf("1. �߰�\n2. ���\n3. �Է�����\n0. ó��ȭ��(�ʱ�ȭ)\n");
	printf("\n��ȣ ���� �� Enter > ");
}

// 3. add()
// - �߰��� �޴��� ���� ������ �Է�
// �Էµ� ������ cart ����ü �迭�� ����
void add(selectedMenu *cart, const selectedMenu (*menuLog)[MAX_COL])
{
	int numMenu, numCount, num;
	int isCorrect = 0;

	// listTop�� 12��� �� �̻� �߰��� �޴��� �����Ƿ� return
	if (listTop >= 12)
	{
		printf("�� �̻� ������ �޴��� �����ϴ�. �޴��������� ���ư����� �ƹ�Ű�� �Է��ϼ���...\n");
		_getch();
		return ;
	}
	// �޴� ��ȣ�� �´��� Ȯ��, Ʋ�� �� ��� �ݺ�
	while (!isCorrect)
	{
		printf("\n�޴���ȣ ���� �� Enter > ");
		scanf("%d", &numMenu);
		for (int r = 0; r < MAX_ROW; r++)
		{
			for (int c = 0; c < MAX_COL; c++)
			{
				if (numMenu == menuLog[r][c].menu->num)
					isCorrect = 1;
			}
		}
		if (isCorrect == 0)
		{
			printf("���� �޴� ��ȣ�Դϴ�. �ٽ� �Է����ּ���.\n");
		}
	}
	// ���� �̹� �߰��� �޴��� �޴���ȣ�� �Է� ������
	// cart�� ����� ����ü�� ã�� count�� ��������
	for (int i = 0; i < listTop; i++)
	{
		if (numMenu == cart[i].menu->num)
		{
			while (1)
			{
				printf("�̹� �߰��� �޴��Դϴ�. ������ �ٲٽðڽ��ϱ�? (1: ��������, 2: �޴��ٽ��߰�) Enter > ");
				scanf("%d", &num);

				if (num == 1)
				{
					result -= cart[i].menu->cost * cart[i].count;
					printf("���� �Է� �� Enter > ");
					scanf("%d", &numCount);
					cart[i].count = numCount;
					result += menuLog[(numMenu / 10) - 1][numMenu % 10].menu->cost * numCount;
					return;
				}
				if (num == 2)
				{
					add(cart, menuLog);
					return;
				}
				else
				{
					num = 0;
					printf("�߸��� ��ȣ�� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���.\n");
					continue;
				}
			}
		}
	}
	printf("���� �Է� �� Enter > ");
	scanf("%d", &numCount);
	// �Էµ� �޴��� cart �迭�� ����
	for (int r = 0; r < MAX_ROW; r++)
	{
		for (int c = 0; c < MAX_COL; c++)
		{
			if (numMenu == menuLog[r][c].menu->num)
			{
				cart[listTop].menu = menuLog[r][c].menu;
				cart[listTop].count = numCount;
				listTop++;
			}
		}
	}
	// result�� �� �޴��� ���ݰ� ������ ���Ͽ� ����
	result += menuLog[(numMenu / 10) - 1][numMenu % 10].menu->cost * numCount;
	printf("result = %d\n", result);
}

// 4. cancel()
// - ���õ� �޴��� �� ����� �޴��� ��
// cart�� ����� �޴��� �� Ư�� �޴��� ����� ������
// �迭�� Ư�� ��Ҹ� �Է¹��� �� �� ���� ��Ҹ� �� ĭ�� �������� ���, listTop�� 1����
void cancel(selectedMenu* cart)
{
	int num;
	int isFound = 0;

	printf("\n");
	printCart(cart);
	while (1)
	{
		printf("����� �޴���ư �Է� �� Enter(0 : cancel) > ");
		scanf("%d", &num);
		if (num == 0)
			return;
		for (int i = 0; i < listTop; i++)
		{
			if (num == cart[i].menu->num)
			{
				isFound = 1;
				result -= cart[i].menu->cost * cart[i].count;
			}
			if (isFound == 1)
				cart[i] = cart[i + 1];
		}
		if (isFound == 1)
			break;
		else if (isFound == 0)
		{
			printf("�Է��� �޴���ȣ�� ã�� �� �����ϴ�. �ٽ� �Է����ּ���.\n");
		}
	}
	listTop -= 1;
}

// 5. quit()
// - ������ ���� �ݾ��� �Է� �� ���
void quit(FILE *fp, const selectedMenu *cart, selectedMenu(*menuLog)[MAX_COL])
{
	int num = 0;
	int bill;
	// ���õ� �޴��� ���� ��� �Լ� ����
	if (result <= 0)
	{
		return;
	}
	printf("\n���� ������ �Ѿ��� %d�Դϴ�\n", result);
	while (1)
	{
		printf("�����κ��� ���� �ݾ��� �Է��� Enter > ");
		scanf("%d", &bill);
		// bill�� result���� ���� ��� �ٽ� �Է��ϰ� �ϰų� main�Լ��� ���ư�
		if (bill < result)
		{
			while (num != 1 && num != 2)
			{
				printf("�Էµ� �ݾ��� �����մϴ�. �ٽ� �Է��Ͻðڽ��ϱ�?(1: �ٽ��Է�, 2: �ʱ�ȭ��) Enter > ");
				scanf("%d", &num);
			}
			if (num == 1)
			{
				num = 0;
				continue;
			}
			else if (num == 2)
				return;
		}
		else break;
	}
	printf("\n��ǥ\n");
	printCart(cart);
	printf("�ݾ� : %d\n", bill);
	printf("�ܵ� : %d\n", bill - result);
	fseek(fp, 0L, SEEK_SET);
	for (int i = 0; i < listTop; i++)
	{
		for (int r = 0; r < MAX_ROW; r++)
		{
			for (int c = 0; c < MAX_COL; c++)
			{
				if (cart[i].menu->num == menuLog[r][c].menu->num)
					menuLog[r][c].count += cart[i].count;
			}
		}
	}
	for (int r = 0; r < MAX_ROW; r++)
	{
		for (int c = 0; c < MAX_COL; c++)
		{
		
			fprintf(fp, "%d %s %d %d\n", menuLog[r][c].menu->num, menuLog[r][c].menu->name, menuLog[r][c].menu->cost, menuLog[r][c].count);
			printf("%d %s %d %d\n", menuLog[r][c].menu->num, menuLog[r][c].menu->name, menuLog[r][c].menu->cost, menuLog[r][c].count);
			//free(menuLog[r][c].menu);
			//free(cart[(3 * r) + c].menu);
		}
	}
	fclose(fp);
	exit(1);
}

// 6. reset()
// - ������ �߻��߰ų� ���� �ݾ��� �����Ͽ� ����� ���� ���� ��� �ٽ� �ʱ�ȭ
void reset(selectedMenu *cart)
{
	result = 0;
	listTop = 0;
	for (int i = 0; i < MAX_LIST-1; i++)
	{
		cart[i].menu = NULL;
		cart[i].count = cart[MAX_LIST].count;
	}
}

// 7. printCart()
// - ���õ� �޴��� ���
void printCart(const selectedMenu *cart)
{
	printf("<���õ� �޴�>\n");
	for (int i = 0; i < listTop; i++)
	{
		printf("%d %s %d x %d = %d\n", cart[i].menu->num, cart[i].menu->name, cart[i].menu->cost, cart[i].count, (cart[i].menu->cost)*(cart[i].count));
	}
	printf("\n");
}

// 8. recommend()
// - ���Ͽ��� �о�� �����͸� �������� ����ڿ��� �޴��� ��õ
void recommend(int maxNum, const selectedMenu(*menuLog)[MAX_COL])
{

	printf("<*��õ�޴�*>\n");
	for (int r = 0; r < MAX_ROW; r++)
	{
		for (int c = 0; c < MAX_COL; c++)
		{
			if (menuLog[r][c].count == maxNum)
			{
				printf("%d %20s %5d\n", menuLog[r][c].menu->num, menuLog[r][c].menu->name, menuLog[r][c].menu->cost);
			}
		}
	}
	printf("\n");
}

// 9. initiate()
// - ���Ͽ� �ִ� �����͸� menuLog�� �������� ���� ���� count�� maxNum�� ����
void initiate(FILE* fp , int *maxNum, selectedMenu *cart, selectedMenu (*menuLog)[MAX_COL]) 
{
	// �����͸� menuLog ����ü �迭�� ����
	for (int r = 0; r < MAX_ROW; r++)
	{
		for (int c = 0; c < MAX_COL; c++)
		{
			menuLog[r][c].menu = (Menu*)malloc(sizeof(Menu));
			cart[(3 * r) + c].menu = (Menu*)malloc(sizeof(Menu));
			menuLog[r][c].menu->name = (char*)malloc(sizeof(char) * 20);
			fscanf(fp, "%d %s %d %hd", &menuLog[r][c].menu->num, menuLog[r][c].menu->name, &menuLog[r][c].menu->cost, &menuLog[r][c].count);
			//printf("%d %s %d %d\n", menuLog[r][c].menu->num, menuLog[r][c].menu->name, menuLog[r][c].menu->cost, menuLog[r][c].count); // ������
		}
	}
	// menuLog���� ���� ���� count�� maxNum�� ����
	for (int r = 0; r < MAX_ROW; r++)
	{
		for (int c = 0; c < MAX_COL; c++)
		{
			if (*maxNum <= menuLog[r][c].count)
				*maxNum = menuLog[r][c].count;
		}
	}
}