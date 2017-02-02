#include <iostream>
#include <iomanip> 
#include <time.h>
#include <math.h>
#include <stdbool.h>
using namespace std;

int *guessed;
int *answer;
int *inputans;
int truelen = 0;
int guesses = 10;
int maxn = 7;

void gui(){
	for(int i = 0; i < truelen; ++i){
		if(guessed[i] == -1){
			cout << "_"  << " ";
		} else {
			cout << guessed[i] << " ";
		}
	}
	cout << "\n";
	cout << endl;
}

int mixd(){
	// Gives number between 1 - maxn
	return (time(NULL) + rand()) % maxn + 1;
}

void makeanswer(){
	answer = new int[truelen];
	guessed = new int[truelen];
	for(int i; i < truelen; ++i){
  		answer[i] = mixd();
  		guessed[i] = -1;
  	}
}

int getdigit(int findex, int inpu){
	int tens = pow(10, truelen - findex);
	int last = inpu % tens;
	return last % 10;
}

void checkanswer(int inp){
	inputans = new int[truelen];
	int counter = inp;
	for(int i = truelen -1; i >= 0; --i){
		inputans[i] = counter % 10;
		counter /= 10;
	}
	for(int i = 0; i < truelen; ++i){
		if (answer[i] == inputans[i]){
			guessed[i] = answer[i];
		}
	}
}

void howclose(){
	for(int i = 0; i < truelen; ++i){
		if(answer[i] == inputans[i]){
			cout << "correct ";
		} else {
			int lookfor = inputans[i];
			bool wrongplace = false;
			for(int i = 0; i < truelen; ++i){
				if(answer[i] == lookfor){
					wrongplace = true;
				}
			}
			if(wrongplace == true){
				cout << "wrongplace ";
			} else {
				cout << "incorrect ";
			}
			
		}
	}
	cout << "\n" << endl;
}

bool checkdone(){
	for(int i = 0; i < truelen; ++i){
		if(answer[i] != inputans[i]){
			return false;
		}
	}
	return true;
}

int constructans(int *arrans){
	int final = 0;
	int count = 1;
	for(int i = 0; i < truelen; ++i){
		final *= 10;
		final += answer[i];
		count *= 10;
	}
	return final;
}

int main()
{
	int len;
	cout << "Masterminded\n";
	cout << "The passcode is made up of numbers between 1-" << maxn << "\n";
  	cout << "State the length (2-5): " << endl;
  	cin >> len;
  	while(len < 2 || len > 5){
  		cout << "State the length (2-5): " << endl;
  		cin >> len;
  	}
  	// Valid length now inputted
  	truelen = len;
  	makeanswer();
  	cout << "You get " << guesses << " guesses" << endl;
  	int input;
  	// Can be 00
  	float min = 0;
  	float max = pow(10, truelen) - 1;
  	while(guesses > 0){
  		gui();
  		cout << guesses << " guesses remaining" << endl;
  		cout << "Input guess: " << endl;
  		do{
  			cin >> input;
  		} while ((input < min) || (input > max));
  		checkanswer(input);
  		howclose();
  		if(checkdone()){
  			cout << "You Win!\n";
  			return 0;
  		}
  		--guesses;
  	}
  	cout << "You Lose!" << endl;
  	cout << "The code was: " << constructans(answer) << "\n" << endl;
  	return 0; 	
}