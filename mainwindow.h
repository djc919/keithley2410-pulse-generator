#ifndef GTKMM_MAINWINDOW_H
#define GTKMM_MAINWINDOW_H

#include <gtkmm.h>

class MainWindow : public Gtk::Window {

public:
	
	MainWindow();
	virtual ~MainWindow();

private:
	//Signal handlers
	void on_menu_file_new_generic();
	void on_menu_file_quit();
	void on_menu_others();

	//Child Widgets
	Gtk::VBox m_Box;

	Glib::RefPtr<Gtk::UIManager> m_refUIManager;
	Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;

};

#endif