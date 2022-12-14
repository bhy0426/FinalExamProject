
///////////////////////////////////////////////////////////
// 
// 2022-11-26 Sat                                        
// <패스트푸트 전문점의 메뉴선택 및 금전등록기 처리 프로그램>
// 
// 제작 - 변하연, 김경수, 김두나
// 
///////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
// 매크로 상수 정의, 구조체 정의, 전역변수 정의가 들어있는 헤더파일 header.h
#include "header.h"

// 사용자 정의 함수 정의
void print_menu();
void add();
void cancel();
void quit(FILE* fp);
void initiate();
void print_cart();

// 1. main()
// - 메뉴를 보여주고 무슨 작업을 할지 결정하는 메인 화면
int main(void)
{
	// 사용자들이 가장 많이 고른 메뉴를 추천
	FILE* fp;
	fp = fopen("menu_log.txt", "r+");
	if (fp == NULL)
	{
		printf("파일 열기 오류");
		exit(1);
	}
	for (int r = 0; r < MAX_ROW; r++)
	{
		for (int c = 0; c < MAX_COL; c++)
		{
			char ch[12][20];
			fscanf(fp, "%d %s %d %d", &menuLog[r][c].menu.num, ch[(3 * r) + c], &menuLog[r][c].menu.cost, &menuLog[r][c].count);
			menuLog[r][c].menu.name = ch[(3 * r) + c];
			printf("%d %s %d %d\n", menuLog[r][c].menu.num, menuLog[r][c].menu.name, menuLog[r][c].menu.cost, menuLog[r][c].count);
		}
	}
	for (int j = 0; j < MAX_ROW; j++)
	{
		for (int k = 0; k < MAX_COL; k++)
		{
			fprintf(fp, "%d %s %d %d\n", menuLog[j][k].menu.num, menuLog[j][k].menu.name, menuLog[j][k].menu.cost, menuLog[j][k].count);
			printf("%d %s %d %d\n", menuLog[j][k].menu.num, menuLog[j][k].menu.name, menuLog[j][k].menu.cost, menuLog[j][k].count);
		}
	}
	int num_main;

	while (1)
	{
		
		print_menu();
		printf("지불할 총액 :       %d\n\n", result);
		printf("1. 추가\n2. 취소\n3. 입력종료\n0. 처음화면(초기화)\n");
		printf("\n번호 선택 후 Enter > ");
		scanf("%d", &num_main);
		switch (num_main)
		{
		// 총 금액과 selected_menu_list 구조체 배열 초기화
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
			quit(fp);
			break;
		}
		// 콘솔 화면 지우기
		//system("cls"); 
	}
	return 0;
}
// 2. print_menu()
// - 버거 메뉴를 출력
void print_menu()
{
	for (int r = 0; r < MAX_ROW; r += 2)
	{
		// menu_list가 2차원 배열임을 이용해서
		// [0][0] ~ [0][2]\t[1][0] ~ [1][2]
		// [2][0] ~ [2][2]\t[3][0] ~ [3][2]
		// 이런식으로 출력
		if (r == 0)
			printf("<세트메뉴>\t\t\t<버거메뉴>\n");
		else if (r == 2)
			printf("<디저트메뉴>\t\t\t<음료메뉴>\n");
		for (int c = 0; c < MAX_COL; c++)
		{
			struct Menu x = menuList[r][c];
			struct Menu y = menuList[r + 1][c];
			printf("%d %20s %5d\t%d %20s %5d\n", x.num, x.name, x.cost, y.num, y.name, y.cost);
		}
		printf("\n");
	}
	print_cart();
}
// 3. add()
// - 추가할 메뉴를 고르고 수량을 입력
// 입력된 내용을 selected_menu_list 구조체 배열에 저장
void add()
{
	int num_menu, num_count, num10, num1, num;
	int is_correct = 0;

	// 메뉴 번호가 맞는지 확인, 틀릴 시 계속 반복
	while (!is_correct) 
	{
		printf("\n메뉴번호 선택 후 Enter > ");
		scanf("%d", &num_menu);
		for (int r = 0; r < MAX_ROW; r++)
		{
			for (int c = 0; c < MAX_COL; c++)
			{
				if (num_menu == menuList[r][c].num)
					is_correct = 1;
			}
		}
		if (is_correct == 0)
		{
			printf("없는 메뉴 번호입니다. 다시 입력해주세요.\n");
		}
	}
	// 만약 이미 추가한 메뉴의 메뉴번호를 입력 받으면
	// selected_menu_list에 저장된 구조체를 찾아 count만 변경해줌
	for (int i = 0; i < listTop; i++)
	{
		if (num_menu == cart[i].menu.num)
		{
			while (1)
			{
				printf("이미 추가한 메뉴입니다. 수량을 바꾸시겠습니까? (1: 수량변경, 2: 메뉴다시추가) Enter > ");
				scanf("%d", &num);
			
				if (num == 1)
				{
					result -= cart[i].menu.cost * cart[i].count;
					printf("수량 입력 후 Enter > ");
					scanf("%d", &num_count);
					cart[i].count = num_count;
					result += menuList[(num_menu / 10) - 1][num_menu % 10].cost * num_count;
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
					printf("잘못된 번호를 입력하셨습니다. 다시 입력해주세요.\n");
					continue;
				}
			}
		}
	}
	printf("수량 입력 후 Enter > ");
	scanf("%d", &num_count);
	// 입력된 메뉴를 selected_menu_list 배열에 저장
	for(int r = 0; r < MAX_ROW; r++)
	{
		for (int c = 0; c < MAX_COL; c++)
		{
			if (num_menu == menuList[r][c].num)
			{
				cart[listTop].menu = menuList[r][c];
				cart[listTop].count = num_count;
				listTop++;
			}
		}
	}
	// result에 고른 메뉴의 가격과 수량을 곱하여 대입
	result += menuList[(num_menu / 10) - 1][num_menu % 10].cost * num_count;
	printf("result = %d\n", result);
}
// 4. cancel()
// - 선택된 메뉴들 중 취소할 메뉴를 고름
// selected_menu_list에 저장된 메뉴들 중 특정 메뉴를 지우고 싶으면
// 배열의 특정 요소를 입력받은 후 그 다음 요소를 한 칸씩 왼쪽으로 당김, list_top도 1감소
void cancel()
{
	int num;
	int is_found = 0;

	printf("\n");
	print_cart();
	while (1)
	{
		printf("취소할 메뉴버튼 입력 후 Enter(0 : cancel) > ");
		scanf("%d", &num);
		if (num == 0)
			return;
		for (int i = 0; i < listTop; i++)
		{
			//x = selected_menu_list[i];
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
			printf("입력한 메뉴번호를 찾을 수 없습니다. 다시 입력해주세요.\n");
		}
	}
	listTop -= 1;
}
// 5. quit()
// - 고객에게 받은 금액을 입력 후 계산
void quit(FILE *fp)
{
	int num = 0;
	int bill;
	// 선택된 메뉴가 없을 경우 함수 종료
	if (result <= 0)
	{
		return 0;
	}
	printf("\n고객이 지불할 총액은 %d입니다\n", result);
	while (1)
	{
		printf("고객으로부터 받은 금액을 입력후 Enter > ");
		scanf("%d", &bill);
		// bill이 result보다 작을 경우 다시 입력하게 하거나 main함수로 돌아감
		if (bill < result)
		{
			while (num != 1 && num != 2)
			{
				printf("입력된 금액이 부족합니다. 다시 입력하시겠습니까?(1: 다시입력, 2: 초기화면) Enter > ");
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
	printf("\n명세표\n");
	print_cart();
	printf("금액 : %d\n", bill);
	printf("잔돈 : %d\n", bill - result);
	fp = fopen("menu_log.txt", "w");
	fseek(fp, 0L, SEEK_SET);
	for (int i = 0; i < listTop; i++)
	{
		for (int r = 0; r < MAX_ROW; r++)
		{
			for (int c = 0; c < MAX_COL; c++)
			{
				if (cart[i].menu.num == menuLog[r][c].menu.num)
					menuLog[r][c].count += cart[i].count;
			}
		}
	}
	for (int r = 0; r < MAX_ROW; r++)
	{
		for (int c = 0; c < MAX_COL; c++)
		{
			struct selectedMenu x = menuLog[r][c];
			printf("%d %s %d %d\n", menuLog[r][c].menu.num, menuLog[r][c].menu.name, menuLog[r][c].menu.cost, menuLog[r][c].count);
			fprintf(fp, "%d %s %d %d\n", x.menu.num, x.menu.name, x.menu.cost, x.count);
		}
	}
	fclose(fp);
	exit(1);
}
// 6. initiate()
// - 오류가 발생했거나 고객이 금액이 부족하여 계산을 하지 못한 경우 다시 초기화
void initiate()
{
	result = 0;
	struct selectedMenu x = { {0, "0", 0}, 0 };
	for (int i = 0; i < MAX_LIST; i++)
		cart[i] = x;
}
// 7. print_cart()
// - 선택된 메뉴를 출력
void print_cart()
{
	printf("<선택된 메뉴>\n");
	for (int i = 0; i < listTop; i++)
	{
		struct selectedMenu x = cart[i];
		printf("%d %s %d x %d = %d\n", x.menu.num, x.menu.name, x.menu.cost, x.count, x.menu.cost * x.count);
	}
	printf("\n");
}