/*************************************************************************
 *
*    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2008
 *
 *    File name   : drv_glcd.h
 *    Description : Graphical LCD driver include file
 *
 *    History :
 *    1. Date        : 6, March 2008
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *
 *    $Revision: 24636 $
 *
 *    @Modify: NXP MCU Application Team - NguyenCao
 *    @Date: 04. March. 2011
 **************************************************************************/
//#include "lpc_types.h"

#ifndef __LCD_H
#define __LCD_H

#define LCD_COLOR_BLACK        0x00000000  // ��ɫ
#define LCD_COLOR_WHITE        0x00FFFFFF  // ��ɫ
#define LCD_COLOR_GRAY         0x007F7F7F  // ��ɫ��50%�Ҷȣ�
#define LCD_COLOR_DARK_GRAY    0x003F3F3F  // ���ɫ��75%�Ҷȣ�
#define LCD_COLOR_LIGHT_GRAY   0x00C3C3C3  // ǳ��ɫ��25%�Ҷȣ�
#define LCD_COLOR_RED          0x000000FF  // ��ɫ
#define LCD_COLOR_DARK_RED     0x0000007F  // ���ɫ���ƺ�ɫ��
#define LCD_COLOR_LIGHT_RED    0x007F7FFF  // ǳ��ɫ���ۺ�ɫ��
#define LCD_COLOR_GREEN        0x0000FF00  // ��ɫ
#define LCD_COLOR_DARK_GREEN   0x00007F00  // ����ɫ
#define LCD_COLOR_LIGHT_GREEN  0x007FFF7F  // ǳ��ɫ
#define LCD_COLOR_BLUE         0x00FF0000  // ��ɫ
#define LCD_COLOR_DARK_BLUE    0x007F0000  // ����ɫ������ɫ��
#define LCD_COLOR_LIGHT        0x00FF7F7F  // ǳ��ɫ������ɫ��
#define LCD_COLOR_YELLOW       0x0000FFFF  // ��ɫ
#define LCD_COLOR_DART_YELLOW  0x00007F7F  // ���ɫ�����ɫ��
#define LCD_COLOR_LIGHT_YELLOW 0x007FFFFF  // ǳ��ɫ
#define LCD_COLOR_PURPLE       0x00FF00FF  // ��ɫ
#define LCD_COLOR_DART_PURPLE  0x007F007F  // ����ɫ
#define LCD_COLOR_LIGHT_PURPLE 0x00FF7FFF  // ǳ��ɫ
#define LCD_COLOR_CYAN         0x00FFFF00  // ��ɫ
#define LCD_COLOR_DARK_CYAN    0x007F7F00  // ����ɫ
#define LCD_COLOR_LIGHT_CYAN   0x00FFFF7F  // ǳ��ɫ������ɫ��
#define LCD_COLOR_ORANGE       0x00007FFF  // ��ɫ
#define LCD_COLOR_GOLD         0x0000D7FF  // ��ɫ

// ��LCD���г�ʼ��
// ��� xSize,ySize: LCD��Ļ�Ĵ�С
extern void LCD_init(int xSize, int ySize);

// �����Դ�ĵ�ַ����ַ�ռ�ΪxSize*ySize*2�ֽڣ�RGB565ģʽ��
extern void LCD_displayMemorySet(unsigned short * addr);

// ֻ����LCD�Դ��趨�Ժ�LCD����������ʹ��
extern void LCD_enable(void);

// LCD�������
// ��� on���Ƿ��  1����  0���ر�
extern void LCD_backLightCtl(int on);

#endif
