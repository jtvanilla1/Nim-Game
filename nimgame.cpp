//nim game final exam project
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
using namespace std;
string difficulty="Coach";//keeping track of which version
int countWin=0, countLoss=0, countRetry=0, countRand=0;//keeping track of scores as global values to be edited by either function



//prototypes
void playGame(int n, int m, bool initialTurn, bool endgame);//game function on line 155, endgame results line 256

int main()//main function displays the menu and gives a switch statement to access rules and the playGame void function
{
	//declare variables and initialize default game settings
	unsigned int n=12, m=3, option_int;//unsigned to prevent less than 0 values
	char option;
	bool endgame = true, isInService = true, initialTurn=true;
	//endgame:false-takelose;true-takewin---initialturn:true=player,elsefalse
	
	do //menu loop
	{
		cout << "************************************" << endl//fancy menu design >:D
			 << "----*-.-*-.-*-NIM GAME-*-.-*-.-*----" << endl
			 << "a coin-swiping game by Josiah Manning" << endl
			 << "for CSCI 101 Biola Fall Semester 2015" << endl
			 << "\"" << difficulty << "\" Version" << endl
			 << "************************************" << endl << endl
			 
			 << "CURRENT RULES:" << endl
			 << "------------------------------------" << endl
			 << "(1) Who goes first:\t";
					if (initialTurn==false) //conditions of who goes first display
						cout << "Computer" << endl;//if I were to not have the ";", could i just continue to cout statement into line 39?
					else
						cout << "Player" << endl; //default
		cout << "(2) Starting coins:\t" << n << endl
			 << "(3) Max coins:\t\t" << m << endl
			 << "(4) Endgame:\t\tPicking last coin ";
					if (endgame==false) //conditions of endgame display
						cout << "loses." << endl;
					else
						cout << "wins." << endl;
		
						
		cout << endl//user options for switch statement
			 << "OPTIONS:" << endl
			 << "---------------------------------" << endl
			 << "(1-4):\tEdit current rules" << endl
 			 << "(P):\tPlay NIM Game with current rules" << endl
			 << "(D):\tDisplay current scores" << endl
 			 << "(R):\tReset current scores" << endl
			 << "(Q):\tQuit NIM Game" << endl << endl
			 
			 << "What would you like to do?: ";
		cin >> option;
		

		//User menu input
		switch(option)
		{
			case '1'://initial turn
			{
			cout << "Who would you like to go first?" << endl
				<< "(1):\tPlayer" << endl
				<< "(2):\tComputer" << endl;
			cin >> option_int;
			if(option_int==2)
				initialTurn=false;//IF INITIALTURN=FALSE, COMPUTER GOES FIRST!!!!!!!!!!!
			else//default
				initialTurn=true;//IF INITIALTURN=TRUE, PLAYER GOES FIRST!!!!!!!!!!!		
				break;
			}
			case '2'://starting coins
			{
			cout << "How many coins would you like the game to start with?: ";	
			cin >> option_int;	
				if (option_int>0)
				{
					n=option_int;
					break;
				}
				else
				{
					cout << "Invalid number. Reset to default." << endl;
					n=12;//default value
					break;
				}
			}
			case '3'://max coins
			{
			cout << "What is the maximum number of coins a player can take?: ";
			cin >> option_int;
				if (option_int>0)
				{
					m=option_int;
					break;
				}
				else//even though its an unsigned int value, just a precaution
				{
					cout << "Invalid number. Reset to default." << endl;
					m=3;//default value
					break;
				}						
			}
			case '4'://endgame
			{
				cout << "What is the effect of taking the last coin?" << endl
					 << "(1): Win" << endl
					 << "(2): Lose" << endl;
				cin >> option_int;
				if(option_int==1)
				endgame=true; 
				else
				endgame=false;
				break;				
			}
			case 'p'://PLAY THE GAME!!!!!!!!!!!!!!!
			{
			playGame(n,m,initialTurn,endgame); //void function recieving data from total coins, max coins, who goes first, and conditions of victory
			break;
			}
			case 'd'://display scores
			{
				cout << "Wins: " << countWin << " | Losses: " << countLoss << " | Retries: " << countRetry << " | Random Moves: " << countRand << " |" << endl;
				break;
			}
			case 'r'://reset scores
			{
				cout << "Your scores for this session have been reset." << endl;
				countWin=0;
				countLoss=0;
				countRetry=0;
				countRand=0;
				break;
			}
			case 'q'://quit
			{
				cout << "Thank you for playing!" << endl;
				isInService=false;
				break;					
			}
			default://any other option
			{
				cout << "Invalid selection." << endl;
			}
		}
	}while(isInService);
	return 0;
}


