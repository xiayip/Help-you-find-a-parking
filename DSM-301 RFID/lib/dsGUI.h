/*******************************************
*
*  File: guiUser.h
*  Purpose��gui api include file
*
********************************************/


#ifndef _GUI_USER_H
#define _GUI_USER_H

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

typedef unsigned long WM_COLOR;

// �ڵ�ǰҳ��������һ��ͼ��
#define IMAGE_ATTRIBUTE_HASTRANS  0x00000001   // ͸������

typedef struct
{
    long xSize;  // ͼƬ�������ص�����
    long ySize;  // ͼƬ������ص�����   
    // ͼƬ���������ݣ���ŷ�ʽΪ���д��ϵ���,ÿ�д����ҡ�
    // ÿ�����ص�ռ��3���ֽڹ�24BIT���ֱ�ΪR(8) G(8) B(8)��
    const unsigned char * data;
}WM_IMAGE;

typedef struct
{
    long xSize;
	long ySize;
	const unsigned char* data;
}
WM_IMAGE_FILTER;

typedef struct
{
    int fontId;       // ��ʾ�ַ���ʱ�õ�����
    WM_COLOR color;   // ��ʾ�ַ���ʱ�õ���ɫ
    const char * str;  // �ַ�������
}WM_STRING;

// ============= ϵͳ����ӿ� ==========================

// ��GUI���г�ʼ��
// xSize��ySize��GUI����ĳߴ磨��λΪ���أ�
// memoryAddr��memorySize��GUI�ڲ�ʹ�õĶ�̬�ڴ档
//        �����С�뻭��ߴ硢ҳ�漰�ؼ��Ķ�����ء���ʼ������Ĵ�һЩ����xSize*ySize*4�ֽڡ�
//        �ڵ���ʱ��WM_MemUsedMax�������ʵ��ʹ������������һ������Ĵ�С����ʡ������ڴ�ռ䡣
void WM_Init(int xSize, int ySize,unsigned long  memoryAddr,unsigned long  memorySize);

// ��ȡGUIʹ�ö�̬�ڴ���� 
//usedSize    ��ǰʹ�ô�С 
//peakSize    ʹ�÷�ֵ
void WM_MemUsedGet(unsigned long * usedSize, unsigned long * peakSize);

// ��ȡ��ǰGUI�İ汾��Ϣ
const char *WM_GetVerString(void);

void WM_Print(char * string);

// // �趨�Դ档�Դ��д�ŵ�����Ҫ������ʾ�������ϵ����ݡ�
// // ���������GUI���ã���Ҫ�û����ʵ�֣�������������������������ʾ����ʾ���ϡ�
// #if GUI_SHOW_TYPE == GUI_TYPE_RGB888
// // ��ʾRGB888ģʽ��һ������
// //    ÿ�����Ӧһ�����֣�LONG����ʵ��ֻ��ǰ24λ��Ч  R(8) G(8) B(8)
// //    ���������������̶�ΪX*Y������  
// void WM_DisplayMemorySet(unsigned long* ptr);
// #elif GUI_SHOW_TYPE == GUI_TYPE_RGB565
// // ��ʾRGB565ģʽ��һ������
// //    ÿ�����Ӧһ�����֣�LONG����16λ  R(5) G(6) B(5)
// //    ���������������̶�ΪX*Y������  
// void WM_DisplayMemorySet(unsigned short* ptr);
// #endif

void WM_Paint(unsigned char * pageBaseAddr, int x, int y, int xSize, int ySize);

// GUIȱʡ������Ӣ��12�ź�16�����壬����������Ҫ��GUIʱ��̬����

// �����ֿ⣬�ֿ��ļ��ɶ�����Ϣ�ṩ��Ŀǰ�ṩӢ��12�š�16�š�24�š�32�š�64�ţ�����12�š�16�š�24�š�32�š�64��
// fontSize�������С����16�����壬��Ϊ16��
// fontData���ֿ��ļ�λ��
// ���أ��ɹ������ֿ�ID���û������ֿ�ID�����ֿ⡣ʧ�ܷ���-1��
int WM_FontLoad(unsigned short fontSize,const unsigned char * fontData);

