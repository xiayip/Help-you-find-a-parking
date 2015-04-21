
#include <windows.h>
#include <stdio.h>

#include "shell.h"


extern void telnetInit(unsigned short port);
extern void telnetSend(const char * buf, int len);

extern int vsprintf(char * /*s*/, const char * /*format*/, va_list /*arg*/);

#define KEY_BACK_CTL   0x08
#define KEY_TAB        0x09
#define KEY_BACK_CHAR  0x7F

#define MAX_USERNAME_LEN 15
#define MAX_PASSWORD_LEN 15

#define SHELL_STATE_CHECK_USERNAME     1
#define SHELL_STATE_CHECK_PASSWORD     2
#define SHELL_STATE_ACTIVE             3

char g_shellUserName[MAX_USERNAME_LEN+1];
char g_shellPassword[MAX_PASSWORD_LEN+1];

#define SHELL_COMMAND_MAX_LEN 128

char g_shellCommand[SHELL_COMMAND_MAX_LEN+1];
DWORD g_shellCommandLen = 0;  // ��������������(�������˸��ɾ��)

typedef struct
{
    char * addr;
    char len;
}SHELL_WORD;
 
typedef struct
{
    SHELL_WORD word[5];
    char number; 
}SHELL_SENTENCE;

SHELL_SENTENCE sentence;
typedef struct
{
    const char * key;
    CMD_FUNC func;
    const char * help;
}TCmd;
  
#define SHELL_CMD_MAX 20
TCmd g_cmd[SHELL_CMD_MAX];

WORD g_cmdNum = 0;	
//LED��˸����

void shellSnd(const char * data, unsigned long len)
{
    telnetSend(data, len);
}
			
/*******************************************************
  �Ǽ������ 
*******************************************************/  
void shellRegCmd(const char * key, CMD_FUNC func, const char * help)
{
    TCmd cmd;
    
    if (g_cmdNum >= SHELL_CMD_MAX)
    {
        return;
    }
    
    cmd.key = key;
    cmd.func = func;
    cmd.help = help;
    
    g_cmd[g_cmdNum] = cmd;
    g_cmdNum++;
}


/*******************************************************
  �����û���������� 
*******************************************************/  
void shellAnalyseCommand(char * command, short cmdLen)
{
    short i, begin;
    char state; // 0����ʾ���ڲ黻����ͷ  1�����ڲ�ѯ����β
    char * key;
    TCmd *pCmd;
    
    sentence.number = 0;
    
    // ���������ӷֽ�Ϊ��������
    
    state = 0;
    for (i = 0; i < cmdLen; i++)
    {
        if (state)
        {
            // ���ڲ�ѯ����β
            if (command[i] == ' ')
            {
                // ���ֿո��򵥴��ѽ�����
                if (sentence.number < 5)
                {
                    sentence.word[sentence.number].addr = command+begin;
                    sentence.word[sentence.number].len = i - begin;

                    sentence.number++;
                }              
                command[i] = '\0'; // ���ո����Ϊ��ֹ�������ں�����ַ����Ƚϡ�                
                state = 0;
            }
        }
        else
        {
            // ��ѯ���ʵĿ�ʼ
            if (command[i] != ' ')
            {
                begin = i;                
                state = 1;
            }
        }
    }
    
    if (state)
    {
          // ���һ������               
         if (sentence.number < 5)
         {
             sentence.word[sentence.number].addr = command+begin;
             sentence.word[sentence.number].len = i - begin + 1;
             sentence.number++;
         }
         
         command[i+1] = '\0';
    }

    if (sentence.number == 0)
    {
        return;
    }

    key = sentence.word[0].addr;
	
  //��Ӧ�����  
    if (((key[0] == 'H') || (key[0] == 'h'))
     && ((key[1] == 'E') || (key[1] == 'e'))
     && ((key[2] == 'L') || (key[2] == 'l'))
     && ((key[3] == 'P') || (key[3] == 'p')))
    {
        shellSnd("\r\n---------- help ------------\r\n", 32);
        for (i = 0; i < g_cmdNum; i++)
        {
            pCmd = &(g_cmd[i]);

            shellSnd(pCmd->key, strlen(pCmd->key));
            shellSnd(" -- ", 4);
            shellSnd(pCmd->help, strlen(pCmd->help));
            shellSnd("\r\n", 2);            
        }
        return;
    }

    if (((key[0] == 'B') || (key[0] == 'b'))
     && ((key[1] == 'Y') || (key[1] == 'y'))
     && ((key[2] == 'E') || (key[2] == 'e')))
    {
//        telnetClose();														//c  b   x 
        return;
    }

    for (i = 0; i < g_cmdNum; i++)
    {
        pCmd = &(g_cmd[i]);
        if (strcmp(pCmd->key, key) == 0)
        {
            // �鵽����
            switch (sentence.number)
            {
                case 1:
                    pCmd->func(0, 0, 0, 0);
                    break;
                case 2:
                    pCmd->func(sentence.word[1].addr, 0, 0, 0);
                    break;
                case 3:
                    pCmd->func(sentence.word[1].addr, sentence.word[2].addr, 0, 0);
                    break;
                case 4:
                    pCmd->func(sentence.word[1].addr, sentence.word[2].addr, 
					           sentence.word[3].addr, 0); 
                    break;
                default:
                    pCmd->func(sentence.word[1].addr, sentence.word[2].addr,
                               sentence.word[3].addr, sentence.word[4].addr);
                    break;
            }
            break;
        }
    }								

    if (i == g_cmdNum)
    {
        shellSnd("\r\nCan not find this command!\r\n", 30);
    }
}		 

