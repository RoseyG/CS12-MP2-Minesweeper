#ifndef _field_
#define _field_
#include<gtkmm.h>
#include"mine.h"
class Field: public Gtk::Window{
//	private:
	int M;
	int N;
	bool win;
	Mine **mines;
	Gtk::Grid grid;
	Gtk::ToggleButton **buttons;
	void makeMinefield();
	void makeButtons();
	void allocateOutput();
	void allocateInput(char*);
	int computeNeighboringMines(int, int);
	void printOutputField();
	void deallocateButtons();
	void deallocateMines();
	void set_win(bool);
//	public:
	int set_m();
	int set_n();
	void on_button_clicked(Mine);
	void check_win();
	void lose();
	bool get_win();
	void gameEnd();
	public:
	Field();
	Field(char *file);
};
#endif