// GUIȱʡ���ص�Ӣ��12�ź�16������ID���û��ɸ���IDֱ��ʹ����Ӧ�ֿ�
#define GUI_FONT_ENG_16    0x000010   // ȱʡ���ص�16��Ӣ���ַ�

// ��λ�豸�������������ȣ�����ӿڣ���ÿ100ms����һ��
// x,y����ǰ��λ�豸λ��
// state����ǰ��λ�豸״̬��1������  0������
void WM_HidState(int x,int y,int state);

// ============= ҳ�����ӿ� ==========================
// ҳ����GUI�Ļ�������Ԫ�����еĿؼ����������ҳ���ϡ�
// ҳ����µ�����������8�㡣
//     �ɼ�����ҳ�棬����ҳ�渲����ҳ�棬ҳ���һ�㣬����ҳ��ɾ������Զ��ָ���ҳ�档
//     Ҳ����ɾ����ҳ�棬�ٴ�����ҳ�棬����ҳ���滻��ҳ�棬ҳ��������䡣

// �ؼ��¼�����
#define WM_MSG_TYPE_CLICK            0   // �����¼�
#define WM_MSG_TYPE_RELEASE          1   // �ͷ��¼�
#define WM_MSG_TYPE_SELECT           2   // ѡ���¼�    
#define WM_MSG_TYPE_VALUE            3   // ��ֵ�ı��¼�
#define WM_MSG_TYPE_FOCUS            4   // ��ý����¼�
#define WM_MSG_TYPE_INIT             5   // �ؼ���ʼ���¼�
#define WM_MSG_TYPE_ACTIVE           6   // ҳ�漤���¼�


// ��������
#define WM_ERROR_TYPE_MEM        -1     // �ڴ�����ʧ��  GUI�����ڴ治��      
#define WM_ERROR_TYPE_PAGE       -2     // ����ҳ����Ŀ��������
#define WM_ERROR_TYPE_CTL        -3     // �����ؼ���Ŀ��������
#define WM_ERROR_TYPE_SIZE       -4     // �����ؼ�λ�ô�С���Ϸ�
#define WM_ERROR_TYPE_PARA       -5     // ���/���� ������������
#define WM_ERROR_TYPE_NO_PAGE    -6     // û�д�����ҳ��


// �ؼ������¼��Ļص�������
typedef void (* WM_PAGE_CTL_CB)(int ctlHandle, int msgType);

// ����һ����ҳ��û��ͼ����0��û�лص���0
//���� 0 �ɹ�  ���� ������
int WM_PageNew(WM_COLOR bkColor, WM_IMAGE * bkImage, WM_PAGE_CTL_CB pageCb);

// ҳ��հ��������¼��Ļص�������
// ���أ���ǰ����ڽ���հ�������������
typedef void (* WM_PAGE_SPACE_CB)(int msgType, int x, int y);

// ��ǰҳ����ӿհ�����Ĵ���ص�����
int WM_SpaceCbAdd(WM_PAGE_SPACE_CB spaceCb);

// ����ҳ�档ҳ�漤���ҳ�����ݲŻ���������ʾ��
void WM_PageActive(void);

// ɾ��ҳ�档��ǰҳ��ɾ�����²�ҳ����Զ���ʾ��
void WM_PageDel(void);

// ɾ���ؼ���
int WM_CtlDelete(int handle);

// ============= ��̬�ؼ� ==========================
// ��̬�ؼ�û�пؼ�ID�����ɼ��û����룬ֻ��ҳ����о�̬���Ρ�

// �ڵ�ǰҳ���ϴ�ӡ�ַ���
void WM_StringDisp(int x, int y, WM_STRING * string);

//�ڵ�ǰҳ������һ��ͼ��
void WM_ImageAdd(int x, int y, WM_IMAGE * image, unsigned long attribute);

// �ڵ�ǰҳ��������һ�����޿� 
void WM_GroupAdd(int x, int y, int xSize, int ySize, WM_STRING * string);

