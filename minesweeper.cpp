#include"field.h"
#include"mine.h"
#include<gtkmm.h>
main(int argc, char **argv){//	char *file = argv[1];
	argc = 1;
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
	Field minesweeper(argv[1]);
	return app->run(minesweeper);
}