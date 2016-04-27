#include"mine.h"

Mine::Mine(){
	X = 0;
	Y = 0;
	open = false;
}

void Mine::set_input(char sym){
	input = sym;
}

void Mine::set_output(int num){
	output = num;
}

void Mine::set_x(int x){
	X = x;
}

void Mine::set_y(int y){
	Y = y;
}

void Mine::set_open(){
	open = true;
}

char Mine::get_input(){
	return input;
}

int Mine::get_output(){
	return output;
}

int Mine::get_x(){
	return X;
}

int Mine::get_y(){
	return Y;
}

bool Mine::get_open(){
	return open;
}