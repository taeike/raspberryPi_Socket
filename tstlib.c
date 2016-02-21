#include "tstlib.h"

/** ---------------------------------------------------------------------- **/
void fnToken(char *Str, char *Head, char *Tail, char IndChar)
{
    int indsw = 1;
    while(indsw)  {
        (*Str == IndChar) ? (Str++, strcpy(Tail , Str), indsw = 0) :
        (*Head = *Str , *Head++ , *Str++);
    }
    *Head-- = 0x00;
}

/** ---------------------------------------------------------------------- **/
void fnRTram(char *Str, char *Dat)
{
	int	StrLen;
	StrLen = strlen(Str) - 1;

	while(*(Str+StrLen) == ' ' || *(Str+StrLen) == '	') StrLen--;
	*(Str+StrLen+1) = 0x00;
	strcpy(Dat, Str);

/**
before modify
	while(indsw)	{
		(*(Str+StrLen) == ' ' || *(Str+StrLen) == '	') ? (StrLen--) : (indsw = 0);
	}
	strncpy(Dat, Str, StrLen+1);
**/
}

/** ---------------------------------------------------------------------- **/
void fnLTram(char *Str, char *Dat)
{
	while(*Str == ' ' || *Str == '	') Str++;
	strcpy(Dat,Str);

/** before modify
	while(*Str)	{ (*Str == ' ' || *Str == '	') ?  *Str++ : (*Dat = *Str, *Str++, *Dat++);
	}
**/
}

/** ---------------------------------------------------------------------- **/
/** Debug or Logging Message with time stemp **/

void	DBPt(const char *fmt, ...)
{
	char *Str;
	va_list vlist;

	Str = malloc(1024);

	va_start(vlist, fmt);
	vsprintf(Str, fmt, vlist);
	va_end(vlist);
	DBP("%s", Str);
}

/** ---------------------------------------------------------------------- **/
/** Debug message to stdout(display) **/
void	DBP(const char *fmt, ...)
{
	va_list vlist;

	va_start(vlist, fmt);
	vprintf(fmt, vlist);
	va_end(vlist);
}

/** ---------------------------------------------------------------------- **/
void	PrintXY(int x, int y, const char *fmt, ...)
{
	_PUT_XY(x, y);
	va_list vlist;

	va_start(vlist, fmt);
	vprintf(fmt, vlist);
	va_end(vlist);
}

/** ---------------------------------------------------------------------- **/
void fnGetTime(char *Time)
{
	char	ret_1[16];
	struct  timeval dt_t;
	struct  tm  *tm_t;

	gettimeofday(&dt_t, NULL);

	tm_t = localtime(&dt_t.tv_sec);
	//Time = &ret_1[0];

	sprintf( Time, "%04d%02d%02d%02d%02d%02d%c",
				tm_t->tm_year + 1900,
				tm_t->tm_mon + 1,
				tm_t->tm_mday,
				tm_t->tm_hour,
				tm_t->tm_min,
				tm_t->tm_sec,
				0x00);
}
/** ---------------------------------------------------------------------- **/
void	fnGetTimeString(char *Str, char d_t)
{
	struct  timeval dt_t;
	struct  tm  *tm_tt;

	gettimeofday(&dt_t, NULL);

	tm_tt = localtime(&dt_t.tv_sec);
	switch(d_t)	{
		case _DATE_:
			//fnTimeGet(Str, tm_tt->tm_year+1900,tm_tt->tm_mon+1,tm_tt->tm_mday, 0x00);
			sprintf(Str, "%04d%02d%02d%c", tm_tt->tm_year+1900,tm_tt->tm_mon+1,tm_tt->tm_mday, 0x00);
			break;
		case _TIME_:
			//fnTimeGet(Str, tm_tt->tm_year+1900,tm_tt->tm_mon+1,tm_tt->tm_mday,tm_tt->tm_hour,tm_tt->tm_min, tm_tt->tm_sec, 0x00);
			sprintf(Str, "%04d%02d%02d%02d%02d%02d%c", tm_tt->tm_year+1900,tm_tt->tm_mon+1,tm_tt->tm_mday,tm_tt->tm_hour,tm_tt->tm_min, tm_tt->tm_sec, 0x00);
			break;
		default:
			//fnTimeGet(Str, tm_tt->tm_year+1900,tm_tt->tm_mon+1,tm_tt->tm_mday,tm_tt->tm_hour,tm_tt->tm_min, tm_tt->tm_sec, 0x00);
			sprintf(Str, "%04d%02d%02d%02d%02d%02d%c", tm_tt->tm_year+1900,tm_tt->tm_mon+1,tm_tt->tm_mday,tm_tt->tm_hour,tm_tt->tm_min, tm_tt->tm_sec, 0x00);
			break;
	}
			
}

