#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<string.h>

struct LIST
{
	char name[10];
	char addr[20];
	int link;
};

int main(int argc, char** argv)
{
	struct LIST *pa;
	struct LIST *pb;
	strcpy(pa->name, "�հ�");
	strcpy(pa->addr, "�۾�");
	pa->link = NULL;
	strcpy(pb->name, "����");
	strcpy(pb->addr, "������");
	pb->link = NULL;
	pa->link = pb;

	printf(" pa->name = %s, pa->addr = %s\n", pa->name, pa->addr);
	printf(" pb->name = %s, pb->addr = %s\n", pb->name, pb->addr);
	printf(" pa->link->name = %s\n", pa->link->name);
	printf(" pa->link->addr = %s\n", pa->link->addr);

	return 0;
}