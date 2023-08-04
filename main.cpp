//#include <iostream>
//#include "ConsoleFormatter.h"
//
//int main()
//{
//    ConsoleFormatter console{};
//    console.SetColour(BACKGROUND,  {200, 200, 0});
//    console.MoveCursorRight(10);
//    std::cout << " ";
//    console.MoveCursorRight(14);
//    std::cout << " ";
//
//    console.MoveCursorDown(10);
//    console.MoveCursorLeft(20);
//    std::cout << "   ";
//    console.MoveCursorRight(20);
//    std::cout << "   ";
//    console.MoveCursorDown(1);
//    console.MoveCursorLeft(23);
//    std::cout << "                    ";
//
//    console.ResetColour();
//}
//



//#include <stdio.h>

// Library where getch() is stored
//#include <conio.h>
#include <windows.h>
#include <iostream>
#include <format>
#include <chrono>
#include <vector>
#include "ConsoleFormatter.h"
using namespace std;

struct Keys
{
    int CorrespondingKeyId;
    SHORT value;
    bool isPressed = false;
    bool isReleased = false;
};

struct Coordinate
{
    int X;
    int Y;
};

struct Pixel 
{
    Coordinate coordinates;
    wchar_t cur;
};

int CoordToInt(Pixel c, int sWidth)
{
    int X = c.coordinates.X;
    int Y = c.coordinates.Y * sWidth;
    return Y + X;
}

Coordinate IntToCoord(int pos, int wWidth, int sWidth)
{
    int X = floor(pos / sWidth);
    int Y = pos % sWidth;
    Coordinate coord = { X,  Y };
    return coord;
}



int main()
{
    //Sleep(2000);
    Keys OldKeyState[255]{};
    Keys NewKeyState[255]{};
    ////printf("%c", _getch());
    //for(int i =0; i < 256; i++)
    //{
    //    SHORT x = GetAsyncKeyState(i);

    //    bool isPressed = x != 0;

    //    OldKeyState[i] = { i, x, isPressed, false };

    //    cout << i << " - " << x << endl;

    //    if (x == 0)
    //        cout << "hello";

    //}

    //while (true)
    //{
    //    Sleep(500);
    //    for (int i = 0; i < 256; i++)
    //    {
    //        
    //        SHORT state = GetAsyncKeyState(i);

    //        bool isPressed = false, isReleased = false;

    //        if (OldKeyState->value != state)
    //        {
    //            if (state == 0)
    //            {

    //                isPressed = false;
    //                isReleased = false;
    //            }
    //            else if (state == 1)
    //            {
    //                isPressed = false;
    //                isReleased = true;
    //            }
    //            else {
    //                isPressed = true;
    //                isReleased = false;
    //            }

    //            cout << "IsPressed - " << isPressed << endl;
    //            cout << "IsReleased - " << isReleased << endl;

    //            string stateStr = isPressed ? "pressed" : "released";

    //            cout << stateStr << " state" << endl;
    //            cout << i << " was " << stateStr << endl;
    //            cout << i << " - " << state << endl;
    //        }
    //        NewKeyState[i] = { i, state, isPressed, isReleased };
    //    }
    //    cout << "==========================" << endl;

    //
    //}

    ConsoleFormatter console{};
    console.SetColour(FOREGROUND, { 255, 0, 0 });
    int sWidth = 120, sHeight = 30;
    int wWidth = 25, wHeight = 15;

    wchar_t* screen = new wchar_t[sWidth * sHeight];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    Pixel cursor{ 0, 0, L'@' };

    //char *screen = new char[width * height];
    auto t1 = chrono::system_clock::now();
    auto t2 = chrono::system_clock::now();

    vector<Pixel> screenPixels;
    //auto screenPixels = new Pixel[sWidth * sHeight];
    
    for (int i = 0; i < sWidth * sHeight; i++)
    {
        wchar_t icon{};
        int wBound = i % sWidth;
        int hBound = (int)i / sWidth;

        if (wBound == 0 && i < wHeight)
            icon = L'6';
        else if (i <= wWidth)
            icon = L'8';
        else if (wBound <= wWidth && hBound <= wHeight)
            icon = L'1';
        else
            icon = L'.';

        Pixel p{ IntToCoord(i, wWidth, sWidth), icon };
        screenPixels.push_back(p);
    }



    while (true)
    {

        for (int i = 0; i < sWidth * sHeight; i++)
        {

            /*int idx = i * (floor(i / width) + 1);*/
            screen[i] = screenPixels[i].cur;
            //cout << icon;
            // 120 * 30
            //cout << i % 10;
        }

        for (int i = 0; i < 256; i++)
        {

            SHORT state = GetAsyncKeyState(i);

            bool isPressed = false, isReleased = false;

            if (OldKeyState->value != state)
            {
                if (state == 0)
                {

                    isPressed = false;
                    isReleased = false;
                }
                else if (state == 1)
                {
                    isPressed = false;
                    isReleased = true;
                }
                else {
                    isPressed = true;
                    isReleased = false;
                }
            }
            NewKeyState[i] = { i, state, isPressed, isReleased };
            OldKeyState[i] = NewKeyState[i];
        }


        if (NewKeyState[VK_UP].isPressed)
            cursor.coordinates.Y--;
        if (NewKeyState[VK_DOWN].isPressed)
            cursor.coordinates.Y++;
        if (NewKeyState[VK_LEFT].isPressed)
            cursor.coordinates.X--;
        if (NewKeyState[VK_RIGHT].isPressed)
            cursor.coordinates.X++;


        if (cursor.coordinates.Y < 0)
            cursor.coordinates.Y = wHeight;
        else if (cursor.coordinates.Y > wHeight)
            cursor.coordinates.Y = 0;

        if (cursor.coordinates.X < 0)
            cursor.coordinates.X = wWidth;
        else if (cursor.coordinates.X > wWidth)
            cursor.coordinates.X = 0;

        if (NewKeyState[VK_SPACE].isPressed)
        {
            int pos = CoordToInt(cursor, sWidth);

            screenPixels[pos].cur = L'+';
        }

        int pos = cursor.coordinates.X + (cursor.coordinates.Y * sWidth);
        screen[pos] = cursor.cur;
        
        t2 = chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = t2 - t1;
        //swprintf_s(screen, 40, L"fps %3.2f", 1.0f / elapsed_seconds.count());

        screen[sWidth * sHeight - 1] = '\0';
        WriteConsoleOutputCharacter(hConsole, screen, sWidth * sHeight, { 0,0 }, &dwBytesWritten);


        t1 = t2;
        //break;
        Sleep(100);
    }



    string x;
    cin >> x;
    return 0;
}