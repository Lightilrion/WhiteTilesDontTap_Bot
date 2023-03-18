
#include <iostream>
#include <windows.h>
using namespace std;
//calculating screen relative coordinates, these are for a 1920x1080 monitor
double fx1 = 65535.0f / 1919.0f;
double fy1 = 65535.0f / 1079.0f;
int main()
{
    //setting the base coordinates for the location of squares
    int row[4] = { 700, 870, 1034, 1200 };
    int col[4] = { 300, 472, 642, 777 };
    
    HDC hdc = GetDC(NULL);
    //waiting for the countdown to finish
    while (GetPixel(hdc, 969, 215) == 0x00191919) Sleep(10);
    Sleep(200);
    //preparing inputs for clicking the mouse
    tagINPUT Inputs[4] = {};
    Inputs[0].type = 0;
    Inputs[0].mi.dwFlags = 0x0002;
    Inputs[1].type = 0;
    Inputs[1].mi.dwFlags = 0x0004;
    //preparing inputs for moving the mouse
    tagINPUT Input = { 0 };
    Input.type = 0;
    Input.mi.dwFlags = 0x8001;
    //initializing the variables for rgb values and for checking whether to click a square
    COLORREF color;
    bool weird;
    //ending the loop when tab is pressed
    while(!GetAsyncKeyState(VK_TAB)) {
        //checking every square
        for (int i = 0; i < 4; i++) {
            //setting the coordinate y for mouse movement
            Input.mi.dy = col[i] * fy1;
            for (int j = 3; j >= 0; j--) {
                //getting the rgb values of a pixel
                color = GetPixel(hdc, row[j], col[i]);
                //setting the coordinate x for mouse movement
                Input.mi.dx = row[j] * fx1;
                //checking if a pixel is white and if its rgb values are all the same
                weird = !(color /256 - color & 0x00FFFF) * ((color ^ 0xFFFFFF) > 0);
                //sending the input
                SendInput(weird, &Input, 40);
                SendInput(2*weird, Inputs, 40);
            }
        }
        //sleeping for 2.7 ms, somehow works better
        Sleep(2.7);
    }
    
    return 0;
}

