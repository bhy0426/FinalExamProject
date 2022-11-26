// 매크로 상수 정의
#define MAX_LIST 12
#define MAX_ROW 4
#define MAX_COL 3

// 구조체 정의
struct menu {
	int num;
	char *name;
	int cost;
};
struct selectedMenu {
	struct menu menu;
	short count;
};

// 전역 변수 정의
// - 구조체
struct menu menu_list[MAX_ROW][MAX_COL] =
{ {{10, "싸이버거세트", 6600}, {11, "화이트갈릭버거세트", 6900}, {12, "휠렛버거세트", 6400}},
{{20, "싸이버거", 4300}, {21, "화이트갈릭버거", 4600}, {22, "휠렛버거", 4100}},
{{30, "케이준 양념 감자(소)", 1800}, {31, "케이준 양념 감자(중)", 3200}, {32, "치즈스틱", 2000}},
{{40, "콜라", 1600}, {41, "오렌지주스", 2000}, {42, "청포도에이드", 2200}} };
struct selectedMenu cart[MAX_LIST];

// - 정수형
int list_top = 0;
int result;