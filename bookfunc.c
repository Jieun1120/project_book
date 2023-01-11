#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bookfunc.h"

int showMenu()
{
	int opt;

	printf("\n===========<메뉴>===========");
	printf("\n원하는 번호를 입력하세요.\n1. 책 등록\n2. 책 확인\n3. 책 대여\n4. 책 반납\n5. 책 삭제\n6. 회원 등록\n7. 회원 정보 확인\n8. 종료\n==============================\n");
	scanf("%d", &opt);

	return opt;
}

Book readBookInfo()
{
	Book book;

	printf("==========<책 등록>==========\n");
	printf("도서명 : ");
	scanf("%s", book.title);
	printf("저자 : ");
	scanf("%s", book.author);
	printf("출판사 : ");
	scanf("%s", book.pub);
	printf("가격 : ");
	scanf("%d", &book.pri);
	printf("=============================\n");

	strcpy(book.brr, "대여 가능");

	return book;
}

void showBookInfo(Book *bptr, int numb)
{
	int i;

	printf("==========<책 확인>==========\n");
	for(i = 0; i < numb; i++)
	{
		printf("%d번. %s, %s, %s, %d, %s \n", i+1, (bptr + i) -> title, (bptr + i) -> author, (bptr + i) -> pub, (bptr + i) -> pri, (bptr + i) -> brr);
	}
	printf("=============================\n");
}

int searchBookInfo(Book *bptr)
{
	char stitle[20];
	int i;
	int chk = -1;

	printf("검색할 도서의 이름을 입력하세요 : ");
	scanf("%s", stitle);

	for(i = 0; i < 100; i++)
	{
		if(strcmp(stitle, (bptr + i) -> title) == 0)
		{
			chk = i;
			break;
		}
	}
	return chk;
}

Book borrowBook(Book binfo, Person **pmem, int numm)
{
	int i, brr, cnum;
	int chk = -1, user = 0;
	Person *mem;

	printf("대여 하시겠습니까?\n1.예 2.아니오");
	scanf("%d", &brr);

	if(brr == 1)
	{
		printf("회원 번호를 입력하세요 : ");
		scanf("%d", &cnum);

		for(i = 0; i < numm; i++)
		{
			mem = pmem[i];

			if(cnum == (mem -> unum))
			{
				user = 1;

				if(strlen(mem -> brrb) == 0)
				{
					chk = i;
					break;
				}
				else
				{
					printf("이전에 빌린 책을 먼저 반납해주세요.\n");
					break;
				}
			}
		}

		 if(user == 0)
		 {
		 	printf("회원 번호가 존재하지 않습니다.\n");
		 }
		 else if(user == 1 && chk != -1)
		 {
		 	mem = pmem[chk];

		 	printf("책을 대여했습니다. \n");
		 	strcpy(binfo.brr, "대여 불가능");
		 	strcpy((mem -> brrb), binfo.title);
		 }
	}

	else if(brr == 2)
	{
		printf("책 검색을 종료합니다.\n");
	}
	else
	{
		printf("범위 내의 값을 입력하세요.\n");
	}
	return binfo;
}

void returnBook(Book *barr, Person **pmem, int numm)
{
	int i, j, cnum, opt;
	int mchk = 0, bchk = 1;

	Person *mem;

	printf("회원 번호를 입력하세요 : ");
	scanf("%d", &cnum);

	for(i = 0; i < numm; i++)
	{
		mem = pmem[i];

		if(cnum == (mem -> unum))
		{
			mchk = 1;
			printf("책을 반납하시겠습니까?\n1.예 2.아니오");
			scanf("%d", &opt);

			if(opt == 1)
			{
				for(j = 0; j < 100; j++)
				{
					mem = pmem[i];

					if(strlen(mem -> brrb) == 0)
					{
						printf("반납할 책이 없습니다.\n");
						break;
					}
					else if(strcmp((mem -> brrb), (barr + j) -> title) == 0)
					{
						printf("반납되었습니다.\n");
						strcpy((mem -> brrb), "");
						strcpy((barr + j) -> brr, "대여 가능");

						break;
					}
					else
					{
						bchk = 0;
					}
				}
				break;
			}
			else if(opt == 2)
			{
				break;
			}
			else
			{
				printf("범위 안의 값을 입력하세요 \n");
			}
		}
	}

	if(mchk == 0)
	{
		printf("입력하신 회원이 없습니다.\n");
	}
	else if(bchk == 0)
	{
		printf("대여하셨던 책이 삭제되었습니다.\n카운터에 문의 주세요.\n");
	}
}

void deleteBook(Book *barr, int *numb, int *bi)
{
	int i, j, opt;
	int chk = 0;
	char fbook[20];
	int num = *numb;
	int bif = *bi;

	printf("삭제할 책의 이름을 적어주세요 : ");
	scanf("%s", fbook);

	for(i = 0; i < 100; i++)
	{
		if(strcmp(fbook, (barr + i) -> title) == 0)
		{
			chk = 1;
			printf("%s를 삭제하시겠습니까?\n1.예 2.아니오", (barr + i) -> title);
			scanf("%d", &opt);

			if(opt == 1)
			{
				for(j = i; j < 100; j++)
				{
					barr[j] = barr[j+1];
				}

				printf("삭제 되었습니다.\n");
				*numb = num - 1;
				*bi = bif - 1;
				break;
			}
			else if(opt == 2)
			{
				break;
			}
			else
			{
				printf("범위 안의 값을 입력하세요. \n");
			}
		}
	}

	if(chk == 0)
	{
		printf("책이 존재하지 않습니다.\n");
	}
}

Person * signup()
{
	Person *member = (Person *)malloc(sizeof(Person));
	static int num = 0;

	num++;
	printf("==========<회원 등록>==========\n");
	printf("회원 번호 : %d\n", num);
	member -> unum = num;
	printf("이름 : ");
	scanf("%s", member -> name);
	printf("전화번호 : ");
	scanf("%s", member -> phoneNum);
	strcpy(member -> brrb, "");
	printf("===============================\n");

	return member;
}

void showMemberInfo(Person **pmem, int numm)
{
	int i, cnum;
	int chk = -1;
	Person *mem;

	printf("회원 번호를 입력하세요 : ");
	scanf("%d", &cnum);

	for(i = 0; i < numm; i++)
	{
		mem = pmem[i];

		if(cnum == (mem -> unum))
		{
			chk = i;
			break;
		}
	}

	if(chk == -1)
	{
		printf("조회하신 회원이 존재하지 않습니다.\n");
	}
	else
	{
		mem = pmem[chk];

		printf("==========<회원 정보>==========\n");
		printf("회원 번호 : %d\n", mem -> unum);
		printf("이름 : %s\n", mem -> name);
		printf("전화번호 : %s\n", mem -> phoneNum);
		printf("대여한 책 : %s\n", mem -> brrb);
		printf("===============================\n");
	}
}
