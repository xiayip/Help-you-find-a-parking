#include"LedArray.h"
void LedArrayInit(void)			//���������ų�ʼ��
{
	HSelect(0);
	nEN(1);
	LT(0);
	SK(0);
}

void ZiMuLoadToMemery(const U8 * from,U8 * to)		  //����ģ���뵽�ڴ���
{
	U32 cnt;
	U32 TempNO=ZiFuNO*16;//һ��LedNO���ֽڣ��ܹ�16��
	for(cnt=0;cnt<TempNO;cnt++)
		*(to+cnt)=*(from+cnt);	
}

void LedArrayByteOut(U8 Byte)  //�����ֽ����
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
//��ʱ��������LED��Խ���ʱ�����ʱ��Ӧ��ԽС�����������˸����
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
*	���ܣ��������ƶ�
*	������pָ����ʾ���ݡ�dir �ƶ�����LEFT����
*		RIGHT����
*	ע�⣺�˺���ֻ�ı���ģ�����������ݣ�����ʵʱ
*		���µ���Ļ
*********************************************/
void LedArrayMovLOrR(U8 *p,U32 dir)
{
	MCU_U temp=0;
	MCU_U cnt1;
	U32 cnt2;
	U8 *AdrTemp;
	 switch(dir)
	 {
	 	case 1://�����ƶ�
/*****************************************************
*	�ƶ���������λ�ķ�ʽ������ÿһ�зֱ���ͬһ�������ƶ���
*		�ƶ��󽫵�һ���ƶ������һ��
*****************************************************/
			for(cnt1=0;cnt1<16;cnt1++)//16��
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
		case 2://�����ƶ�
			for(cnt1=0;cnt1<16;cnt1++)//16��
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
*	�ƶ���������ʾ�����������ݷֱ��ƶ�һ��	������������
*	����˵����ChaRuΪ��������ݣ�pΪ��ʾ�����������ݣ�
*		dirΪ�ƶ�����UP���ϣ�DOWN����
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
			for(cnt1=0;cnt1<15;cnt1++)//����2��16�зֱ�����
			{
				PTempL=p+cnt1*ZiFuNO;
				PTempB=p+cnt1*ZiFuNO+ZiFuNO;
				for(cnt2=0;cnt2<LedNO;cnt2++)
					*(PTempL++)=*(PTempB++);
			}
			PTempL=p+cnt1*ZiFuNO;
			for(cnt2=0;cnt2<LedNO;cnt2++)//��16�в���������
				*(PTempL++)=*(ChaRu++);
		break;
		case 2:
			for(cnt1=15;cnt1!=0;cnt1--)//��1��15�зֱ������ƶ�
			{
				PTempL=p+(cnt1-1)*ZiFuNO;
				PTempB=p+cnt1*ZiFuNO;
				for(cnt2=0;cnt2<LedNO;cnt2++)
					*(PTempB++)=*(PTempL++);
			}
			for(cnt2=0;cnt2<LedNO;cnt2++)//��1�в���������
				*(p++)=*(ChaRu++);
		break;
	}
		
}


