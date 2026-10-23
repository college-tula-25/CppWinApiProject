#include <iostream>
#include <Windows.h>

enum Colors
{
    Black,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Yellow,
    LightGray,
    Gray,
    LightBlue,
    LightGreen,
    LightCyan,
    LightRed,
    LightMagenta,
    LightYellow,
    White
};

struct Point
{
    int row;
    int column;
};

struct Size
{
    int width;
    int height;
};

struct Box
{
    Point point;
    Size size;
    Colors background;
    Colors foreground;
};

void SetForeground(HANDLE console, Colors color);
void SetBackground(HANDLE console, Colors color);
void SetPosition(HANDLE console, Point point);

void BoxView(HANDLE console, Box box);

int main()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    
    Box box{ { 10, 4 }, { 20, 5 }, Red, White };

    BoxView(console, box);

}

void SetForeground(HANDLE console, Colors color)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(console, &info);
    WORD background = info.wAttributes & 0xF0;

    SetConsoleTextAttribute(console, background | color);
}
void SetBackground(HANDLE console, Colors color)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(console, &info);
    WORD foreground = info.wAttributes & 0xF;

    SetConsoleTextAttribute(console, (color << 4) | foreground);
}

void SetPosition(HANDLE console, Point point)
{
    COORD position{ point.row, point.column };
    SetConsoleCursorPosition(console, position);
}

void BoxView(HANDLE console, Box box)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(console, &info);
    WORD oldColors = info.wAttributes;

    SetBackground(console, box.background);
    SetForeground(console, box.foreground);

    for (int i{}; i < box.size.height; i++)
        for (int j{}; j < box.size.width; j++)
        {
            SetPosition(console, { box.point.column + j, box.point.row + i });
            std::cout << " ";
        }

    SetConsoleTextAttribute(console, oldColors);
}