void shellRcv(const char * data, unsigned long len)
{
    DWORD i;
    char ch;

    for (i = 0; i < len; i++)
    {
        switch (*(data+i))
        {
        case '\r':
            // ִ������
            //shellSnd("\r\n", 2);

            shellAnalyseCommand(g_shellCommand, g_shellCommandLen);
            g_shellCommandLen = 0;

            shellSnd("->", 2);
            break;

        case '\n':
            break;

        case KEY_BACK_CTL:
        case KEY_BACK_CHAR:
            if (g_shellCommandLen)
            {
                g_shellCommandLen--;
                g_shellCommand[g_shellCommandLen] = 0;

                ch = KEY_BACK_CTL;
                shellSnd(&ch, 1);
                ch = ' ';
                shellSnd(&ch, 1);
                ch = KEY_BACK_CTL;
                shellSnd(&ch, 1);
            }
            break;
        case KEY_TAB:
            if (g_shellCommandLen >= (SHELL_COMMAND_MAX_LEN-4))
            {
                return;
            }
        
            g_shellCommand[g_shellCommandLen] = ' ';
            g_shellCommandLen++;
            g_shellCommand[g_shellCommandLen] = ' ';
            g_shellCommandLen++;
            g_shellCommand[g_shellCommandLen] = ' ';
            g_shellCommandLen++;
            g_shellCommand[g_shellCommandLen] = ' ';
            g_shellCommandLen++;
            g_shellCommand[g_shellCommandLen] = '\0';

            shellSnd("    ", 4);
            break;
            
        default:
            if (g_shellCommandLen >= (SHELL_COMMAND_MAX_LEN-1))
            {
                return;
            }

            g_shellCommand[g_shellCommandLen] = data[i];
            g_shellCommandLen++;
            g_shellCommand[g_shellCommandLen] = '\0';

            // ���л���
            //shellSnd(data+i, 1);
        }
    }
}

void shellInit(void)
{	
    telnetInit(2500);
    g_shellCommandLen = 0;
    g_cmdNum = 0;
    
    strcpy(g_shellUserName, "admin");
    strcpy(g_shellPassword, "admin");
    
    //shellRegCmd("paint", cmdLcdPait, "paint start...");
}

char g_uartPrintStr[256];

void shellPrint(const char *fmt, ...)
{
    va_list ap;
    int i;
	
    va_start(ap, fmt);
    vsprintf((char *)g_uartPrintStr, fmt, ap);
    
    va_end(ap);

    for (i = 0; i < 128; i++)
    {
        if (g_uartPrintStr[i] == '\0')
        {
             break;
        }
    }

    shellSnd(g_uartPrintStr , i);
}

//// ͨ������������ݣ����ݳ��Ȳ��ܳ���255���ֽڡ�
//void shellOut(const char *data, unsigned long len)
//{
//    shellSnd(data, len);
//}
//
 



