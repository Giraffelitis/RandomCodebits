#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;

constexpr char kCursor = '_';
constexpr char kTopRightBorder = 187;
constexpr char kTopLeftBorder = 201;
constexpr char kBottomRightBorder = 188;
constexpr char kBottomLeftBorder = 200;
constexpr char kHorizontalBorder = 205;
constexpr char kVerticalBorder = 186;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;

constexpr int kEscapeKey = 27;
constexpr int kBackspace = 8;

void GetLevelDimensions(int& width, int& height);
void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY);
int GetIndexFromXY(int x, int y, int width);
void DisplayTopBorder(int width);
void DisplayLeftBorder();
void DisplayRightBorder();
void DisplayBottomBorder(int width);
bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int width, int height);
void SaveLevel(char* pLevel, int width, int height);
void DisplayLegend();
void RunEditor(char* pLevel,int width, int height);

int main()
{
    int levelWidth;
    int levelHeight;
    bool done = false;
    char* pLevel = nullptr;

    while (!done)
    {
        system("cls");
        cout << " Please select one of the following options." << endl;
        cout << "1. Load Level " << endl;
        cout << "2. New Level" << endl;
        cout << "3. Quit" << endl;

        int input;
        cin >> input;

        if (input == 1)
        {
            cout << "What level do you want to load?" << endl;
            string levelName;
            cin >> levelName;

            levelName.insert(0, "../");

            ifstream levelFile;
            levelFile.open(levelName);

            if (!levelFile)
            {
                cout << "loading level failed." << endl;
            }
            else
            {
                constexpr int tempSize = 25;
                char temp[tempSize];

                levelFile.getline(temp, tempSize, '\n');
                levelWidth = atoi(temp);

                levelFile.getline(temp, tempSize, '\n');
                levelHeight = atoi(temp);

                pLevel = new char[levelWidth * levelHeight];
                levelFile.read(pLevel, levelWidth * levelHeight);
                levelFile.close();

                RunEditor(pLevel, levelWidth, levelHeight);

                delete[] pLevel;
                pLevel = nullptr;
            }
        }
        else if (input == 2)
        {
            GetLevelDimensions(levelWidth, levelHeight);
            pLevel = new char[levelWidth * levelHeight];

            for (int i = 0; i < levelWidth * levelHeight; i++)
            {
                pLevel[i] = ' ';
            }

            RunEditor(pLevel, levelWidth, levelHeight);

            delete[] pLevel;
            pLevel = nullptr;
        }
        else
        {
            done = true;
        }
    }
}

void RunEditor(char* pLevel, int width, int height)
{
    int cursorY = 0;
    int cursorX = 0;
    bool doneEditing = false;

    while (!doneEditing)
    {
        system("cls");
        DisplayLevel(pLevel, width, height, cursorX, cursorY);
        DisplayLegend();
        doneEditing = EditLevel(pLevel, cursorX, cursorY, width, height);
    }

    system("cls");
    DisplayLevel(pLevel, width, height, -1, -1);

    SaveLevel(pLevel, width, height);
}

void DisplayLegend()
{
    cout << "Arrows to move cursor" << endl;
    cout << "ESC to finish editing" << endl;
    cout << "+ | - for walls" << endl;
    cout << "@ for player start" << endl;
    cout << "r g b for key" << endl;
    cout << "R G B for door" << endl;
    cout << "1 2 3 4 for Teleporters  they need to have two of the same number for them to work 1 & 1, 2 & 2 etc.." << endl;
    cout << "L for Lava" << endl;
    cout << "W for Water bucket" << endl;
    cout << "$ for Money" << endl;
    cout << "v for Veritcal moving enemy" << endl;
    cout << "h for Horizontal moving enemy" << endl;
    cout << "s for enemy moving in a square" << endl;
    cout << "e for non moving enemy" << endl;
    cout << "X for end" << endl;
}

void GetLevelDimensions(int& width, int& height)
{
    cout << "Enter the desired level size" << endl;
    cout << "Width: ";
    cin >> width;
    cout << "Height: ";
    cin >> height;
}

void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY)
{
    DisplayTopBorder(width);
    for (int y = 0; y < height; y++)
    {
        DisplayLeftBorder();
        for (int x = 0; x < width; x++)
        {
            if (cursorX == x && cursorY == y)
            {
                cout << kCursor;
            }
            else
            {
                int index = GetIndexFromXY(x, y, width);
                cout << pLevel[index];
            }
        }
        DisplayRightBorder();
    }
    DisplayBottomBorder(width);
}

bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int width, int height)
{
    int newCursorX = cursorX;
    int newCursorY = cursorY;

    int intInput = _getch();

    if (intInput == kArrowInput)
    {
        int arrowInput = _getch();

        switch (arrowInput)
        {
        case kLeftArrow:
            newCursorX--;
            break;
        case kRightArrow:
            newCursorX++;
            break;
        case kUpArrow:
            newCursorY--;
            break;
        case kDownArrow:
            newCursorY++;
            break;
        }

        if (newCursorX < 0)
            newCursorX = 0;
        else if (newCursorX == width)
            newCursorX = width - 1;
        if (newCursorY < 0)
            newCursorY = 0;
        else if (newCursorY == height)
            newCursorY = height - 1;

        cursorX = newCursorX; 
        cursorY = newCursorY;
    }
    else
    {
        if (intInput == kEscapeKey)
        {
            return true;
        }
        else if (intInput == kBackspace)
        {
            //ignore
        }
        else
        {
            int index = GetIndexFromXY(newCursorX, newCursorY, width);
            pLevel[index] = (char)intInput;
        }
    }
    return false;
}

int GetIndexFromXY(int x, int y, int width)
{
    return x + y * width;
}

void DisplayTopBorder(int width)
{
    cout << kTopLeftBorder;
    for (int i = 0; i < width; i++)
    {
        cout << kHorizontalBorder;
    }
    cout << kTopRightBorder << endl;
}

void DisplayLeftBorder()
{
    cout << kVerticalBorder;
}

void DisplayRightBorder()
{
    cout << kVerticalBorder << endl;
}

void DisplayBottomBorder(int width)
{
    cout << kBottomLeftBorder;
    for (int i = 0; i < width; i++)
    {
        cout << kHorizontalBorder;
    }
    cout << kBottomRightBorder << endl;
}

void SaveLevel(char* pLevel, int width, int height)
{
    cout << "Pick an name for your level file (eg: level.txt)";
    string levelName;
    cin >> levelName;

    levelName.insert(0, "../");

    ofstream levelFile;
    levelFile.open(levelName);
    if (!levelFile)
    {
        cout << "Opening level file failed." << endl;
    }
    else
    {
        levelFile << width << endl;
        levelFile << height << endl;
        levelFile.write(pLevel, width * height);
        if (!levelFile)
        {
            cout << "Write failed." << endl;
        }
        levelFile.close();
    }
}