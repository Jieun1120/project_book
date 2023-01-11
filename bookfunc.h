#ifndef __BOOKFUNC_H__
#define __BOOKFUNC_H__

typedef struct person
{
	int unum;
	char name[20];
	char phoneNum[20];
	char brrb[20];
}Person;

typedef struct book
{
	char title[20];
	char author[20];
	char pub[20];
	int pri;
	char brr[20];
}Book;

int showMenu();
Book readBookInfo();
void showBookInfo(Book *barr, int numb);
int searchBookInfo(Book *barr);
Book borrowBook(Book binfo, Person **pmem, int numm);
void returnBook(Book *barr, Person **pmem, int numm);
void deleteBook(Book *barr, int *numb, int *bi);
Person * signup();
void showMemberInfo(Person **pmem, int numm);

#endif
