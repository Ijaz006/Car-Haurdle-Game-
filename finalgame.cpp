#include <iostream>
#include <conio.h>
#include <string>
#include<dos.h> 
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 30
#define WIN_WIDTH 85

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);


//made this function gloably available so that it can be used in any classes 
void displayAnywhere(int x, int y){ //function which take two parameters and set the cursor position to that co-ordinate 
	COORD CursorPosition;
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) { //function to set cursor at any point on screen
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

class Car{ // class of car 
	protected:
		string myCar[4]; //data member for car shape
		int car_pos;
	
	public:
		
		Car(){ // constructor to initialize array of data member car
			for(int i; i < 4; i++){
				myCar[i] = "no shape";
			}
			car_pos = 0;
		}
		void setCar(string* car){ // it will set car shape
			for(int i=0; i<4; i++){
				myCar[i] = car[i];
			}
			this->car_pos = WIN_WIDTH/2;
		}

		void displayCar(){ // it will display car at screen
			for(int i=0; i < 4; i++){
				displayAnywhere(car_pos,21+i); cout<<myCar[i];
				
			}
		}
		void vanish_car(){ // it will vanish car at screen
			for(int i=0; i < 4; i++){
				displayAnywhere(car_pos,21+i); cout<<"    ";
			}
		}
		
		virtual int crash() = 0;
	
};

class screen{ // made this class for provding backgrounds and multiple screens need for game 
	public:
		void displayBorder(){  // this method is used for making border at screen in which our game willl be played 
			for(int i=0; i<SCREEN_HEIGHT; i++){
				for(int j=0; j<14; j++){ 
					displayAnywhere(0+j,i); cout<<"#"; // displayAnywhere function will set the border with symbol # less than 14 width of screen
					displayAnywhere(WIN_WIDTH-j,i); cout<<"#";
				}
			} 
			for(int i=0; i<SCREEN_HEIGHT; i++){ // create another line apart from a box for car game
				displayAnywhere(SCREEN_WIDTH,i); cout<<"         #";
			} 
		}
		void gameover(){//function to display gamover screen
			system("cls");
			cout<<endl;
			cout<<"\t\t________/////////_______"<<endl;
			cout<<"\t\t**** Game Over!!! ****"<<endl;
			cout<<"\t\t________/////////________"<<endl<<endl;
			cout<<"\t\tPress any key to go back to menu.";
			getch();
		}
		void instructions(){// this will display instruction screen
			system("cls");
			cout<<"Instructions about how  to play the game";
			cout<<"\n---------------------------------------";
			cout<<"\n you can move left and right to avoid hurdles ";
			cout<<"\n\n Press 'a' to move left";
			cout<<"\n Press 'd' to move right";
			cout<<"\n Press 'escape' to exit";
			cout<<"\n\n Press any key to go back to menu";
			getch();
		}
		void main_menu(){// this will display main menu screen
			system("cls");
			cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl; 
			cout<<"		Welcome to CAR HURDLE GAME							"<<endl;
			cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
			displayAnywhere(10,9); cout<<"           Choose options from downside : ";
			displayAnywhere(10,11); cout<<"            PRESS 1 to Start the Game";
			displayAnywhere(10,12); cout<<"            PRESS 2 to go to Instructions screen";	 
			displayAnywhere(10,13); cout<<"            PRESS 3 TO Quit the game";
			
			getch();			
		}
		void side_screen(){
				displayAnywhere(WIN_WIDTH + 2, 2);cout<<"===CAR HURDLE GAME===";
				displayAnywhere(WIN_WIDTH + 6, 4);cout<<"==========";
				displayAnywhere(WIN_WIDTH + 6, 9);cout<<"==========";
				displayAnywhere(WIN_WIDTH + 6, 12);cout<<"Controls ";
				displayAnywhere(WIN_WIDTH + 6, 13);cout<<"======== ";
				displayAnywhere(WIN_WIDTH + 2, 14);cout<<"  A Key - Left";
				displayAnywhere(WIN_WIDTH + 2, 15);cout<<"  D Key - Right"; 
				displayAnywhere(18, 5);cout<<"Press any key to start";
				getch();
				displayAnywhere(18, 5);cout<<"                      ";
		}
};

class hurdles{
	protected:
		int hurdleX[3];
		int hurdleY[3];
		int hurdle[3];
	public:
		hurdles(){//this will initialize data members
			for(int i; i < 3; i++){
				hurdleX[i] = 0;
				hurdleY[i] = 0;
				hurdle[i] = 0;
			}

		}
		void makehurdles(int H){// this will make hurdles appear randomly on screen
			hurdleX[H] = 17 + rand()%(50);
		}
		void hurdleShape(int H){// this will print shape of hurdle on screen
			if( hurdle[H] == true ){
				displayAnywhere(hurdleX[H], hurdleY[H]);   cout<<"####";  
				displayAnywhere(hurdleX[H], hurdleY[H]+1); cout<<" ## "; 
				displayAnywhere(hurdleX[H], hurdleY[H]+2); cout<<"####"; 
				displayAnywhere(hurdleX[H], hurdleY[H]+3); cout<<" ## ";  
			} 

		}
		void vanish_hurdle(int H){// this will make hurdles run at limit of screen after it they will vanish
			if( hurdle[H] == true ){
				displayAnywhere(hurdleX[H], hurdleY[H]); cout<<"    ";  
				displayAnywhere(hurdleX[H], hurdle[H]+1); cout<<"    "; 
				displayAnywhere(hurdleX[H], hurdleY[H]+2); cout<<"    "; 
				displayAnywhere(hurdleX[H], hurdleY[H]+3); cout<<"    "; 
			}
		}
		void resethurdle(int H){// this will reproduce hurdle after run one time
			vanish_hurdle(H);
			hurdleY[H] = 1;
			makehurdles(H);
		}

};
// score board class 
class scoreboard{
	protected:
		int highscore,score;
		
	public:
		leaderboard(){
			this->highscore = 0;
			this->score = 0;
		}
		leaderboard(int highscore,int score){
			this->highscore = highscore;
			this->score = score;
		}
				
		void add_score(){
			score+=10;
			cout<<"Score: "<<score<<endl;
		}


		
	
};

//play class which will inherit all the classes 
class play : public Car, public screen, public hurdles, public scoreboard{
	
	public:
		// virtual function declarartion here
		int crash(){//crash function if car and hurdle position be same car will explodde
			if(hurdleY[0]+4 >= 23){
				if(hurdleX[0] + 4 - car_pos >= 0 && hurdleX[0] + 4 - car_pos < 9){
					for(int i=0; i < 4; i++){
						displayAnywhere(car_pos,21+i); cout<<"oooo";
						
					}
					if(highscore <  score){ //for highscore
						highscore = score;
					}
					return 1;
				}
			}
			return 0;
		}
		
		void playGame(){ // play game function it's  a main function where all the game run 
			score = 0; 
			car_pos = WIN_WIDTH/2; //set to mid of the screen
			hurdle[0] = 1;
			hurdle[1] = 0;
			hurdleY[0] = hurdleY[1] = 1;
		
			system("cls");
			screen::displayBorder();
			screen::side_screen();
			
			hurdles::makehurdles(0);
			hurdles::makehurdles(1);
					
			while(1){
				if(kbhit()){
				char ch = getch();
					if( ch=='a' || ch=='A' ){
						if( car_pos > 18 )
							car_pos -= 4; //move left

					}
					if( ch=='d' || ch=='D' ){
						if( car_pos < 65 )
						car_pos += 4; // move right

					}

					if(ch==27){ //escape
						break;
					}					
				}
				
				
				Car::displayCar();
				hurdles::hurdleShape(0);
				hurdles::hurdleShape(1);
				
				if(crash() == 1){
					
					screen::gameover();
					//after gameover scores will be shown
					displayAnywhere(WIN_WIDTH , 5);cout<<"High Score: "<<highscore;
					displayAnywhere(WIN_WIDTH , 6);cout<<"Score: "<<score;
					Sleep(2000);
					return;
				}
				
				Sleep(50);
				Car::vanish_car();
				hurdles::vanish_hurdle(0);
				hurdles::vanish_hurdle(1);
				
				if( hurdleY[0] == 10 ){ //hurdles will run from it
					if( hurdle[1] == 0 )
						hurdle[1] = 1;
				}
					
		
				if( hurdle[0] == 1 ){
					hurdleY[0] += 1;
				}
					
		
				if( hurdle[1] == 1 ){
					hurdleY[1] += 1;
				}
					
		 
				if( hurdleY[0] > SCREEN_HEIGHT-4 ){ // if hurdle will out from screen it will reset from begining
					hurdles::resethurdle(0);
					displayAnywhere(WIN_WIDTH + 6, 5);scoreboard::add_score();

				}
				
				if( hurdleY[1] > SCREEN_HEIGHT-4 ){
					hurdles::resethurdle(1);
					displayAnywhere(WIN_WIDTH + 6, 5);scoreboard::add_score();
				
				}
			}		
			
		}

};




int main(){
	
	setcursor(0,0);//this function used to set cursor at any point on screen
	srand((unsigned) time(NULL));
	//array declared here the shapes of car 
	string car1[] = {" $ ","$$$"," $ ","$ $"};
	//declared play class object it access all class function	
	play p1;

	while(1){
		system("cls");
		p1.main_menu();
		char press = getch();
		if(press == '1'){
			system("cls");
			p1.setCar(car1);
			p1.playGame();				
			}
		else if(press == '2'){
			p1.instructions();
		}
		else if(press == '3'){
			break;
		}
	}

	return 0;
}