// �ڵ�ǰҳ����ʹ��ָ����ɫ�������
void WM_ClearByColor(int x, int y, int xSize, int ySize, WM_COLOR color);

// ============= ��̬�ؼ� ==========================
// ��̬�ؼ��пؼ�ID����Ҫ�����ɼ��û����롣

// ~~~~~~~~~~~~~ ��ť�ؼ� ~~~~~~~~~~~~~~~~~~~~~~~~

// �ڵ�ǰҳ��������һ����ť	  �����ɹ����ذ������
// ���ؿؼ�ID  
int WM_ButtonAdd(int x , int y, int xSize, int ySize);

// ���ð�ť����ɫ
void WM_ButtonSetBkColor(int handle, WM_COLOR bkColor);

// ���ð�ť�ַ�
void WM_ButtonSetText(int handle, WM_STRING * string);

// ���ð�ť����ͼ
void WM_ButtonSetImage(int handle, WM_IMAGE * image);

//���ñ߿� on��1 : ��  0: ��
void WM_ButtonSetBorder(int handle, int on);

//����͸�� on��1 : ��  0: ��
void WM_ButtonSetTransparent(int handle, int on);

// ��ť��Ӧ�¼�����
//  WM_MSG_TYPE_CLICK / WM_MSG_TYPE_RELEASE

// ~~~~~~~~~~~~~ ��ѡ��ؼ� ~~~~~~~~~~~~~~~~~~~~~~~~

// �ڵ�ǰҳ��������һ����ѡ��  defaultState 1��ȱʡ״̬Ϊѡ��  0��ȱʡ״̬Ϊδѡ��
int WM_CheckBoxAdd(int x, int y, int xSize, int ySize, WM_STRING * string, int defaultState);

// ���ø�ѡ���״̬  1��ѡ��   0��δѡ��
void WM_CheckBoxSet(int handle, int state);

// ��ȡ��ѡ���״̬
//   ���� 1��ѡ��   0��δѡ��
int WM_CheckBoxGet(int handle);

// ��ѡ����Ӧ�¼�����
// WM_MSG_TYPE_RELEASE

// ~~~~~~~~~~~~~ �б��ؼ� ~~~~~~~~~~~~~~~~~~~~~~~~

// �ڵ�ǰҳ��������һ���б��
int WM_ListBoxAdd(int x, int y, int xSize, int ySize, WM_COLOR bkColor, WM_COLOR textColor, int fontId);

// ���б��������һ������
void WM_ListBoxItemAdd(int handle, const char * str);

// ���б����ɾ��һ������
void WM_ListBoxItemDel(int handle, int itemIndex);

// �����б���е�ѡ����
void WM_ListBoxSet(int handle, int itemIndex);

// �õ��б���е�ѡ����(û��ѡ�У�����-1)��*pStr����ѡ������ַ���
int WM_ListBoxGet(int handle);

// �б����Ӧ�¼�����
// WM_MSG_TYPE_SELECTED_CHANGED

// ~~~~~~~~~~~~~ ��ѡ��ؼ� ~~~~~~~~~~~~~~~~~~~~~~~~

// �ڵ�ǰҳ��������һ����ѡ��
int WM_RadioAdd(int x, int y, int xSize, int ySize, WM_COLOR textColor, int fontId);

// �ڵ�ѡ��������һ������
void WM_RadioItemAdd(int handle, const unsigned char * str);

// ���õ�ѡ���е�ѡ����
void WM_RadioSet(int handle, int itemIndex);

// �õ���ѡ���е�ѡ����(û��ѡ�У�����-1)
int WM_RadioGet(int handle);

// ��ѡ����Ӧ�¼�����
// WM_MSG_TYPE_SELECTED_CHANGED

// ~~~~~~~~~~~~~ �������ؼ� ~~~~~~~~~~~~~~~~~~~~~~~~
#define SLIDER_MODE_SLIDER   0    //������
#define SLIDER_MODE_LOCK     1    //������
// �ڵ�ǰҳ��������һ�����������ص����ػ���ʱ�ĵ�ǰ�̶�
int WM_SliderAdd(int x, int y, int xSize, int ySize, int min, int max);

