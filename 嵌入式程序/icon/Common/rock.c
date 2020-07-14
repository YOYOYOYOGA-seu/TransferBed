/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*                                                                    *
* C-file generated by                                                *
*                                                                    *
*        Bitmap Converter (ST) for emWin V5.32.                      *
*        Compiled Oct  8 2015, 11:58:22                              *
*                                                                    *
*        (c) 1998 - 2015 Segger Microcontroller GmbH & Co. KG        *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: rock                                                  *
* Dimensions:  16 * 16                                               *
* NumColors:   16bpp: 65536                                          *
*                                                                    *
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmrock;

static GUI_CONST_STORAGE unsigned short _acrock[] = {
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x528C, 0x4253, 0x39D3, 0x420E, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x630E, 0xAD9E, 0x4A9F, 0x191E, 0x0899, 0x210F, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4A4A, 0x52DB, 0x6B5F, 0x31DE, 0x215B, 0x10D7, 0x0012, 0x294B, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4A4D, 0x295A, 0x215C, 0x211B, 0x18D8, 0x0894, 0x000F, 0x104B, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x528B, 0x0854, 0x0897, 0x10D6, 0x0854, 0x0811, 0x000D, 0x18CB, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x39CD, 0x000F, 0x000F, 0x000E, 0x000C, 0x000B, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x524D, 0x18CD, 0x084B, 0x18CB, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xA532, 0x5248, 0x4A08, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x8D56, 0x8D57, 0x7D37, 0x7D9A, 0xAE7A, 0x7B8E, 0x6CB4, 0x9E39, 0x7557, 0x6CF6, 0x630C, 0x0000, 0x0000,
  0x0000, 0x0000, 0x9E3A, 0xB7FF, 0x9F3F, 0xA77F, 0x8D99, 0x94F4, 0x5ACA, 0x7D58, 0x973F, 0x6EFF, 0x773F, 0x7558, 0x0000, 0x0000,
  0x0000, 0x7412, 0xA73F, 0x8E7D, 0x867E, 0xAEBC, 0xDD94, 0x7B4B, 0x2903, 0x8B4B, 0x64B6, 0x34BA, 0x3418, 0x4CB9, 0x5B4E, 0x0000,
  0x0000, 0x8DFC, 0x86BF, 0x7E3D, 0x6E3E, 0x6DFC, 0x9DFA, 0x84B4, 0x638F, 0x6454, 0x4C57, 0x33D6, 0x1B13, 0x2354, 0x4C14, 0x0000,
  0x0000, 0x6D5B, 0x655C, 0x54FB, 0x44BB, 0x4CFC, 0x345A, 0x345A, 0x655D, 0x553C, 0x54FB, 0x4CBA, 0x3BD7, 0x3BD6, 0x64B8, 0x0000,
  0x0000, 0x6CF9, 0x2B98, 0x0AD6, 0x1317, 0x12D7, 0x1B16, 0x2357, 0x2316, 0x1AD6, 0x1AD6, 0x2356, 0x2357, 0x5CFB, 0x7D5A, 0x0000,
  0x0000, 0x5458, 0x2BD9, 0x0B17, 0x0B18, 0x0AD7, 0x1358, 0x2357, 0x1B57, 0x12D7, 0x12D6, 0x12D6, 0x1B57, 0x54FB, 0x64F9, 0x0000,
  0x0000, 0x0000, 0x0A56, 0x0256, 0x0216, 0x0216, 0x0296, 0x1296, 0x0A96, 0x0255, 0x0255, 0x0214, 0x0254, 0x2358, 0x0000, 0x0000
};

GUI_CONST_STORAGE GUI_BITMAP bmrock = {
  16, // xSize
  16, // ySize
  32, // BytesPerLine
  16, // BitsPerPixel
  (unsigned char *)_acrock,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP565
};

/*************************** End of file ****************************/
