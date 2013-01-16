#include "helloworld.h"
#include <gtkmm/stock.h>
#include <iostream>
#include <cstdio>

HelloWorld::HelloWorld() : m_adjustment_amp(0.0, 0.0, 1000.0, 0.000001, 0.0001, 0.0),
	m_spinbutton_amp(m_adjustment_amp),
	m_table(5, 2, true),
	m_button1("Button 1"),
	m_button2("Button 2") { 

	set_title("A Remote Terminal ExperiMent Interface System - ARTEMIS");
	set_default_size(800,600);

	//Menu Bar code
	add(m_box1);
	add(m_table);

	m_refActionGroup = Gtk::ActionGroup::create();

	//File|New sub menu:
	//m_refActionGroup->add(Gtk::Action::create("FileNew",Gtk::Stock::NEW, "_New", "Create a new file"),
		//sigc::mem_fun(*this, &HelloWorld::on_menu_file_new_generic));

	//File menu:
	m_refActionGroup->add(Gtk::Action::create("FileMenu", "File"));
	
	//Sub menu:
	m_refActionGroup->add(Gtk::Action::create("FileNew", Gtk::Stock::NEW));
	m_refActionGroup->add(Gtk::Action::create("FileQuit", Gtk::Stock::QUIT),
		sigc::mem_fun(*this, &HelloWorld::on_menu_file_quit));

	//Edit menu
	m_refActionGroup->add(Gtk::Action::create("EditMenu", "Edit"));
	m_refActionGroup->add(Gtk::Action::create("EditCopy", Gtk::Stock::COPY),
		sigc::mem_fun(*this, &HelloWorld::on_menu_others));
	m_refActionGroup->add(Gtk::Action::create("EditPaste", Gtk::Stock::PASTE),
		sigc::mem_fun(*this, &HelloWorld::on_menu_others));

	//Choices menu, to demonstrate radio items
	m_refActionGroup->add(Gtk::Action::create("ChoicesMenu", "Choices"));
	Gtk::RadioAction::Group group_userlevel;
	m_refChoiceOne = Gtk::RadioAction::create(group_userlevel, "ChoiceOne", "One");
	m_refActionGroup->add(m_refChoiceOne,
		sigc::mem_fun(*this, &HelloWorld::on_menu_choices_one));
	m_refChoiceTwo = Gtk::RadioAction::create(group_userlevel, "ChoiceTwo", "Two");
	m_refActionGroup->add(m_refChoiceTwo,
		sigc::mem_fun(*this, &HelloWorld::on_menu_choices_two));

	//Help menu
	m_refActionGroup->add(Gtk::Action::create("HelpMenu", "Help"));
	m_refActionGroup->add(Gtk::Action::create("HelpAbout", Gtk::Stock::HELP),
		sigc::mem_fun(*this, &HelloWorld::on_menu_others));

	m_refUIManager =Gtk::UIManager::create();
	m_refUIManager->insert_action_group(m_refActionGroup);

	add_accel_group(m_refUIManager->get_accel_group());

	//Laying out menubar and toolbar
	Glib::ustring ui_info = 
		"<ui>"
		"	<menubar name='MenuBar'>"
		"		<menu action='FileMenu'>"
		"			<menu action ='FileNew'>"
		"		</menu>"
		"			<separator/>"
		"			<menuitem action='FileQuit'/>"
		"		</menu>"
		"		<menu action='EditMenu'>"
		"			<menuitem action='EditCopy'/>"
		"			<menuitem action='EditPaste'/>"
		"		</menu>"
		"		<menu action='ChoicesMenu'>"
		"			<menuitem action='ChoiceOne'/>"
		"			<menuitem action='ChoiceTwo'/>"
		"		</menu>"
		"		<menu action='HelpMenu'>"
		"			<menuitem action='HelpAbout'/>"
		"		</menu>"
		"	</menubar>"
//		"	<toolbar name='ToolBar'>"
//		"		<toolbaritem action='FileNew'/>"
//		"		<toolbaritem action='FileQuit'/>"
//		"	</toolbar>"
		"</ui>";

	try	{

		m_refUIManager->add_ui_from_string(ui_info);

	}

	catch(const Glib::Error& ex)	{

		std::cerr <<"building menus failed: " << ex.what();

	}


	Gtk::Widget* pMenubar = m_refUIManager->get_widget("/MenuBar");
	if(pMenubar)
		m_box1.pack_start(*pMenubar, Gtk::PACK_SHRINK);

	Gtk::Widget* pToolbar = m_refUIManager->get_widget("/ToolBar");
	if(pToolbar)
		m_box1.pack_start(*pToolbar, Gtk::PACK_SHRINK);

	//Now when the button is clokced, we call the "on_button_clicked" function
	//with a pointer to "button 1" as its argument
	m_button1.signal_clicked().connect(sigc::bind<Glib::ustring>(
		sigc::mem_fun(*this, &HelloWorld::on_button_clicked), "button 1"));

	//instead of gtk_container_add, we pack this button into the invisible
	//box, which has been packind into the window.
	m_table.attach(m_button1, 0, 1, 1, 2);

	m_button1.show();

	m_button2.signal_clicked().connect(sigc::bind<-1, Glib::ustring>(
		sigc::mem_fun(*this, &HelloWorld::on_button_clicked), "button 2"));

	m_table.attach(m_button2, 1, 2, 1, 2);

	m_button2.show();

	m_spinbutton_amp.set_wrap();
	m_table.attach(m_spinbutton_amp, 0, 1, 0, 1);
	m_box1.show();

	m_box1.pack_end(m_table);

	show_all_children();

}

HelloWorld::~HelloWorld() {}

void HelloWorld::on_menu_file_quit() {

	hide();

}

void HelloWorld::on_menu_file_new_generic() {

	std::cout << "A File|New menu item was selected." << std::endl;

}

void HelloWorld::on_menu_others() {

	std::cout << "A menu item was selected." << std::endl;

}

void HelloWorld::on_menu_choices_one() {

	Glib::ustring message;

	if(m_refChoiceOne->get_active())
		message = "Choice 1 was selected.";
	else
		message = "Choice 1 was deselected.";

	std::cout << message << std::endl;

}

void HelloWorld::on_menu_choices_two() {

	Glib::ustring message;

	if(m_refChoiceTwo->get_active())
		message = "Choice 2 was selected.";
	else
		message = "Choice 2 was deselected.";

	std::cout << message << std::endl;

}

void HelloWorld::on_button_clicked(Glib::ustring data) {

	std::cout <<"Hello World -" << data << "was pressed" << std::endl;

}