#include <windows.h>
#include <string.h>
#include "dsFat.h"
#include "shell.h"
#include "dsGUI.h"
#include "guiMain.h"
#include "rfLabel.h"

extern void pageCreate(void);
extern void demoDialTick(void);

extern void demoCaculatorCreate(void);

extern void demoLineChartTick(void);
// ÿ10MSִ��һ��
extern void demoProgBarTick(void);

extern unsigned char g_touchIsOn;
extern unsigned short g_touchX, g_touchY;

extern HINSTANCE g_instance;

#define DEMO_MEM_TMP_SIZE  0x300000
long g_fontChinese16;

unsigned char * sdramAlloc(unsigned long size)
{
    return (unsigned char*)malloc(size + 3);
}

void guiDemoInit(void)
{
    char *font_handle;

    rfidInit();

    comThreadCreate();

    // ������4.3��������7������GUI��ʹ��480*272
    WM_Init(480, 272, (unsigned long)sdramAlloc(480*272*4*6), 480*272*4*6);
		
	g_touchX = g_touchY = 0xFFFF;
	
    //װ���ֿ��ļ�
    HRSRC h=FindResource(g_instance,"IDR_FONT","DFC");
    HGLOBAL h1=LoadResource(g_instance,h);
    font_handle=(char*)LockResource(h1);
    g_fontChinese16 = WM_FontLoad(16, font_handle);
		
    // ִ�е�һ������
    pageCreate();

}

void eventHandleGui(void)
{
    if (g_touchIsOn)
    {
        WM_HidState(g_touchX, g_touchY ,1);
    }
    else
    {
        WM_HidState(0, 0, 0);
    }
}

// ��BMPλͼ�ļ�ת����IMAGE��RGB888��ʽ
void bmp24FileToImage(unsigned char * fileAddr, unsigned long fileSize, 
                      unsigned char *imageAddr, unsigned long imageSize,
                      int *xSize, int * ySize)
{
	unsigned long iLineByteCnt;
	int i,j;
	
	// У���ļ��û����õĴ�С�Ƿ���ȷ
	if(imageSize < fileSize)
	{
		return;
	}
	
	// У�������ļ���ʽ
	if(fileAddr[0] != 'B' || fileAddr[1] != 'M')
	{
		return;
	}
	
	// ���ͼ��Ĵ�С��Ϣ
	*xSize = fileAddr[19]<<8 | fileAddr[18] ;
	*ySize	= fileAddr[23]<<8 | fileAddr[22];
	
	// �ж��ṩ���ڴ�ռ��Ƿ����
	if(imageSize < ((*xSize) * (*ySize) * 3))
	{
		return;
	}
	
	// ����ͼ��
	iLineByteCnt = ((*xSize * 24 + 31)>>5) <<2;

	for (i = *ySize-1; i >= 0; i--)
	{
        for (j = 0; j < *xSize; j++)
        {
           *(imageAddr + 3*j) = (unsigned char)*(fileAddr + 0x36 +(iLineByteCnt * i)+ 3*j) ;
           *(imageAddr + 3*j + 1) = (unsigned char)*(fileAddr + 0x36 +(iLineByteCnt * i)+ 3*j + 1) ;
           *(imageAddr + 3*j + 2) = (unsigned char)*(fileAddr + 0x36 +(iLineByteCnt * i)+ 3*j + 2);
        }
        imageAddr += 3*(*xSize);
	}	
}



