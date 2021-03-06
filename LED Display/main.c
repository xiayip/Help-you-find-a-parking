
#include"LedArray.h"

#define SPEED 4//控制字符移动速度


code char ZiMu[]={

0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0x80,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x07,0xBF,0xEF,0xC3,0xE7,0xE3,0xFF,0xFF,
0xBB,0xBB,0xEF,0xBD,0xDB,0xDB,0xFD,0xFF,
0xBB,0xBD,0xDF,0xBD,0xBD,0xBF,0xF3,0xFF,
0xBB,0xBE,0xBF,0xFB,0xBD,0xBF,0xC7,0xFF,
0x87,0xBF,0x7F,0xE7,0xBD,0xA7,0x00,0x01,
0xBB,0xBE,0xBF,0xFB,0xBD,0x9B,0xC7,0xFF,
0xBD,0xBD,0xDF,0xFD,0xBD,0xBD,0xF3,0xFF,
0xBD,0xBB,0xEF,0xFD,0xBD,0xBD,0xFD,0xFF,
0xBD,0xB7,0xEF,0xBD,0xBD,0xBD,0xFF,0xFF,
0xBB,0xBF,0xFF,0xBB,0xDB,0xDB,0xFF,0xFF,
0x07,0xBF,0xFF,0xC7,0xE7,0xE7,0xFF,0xFF,
0xFF,0x80,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,



};
void delay(void);             //延时
void LedArrayBlink(U8 * Byte);//此显示效果用来过度其它效果
void main()
{
	MCU_U cnt;
	MCU_U MoveCnt;
	xdata U8 temp[16][8];//将ROM中的字模转入
	TMOD=0x20;//设置定时器1为工作方式2
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	REN=1;
	SM0=0;
	SM1=1;
	EA=1;
	ES=1;
	RI=0;
	while(1)  
	{
      if(RI==1)
	  {
	     				 
		}
	}
}

void ser() interrupt 4
{
    int num;
	xdata U8 temp[16][8];
	if(RI)
	{
	RI=0;
	 if(SBUF)    
				{
				 LedArrayInit();
				 ZiMuLoadToMemery(ZiMu,temp[0]);
				 for(num=1;num<20;num++) {
				 LedArrayDisp(ZiMu);
				 }
				  }      
	 }         
   
}
void delay(void)
{
	U16 cnt1,cnt2;
	for(cnt1=1000;cnt1!=0;cnt1--)
		for(cnt2=100;cnt2!=0;cnt2--);
}

void LedArrayBlink(U8 * Byte)
{
	MCU_U speed;
	for(speed=20;speed!=0;speed--)
			LedArrayDisp(Byte);
	delay();
	for(speed=20;speed!=0;speed--)
			LedArrayDisp(Byte);
	delay();
	for(speed=20;speed!=0;speed--)
			LedArrayDisp(Byte);			
}


