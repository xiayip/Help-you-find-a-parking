
#ifndef __RFLABEL_H
#define __RFLABEL_H

// ��ʼ�� 
extern void rfidInit(void);

// ÿ��ִ��һ�� 
extern void rfidTick(void);

// ����һҳ
extern void rfidPageNext(void); 

// ��ǰһҳ
extern void rfidPagePrev(void);

// ���Կ�ʼ
extern void rfidTestStart(int com);

// ���Խ���
extern void rfidTestStop(void);

// ��һҳ
extern void rfidNextPage(void);

// ǰһҳ
extern void rfidPrevPage(void);

#endif





