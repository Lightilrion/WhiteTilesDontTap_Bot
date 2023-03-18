
#include <iostream>
#include <windows.h>
using namespace std;
double fx1 = 65535.0f / 1919.0f;
double fy1 = 65535.0f / 1079.0f;
int main()
{
    int row[4] = { 700, 870, 1034, 1200 };
    int col[4] = { 300, 472, 642, 777 };
    HDC hdc = GetDC(NULL);
    while (GetPixel(hdc, 969, 215) == 0x00191919) Sleep(10);
    Sleep(200);
    tagINPUT Inputs[4] = {};
    Inputs[0].type = 0;
    Inputs[0].mi.dwFlags = 0x0002;
    Inputs[1].type = 0;
    Inputs[1].mi.dwFlags = 0x0004;
    tagINPUT Input = { 0 };
    Input.type = 0;
    Input.mi.dwFlags = 0x8001;
    COLORREF color;
    bool weird;
    while(!GetAsyncKeyState(VK_TAB)) {
        for (int i = 0; i < 4; i++) {
            for (int j = 3; j >= 0; j--) {
                color = GetPixel(hdc, row[j], col[i]);
                Input.mi.dx = row[j] * fx1;
                Input.mi.dy = col[i] * fy1;
                weird = !(color /256 - color & 0x00FFFF) * ((color ^ 0xFFFFFF) > 0);
                SendInput(weird, &Input, 40);
                SendInput(2*weird, Inputs, 40);
            }
        }
        Sleep(2.7);
    }
    
    return 0;
}

