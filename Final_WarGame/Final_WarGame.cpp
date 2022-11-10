//#include "vld.h"
#include <iostream>
#include "Game.h"
#include "Deck.h"
#include "Card.h"
#include "Menu.h"

using std::cout;
using std::endl;

void DisplayFinalResults(int& pOneWins, int& pTwoWins, int& draw, int& numOfGames, int& totalNumOfRounds, int& longRounds, int& shortRounds);

int main()
{
    int numOfPlayers = 2;
    int numOfGames = 0;
    int playerOneWins = 0;
    int playerTwoWins = 0;
    int numOfDraws = 0;
    int numOfRounds = 0;
    int totalNumOfRounds = 0;
    int longRounds = 0;
    int shortRounds = 1000000;
    bool isGameOver = false;
    bool showRounds = false;
    bool isManual = false;
    bool keepPlaying = true;

    //Create member object
    Menu menu;

    do
    {   //Opens main menu to receive game settings and stores them for use
        menu.MainMenu(numOfGames, showRounds, isManual, keepPlaying);

        if (keepPlaying)
        {
            //Creates game using settings selected in menu
            system("cls");
            Game myGame(numOfPlayers, numOfRounds, totalNumOfRounds, showRounds, isManual);

            for (int i = 0; i < numOfGames; i++)
            {
                //Plays through game until the game is over
                while (!isGameOver)
                {                    
                    myGame.PlayGame(isGameOver, playerOneWins, playerTwoWins, numOfDraws, totalNumOfRounds, longRounds, shortRounds);
                }
                myGame.ResetGame(isGameOver);
            }
            // Displays final results after all games have been played through
            DisplayFinalResults(playerOneWins, playerTwoWins, numOfDraws, numOfGames, totalNumOfRounds, longRounds, shortRounds);

            cout << "Do you want to play again?" << endl;
            keepPlaying = menu.YesOrNoPrompt();
        }       
        playerOneWins = 0;
        playerTwoWins = 0;

    } while (keepPlaying);
    return 0;
}


//Displays results of all games played this session
void DisplayFinalResults(int& pOneWins, int& pTwoWins, int& draw, int& numOfGames, int& totalNumOfRounds, int& longRounds, int& shortRounds)
{
    int avgNumofRounds = 0;
    if (numOfGames != 0)
    {
        avgNumofRounds = totalNumOfRounds / numOfGames;
    }

    cout << "************************************" << endl;
    cout << "Number of games played: " << numOfGames << endl;
    cout << "Player One Wins: " << pOneWins << endl;
    cout << "Player Two Wins: " << pTwoWins << endl;
    cout << "# of Draws: " << draw << endl;
    cout << "The shortest game was " << shortRounds << " rounds" << endl;
    cout << "The longest game was " << longRounds << " rounds" << endl;
    cout << "Total Rounds Played: " << totalNumOfRounds << endl;
    cout << "Average number of rounds: " << avgNumofRounds << endl;
    cout << "************************************" << endl;
}