void WM_SliderSetMode(int handle, int mode);   //Ĭ���ǻ�����

// �ڻ��������õ�ǰֵ
void WM_SliderSet(int handle, int value);

// �ڻ�������ѯ��ǰֵ
int WM_SliderGet(int handle);

// ���û������ı���ͼ
//    bkImage0��������δ����ʱ�ı���ͼ
//    bkImage1�������������Ժ�ı���ͼ���������������ǰ�󣬱���ͼ���䣬����0��
void WM_sliderSetBkImage(int handle, WM_IMAGE * bkImage0, WM_IMAGE * bkImage1);

// ���û������Ӧ��ͼƬ
//    barImage���������ͼƬ
//    barFileter���ػ滬��ͼʱʹ�õ��˾�������Ҫ�˾�ʱ����0����ʱ��������ȫ���Ǳ�����
void WM_sliderSetBarImage(int handle, WM_IMAGE * barImage, WM_IMAGE_FILTER * barFilter);

// ��������Ӧ�¼�����
// WM_MSG_TYPE_VALUE_CHANGED

// ~~~~~~~~~~~~~ �������ؼ� ~~~~~~~~~~~~~~~~~~~~~~~~

// �ڵ�ǰҳ��������һ��������
int WM_ProgBarAdd(int x, int y, int xSize, int ySize, WM_COLOR leftColor, WM_COLOR rightColor);

// ���ý�����
int WM_ProgBarSet(int handle, int value);

// ������������Ӧ�ⲿ�����¼�

// ~~~~~~~~~~~~~ �༭��ؼ� ~~~~~~~~~~~~~~~~~~~~~~~~

//  �ڵ�ǰҳ��������һ���༭��
//  ���� attribute��BIT 0 �����Ҷ���    1 ���������
int WM_EditAdd(int x, int y, int xSize, int ySize, WM_COLOR bkColor, WM_COLOR textColor, int fontId,unsigned char attribute);

// ���ַ������õ��༭����
void WM_EditSet(int handle, const char * str);

// �ӱ༭���ѯ�õ���ǰ����ֵ
const char * WM_EditGet(int handle);

void WM_EditSetBkColor(int handle, WM_COLOR bkColor);

// �༭����Ӧ�¼�����
// WM_MSG_TYPE_FOCUS

// ~~~~~~~~~~~~~ �ı���ؼ� ~~~~~~~~~~~~~~~~~~~~~~~~

//  �ڵ�ǰҳ��������һ���ı���
//  ���� attribute��BIT 0-1 ��0:���Ҷ��� 1 ���������   2: ���ж��� 
int WM_LabelAdd(int x, int y, int xSize, int ySize, WM_COLOR bkColor, WM_COLOR textColor, int fontId ,unsigned char attribute);

// ���ַ������õ��ı�����
void WM_LabelSet(int handle, const char * str);

void WM_LabelSetBkColor(int handle, WM_COLOR bkColor);

void WM_LabelSetFrontColor(int handle, WM_COLOR frontColor);

// �ı���������Ӧ�ⲿ�����¼�

// ~~~~~~~~~~~~~ ������ؼ� ~~~~~~~~~~~~~~~~~~~~~~~~

// �ڵ�ǰҳ��������һ��������
int WM_DropDownAdd(int x, int y, int xSize, int ySize, WM_COLOR bkColor, WM_COLOR textColor, int fontId);

// ��������������һ������
void WM_DropDownItemAdd(int handle, const char * str);

// ����������ɾ��һ������
void WM_DropDownItemDel(int handle, int itemIndex);

// �����������е�ѡ����
void WM_DropDownSet(int handle, int itemIndex);

// �õ��������е�ѡ����(û��ѡ�У�����-1)��*pStr����ѡ������ַ���
int WM_DropDownGet(int handle);

// ��������Ӧ�¼�����
// WM_MSG_TYPE_SELECTED_CHANGED


