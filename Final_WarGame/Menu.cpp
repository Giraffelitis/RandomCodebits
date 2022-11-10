#include "Menu.h"

Menu::Menu()
    : m_selection(0)
    , m_numOfGames(1)
    , m_showRounds(true)
    , m_isManual(true)
    , m_keepPlaying(true)
    , m_menuSize(0)
    , m_isValid(false)
{

}

Menu::~Menu()
{

}

void Menu::MainMenu(int& numOfGames, bool& showRounds, bool& isManual, bool& keepPlaying)
{
    do
    {
        system("cls");
        cout << "***** Welcome to my Game of War *****" << endl;
        cout << "Choose an option from the menu" << endl;
        cout << "1. Rules" << endl;
        cout << "2. Play Game" << endl;
        cout << "0. Quit" << endl;
        cin >> m_selection;
        m_isValid = ValidateInput(m_selection, 2); // 2 = number of menu options
    } while (!m_isValid);
    
    switch (m_selection)
    {
    case 1:
    {
        ListRules(numOfGames, showRounds, isManual, keepPlaying);
        break;
    }
    case 2:
    {
        GameMode(numOfGames, showRounds, isManual, keepPlaying);
        break;
    }
    case 0:
    {
        keepPlaying = false;
        break;
    }
    default:
        MainMenu(numOfGames, showRounds, isManual, keepPlaying);
        break;
    }
}

void Menu::ListRules(int& numOfGames, bool& showRounds, bool& isManual, bool& keepPlaying)
{
    system("cls");
    cout << "***** RULES *****" << endl;
    cout << "Each player plays a card at the same time and whichever card is highest wins the round." << endl;
    cout << "If there is a draw then a WAR is declared. Each player lays down three more cards on the " << endl;
    cout << "board for a total of 4 cards played. The value of the third card played during WAR. The " << endl;
    cout << "fourth card total is the card you use to battle with. If that results in a draw you initiate " << endl;
    cout << "another WAR and keep going until a winner is decided or both players run out of cards." << endl;
    cout << endl;
    cout << "The player who wins the round receives all of the cards played in that round. an places them in " << endl;
    cout << "a separate discard pile. When a player runs out of cards in their hand they can pickup the discard " << endl;
    cout << "pile and shuffle it and start using it as thier hand and continue playing." << endl;
    cout << endl;
    cout << "The game ends when one player collects all of the cards. They are declared the winner of the game" << endl;
    cout << "In the event that both players run out of cards in the same round then the game end in a draw." << endl;
    cout << "2. Play Game" << endl;

    PressEnterToContinue();
    MainMenu(numOfGames, showRounds, isManual, keepPlaying);
}


    // Allows user to pick game mode and saves it and prompts for next menu
void Menu::GameMode(int& numOfGames, bool& showRounds, bool& isManual, bool& keepPlaying)
{
    do
    {
        system("cls");
        cout << "*** Game Mode ***" << endl;
        cout << "1. Manual     -- You press a button to play each hand." << endl;
        cout << "2. Automatic  -- Computer automatically plays each round and determines winner." << endl;
        cout << "0. Main Menu" << endl;
        cin >> m_selection;
        m_isValid = ValidateInput(m_selection, 2); // 2 = number of menu options
    } while (!m_isValid);

    switch (m_selection)
    {
    case 1:
    {
        isManual = true;
        NumberOfGames(numOfGames, showRounds);
        break;
    }
    case 2:
    {
        isManual = false;
        NumberOfGames(numOfGames, showRounds);
        AutomaticOptions(numOfGames, showRounds, isManual, keepPlaying);
        break;
    }
    case 0:
    {
        MainMenu(numOfGames, showRounds, isManual, keepPlaying);
        break;
    }
    default: 
        MainMenu(numOfGames, showRounds, isManual, keepPlaying);
        break;
    }
}

    //Allows user to pick how many games they want to play
void Menu::NumberOfGames(int& numOfGames, bool& showRounds)
{
    do
    {
        system("cls");
        cout << "How many games do you want to play through?" << endl;
        cout << "Maximum 10,000" << endl;
        cin >> m_selection;
        m_isValid = ValidateInput(m_selection, 10000); // 10,000 = maximum number allowed
    } while (!m_isValid);  

    numOfGames = m_selection;
    showRounds = true;
}

    //Allows user to determine if they want every hand shown
void Menu::AutomaticOptions(int& numOfGames, bool& showRounds, bool& isManual, bool& keepPlaying)
{
    do
    {
        system("cls");
        cout << "Do you want to show detailed results of every hand played?" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        cout << "0. Main Menu" << endl;
        cin >> m_selection;
        m_isValid = ValidateInput(m_selection, 2); // 2 = number of menu options

    } while (!m_isValid);

    switch (m_selection)
    {
    case 1:
    {
        showRounds = true;
        break;
    }
    case 2:
    {
        showRounds = false;
        break;
    }
    case 0:
    {
        MainMenu(numOfGames, showRounds, isManual, keepPlaying);
        break;
    }
    default:
        MainMenu(numOfGames, showRounds, isManual, keepPlaying);
        break;
    }
}

    //Check user entered data for invalid entries
bool Menu::ValidateInput(int& select, int menuSize)
{
    bool inRange = select >= 0 && select <= menuSize;

    if (cin.fail() || !inRange)
    {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid Entry. Press enter to continue..." << endl;
        cin.ignore(100, '\n');
        return false;
    }
    return true;
}

void Menu::PressEnterToContinue()
{
    cout << endl;
   cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Press Enter to Continue." << endl;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//Prompt for a Yes or No reposnse and return with ture / false
bool Menu::YesOrNoPrompt()
{
    char choice;
    bool isValid = false;

    do
    {
        cout << "(Y/N): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y')
        {
            isValid = true;
        }
        else if (choice == 'n' || choice == 'N')
        {
            isValid = true;
            return false;
        }
        else
        {
            cout << "Invalid Input." << endl;
            cout << endl;
            isValid = false;
        }
    } while (!isValid);

    return true;
}

void DisplayMessage(string message)
{
    cout << message << endl;
}