/*
 ============================================================================
 Name        : LinkedList.c
 Author      : f
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct DrviceListStruct {
	unsigned char (*Write)(unsigned long addr, unsigned char *dat,unsigned short siz);
	unsigned char (*Read)(unsigned long addr, unsigned char *dat,unsigned short siz);
	unsigned char (*Init)(unsigned long init);
	unsigned char Text[10];
} DrviceList_t, *PDrviceList;
typedef struct LinkedListStruct {
	DrviceList_t Drvice;
	struct LinkedListStruct *next;
} LinkedList_t, *PLinkedList;

PLinkedList NewLinkedList(DrviceList_t DrviceList) {
	PLinkedList Plst = (PLinkedList) malloc(sizeof(LinkedList_t));
	if (Plst == NULL) {
		printf("内存紧张！\r\n");
		return 0;
	}
	Plst->Drvice = DrviceList;
	Plst->next = NULL;
	printf("新增成功!! \r\n");
	return Plst;
}
int InitLinkedList(PLinkedList *LinkedList) {
	if (*LinkedList != NULL) {
		printf("这个链表有数据！！\r\n");
		//Free
	}
	*LinkedList = NULL;
	printf("链表成功初始化！！\r\n");
	return 0;
}
//在头加节点
long InsertHeadLinkedList(PLinkedList *LinkedList, DrviceList_t DrviceList) {
	PLinkedList *PTail = LinkedList;
	PLinkedList Plst = NewLinkedList(DrviceList);
	if (Plst == NULL) {
		printf("申请空间出错!!\r\n");
		return -1;
	}
	if (*PTail == NULL) {
		*PTail = Plst;
		return 0;
	}
	Plst->next = *PTail;
	*PTail = Plst;
	printf("成功在头添加!!\r\n");
	return 0;
}
// 在尾加节点
long InsertTailLinkedList(PLinkedList *LinkedList, DrviceList_t DrviceList) {
	PLinkedList *PTail = LinkedList;
	PLinkedList Plst = NewLinkedList(DrviceList);
	PLinkedList Tail = *LinkedList;
	unsigned long Fnum = 0;
	if (Plst == NULL) {
		return -1;
	}
	if (*PTail == NULL) {
		*PTail = Plst;
		return 0;
	}
	while (Tail->next != NULL) {
		Tail = Tail->next;
		Fnum++;
	}
	Tail->next = Plst;
	printf("在尾新加成功！\r\n");
	return Fnum;
}

//在指定位置 插入
long InsertLinkedList(PLinkedList *LinkedList, DrviceList_t DrviceList,
		DrviceList_t DrviceListCmp) {
	PLinkedList *PTail = LinkedList;
	PLinkedList Plst = NewLinkedList(DrviceList);
	PLinkedList Tail = *LinkedList;
	unsigned long Fnum = 0;
	if (Plst == NULL) {
		return -1;
	}
	if (*PTail == NULL) {
		*PTail = Plst;
		return 0;
	}
	while (Tail->next != NULL
			&& memcmp(Tail->Drvice.Text, DrviceListCmp.Text,
					sizeof(DrviceListCmp.Text)) != 0) {
		Tail = Tail->next;
		Fnum++;
	}
	Plst->next = Tail->next;
	Tail->next = Plst;
	return Fnum;
}
long LsLinkedList(PLinkedList *LinkedList) {
	PLinkedList StartLinkedList = *LinkedList;
	long Pnum = 0;
	if (StartLinkedList == NULL) {
		return -1;
	}
	printf("Ls:%s\r\n", StartLinkedList->Drvice.Text);
	while (StartLinkedList->next != NULL) {
		printf("Ls:%s\r\n", StartLinkedList->next->Drvice.Text);
		StartLinkedList = StartLinkedList->next;
		Pnum++;
	}
	return Pnum;
}
//按TEXT查找 返回查到的指针
PLinkedList FindTextLinkedList(PLinkedList *LinkedList,
		DrviceList_t DrviceListCmp) {
	PLinkedList *PTail = LinkedList;
	PLinkedList Tail = *LinkedList;
	if (*PTail == NULL) {
		return 0;
	}
	while (Tail->next != NULL
			&& memcmp(Tail->Drvice.Text, DrviceListCmp.Text,
					sizeof(DrviceListCmp.Text)) != 0) {
		Tail = Tail->next;
	}

	if (Tail->next == NULL) {
		return 0;
	}
	return Tail;
}
//按TEXT查找 删除
long FindTextDelLinkedList(PLinkedList *LinkedList, DrviceList_t DrviceListCmp) {
	PLinkedList *PTail = LinkedList;
	PLinkedList Tail = *LinkedList;
	PLinkedList Previous = *LinkedList;
	unsigned long Fnum = 0;
	if (*PTail == NULL) {
		return -1;
	}
	while (Tail->next != NULL
			&& memcmp(Tail->Drvice.Text, DrviceListCmp.Text,
					sizeof(DrviceListCmp.Text)) != 0) {
		Previous = Tail;
		Tail = Tail->next;
		Fnum++;
	}
	if (Tail->next == NULL) {
		return -1;
	}
	if (Fnum == 0) {
		*PTail = Tail->next;
		free(Previous);
		return 0;
	}
	Previous->next = Tail->next;
	free(Tail);
	return Fnum;
}
//按Grade查找 返回查到的指针
PLinkedList FindGradeLinkedList(PLinkedList *LinkedList, unsigned long Num) {
	PLinkedList *PTail = LinkedList;
	PLinkedList Tail = *LinkedList;

	unsigned long Fnum = 0;
	if (*PTail == NULL) {
		return 0;
	}
	while (Tail->next != NULL && Num > Fnum) {
		Tail = Tail->next;
		Fnum++;
		printf("F:%ld  ", Fnum);
	}
	if (Tail->next == NULL) {
		return 0;
	}
	return Tail;
}
//按Grade删除 返回查到的指针
long DelGradeLinkedList(PLinkedList *LinkedList, unsigned long Num) {
	PLinkedList *PTail = LinkedList;
	PLinkedList Tail = *LinkedList;
	PLinkedList Previous;
	unsigned long Fnum = 0;
	if (*PTail == NULL) {
		return -1;
	}
	while (Tail->next != NULL && Num > Fnum) {
		Previous = Tail;
		Tail = Tail->next;

		Fnum++;
	}
	if (Tail->next == NULL) {
		return -1;
	}
	Previous->next = Tail->next;
	free(Tail);
	return Fnum;
}
int main(void) {
	puts("Hello World"); /* prints Hello World */
	DrviceList_t Dlist;
	DrviceList_t DlistCmp;
	memset(Dlist.Text, 0, sizeof(Dlist.Text));
	memcpy(Dlist.Text, "hello\0", strlen("hello\0") + 1);
	PLinkedList PListedLst;
	if (PListedLst == NULL) {
		printf("这是一个空链表！\r\n");
	}

	InitLinkedList(&PListedLst);
	if (PListedLst == NULL) {
		printf("这是一个空链表！\r\n");
	}
	InsertTailLinkedList(&PListedLst, Dlist);
	LsLinkedList(&PListedLst);
	memset(Dlist.Text, 0, sizeof(Dlist.Text));
	memcpy(Dlist.Text, "one\0", strlen("one\0") + 1);
	InsertTailLinkedList(&PListedLst, Dlist);
	LsLinkedList(&PListedLst);

	memset(Dlist.Text, 0, sizeof(Dlist.Text));
	memcpy(Dlist.Text, "tow\0", strlen("tow\0") + 1);
	InsertTailLinkedList(&PListedLst, Dlist);

	LsLinkedList(&PListedLst);
	memset(Dlist.Text, 0, sizeof(Dlist.Text));
	memcpy(Dlist.Text, "add3\0", strlen("add3\0") + 1);
	InsertHeadLinkedList(&PListedLst, Dlist);
	LsLinkedList(&PListedLst);
	memset(Dlist.Text, 0, sizeof(Dlist.Text));
	memcpy(Dlist.Text, "add0\0", strlen("add0\0") + 1);
	InsertHeadLinkedList(&PListedLst, Dlist);
	LsLinkedList(&PListedLst);
	//InsertLinkedList(PLinkedList *LinkedList,DrviceList_t DrviceList,DrviceList_t DrviceListCmp)
	memset(Dlist.Text, 0, sizeof(Dlist.Text));
	memset(DlistCmp.Text, 0, sizeof(Dlist.Text));
	memcpy(Dlist.Text, "insert\0", strlen("insert\0") + 1);
	memcpy(DlistCmp.Text, "add0\0", strlen("add0\0") + 1);

	InsertLinkedList(&PListedLst, Dlist, DlistCmp);
	LsLinkedList(&PListedLst);

	printf("Find:%s \r\n", FindGradeLinkedList(&PListedLst, 2)->Drvice.Text);

	//InsertTailLinkedList(&PListedLst,Dlist);
	printf("NUM:%ld", LsLinkedList(&PListedLst));
	printf("删除中....\r\n");
	DelGradeLinkedList(&PListedLst, 2);
	printf("NUM:%ld", LsLinkedList(&PListedLst));
	printf("删除中.....\r\n");
	memcpy(DlistCmp.Text, "hello\0", strlen("hello\0") + 1);
	printf("Del:%ld \r\n", FindTextDelLinkedList(&PListedLst, DlistCmp));
	printf("NUM:%ld", LsLinkedList(&PListedLst));
	return EXIT_SUCCESS;
}
