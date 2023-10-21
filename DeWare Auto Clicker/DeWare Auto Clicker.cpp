#include <iostream>
#include <windows.h>
#include <string>
#include <thread>

using namespace std;

bool leftClick = false;
bool rightClick = false;

int cps;

void leftClicker()
{
    INPUT leftINPUT[3] = { 0 };

    leftINPUT[0].type = INPUT_MOUSE;
    leftINPUT[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE;

    leftINPUT[1].type = INPUT_MOUSE;
    leftINPUT[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    leftINPUT[2].type = INPUT_MOUSE;
    leftINPUT[2].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    while (true)
    {
        if (leftClick) {
            POINT cursorPoint;
            GetCursorPos(&cursorPoint);

            leftINPUT[0].mi.dx = cursorPoint.x;
            leftINPUT[0].mi.dy = cursorPoint.y;

            SendInput(3, leftINPUT, sizeof(INPUT));
            
            // cout << leftINPUT[2].mi.dwFlags << "|" << cursorPoint.x << "|" << cursorPoint.y << endl;

            this_thread::sleep_for(chrono::milliseconds(1000 / cps));
        }
    }
}

void rightClicker()
{
    INPUT rightINPUT[3] = { 0 };

    rightINPUT[0].type = INPUT_MOUSE;
    rightINPUT[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE;

    rightINPUT[1].type = INPUT_MOUSE;
    rightINPUT[1].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

    rightINPUT[2].type = INPUT_MOUSE;
    rightINPUT[2].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

    while (true)
    {
        if (rightClick) {
            POINT cursorPoint;
            GetCursorPos(&cursorPoint);

            rightINPUT[0].mi.dx = cursorPoint.x;
            rightINPUT[0].mi.dy = cursorPoint.y;

            SendInput(3, rightINPUT, sizeof(INPUT));

            // cout << rightINPUT[2].mi.dwFlags << "|" << cursorPoint.x << "|" << cursorPoint.y << endl;

            this_thread::sleep_for(chrono::milliseconds(1000 / cps));
        }
    }
}

void autoClicker(int interval)
{
    system("cls");
    cout << "DeWare auto clicker\n\nInterval: " << interval << "\n\n[Hold F]: left click\n[Hold V]: right click" << endl;

    while (true)
    {
        if (GetAsyncKeyState('F') & 1)
        {
            leftClick = !leftClick;
        }

        if (GetAsyncKeyState('V') & 1)
        {
            rightClick = !rightClick;
        }
    }
}

int main()
{
    cout << "DeWare clicker" << endl;

    cout << "Modes: \n\n[1]: Left-Right clicker\n\n>";
    int selection;

    cin >> selection;

    if (selection == 1)
    {
        cin >> cps;

        thread(leftClicker).detach();
        thread(rightClicker).detach();

        autoClicker(cps);
    }
}