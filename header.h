// ��ũ�� ��� ����
#define MAX_LIST 13
#define MAX_ROW 4
#define MAX_COL 3

// ����ü ����
typedef struct _Menu {
	int num;
	char *name;
	int cost;
}Menu;
typedef struct _selectedMenu {
	Menu *menu;
	short count;
}selectedMenu;

// ����
// - int
int listTop = 0;
int result;