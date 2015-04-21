#include"LedArray.h"
void LedArrayInit(void)			//点阵屏引脚初始化
{
	HSelect(0);
	nEN(1);
	LT(0);
	SK(0);
}

void ZiMuLoadToMemery(const U8 * from,U8 * to)		  //将字模载入到内存中
{
	U32 cnt;
	U32 TempNO=ZiFuNO*16;//一行LedNO个字节，总共16行
	for(cnt=0;cnt<TempNO;cnt++)
		*(to+cnt)=*(from+cnt);	
}

void LedArrayByteOut(U8 Byte)  //单个字节输出
{
	MCU_U cnt;
	for(cnt=0;cnt<8;cnt++){
		DataOut(Byte>>7);
		SK(1);
		Byte<<=1;
		SK(0);
	}
}

void LedArrayDisp(U8 * Byte)
{
	U8 * PTemp;
	MCU_U cnt1;
	U32 cnt2;
	U32 cnt;
	nEN(0);	
	for(cnt1=0;cnt1<16;cnt1++){
		PTemp = Byte+ZiFuNO*cnt1;
		for(cnt2=0;cnt2<LedNO;cnt2++){
			LedArrayByteOut(*(PTemp++));
		}
//延时。串联的LED板越多的时候，这个时间应当越小，否则会有闪烁现象
		for(cnt=20;cnt!=0;cnt--);
		LT(0);
		LT(1);
		HSelect(cnt1);
	}
	nEN(1);
}

void LedArrayCurrentBufClr(U8 * Byte)
{
	MCU_U cnt1;
	U32 cnt2;
	U8 *PTemp;
	for(cnt1=0;cnt1<16;cnt1++){
		PTemp = Byte+ZiFuNO*cnt1;
		for(cnt2=0;cnt2<LedNO;cnt2++)
			*(PTemp++)=0;
	}

}

/*********************************************
*	功能：向左右移动
*	参数：p指向显示内容。dir 移动方向，LEFT向左
*		RIGHT向右
*	注意：此函数只改变字模缓冲区的内容，并不实时
*		更新到屏幕
*********************************************/
void LedArrayMovLOrR(U8 *p,U32 dir)
{
	MCU_U temp=0;
	MCU_U cnt1;
	U32 cnt2;
	U8 *AdrTemp;
	 switch(dir)
	 {
	 	case 1://向左移动
/*****************************************************
*	移动方法：以位的方式操作，每一列分别向同一个方向移动。
*		移动后将第一列移动到最后一列
*****************************************************/
			for(cnt1=0;cnt1<16;cnt1++)//16行
			{
				temp = (*(p+cnt1*ZiFuNO) & 0X80)>>7; 
				for(cnt2=0;cnt2<ZiFuNO-1;cnt2++)
				{
					AdrTemp=p+cnt1*ZiFuNO+cnt2;
					*AdrTemp =(*AdrTemp<<1) + ((*(AdrTemp+1)&0x80)>>7);
				}
				AdrTemp=p+cnt1*ZiFuNO+cnt2;
				*AdrTemp=(*AdrTemp<<1)+ temp;
			}
		break;				
		case 2://向右移动
			for(cnt1=0;cnt1<16;cnt1++)//16行
			{
				temp = (*(p+(cnt1+1)*ZiFuNO-1) & 0X01)<<7; 
				for(cnt2=ZiFuNO-1;cnt2!=0;cnt2--)
				{
					AdrTemp=p+cnt1*ZiFuNO+cnt2;
					*AdrTemp =(*AdrTemp>>1) + ((*(AdrTemp-1)&0x01)<<7);
				}
				AdrTemp=p+cnt1*ZiFuNO;
				*AdrTemp=(*AdrTemp>>1)+ temp;
			}
		break;
	 }	
}

/*****************************************************
*	移动方法：显示缓冲区的内容分别移动一行	并插入新内容
*	参数说明：ChaRu为插入的内容；p为显示缓冲区的内容；
*		dir为移动方向，UP向上，DOWN向下
*****************************************************/
void LedArrayMovUOrD(U8 *ChaRu,U8 *p,U32 dir)
{
	MCU_U cnt1;
	U32 cnt2;
	U8 *PTempL;
	U8 *PTempB;
	switch(dir)
	{
		case 1:		
			for(cnt1=0;cnt1<15;cnt1++)//将第2到16行分别上移
			{
				PTempL=p+cnt1*ZiFuNO;
				PTempB=p+cnt1*ZiFuNO+ZiFuNO;
				for(cnt2=0;cnt2<LedNO;cnt2++)
					*(PTempL++)=*(PTempB++);
			}
			PTempL=p+cnt1*ZiFuNO;
			for(cnt2=0;cnt2<LedNO;cnt2++)//第16行插入新内容
				*(PTempL++)=*(ChaRu++);
		break;
		case 2:
			for(cnt1=15;cnt1!=0;cnt1--)//第1到15行分别向下移动
			{
				PTempL=p+(cnt1-1)*ZiFuNO;
				PTempB=p+cnt1*ZiFuNO;
				for(cnt2=0;cnt2<LedNO;cnt2++)
					*(PTempB++)=*(PTempL++);
			}
			for(cnt2=0;cnt2<LedNO;cnt2++)//第1行插入新内容
				*(p++)=*(ChaRu++);
		break;
	}
		
}


