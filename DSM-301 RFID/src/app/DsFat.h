#ifndef __DS_FAT_H
#define __DS_FAT_H

#define FAT_TRUE   1
#define FAT_FALSE  0

typedef unsigned long FAT_FILE_HANDLE;
typedef unsigned char FAT_BOOL;

#define FAT_FILE_HANDLE_NULL 0xFFFFFFFF
#define FAT_FILE_DESC_NUM  32

#define MAX_FILE_NAME_LEN  255  // �ļ�������󳤶�  
#define MIN_FILE_NAME_LEN  12   // �ļ�����С����

#define FAT_LIST_TYPE_READ      0x01	   //ֻ��
#define FAT_LIST_TYPE_HIDE      0x02	   //����
#define FAT_LIST_TYPE_SYS       0x04	   //ϵͳ
#define FAT_LIST_TYPE_LABLE     0x08	   //���
#define FAT_LIST_TYPE_DIR       0x10	   //��Ŀ¼
#define FAT_LIST_TYPE_DOC       0x20	   //�浵

#define FAT_FILE_OPEN_READ      0x01
#define FAT_FILE_OPEN_WRITE     0x02

typedef struct
{
    char * name;
    unsigned long nameLen;

    unsigned short year;
    unsigned char mon;
    unsigned char day;
    unsigned char hour;
    unsigned char min;
    unsigned char sec;
    
    unsigned char type;
    
    unsigned long size;
}FAT_LIST_INFO;


//===========FAT�ļ�ϵͳ��API��̽ӿ�=============================================================

extern FAT_BOOL fatInit(unsigned long flashSize);

// �õ�FAT�ļ���İ汾��
extern char * fatVersion(void);

// ���ļ�ϵͳ���½��и�ʽ��
//���� falshSize  ��λ:KB
extern void fatFormat(unsigned long flashSize);

// ��ȡ�ļ�ϵͳ�Ŀռ�ռ�ô�С��Ϣ
//���� allSize freeSize  ��λ:KB
extern void fatGetSize(unsigned long  *allSize,unsigned long  * freeSize);

// �õ���ǰĿ¼�ĵ�һ����Ŀ����Ŀ¼���ļ�����Ϣ
// ����FALSE��Ϊ��Ŀ¼��û���κ���Ŀ
// ����TRUE���ɹ���ȡ��1����Ŀ��
extern FAT_BOOL fatGetDirectoryListFirst(FAT_LIST_INFO * listInfo);

// �õ���ǰĿ¼����һ����Ŀ����Ŀ¼���ļ�����Ϣ
// ����FALSE���ѵ���β��û����һ����Ŀ��
// ����TRUE���ɹ���ȡ��һ����Ŀ��
extern FAT_BOOL fatGetDirectoryListNext(FAT_LIST_INFO * listInfo);

// �ڵ�ǰĿ¼�д�����Ŀ¼
// ����FALSE��������Ŀ¼ʧ�ܡ�
// ����TRUE��������Ŀ¼�ɹ���
extern FAT_BOOL fatMakeDirtory(char * subDirectoryName);

// �ڵ�ǰĿ¼���Ƴ���Ŀ¼
// ����FALSE���Ƴ���Ŀ¼ʧ�ܡ�
// ����TRUE���Ƴ���Ŀ¼�ɹ���
extern FAT_BOOL fatRemoveDirtory(char * subDirectoryName);

// ���뵱ǰĿ¼����Ŀ¼
// ����FALSE�������ڸ���Ŀ¼��
// ����TRUE���ɹ�������Ŀ¼��
extern FAT_BOOL fatEnterDirectory(char * subDirectoryName);

// �˻ص���Ŀ¼
extern void fatBackToRootDirectory(void);

// �ڵ�ǰĿ¼�д����ļ�
// ����FALSE�������ļ�ʧ�ܡ�
// ����TRUE�������ļ��ɹ���
extern FAT_BOOL fatMakeFile(char * fileName);

// �ڵ�ǰĿ¼���Ƴ��ļ�
// ����FALSE���Ƴ��ļ�ʧ�ܡ�
// ����TRUE���Ƴ��ļ��ɹ���
extern FAT_BOOL fatRemoveFile(char * fileName);

// �ڵ�ǰĿ¼�д�ָ�����ļ�
// ����1��fileName ��Ҫ�򿪵��ļ���
// ����2��openMode ���ļ���ģʽ������д
// ���ش��ļ��ľ��
// ����FAT_FILE_HANDLE_NULL�����ļ�ʧ�ܡ� 
FAT_FILE_HANDLE fatFileOpen(char * fileName, unsigned char openMode);

// �ر��ļ��� 
extern FAT_BOOL fatFileClose(FAT_FILE_HANDLE handle);

// �õ��ļ��ĳ���
extern unsigned long fatFileGetLen(FAT_FILE_HANDLE handle);

// ���ļ��ĵ�ǰλ�ö�ָ�����ȵ�����
// ����ʵ�ʶ��������ݳ��ȣ����ļ���ǰλ�õ���β�ĳ���С��buffer�ռ�ʱ��
extern unsigned long fatFileRead(FAT_FILE_HANDLE handle, unsigned char * buffer, unsigned long size);

// ����ļ��������ݡ�
extern FAT_BOOL fatFileClear(FAT_FILE_HANDLE handle);

// ���ļ��Ľ�β׷��ָ�����ȵ����ݣ�
extern FAT_BOOL fatFileAppend(FAT_FILE_HANDLE handle, unsigned char * data, unsigned long len);

//==================FAT�ļ�ϵͳ������洢���ĵײ�ӿ�===================================================================

// ���ļ�ϵͳ���г�ʼ������ȷ���ļ�ϵͳ��ʹ�õ�FLASH�ռ�Ĵ�С��
// flashSize�������1��G��
//����flashSize ��λ:KB
extern FAT_BOOL fatInit(unsigned long flashSize);

// ��FLASH��ָ��λ��д������
extern void fatFlashWrite(unsigned long addr, const unsigned char * data, unsigned long len);

// ��FLASH��ָ��λ�ö�������
extern void fatFlashRead(unsigned long addr, unsigned char * data, unsigned long len);

// ��FLASH��ָ��λ���������
extern void fatFlashClear(unsigned long addr, unsigned long len);

// FAT��ȡ��ǰ��ʱ����Ϣ
extern void fatGetDateTime(unsigned short * year, 
                           unsigned char * mon, 
                           unsigned char * day,
                           unsigned char * hour,
                           unsigned char * min,
                           unsigned char * sec);

// FAT���������Ϣ
extern void fatDebugOut(char * str);


extern unsigned char * fatAllocMem(unsigned long size);

extern void fatFreeMem(unsigned char * mem);

#endif
