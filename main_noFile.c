
///////////////////////////////////////////////////////////
// 
// 2022-11-26 Sat                                        
// <�н�ƮǪƮ �������� �޴����� �� ������ϱ� ó�� ���α׷�>
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
void print_menu();
void add();
void cancel();
void quit();
void initiate();
void print_cart();

// 1. main()
// - �޴��� �����ְ� ���� �۾��� ���� �����ϴ� ���� ȭ��
int main(void)
{
	// + ��縸 �˰�����
	// ����ڵ��� ���� ���� ���� �޴��� ��õ
	// 
	int num_main;

	while (1)
	{
		print_menu();
		printf("������ �Ѿ� :       %d\n\n", result);
		printf("1. �߰�\n2. ���\n3. �Է�����\n0. ó��ȭ��(�ʱ�ȭ)\n");
		printf("\n��ȣ ���� �� Enter > ");
		scanf("%d", &num_main);
		switch (num_main)
		{
			// �� �ݾװ� cart ����ü �迭 �ʱ�ȭ
		case 0:
			initiate();
			break;
		case 1:
			add();
			break;
		case 2:
			cancel();
			break;
		case 3:
			quit();
			break;
		}
		// �ܼ� ȭ�� �����
		system("cls"); 
	}
	return 0;
}

// 2. print_menu()
// - ���� �޴��� ���
void print_menu()
{
	for (int r = 0; r < MAX_ROW; r += 2)
	{
		// menu_list�� 2���� �迭���� �̿��ؼ�
		// [0][0] ~ [0][2]\t[1][0] ~ [1][2]
		// [2][0] ~ [2][2]\t[3][0] ~ [3][2]
		// �̷������� ���
		if (r == 0)
			printf("<��Ʈ�޴�>\t\t\t<���Ÿ޴�>\n");
		else if (r == 2)
			printf("<����Ʈ�޴�>\t\t\t<����޴�>\n");
		for (int c = 0; c < MAX_COL; c++)
		{
			struct menu x = menu_list[r][c];
			struct menu y = menu_list[r + 1][c];
			printf("%d %20s %5d\t%d %20s %5d\n", x.num, x.name, x.cost, y.num, y.name, y.cost);
		}
		printf("\n");
	}
	print_cart();
}

// 3. add()
// - �߰��� �޴��� ������ ������ �Է�
// �Էµ� ������ cart ����ü �迭�� ����
void add()
{
	int num_menu, num_count, num;
	int is_correct = 0;

	// list_top�� 12��� �� �̻� �߰��� �޴��� �����Ƿ� return
	if (list_top >= 12)
	{
		printf("�� �̻� ������ �޴��� �����ϴ�. �޴��������� ���ư����� �ƹ�Ű�� �Է��ϼ���...\n");
		_getch();
		return 0;
	}
	// �޴� ��ȣ�� �´��� Ȯ��, Ʋ�� �� ��� �ݺ�
	while (!is_correct)
	{
		printf("\n�޴���ȣ ���� �� Enter > ");
		scanf("%d", &num_menu);
		for (int r = 0; r < MAX_ROW; r++)
		{
			for (int c = 0; c < MAX_COL; c++)
			{
				if (num_menu == menu_list[r][c].num)
					is_correct = 1;
			}
		}
		if (is_correct == 0)
		{
			printf("���� �޴� ��ȣ�Դϴ�. �ٽ� �Է����ּ���.\n");
		}
	}
	// ���� �̹� �߰��� �޴��� �޴���ȣ�� �Է� ������
	// cart�� ����� ����ü�� ã�� count�� ��������
	for (int i = 0; i < list_top; i++)
	{
		if (num_menu == cart[i].menu.num)
		{
			while (1)
			{
				printf("�̹� �߰��� �޴��Դϴ�. ������ �ٲٽðڽ��ϱ�? (1: ��������, 2: �޴��ٽ��߰�) Enter > ");
				scanf("%d", &num);

				if (num == 1)
				{
					result -= cart[i].menu.cost * cart[i].count;
					printf("���� �Է� �� Enter > ");
					scanf("%d", &num_count);
					cart[i].count = num_count;
					result += menu_list[(num_menu / 10) - 1][num_menu % 10].cost * num_count;
					return;
				}
				if (num == 2)
				{
					add();
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
	scanf("%d", &num_count);
	// �Էµ� �޴��� cart �迭�� ����
	for (int r = 0; r < MAX_ROW; r++)
	{
		for (int c = 0; c < MAX_COL; c++)
		{
			if (num_menu == menu_list[r][c].num)
			{
				cart[list_top].menu = menu_list[r][c];
				cart[list_top].count = num_count;
				list_top++;
			}
		}
	}
	// result�� ���� �޴��� ���ݰ� ������ ���Ͽ� ����
	result += menu_list[(num_menu / 10) - 1][num_menu % 10].cost * num_count;
	printf("result = %d\n", result);
}

// 4. cancel()
// - ���õ� �޴��� �� ����� �޴��� ����
// cart�� ����� �޴��� �� Ư�� �޴��� ����� ������
// �迭�� Ư�� ��Ҹ� �Է¹��� �� �� ���� ��Ҹ� �� ĭ�� �������� ���, list_top�� 1����
void cancel()
{
	int num;
	int is_found = 0;

	printf("\n");
	print_cart();
	while (1)
	{
		printf("����� �޴���ư �Է� �� Enter(0 : cancel) > ");
		scanf("%d", &num);
		if (num == 0)
			return;
		for (int i = 0; i < list_top; i++)
		{
			if (num == cart[i].menu.num)
			{
				is_found = 1;
				result -= cart[i].menu.cost * cart[i].count;
			}
			if (is_found == 1)
				cart[i] = cart[i + 1];
		}
		if (is_found == 1)
			break;
		else if (is_found == 0)
		{
			printf("�Է��� �޴���ȣ�� ã�� �� �����ϴ�. �ٽ� �Է����ּ���.\n");
		}
	}
	list_top -= 1;
}

// 5. quit()
// - �������� ���� �ݾ��� �Է� �� ���
void quit()
{
	int num = 0;
	int bill;
	// ���õ� �޴��� ���� ��� �Լ� ����
	if (result <= 0)
	{
		return;
	}
	printf("\n������ ������ �Ѿ��� %d�Դϴ�\n", result);
	while (1)
	{
		printf("�������κ��� ���� �ݾ��� �Է��� Enter > ");
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
	printf("\n����ǥ\n");
	print_cart();
	printf("�ݾ� : %d\n", bill);
	printf("�ܵ� : %d\n", bill - result);
	exit(1);
}

// 6. initiate()
// - ������ �߻��߰ų� ������ �ݾ��� �����Ͽ� ����� ���� ���� ��� �ٽ� �ʱ�ȭ
void initiate()
{
	result = 0;
	struct selectedMenu x = { {0, "0", 0}, 0 };
	for (int i = 0; i < MAX_LIST; i++)
		cart[i] = x;
}

// 7. print_cart()
// - ���õ� �޴��� ���
void print_cart()
{
	printf("<���õ� �޴�>\n");
	for (int i = 0; i < list_top; i++)
	{
		struct selectedMenu x = cart[i];
		printf("%d %s %d x %d = %d\n", x.menu.num, x.menu.name, x.menu.cost, x.count, x.menu.cost * x.count);
	}
	printf("\n");
}