/** ---------------------------------------------------------------------- **/
void	fnTimeGet(const char *fmt, ...)
{
	va_list vlist;

	TimeStr = malloc(200);

	va_start(vlist, fmt);
	vsprintf(TimeStr, fmt, vlist);
	va_end(vlist);
}
/** =========================
	ANSI control function
    ========================= **/
/** ---------------------------------------------------------------------- **/
void PosXY(int y, int x)
{
	printf("[%d;%dH", x, y);	// Move cursor to x, y
}

/** ---------------------------------------------------------------------- **/
void GetString(int x, int y, char *Str, char *ViewStr)
{
	PosXY(x, y);
	PutString(x , y, ViewStr);
	PosXY(x + strlen(ViewStr), y);
	scanf("%s", Str);
	if(strlen(Str) < 1)
		printf("No Data Input\n\n");
}

/** ---------------------------------------------------------------------- **/
void GetNumeric(int x, int y, int Num)
{
	PosXY(x, y);
	scanf("%d", Num);
}
/** ---------------------------------------------------------------------- **/
void PutString(int x, int y, char *Str)
{
	PosXY(x, y);
	printf("%s", Str);
}

/** ---------------------------------------------------------------------- **/
//	Arrow Key Test 
void GetImmString(int x, int y, char *Str)
{
	int	i;
	char	inpChar;
	char	inpStr[101];

	memset(inpStr, 0x00, 101);

	PosXY(x, y);

	for(i = 0; i < 20; i++)	{
		inpChar = getchar();
		if(inpChar == 0x0d || inpChar == 0x0a)
			break;
		inpStr[i] = inpChar;
		if(inpChar == '')	{
			inpChar = getchar();
			inpStr[i+1] = inpChar;
			i++;
		}
		printf("[%c], [%s]\n", inpChar, inpStr);
	}
	inpStr[i] = 0x00;

	strcpy(Str, inpStr);
}
/** ---------------------------------------------------------------------- **/
void ansi_print()
{
	printf("[0m  : 모든 색과 스타일 초기화\n");
	printf("[1m  : 굵게(bold) / 밝게\n");
	printf("[3m  : 이탤릭체(italic)\n");
	printf("[4m  : 밑줄(underline)\n");
	printf("[7m  : 반전(글자색/배경색을 거꾸로)\n");
	printf("[9m  : 가로줄 치기\n");
	printf("[22m : 굵게(bold) 제거\n");
	printf("[23m : 이탤릭체(italic)제거\n");
	printf("[24m : 밑줄(underline)제거\n");
	printf("[27m : 반전 제거\n");
	printf("[29m : 가로줄 제거\n");
	printf("[30m : 글자색:검정\n");
	printf("[31m : 글자색:빨강\n");
	printf("[32m : 글자색:초록\n");
	printf("[33m : 글자색:노랑\n");
	printf("[34m : 글자색:파랑\n");
	printf("[35m : 글자색:마젠트(분홍)\n");
	printf("[36m : 글자색:시안(청록)\n");
	printf("[37m : 글자색:백색\n");
	printf("[39m : 글자색으로 기본값으로\n");
	printf("[40m : 바탕색:흑색\n");
	printf("[41m : 바탕색:적색\n");
	printf("[42m : 바탕색:녹색\n");
	printf("[43m : 바탕색:황색\n");
	printf("[44m : 바탕색:청색\n");
	printf("[45m : 바탕색:분홍색\n");
	printf("[46m : 바탕색:청록색\n");
	printf("[47m : 바탕색:흰색\n");
	printf("[49m : 바탕색을 기본값으로\n");
}

/** ---------------------------------------------------------------------- **/
/** ---------------------------------------------------------------------- **/
/** ---------------------------------------------------------------------- **/
/** ---------------------------------------------------------------------- **/
----->>>>>>
Header file 이다. 
tstlib.h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <sys/errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <wiringPi.h>

#ifndef	SUCC
#define	SUCC	1
#endif

#ifndef	FAIL
#define	FAIL 0
#endif
#define _TIME_ 't'
#define _DATE_ 'd'

