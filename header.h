// ��ũ�� ��� ����
#define MAX_LIST 12
#define MAX_ROW 4
#define MAX_COL 3

// ����ü ����
struct menu {
	int num;
	char *name;
	int cost;
};
struct selectedMenu {
	struct menu menu;
	short count;
};

// ���� ���� ����
// - ����ü
struct menu menu_list[MAX_ROW][MAX_COL] =
{ {{10, "���̹��ż�Ʈ", 6600}, {11, "ȭ��Ʈ�������ż�Ʈ", 6900}, {12, "�ٷ����ż�Ʈ", 6400}},
{{20, "���̹���", 4300}, {21, "ȭ��Ʈ��������", 4600}, {22, "�ٷ�����", 4100}},
{{30, "������ ��� ����(��)", 1800}, {31, "������ ��� ����(��)", 3200}, {32, "ġ�ƽ", 2000}},
{{40, "�ݶ�", 1600}, {41, "�������ֽ�", 2000}, {42, "û�������̵�", 2200}} };
struct selectedMenu cart[MAX_LIST];

// - ������
int list_top = 0;
int result;