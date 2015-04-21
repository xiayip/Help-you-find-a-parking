#ifndef __LEDARRAY_H
#define	__LEDARRAY_H
#include<reg52.h>
//���Ͷ���
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
/***********��Ҫ����ʵ���������****************/
#define LedNO 8//��������LED��
#define ZiFuNO 8//�����ַ���
/*******************MCU��������������Ŷ�Ӧ��ϵ********************
*	LA=P1^0	LB=P1^1	LC=P1^2	LD=p1^3
*	EN=P1^4	R1=P1^5	LT=P1^6	SK=P1^7
*	ʹ��ʱ�������͵�Ƭ�����빲��
*******************************************************************/
#define HSelect(x)	P1 &= 0XF0;P1 |= (x);
sbit en=P1^4;
#define nEN(X)		en=(X)
sbit DOut=P1^5;
#define DataOut(X)	DOut=(X)//led����͵�ƽ����
sbit lt=P1^6;
#define LT(X)		lt=(X)
sbit sk=P1^7;
#define SK(X)		sk=(X)

void ZiMuLoadToMemery(const U8 * from,U8 * to);//����ģ���뵽�ڴ���
void LedArrayInit(void);//���������ų�ʼ��
void LedArrayByteOut(U8 Byte);//�����ֽ����
void LedArrayDisp(U8 * Byte);//��ģ���
void LedArrayCurrentBufClr(U8 * Byte);//�����ӦLED��������ʾ����������
void LedArrayMovLOrR(U8 *p,U32 dir);//�����ƶ�1��
void LedArrayMovUOrD(U8 *ChaRu,U8 *p,U32 dir);//�����ƶ�1��


#endif
