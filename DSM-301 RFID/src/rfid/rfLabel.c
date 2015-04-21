#include<stdio.h>
#include <windows.h>
#include "serial.h"
#include "shell.h"
#include "rfLabel.h"

extern void pageSetCardNum(int num);

#define FILTRATION_TIME			1   //s 

#define FILTRATION_PAGE_COUNT 	3

typedef struct
{
    unsigned long id;
    unsigned char lossPower;
    unsigned long keepSecond;
    unsigned char msgCount[10];  // ���10���ڽ��յ���Ϣ���� 
}T_LABLE;

typedef struct
{
	unsigned long id;
	unsigned long lossPower;
	unsigned long count;
	unsigned long timeCount;
}FILTRATION;

#define TALBE_NUM    200
T_LABLE  g_label[TALBE_NUM];

#define LINE_PER_PAGE   6   // ÿҳ6�� 

FILTRATION g_filtrationArray[TALBE_NUM];

unsigned long g_filtrationArrayNumber = 0;

int g_labelNum, g_pageNo;

int g_rfidTestOn;

void addInfoToShowArray(unsigned long id, unsigned long lossPower);

void rfidRcvMsg(unsigned char msg[])
{
    unsigned long id;
    unsigned char lossPower;
    int i;
    
    if ((msg[0] ^ msg[1] ^ msg[2] ^ msg[3] ^ msg[4] ^ msg[5]) != msg[6])
    {
        shellPrint("check error ");
        return;
    }

    id = (unsigned long)msg[5] 
      | ((unsigned long)msg[4] << 8)
      | ((unsigned long)msg[3] << 16)
      | ((unsigned long)msg[2] << 24);

    lossPower = msg[1] & 0x80 ?  1 : 0;
		
	for (i = 0; i < g_labelNum; i++)
    {
        if (g_label[i].id == id)
        {
            g_label[i].lossPower = lossPower;
            g_label[i].msgCount[9]++;
                        
            return;
        }
    }
    
    //filtration count
    for(i=0; i<g_filtrationArrayNumber; i++)
	{		
	    if(g_filtrationArray[i].id == id)
	    {
			g_filtrationArray[i].count++;
			g_filtrationArray[i].lossPower = lossPower;
		
			if(g_filtrationArray[i].timeCount < FILTRATION_TIME)
			{
				if(g_filtrationArray[i].count >= FILTRATION_PAGE_COUNT)
				{
//					shellPrint("11timeCount = %d count = %d\r\n", g_filtrationArray[i].timeCount, g_filtrationArray[i].count);
					g_filtrationArray[i].count = 1;
					g_filtrationArray[i].timeCount = 0;
					
					addInfoToShowArray(g_filtrationArray[i].id, g_filtrationArray[i].lossPower);
				}
			}
			
			return;
		}
	}
		
	//add to filtration
	if(g_filtrationArrayNumber < TALBE_NUM)
	{
		g_filtrationArray[g_filtrationArrayNumber].id =id;
		g_filtrationArray[g_filtrationArrayNumber].count = 1;
		g_filtrationArray[g_filtrationArrayNumber].lossPower = lossPower;
		
		g_filtrationArrayNumber++;			
	}

		
//    if (g_labelNum < TALBE_NUM)
//    {
//        g_label[g_labelNum].id = id;
//        g_label[g_labelNum].lossPower = lossPower;
//     	    
//        for (i = 0;  i < 10; i++)
//        {
//            g_label[g_labelNum].msgCount[i] = 2;
//        }
//        
//        g_label[g_labelNum].keepSecond = 0;

//        g_labelNum++;
//    }
}

void comRead(unsigned char * data, unsigned long len)
{
    static unsigned char msg[7];
    static unsigned char msgLen = 0;
    int i;
    
    for (i = 0; i < len; i++)
    {
        if (msgLen < 5)
        {
            if (data[i] != 0xFF)
            {
                msgLen = 0;
                shellPrint("NOT FF %d ", i);
                continue;
            }
            else
            {
                msgLen++;
            }
        }
        else
        {
            msg[msgLen-5] = data[i];
            msgLen++;
            
            if (msgLen >= 12)
            {
                rfidRcvMsg(msg);
                
                msgLen = 0;
            }
        }
    }
}

void rfidInit(void)
{
	g_filtrationArrayNumber = 0;
    g_labelNum = 0;
    g_pageNo = 0; 
}

