
///////////////////////////////////////////////////////////
// 
// 2022-12-10 Sat                                        
// <패스트푸트 전문점의 메뉴선택 및 금전등록기 처리 프로그램>
// '맘스터치 키오스크'
// 
// 제작 - 변하연, 김경수, 김두나
// 
///////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
// 매크로 상수 정의, 구조체 정의, 전역변수 정의가 들어있는 헤더파일 header.h
#include "header.h"

// 사용자 정의 함수 정의
void printMenu(const selectedMenu* cart);
void add(selectedMenu* cart, const selectedMenu(*menuLog)[MAX_COL]);
void cancel(selectedMenu* cart);
void quit(FILE* fp, const selectedMenu *cart, selectedMenu (*menuLog)[MAX_COL]);
void reset(selectedMenu* cart);
void printCart(const selectedMenu* cart);
void recommend(int maxNum, const selectedMenu(*menuLog)[MAX_COL]);
void initiate(FILE* fp, int* maxNum, selectedMenu *cart,selectedMenu(*menuLog)[MAX_COL]);

// 1. main()
// - 메뉴를 보여주고 무슨 작업을 할지 결정하는 메인 화면
int main(void)
{
	// 지역 변수 선언 & 초기화
	FILE* fp;
	int numMain = 0;
	int maxNum = 0;
	selectedMenu cart[MAX_LIST];
	selectedMenu menuLog[MAX_ROW][MAX_COL];

	// 초기화 작업
	// menu_log.txt 파일을 열고
	fp = fopen("menu_log.txt", "r+");
	if (fp == NULL)
	{
		printf("파일 열기 오류");
		exit(1);
	}
	// 파일에 있는 데이터를 menuLog에 가져오고 가장 높은 count를 maxNum에 저장
	initiate(fp, &maxNum, cart, menuLog);

	while (1)
	{	
		// menuLog를 바탕으로 고객들이 가장 많이 고른 메뉴를 출력
		recommend(maxNum, menuLog);
		printMenu(cart, menuLog);
		scanf("%d", &numMain);
		switch (numMain)
		{
		case 0: 
			reset(cart); // 총 금액과 cart 구조체 배열 초기화
			break;
		case 1:
			add(cart, menuLog); // 메뉴 추가
			break;
		case 2:
			cancel(cart); // 메뉴 취소
			break;
		case 3:
			quit(fp, cart, menuLog); // cart에 담긴 메뉴 계산 
			break;
		}
		// 콘솔 화면 지우기
		system("cls"); 
	}
	return 0;
}

// 2. printMenu()
// - 메뉴를 출력
void printMenu(const selectedMenu *cart, const selectedMenu(*menuLog)[MAX_COL])
{

	for (int r = 0; r < MAX_ROW; r += 2)
	{
		// menuList가 2차원 배열임을 이용해서
		// [0][0] ~ [0][2]\t[1][0] ~ [1][2]
		// [2][0] ~ [2][2]\t[3][0] ~ [3][2]
		// 이런식으로 출력
		if (r == 0)
			printf("<세트메뉴>\t\t\t<버거메뉴>\n");
		else if (r == 2)
			printf("<디저트메뉴>\t\t\t<음료메뉴>\n");
		for (int c = 0; c < MAX_COL; c++)
			printf("%d %20s %5d\t%d %20s %5d\n", menuLog[r][c].menu->num, menuLog[r][c].menu->name, menuLog[r][c].menu->cost, menuLog[r + 1][c].menu->num, menuLog[r + 1][c].menu->name, menuLog[r + 1][c].menu->cost);

		printf("\n");
	}
	printCart(cart); // cart에 담긴 메뉴 출력
	printf("지불할 총액 :       %d\n\n", result);
	printf("1. 추가\n2. 취소\n3. 입력종료\n0. 처음화면(초기화)\n");
	printf("\n번호 선택 후 Enter > ");
}

