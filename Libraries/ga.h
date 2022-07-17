#ifndef GA_H_
#define GA_H_

#include <Windows.h>
/*Function Prototypes*/

BOOL InitGA(void);
void Pos(int row, int col); //İmleci belli bir koordinata konumlandırır
void WriteChar(int row, int col, int ch); //Belli bir koordinata karakter yazar
void WriteCharAttr(int row, int col, int ch, int attr);
void WriteStr(int row, int col, LPCSTR szStr);//Belli bir koordinata string yazar
void WriteStrAttribute(int row, int col, LPCSTR szStr, int attr);
void FillChar(int row, int col, int ch, int n); //Belli bir koordinata n kadar karakter yazar
void FillCharAttr(int row, int col, int ch, int n, int attr);
void VFillChar(int row, int col, int ch, int n); //Dikey Doldurur
void VFillCharAttr(int row, int col, int ch, int n, int attr);
void DrawFrame(int row1, int col1, int row2, int col2); //Sol üst köşesi ve sağ alt köşesi verilir ve frame çizilir

#endif