void playGame(int n, int m, bool initialTurn, bool endgame)
{
	//declaration of variables and conditional initialization of current turn
	//rematch scores initialized to the original score, so all settings are reset
	bool isInService=true, rematchTurn=initialTurn;//rematchTurn initializes with the original value of initialTurn, so in a rematch, initialTurn can be reinitialized with rematchTurn
	int takeCoins, rematchN=n, optimal, randTakeCoins, preRandN; //rematchN follows the same logic as rematch turn;;;preRandN also follows this logic, but on each iteration of the loop for the random move
	char rematch, option;//different input names; I probably could have simplified this, but it helps clarify which input the program is receiving

beginning://label for goto returning to the loop for rematch option
	do
	{
		if (endgame==true)
		optimal=n%(m+1);
		else
		optimal=(n-1)%(m+1);
		
		cout << "There are " << n << " coins left." << endl << endl;
		
		if(initialTurn==true)//player's turn
		{
			RetryPoint://goto label for the rety option
			cout << "How many coins (1-" << m << ") would you like to take?: ";
			cin >> takeCoins;
			
			if(takeCoins>0 && takeCoins<=m && n-takeCoins>=0)
			{
				if(takeCoins==optimal)//compares the input to the optimal formula, which is applicable to both the player and the computer
				{
				cout << "Computer's comments: Good job! You picked the best move." << endl;
				n-=takeCoins;
				initialTurn=false; //at the end of the turn, switch
				}
				else if (takeCoins!=optimal&&optimal!=0) //if optimal exists but the player hasnt chosen it
				{
				cout << "Computer's comments: That's not the best move. Would you like to try again?" << endl
					 << "Press (y) for a retry, anything else to SKIP." << endl;
				cin >> option;
					if (option=='y')//retry options
					{
					countRetry++;
					goto RetryPoint;//because its a pseudo-loop, this conditional will repeat until the player gets the optimal move or they decide to skip
					}
					else
					{
					n-=takeCoins;
					initialTurn=false;
					}	 
				}
				else if (takeCoins!=optimal&&optimal==0)//if no optimal move exists for the player
				{
					cout << "There is no optimal move for you, so your move is fine." << endl;
					n-=takeCoins;//nuff said
					initialTurn=false;
				}
			}
			else
			{	
				cout << "Invalid. Please pick a number between 1 and " << m << "." << endl;//default error message. Will repeat if input is invalid
			}
		}
		else if(initialTurn==false)//computer's turn
		{
			if(optimal==0)//no optimal move for computer; pick random number between 1 and m
			{
			preRandN=n;
			n-=rand()%m+1;
			cout << "It is my turn. I have no optimal move, so I take " << preRandN-n << " at random." << endl;
			initialTurn=true; // at the end of the turn, switch
			}
			else if(optimal!=0)//if computer has an optimal move
			{
			cout << "It is my turn. I have an optimal move. Would you like me\nto make a random move instead?" << endl
				 << "Press (y) to have me make a random move, anything else to SKIP." << endl;
			cin >> option;
				if(option=='y')
				{
				 	preRandN=n;
					n-=rand()%m+1;//random number from 1 to m
					cout << "I take " << preRandN-n << " at random." << endl;//preRandN initializes to n in order to display the difference between n and the new value of n after the subtraction
					countRand++;
					initialTurn=true; // at the end of the turn, switch	
				}
				else
				{
					cout << "I take the optimal move of " << optimal << "." << endl;//if the player decides to waive the forced random
					n-=optimal;
					initialTurn=true;
				}
			}
		}
		
		//loop ends when n=0, then it continues to the endgame conditions
		if (n>0)
		isInService=true;
		else if (n<=0)
		{
		isInService=false;
		break;
		}
	}while(isInService=true);//end of loop

	//ENDGAME SETTINGS
	if (endgame==true)//RULE: player taking last coin wins
	{
		if (initialTurn==false)//player wins; endgame check happens after a turn is traded
		{
			countWin++;
			cout << endl << "Congradulations! You win because you took the last coin!" << endl
		 		 << "Your current score is " << countWin << " wins and " << countLoss << " losses." << endl	//display score
				 << "You currently have " << countRetry << " retries and " << countRand << " times you forced me\n"		
				 << "to take a random number. Rematch with same rules?(y/n): ";
			cin >> rematch;
			if (rematch=='y')
			{
			n=rematchN;//reinitialize to original rule settings
			initialTurn=rematchTurn;// ||
			goto beginning;//plugs back into the do-while loop, skipping the variable definitions
			}
			else
			return;//not needed with a void, but helpful to visualize
		}
		else//player loses
		{
			countLoss++;
			cout << endl << "Good game! However, I won because I took the last coin." << endl
		 		 << "Your current score is " << countWin << " wins and " << countLoss << " losses." << endl	
				 << "You currently have " << countRetry << " retries and " << countRand << " times you forced me\n"		
				 << "to take a random number. Rematch with same rules?(y/n): ";
			cin >> rematch;
			if (rematch=='y')
			{
			n=rematchN;
			initialTurn=rematchTurn;
			goto beginning;
			}
			else
			return;			
		}
	}
	else //RULE: player taking last coin loses
	{	//EVERYTHING BELOW is EXACTLY THE SAME AS ABOVE, but flipped, and a few display changes
		if (initialTurn==false)//player loses; it traded turns before
		{
			countLoss++;
			cout << endl << "Good game! However, I won because you took the last coin." << endl
		 		 << "Your current score is " << countWin << " wins and " << countLoss << " losses." << endl	
				 << "You currently have " << countRetry << " retries and " << countRand << " times you forced me\n"		
				 << "to take a random number. Rematch with same rules?(y/n): ";
			cin >> rematch;
			if (rematch=='y')
			{
			n=rematchN;
			initialTurn=rematchTurn;
			goto beginning;
			}
			else
			return;	
		}
		else//player wins
		{

			countWin++;
			cout << endl << "Congradulations! You win because I took the last coin!" << endl
		 		 << "Your current score is " << countWin << " wins and " << countLoss << " losses." << endl	
				 << "You currently have " << countRetry << " retries and " << countRand << " times you forced me\n"		
				 << "to take a random number. Rematch with same rules?(y/n): ";
			cin >> rematch;
			if (rematch=='y')
			{
			n=rematchN;
			initialTurn=rematchTurn;
			goto beginning;
			}
			else
			return;		
		}		
	}
}