/** ansi color code
[0m  : 모든 색과 스타일 초기화
[1m  : 굵게(bold) / 밝게
[3m  : 이탤릭체(italic)
[4m  : 밑줄(underline)
[7m  : 반전(글자색/배경색을 거꾸로)
[9m  : 가로줄 치기
[22m : 굵게(bold) 제거
[23m : 이탤릭체(italic)제거
[24m : 밑줄(underline)제거
[27m : 반전 제거
[29m : 가로줄 제거
[30m : 글자색:검정
[31m : 글자색:빨강
[32m : 글자색:초록
[33m : 글자색:노랑
[34m : 글자색:파랑
[35m : 글자색:마젠트(분홍)
[36m : 글자색:시안(청록)
[37m : 글자색:백색
[39m : 글자색으로 기본값으로
[40m : 바탕색:흑색
[41m : 바탕색:적색
[42m : 바탕색:녹색
[43m : 바탕색:황색
[44m : 바탕색:청색
[45m : 바탕색:분홍색
[46m : 바탕색:청록색
[47m : 바탕색:흰색\n");
[49m : 바탕색을 기본값으로\n");
**/

/** ---------------------------------------------------------------------- **/
/** ANSI Screen control code **/
#define _CLR			"\e[0m ";	// 모든 색과 스타일 초기화
#define _BOLD			"\e[1m ";	// 굵게(bold 
#define _ITALIC		 	"\e[3m ";	// 이탤릭체(italic
#define _UNDERLINE		"\e[4m ";	// 밑줄 (underline
#define _REVERSE		"\e[7m ";	// 반전(글자색/배경색을 거꾸로
#define _CANCLE		 	"\e[9m ";	// 가로줄(취소선
#define _CLR_BOLD		"\e[22m";	// 굵게(bold		제거
#define _CLR_ITALIC		"\e[23m";	// 이탤릭체(italic 제거
#define _CLR_UNDERLINE	"\e[24m";	// 밑줄(underline	제거
#define _CLR_REVERSE	"\e[27m";	// 반전			 제거
#define _CLR_CANCLE		"\e[29m";	// 가로줄			제거
#define _BLACK			"\e[30m";	// 글자색	검정
#define _RED			"\e[31m";	// 글자색	빨강
#define _GREEN			"\e[32m";	// 글자색	초록
#define _YELLOW		 	"\e[33m";	// 글자색	노랑
#define _BLUE			"\e[34m";	// 글자색	파랑
#define _MAGENTA		"\e[35m";	// 글자색	마젠트(분홍
#define _CYAN			"\e[36m";	// 글자색	시안(청록
#define _WHITE			"\e[37m";	// 글자색	백색
#define _BAS			"\e[39m";	// 글자색	기본값으로
#define _B_BLACK		"\e[40m";	// 바탕색	흑색
#define _B_RED			"\e[41m";	// 바탕색	적색
#define _B_GREEN		"\e[42m";	// 바탕색	녹색
#define _B_YELLOW		"\e[43m";	// 바탕색	황색
#define _B_BLUE		 	"\e[44m";	// 바탕색	청색
#define _B_MAGENTA		"\e[45m";	// 바탕색	분홍색
#define _B_CYAN		 	"\e[46m";	// 바탕색	청록색
#define _B_WHITE		"\e[47m";	// 바탕색	흰색
#define _B_CLR			"\e[49m";	// 바탕색	기본값으로
#define _ALL_CLR		"\e[49m\e[39m"; // 모두 기본으로

#define	_PUT_XY(y, x)	printf("[%d;%dH", x, y);	// Move cursor to x, y
#define _PUT_STR(y,x,str) printf("[%d;%dH%s", x, y, str);	// Move cursor to x, y
#define _CLR_SCR() printf("[s[2J");	// Clear terminal
#define _RST_SCR() printf("[u");	// restore termainal status
/** ---------------------------------------------------------------------- **/
/** ProtoType **/
void	fnToken(char *Str, char *Head, char *Tail, char IndChar);
void	fnRTram(char *Str, char *Dat);
void	fnLTram(char *Str, char *Dat);
void    fnDefaultStatusSet(FILE *df);
void	fnGettime(char *);
void	ParseStatus();

void	DBP(const char *fmt, ...);
void	DBF(const char *fmt, ...);
void	fnGetTimeString(char *Str, char);
void	fnTimeGet(const char *fmt, ...);
void	PrintXY(int , int, const char *fmt, ...);

/** ANSI Screen control function ----------------------------------------- **/
void PosXY(int x, int y);
void GetString(int x, int y, char *Str, char *);
void PutString(int x, int y, char *Str);
void GetImmString(int, int ,char *Str);
void ansi_print();
/** ---------------------------------------------------------------------- **/
char *TimeStr;
/** ---------------------------------------------------------------------- **/