//  ~~~~~~~~~~~~~~~~ ��Ϣ�� ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ��Ϣ�򴴽����ؿؼ����  ��Ϣ���û�������� WM_MSG_TYPE_SELECT��Ϣ
//captionStr  ����Ϣ���ı�
//button0Str  : ��һ����ť���ı�
//button1Str  : �ڶ�����ť���ı�
//button2Str  : ��������ť���ı�                 
// ����ֵ����Ϣ��Ŀؼ����
int WM_MsgBoxAdd(int x, int y, int xSize, int ySize, WM_STRING * captionStr, WM_STRING * button0Str, WM_STRING * button1Str, WM_STRING * button2Str);

// ��ȡ��Ϣ�򱻰��µļ����
// ����ֵ��  0��button0
//           1: button1
//           2: button2
int WM_MsgBoxGet(int handle);

#define WM_COLOR_TRANSPARENT  0xFFFFFFFF  // ͸��ɫ
#define WM_COLOR_BLACK        0x00000000  // ��ɫ
#define WM_COLOR_WHITE        0x00FFFFFF  // ��ɫ
#define WM_COLOR_GRAY         0x007F7F7F  // ��ɫ��50%�Ҷȣ�
#define WM_COLOR_DARK_GRAY    0x003F3F3F  // ���ɫ��75%�Ҷȣ�
#define WM_COLOR_LIGHT_GRAY   0x00C3C3C3  // ǳ��ɫ��25%�Ҷȣ�
#define WM_COLOR_RED          0x00FF0000  // ��ɫ
#define WM_COLOR_DARK_RED     0x007F0000  // ���ɫ���ƺ�ɫ��
#define WM_COLOR_LIGHT_RED    0x00FF7F7F  // ǳ��ɫ���ۺ�ɫ��
#define WM_COLOR_GREEN        0x0000FF00  // ��ɫ
#define WM_COLOR_DARK_GREEN   0x00007F00  // ����ɫ
#define WM_COLOR_LIGHT_GREEN  0x007FFF7F  // ǳ��ɫ
#define WM_COLOR_BLUE         0x000000FF  // ��ɫ
#define WM_COLOR_DARK_BLUE    0x0000007F  // ����ɫ������ɫ��
#define WM_COLOR_LIGHT        0x007F7FFF  // ǳ��ɫ������ɫ��
#define WM_COLOR_YELLOW       0x00FFFF00  // ��ɫ
#define WM_COLOR_DART_YELLOW  0x007F7F00  // ���ɫ�����ɫ��
#define WM_COLOR_LIGHT_YELLOW 0x00FFFF7F  // ǳ��ɫ
#define WM_COLOR_PURPLE       0x00FF00FF  // ��ɫ
#define WM_COLOR_DART_PURPLE  0x007F007F  // ����ɫ
#define WM_COLOR_LIGHT_PURPLE 0x00FF7FFF  // ǳ��ɫ
#define WM_COLOR_CYAN         0x0000FFFF  // ��ɫ
#define WM_COLOR_DARK_CYAN    0x00007F7F  // ����ɫ
#define WM_COLOR_LIGHT_CYAN   0x007FFFFF  // ǳ��ɫ������ɫ��
#define WM_COLOR_ORANGE       0x00FF7F00  // ��ɫ
#define WM_COLOR_GOLD         0x00FFD700  // ��ɫ



//��ͼ����

//���û���
void WM_PenSet(WM_COLOR color, int size);

//����
void WM_PainPoint(int x, int y);

//����
void WM_DrawLine(int x0, int y0, int x1, int y1);

//��ɫ
void WM_FillColor(int x, int y, WM_COLOR color);

//��Բ
void WM_DrawCircle(int x0, int y0, int r);

//����
void WM_DrawArc(int x0, int y0, int x1, int y1, int r, int isChord);
//�ػ�
void WM_Redraw(void);

//�����ʹ��
//enable 1: ʹ��  0����ʹ��
void WM_AntiAliasingEnable(unsigned long enable);

#if defined(__cplusplus)
}
#endif 


#endif
