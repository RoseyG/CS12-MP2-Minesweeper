#ifndef _mine_
#define _mine_
class Mine{
	private:
	char input;
	int output;
	bool open;
	int X;
	int Y;
	public:
	Mine();
	void set_input(char);
	void set_output(int);
	void set_x(int);
	void set_y(int);
	void set_open();
	char get_input();
	int get_output();
	int get_x();
	int get_y();
	bool get_open();
};
#endif