// 3. add()
// - 추가할 메뉴를 고르고 수량을 입력
// 입력된 내용을 cart 구조체 배열에 저장
void add(selectedMenu *cart, const selectedMenu (*menuLog)[MAX_COL])
{
	int numMenu, numCount, num;
	int isCorrect = 0;

	// listTop이 12라면 더 이상 추가할 메뉴가 없으므로 return
	if (listTop >= 12)
	{
		printf("더 이상 선택할 메뉴가 없습니다. 메뉴선택으로 돌아가려면 아무키나 입력하세요...\n");
		_getch();
		return ;
	}
	// 메뉴 번호가 맞는지 확인, 틀릴 시 계속 반복
	while (!isCorrect)
	{
		printf("\n메뉴번호 선택 후 Enter > ");
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
			printf("없는 메뉴 번호입니다. 다시 입력해주세요.\n");
		}
	}
	// 만약 이미 추가한 메뉴의 메뉴번호를 입력 받으면
	// cart에 저장된 구조체를 찾아 count만 변경해줌
	for (int i = 0; i < listTop; i++)
	{
		if (numMenu == cart[i].menu->num)
		{
			while (1)
			{
				printf("이미 추가한 메뉴입니다. 수량을 바꾸시겠습니까? (1: 수량변경, 2: 메뉴다시추가) Enter > ");
				scanf("%d", &num);

				if (num == 1)
				{
					result -= cart[i].menu->cost * cart[i].count;
					printf("수량 입력 후 Enter > ");
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
					printf("잘못된 번호를 입력하셨습니다. 다시 입력해주세요.\n");
					continue;
				}
			}
		}
	}
	printf("수량 입력 후 Enter > ");
	scanf("%d", &numCount);
	// 입력된 메뉴를 cart 배열에 저장
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
	// result에 고른 메뉴의 가격과 수량을 곱하여 대입
	result += menuLog[(numMenu / 10) - 1][numMenu % 10].menu->cost * numCount;
	printf("result = %d\n", result);
}

// 4. cancel()
// - 선택된 메뉴들 중 취소할 메뉴를 고름
// cart에 저장된 메뉴들 중 특정 메뉴를 지우고 싶으면
// 배열의 특정 요소를 입력받은 후 그 다음 요소를 한 칸씩 왼쪽으로 당김, listTop도 1감소
void cancel(selectedMenu* cart)
{
	int num;
	int isFound = 0;

	printf("\n");
	printCart(cart);
	while (1)
	{
		printf("취소할 메뉴버튼 입력 후 Enter(0 : cancel) > ");
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
			printf("입력한 메뉴번호를 찾을 수 없습니다. 다시 입력해주세요.\n");
		}
	}
	listTop -= 1;
}

// 5. quit()
// - 고객에게 받은 금액을 입력 후 계산
void quit(FILE *fp, const selectedMenu *cart, selectedMenu(*menuLog)[MAX_COL])
{
	int num = 0;
	int bill;
	// 선택된 메뉴가 없을 경우 함수 종료
	if (result <= 0)
	{
		return;
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
	printCart(cart);
	printf("금액 : %d\n", bill);
	printf("잔돈 : %d\n", bill - result);
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
// - 오류가 발생했거나 고객이 금액이 부족하여 계산을 하지 못한 경우 다시 초기화
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
// - 선택된 메뉴를 출력
void printCart(const selectedMenu *cart)
{
	printf("<선택된 메뉴>\n");
	for (int i = 0; i < listTop; i++)
	{
		printf("%d %s %d x %d = %d\n", cart[i].menu->num, cart[i].menu->name, cart[i].menu->cost, cart[i].count, (cart[i].menu->cost)*(cart[i].count));
	}
	printf("\n");
}

// 8. recommend()
// - 파일에서 읽어온 데이터를 바탕으로 사용자에게 메뉴를 추천
void recommend(int maxNum, const selectedMenu(*menuLog)[MAX_COL])
{

	printf("<*추천메뉴*>\n");
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
// - 파일에 있는 데이터를 menuLog에 가져오고 가장 높은 count를 maxNum에 저장
void initiate(FILE* fp , int *maxNum, selectedMenu *cart, selectedMenu (*menuLog)[MAX_COL]) 
{
	// 데이터를 menuLog 구조체 배열에 저장
	for (int r = 0; r < MAX_ROW; r++)
	{
		for (int c = 0; c < MAX_COL; c++)
		{
			menuLog[r][c].menu = (Menu*)malloc(sizeof(Menu));
			cart[(3 * r) + c].menu = (Menu*)malloc(sizeof(Menu));
			menuLog[r][c].menu->name = (char*)malloc(sizeof(char) * 20);
			fscanf(fp, "%d %s %d %hd", &menuLog[r][c].menu->num, menuLog[r][c].menu->name, &menuLog[r][c].menu->cost, &menuLog[r][c].count);
			//printf("%d %s %d %d\n", menuLog[r][c].menu->num, menuLog[r][c].menu->name, menuLog[r][c].menu->cost, menuLog[r][c].count); // 디버깅용
		}
	}
	// menuLog에서 가장 높은 count를 maxNum에 저장
	for (int r = 0; r < MAX_ROW; r++)
	{
		for (int c = 0; c < MAX_COL; c++)
		{
			if (*maxNum <= menuLog[r][c].count)
				*maxNum = menuLog[r][c].count;
		}
	}
}