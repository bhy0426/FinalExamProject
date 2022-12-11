// 매크로 상수 정의
#define MAX_LIST 13
#define MAX_ROW 4
#define MAX_COL 3

// 구조체 선언
typedef struct _Menu {
	int num;
	char *name;
	int cost;
}Menu;
typedef struct _selectedMenu {
	Menu *menu;
	short count;
}selectedMenu;

// 전역
// - int
int listTop = 0;
int result;