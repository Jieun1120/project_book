/*
	Date : 10월 26일
	Description : 구조체를 이용한 도서 관리 프로그램
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bookfunc.h"

int main()
{
	Book barr[100];
	Book brrb;
	Person *pmem[50];
	int opt, chk;
	int i = 0, j = 0, numb = 0, numm = 0;

	opt = showMenu();
	while(1)
	{
		if(opt == 1)
		{
			if(numb < 100)
			{
				barr[i] = readBookInfo();
				i++;
				numb++;
			}
			else
				printf("등록 가능 권수를 넘었습니다.\n");
		}
		else if(opt == 2)
		{
			showBookInfo(barr, numb);
		}
		else if(opt ==3)
		{
			chk = searchBookInfo(barr);
			if(chk != -1)
			{
				printf("==========<책 검색>==========\n");
				printf("검색하신 도서의 정보입니다.\n도서명 : %s\n저자 : %s\n출판사: %s\n가격 : %d\n%s\n", barr[chk].title, barr[chk].author, barr[chk].pub, barr[chk].pri, barr[chk].brr);
				printf("=============================\n");

				if(strcmp(barr[chk].brr, "대여 가능") == 0)
				{
					brrb = borrowBook(barr[chk], pmem, numm);
					barr[chk] = brrb;
				}
				else
				{
					printf("현재 대출중입니다.\n");
				}
			}
			else
				printf("입력하신 이름의 도서가 존재하지 않습니다.\n");
		}
		else if(opt == 4)
		{
			returnBook(barr, pmem, numm);
		}
		else if(opt == 5)
		{
			deleteBook(barr, &numb, &i);
		}
		else if(opt == 6)
		{
			if(numm < 50)
			{
				pmem[j] = signup();
				j++;
				numm++;
			}
			else
			{
				printf("현재 회원을 받고 있지 않습니다.\n");
			}
		}
		else if(opt == 7)
		{
			showMemberInfo(pmem, numm);
		}
		else if(opt == 8)
		{
			printf("종료합니다.\n");
			break;
		}
		else
		{
			printf("범위 내의 값을 입력하세요.\n");
		}
		opt = showMenu();
	}

	for(i = 0; i < 50; i++)
	{
		free(pmem[i]);
	}

	return 0;
}
