
#ifndef __SHELL_H
  #define __SHELL_H


#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*******************************************************
  �Ǽ������
    ���� ����ؼ��֡��������������� 
*******************************************************/  
//SHELLģ���ʼ��
extern void shellInit(void);

typedef void(* CMD_FUNC)(char * p0, char * p1, char * p2, char * p3);

extern void shellRegCmd(const char * key, CMD_FUNC func, const char * help);

// ͨ�����ڴ�ӡ���ݣ��ַ������Ȳ��ܳ���255���ֽڡ�
extern void shellPrint(const char *fmt, ...);

// ͨ������������ݣ����ݳ��Ȳ��ܳ���255���ֽڡ�
extern void shellOut(const unsigned char *data, unsigned long len);


#if defined(__cplusplus)
}
#endif 

#endif


