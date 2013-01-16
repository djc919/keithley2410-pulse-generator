#ifndef GTKMM_HELLOWORLD_H
#define GTKMM_HELLOWORLD_H

#include <gtkmm.h>

class HelloWorld : public Gtk::Window	{

public:

	HelloWorld();

	virtual ~HelloWorld();

private:

	//Signal handlers:
	void on_button_clicked(Glib::ustring data);

	void on_menu_file_new_generic();
	void on_menu_file_quit();
	void on_menu_others();

	void on_menu_choices_one();
	void on_menu_choices_two();

	//Member widgets:
	

	//Child widgets:
	Gtk::VBox m_box1;
	Gtk::Table m_table;
	Gtk::Button m_button1, m_button2;
	Gtk::Adjustment m_adjustment_amp;
	Gtk::SpinButton m_spinbutton_amp;

	Glib::RefPtr<Gtk::UIManager> m_refUIManager;
	Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
	Glib::RefPtr<Gtk::RadioAction> m_refChoiceOne, m_refChoiceTwo;

};

#endif