#include"field.h"
#include"mine.h"
#include<iostream>
#include<fstream>
#include<gtkmm.h>
Field::Field(){	//????? keep this???????
	allocateInput(NULL);
	allocateOutput();
	makeButtons();
	printOutputField();
}

Field::Field(char *file){
	allocateInput(file);
	allocateOutput();
	makeButtons();
	printOutputField();
}

void Field::allocateInput(char *file){
	std::fstream inFile;
	char mine;
	int num;
	inFile.open(file);
	if (inFile.fail()){
		std::cin>>num;
		M = num;
		std::cin>>num;
		N = num;
		makeMinefield();
		for(int x=0; x<M; x++){
			for(int y=0; y<N; y++){
				std::cin>>mine;
				mines[x][y].set_input(mine);
			}
		}
	}
	else{
		inFile>>num;
		M = num;
		inFile>>num;
		N = num;
		makeMinefield();
		for(int x=0; x<M; x++){
			for(int y=0; y<N; y++){
				inFile>>mine;
				mines[x][y].set_input(mine);
			}
		}
		inFile.close();
	}
}

void Field::allocateOutput(){
	for(int x=0; x<M; x++){
		for(int y=0; y<N; y++){
			if(mines[x][y].get_input() == '.'){
				int minesum = computeNeighboringMines(x,y);
				mines[x][y].set_output(minesum);
				}
			else
				mines[x][y].set_output(9);
		}
	}
}
int Field::computeNeighboringMines(int i, int j){
	int minesum = 0;
	int u = ((i-1) < 0)?0:(i-1); //left bound
	int v = (i == (M-1))?i:(i+1); //right bound
	int s = ((j-1) < 0)?0:(j-1); //up bound
	int t = (j == (N-1))?j:(j+1); //down bound
	for (int x = u; x <= v; x++){
		for (int y = s; y <= t; y++){
			if (mines[x][y].get_input() == '*')
				minesum += 1;
		}
	}
	return minesum;
}

void Field::printOutputField(){
	for(int x=0; x<M; x++){
		for(int y=0; y<N; y++){
			std::cout<<mines[x][y].get_output()<<" ";
		}
		std::cout<<std::endl;
	}
}

void Field::makeMinefield(){
	mines = new Mine*[M];
	for(int x=0; x<M; x++){
		mines[x] = new Mine[N];
		for(int y=0; y<N; y++){
			mines[x][y].set_x(x);
			mines[x][y].set_y(y);
		}
	}
}

void Field::makeButtons(){
	buttons = new Gtk::ToggleButton *[M];
	add(grid);
	for(int x=0; x<M; x++){
		buttons[x] = new Gtk::ToggleButton [N];
		for(int y=0; y<N; y++){
			buttons[x][y].set_label(" ");
			buttons[x][y].set_size_request(32,32);
			buttons[x][y].signal_toggled().connect(sigc::bind<Mine>(sigc::mem_fun(*this,&Field::on_button_clicked),mines[x][y]));
			grid.attach(buttons[x][y],y,x,1,1);
			buttons[x][y].show();
		}
	}
	grid.show();
}

void Field::on_button_clicked(Mine mine){//add data identifier...
	int x_loc = mine.get_x();
	int y_loc = mine.get_y();
	int z = mine.get_output();
	std::string num;
	std::stringstream out;
	out<<mine.get_output();
	num = out.str();
	if (!mines[x_loc][y_loc].get_open()){
		mines[x_loc][y_loc].set_open();
		if (z == 9){
			buttons[x_loc][y_loc].set_label("*");
			lose();
		}
		else {
			if (z > 0)
				buttons[x_loc][y_loc].set_label(num);
			else{
				buttons[x_loc][y_loc].set_label(" ");
				if (y_loc<(N-1))// check right
					if (mines[x_loc][y_loc+1].get_output() < 9)
						buttons[x_loc][y_loc+1].toggled();
				if (x_loc<(M-1))// check down
					if (mines[x_loc+1][y_loc].get_output() < 9)
						buttons[x_loc+1][y_loc].toggled();
				if (y_loc>0)// check left
					if (mines[x_loc][y_loc-1].get_output() < 9)
						buttons[x_loc][y_loc-1].toggled();
				if (x_loc>0)//check up
					if (mines[x_loc-1][y_loc].get_output() < 9)
						buttons[x_loc-1][y_loc].toggled();
			}
			check_win();
		}
	}
	buttons[x_loc][y_loc].set_active(true);
}

void Field::check_win(){
	set_win(true);
	for(int x = 0; x<M; x++)
		for(int y = 0; y<N; y++)
			if(mines[x][y].get_output() < 9)
				if(!mines[x][y].get_open()){
					set_win(false);
				}
	if(get_win()){
		gameEnd();
		std::cout<<"You win!"<<std::endl;
	}
}

void Field::set_win(bool cond){
	win = cond;
}

bool Field::get_win(){
	return win;
}

void Field::lose(){
	std::cout<<"You Lose!"<<std::endl;
	for(int x=0; x<M; x++)
		for(int y=0; y<N; y++)
			if(mines[x][y].get_output() == 9)
				if(!mines[x][y].get_open()){
					mines[x][y].set_open();
					buttons[x][y].set_label("*");
					buttons[x][y].set_active(true);
				}
	gameEnd();
}

void Field::gameEnd(){
	std::cout<<"Game Over!"<<std::endl;
//	dioalogue  box: "You lose"
//	deallocateButtons();
//	deallocateMines();
}
void Field::deallocateButtons(){
	for(int x=0; x<M; x++)
		delete[] buttons[x];
	delete[] buttons;
}
void Field::deallocateMines(){
	for(int x=0; x<M; x++)
		delete[] mines[x];
	delete[] mines;
}