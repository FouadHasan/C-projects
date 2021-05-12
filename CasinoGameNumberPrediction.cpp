#include <iostream>
#include <string> // Needed to use strings
#include <cstdlib> // Needed to use random numbers
#include <ctime>
using namespace std;
 
void GameRules();
 
int main()
{
    string playerName;
    int amount; // hold player's balance amount
    int bettingAmount; 
    int guess;
    int dice; // hold computer generated number
    char choice;
 
    srand(time(0)); // "Seed" the random generator

    cout << "CASINO GAME";
    cout << "\nEnter Your Name : ";
    getline(cin, playerName);
 
    cout << "\nEnter Deposit amount to play game : $";
    cin >> amount;
    
    do
    {
        GameRules();
        cout << "\nYour current balance is $ " << amount;
		
		// Get player's betting amount
        do
        {
            cout <<"\n"<<playerName<<", enter money to bet : $";
            cin >> bettingAmount;
            if(bettingAmount > amount)
                cout << "\nYour betting amount is more than your current balance"
                       <<"\nRe-enter data";
        }while(bettingAmount > amount);
 
		// Get player's numbers
        do
        {
            cout << "Guess your number to bet between 1 to 10 :";
            cin >> guess;
            if(guess <= 0 || guess > 10)
                cout << "Please check the number!! should be between 1 to 10\n"
                    <<"\nRe-enter data\n ";
        }while(guess <= 0 || guess > 10);
 
        dice = rand()%10 + 1; // Will hold the randomly generated integer between 1 and 10
    
        if(dice == guess)
        {
            cout << "\nGood Luck!! You won $." << bettingAmount * 10;
            amount = amount + bettingAmount * 10;
        }
        else
        {
            cout << "\n"<<"Bad Luck this time !! You lost $ "<< bettingAmount ;
            amount = amount - bettingAmount;
        }
 
        cout << "\nThe winning number was : " << dice ;
        cout << "\n"<<playerName<<", You have $ " << amount ;
        if(amount == 0)
        {
            cout << "\n"<<"You have no money to play ";
            break;
        }
        cout << "\nDo you want to play again (y/n)? ";		
        cin >> choice;
    }while(choice =='Y'|| choice=='y');
    
    cout << "\n"<< "Thanks for playing game. Your balance amount is $ " << amount ;

    return 0;
} // END OF main PROGRAM
 
void GameRules()
{
    cout << "\nRULES OF THE GAME";

    cout << "\n1. Choose any number between 1 to 10";
    cout << "\n2. If you win you will get 10 times of money you bet";
    cout << "\n3. If you bet on wrong number you will lose your betting amount";
} // END OF GameRules