void rfidUpdataLine(int index, int line)
{
    int i, single; 
    
    single = g_label[index].msgCount[0];
    
    for (i = 1; i < 10; i++)
    {
        single += g_label[index].msgCount[i];
    }
    
    single = single*100/20;  // ��������£�10����յ�����20�����ݰ�
    
	char* COMx = "com2"; 
     FILE* fp;
    	if(single > 80 )
    	{ 
     	fp = fopen(COMx, "wb+"); //�Ĵ���������
	 	fwrite((char*)"1", sizeof("1"), 1, fp); //д1
	 	fclose(fp) ;
		 fp=NULL;
    	 }
    	 else
    	 {
    	 fp=NULL;
    	 fclose(fp);	
    	 }
    pageUpdataLine(line, index, g_label[index].id, g_label[index].lossPower, 
                   single > 100 ? 100:single, g_label[index].keepSecond);
}

// ˢ�µ�ǰҳ�� 
void rfidUpdataPage(void)
{
    int line, index;
    
    // ˢ�µ�ǰҳ�� 
    pageSetCardNum(g_labelNum);

    index = g_pageNo * LINE_PER_PAGE;
    
    for (line = 0; line < LINE_PER_PAGE; line++)
    {
        if (index < g_labelNum)
        {
            rfidUpdataLine(index, line);
        }
        else
        {
            pageClearLine(line);
        }
        
        index++;
    }

}

//�������ݵ���ʾ���� 
void addInfoToShowArray(unsigned long id, unsigned long lossPower)
{
	int i = 0;
	
	for(i=0; i<g_labelNum; i++)
	{
		if(id == g_label[i].id)
		{
			return;
		}		
	}
		
    if (g_labelNum < TALBE_NUM)
    {
        g_label[g_labelNum].id = id;
        g_label[g_labelNum].lossPower = lossPower;
     	    
        for (i = 0;  i < 10; i++)
        {
            g_label[g_labelNum].msgCount[i] = 2;
        }
        
        g_label[g_labelNum].keepSecond = 0;

        g_labelNum++;
    }	
}

// ÿ��ִ��һ�� 
void rfidTick(void)
{
    int i, j, k;
    
    if (!g_rfidTestOn)
    {
        return;
    }
    
    rfidUpdataPage(); 

	//filtration handle	
	for(i=0; i<g_filtrationArrayNumber; i++)
	{
		g_filtrationArray[i].timeCount++;
		
		if(g_filtrationArray[i].timeCount > FILTRATION_TIME)
		{
			if(g_filtrationArray[i].count >= FILTRATION_PAGE_COUNT)
			{
				
//				shellPrint("timeCount = %d count = %d\r\n", g_filtrationArray[i].timeCount, g_filtrationArray[i].count);
				g_filtrationArray[i].count = 1;
				g_filtrationArray[i].timeCount = 0;
				
				addInfoToShowArray(g_filtrationArray[i].id, g_filtrationArray[i].lossPower);
			}
			else
			{				
				//delete filtration info
				for(j=i; j<g_filtrationArrayNumber-1; j++)
				{
					memcpy(&g_filtrationArray[j], & g_filtrationArray[j+1], sizeof(FILTRATION));
				}
				g_filtrationArrayNumber--;
				i--;
			}
		}				
	}

    // ����һ�±�ǩ��״̬    
    for (i = 0; i < g_labelNum; i++)
    {    	
        // ɾ�������һ������Ϣ������
        for (j = 0; j < 9; j++)
        {
            g_label[i].msgCount[j] = g_label[i].msgCount[j+1];
        }
        
        g_label[i].msgCount[9] = 0;
        
        for (j = 0; j < 9; j++)
        {
            if (g_label[i].msgCount[j])
            {
                break;
            }
        }
        
        if (j >= 9)
        {
            // �Ѿ���9��û����Ϣ�ˣ�ֹͣ���� 
            g_label[i].keepSecond = 0;
        }
        else
        {
            g_label[i].keepSecond++;
        }
    }
}

void rfidTestStart(int com)
{
    int i;

	g_filtrationArrayNumber = 0;
    g_labelNum = 0;
    g_pageNo = 0;

    pageSetCardNum(0);    

    for (i = 0; i < LINE_PER_PAGE; i++)
    {
        pageClearLine(i);
    }
    
    openCom(com, BAUDRATE_9600);

    g_rfidTestOn = 1;
}

void rfidTestStop(void)
{
    g_rfidTestOn = 0;

    closeCom();
}

void rfidNextPage(void)
{
    if ((g_pageNo + 1) * LINE_PER_PAGE < g_labelNum)
    {
        g_pageNo++;
        
        rfidUpdataPage();
    }
}

void rfidPrevPage(void)
{
    if (g_pageNo)
    {
        g_pageNo--;

        rfidUpdataPage();
    }
}


