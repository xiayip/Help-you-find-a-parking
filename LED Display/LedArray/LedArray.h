#ifndef __LEDARRAY_H
#define	__LEDARRAY_H
#include<reg52.h>
//类型定义
typedef unsigned	char	MCU_U ;
typedef unsigned	char	U8;
typedef signed		char	S8;
typedef unsigned	short	U16;
typedef signed		short	S16;
typedef unsigned	long	U32;
typedef signed		long	S32;

#define LEFT 1
#define RIGHT 2
#define UP 1
#define DOWN 2
/***********需要根据实际情况调整****************/
#define LedNO 8//横向串联的LED数
#define ZiFuNO 8//横向字符数
/*******************MCU引脚与点阵屏引脚对应关系********************
*	LA=P1^0	LB=P1^1	LC=P1^2	LD=p1^3
*	EN=P1^4	R1=P1^5	LT=P1^6	SK=P1^7
*	使用时点阵屏和单片机必须共地
*******************************************************************/
#define HSelect(x)	P1 &= 0XF0;P1 |= (x);
sbit en=P1^4;
#define nEN(X)		en=(X)
sbit DOut=P1^5;
#define DataOut(X)	DOut=(X)//led点阵低电平点亮
sbit lt=P1^6;
#define LT(X)		lt=(X)
sbit sk=P1^7;
#define SK(X)		sk=(X)

void ZiMuLoadToMemery(const U8 * from,U8 * to);//将字模载入到内存中
void LedArrayInit(void);//点阵屏引脚初始化
void LedArrayByteOut(U8 Byte);//单个字节输出
void LedArrayDisp(U8 * Byte);//字模输出
void LedArrayCurrentBufClr(U8 * Byte);//清除对应LED点阵屏显示缓冲区内容
void LedArrayMovLOrR(U8 *p,U32 dir);//左右移动1列
void LedArrayMovUOrD(U8 *ChaRu,U8 *p,U32 dir);//上下移动1行


#endif
