// ��ũ�� ��� ����
#define MAX_LIST 13
#define MAX_ROW 4
#define MAX_COL 3

// ����ü ����
struct Menu {
	int num;
	char *name;
	int cost;
};
struct selectedMenu {
	struct Menu menu;
	short count;
};

// ���� ���� ����
// - ����ü
struct Menu menuList[MAX_ROW][MAX_COL] =
{ {{10, "���̹��ż�Ʈ", 6600}, {11, "ȭ��Ʈ�������ż�Ʈ", 6900}, {12, "�ٷ����ż�Ʈ", 6400}},
{{20, "���̹���", 4300}, {21, "ȭ��Ʈ��������", 4600}, {22, "�ٷ�����", 4100}},
{{30, "������ ��� ����(��)", 1800}, {31, "������ ��� ����(��)", 3200}, {32, "ġ�ƽ", 2000}},
{{40, "�ݶ�", 1600}, {41, "�������ֽ�", 2000}, {42, "û�������̵�", 2200}} };
struct selectedMenu cart[MAX_LIST];
struct selectedMenu menuLog[MAX_ROW][MAX_COL];
FILE* fp;

// - ������
int listTop = 0;
int result;