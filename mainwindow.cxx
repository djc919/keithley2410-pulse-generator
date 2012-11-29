#include"mainwindow.h"
#include<gtkmm/stock.h>
#include <iostream>

MainWindow::MainWindow() {

	set_title("Aperture Keithley 2410 Control Interface");
	set_default_size(640,480);

	//Put a MenuBar at the top of the box and other stuff below it.
	add(m_Box);

	//Create actions for menus and toolbars
	m_refActionGroup = Gtk::ActionGroup::create();

	//File|New sub menu
	m_refActionGroup->add(Gtk::Action::create("FileNewStandard",
		Gtk::Stock::NEW, "_New", "Create a new file"),
		sigc::mem_fun(*this, &MainWindow::on_menu_file_new_generic));

	m_refActionGroup->add(Gtk::Action::create("FileMenu", "File"));
	
	//Sub menu
	m_refActionGroup->add(Gtk::Action::create("FileNew", Gtk::Stock::NEW));
	m_refActionGroup->add(Gtk::Action::create("FileOpen", Gtk::Stock::OPEN));
	m_refActionGroup->add(Gtk::Action::create("FileSave", Gtk::Stock::SAVE));
	m_refActionGroup->add(Gtk::Action::create("FileSaveAs", Gtk::Stock::SAVE_AS));
	m_refActionGroup->add(Gtk::Action::create("FileQuit", Gtk::Stock::QUIT),
		sigc::mem_fun(*this, &MainWindow::on_menu_file_quit));

	//Edit menu
	m_refActionGroup->add(Gtk::Action::create("EditMenu", "Edit"));
	//Sub menu
	m_refActionGroup->add(Gtk::Action::create("EditCopy", Gtk::Stock::COPY),
		sigc::mem_fun(*this, &MainWindow::on_menu_others));
	m_refActionGroup->add(Gtk::Action::create("EditPaste", Gtk::Stock::PASTE),
		sigc::mem_fun(*this, &MainWindow::on_menu_others));
	
	//Options menu
	m_refActionGroup->add(Gtk::Action::create("OptionsMenu", "Options"));

	//View menu
	m_refActionGroup->add(Gtk::Action::create("ViewMenu", "View"));
	//Sub menu
	m_refActionGroup->add(Gtk::Action::create("ViewFullScreen", Gtk::Stock::FULLSCREEN),
		sigc::mem_fun(*this, &MainWindow::on_menu_others));

	//Help menu
	m_refActionGroup->add(Gtk::Action::create("HelpMenu", "Help"));
	//Sub menu
	m_refActionGroup->add(Gtk::Action::create("HelpHelp", Gtk::Stock::HELP),
		sigc::mem_fun(*this, &MainWindow::on_menu_others));
	m_refActionGroup->add(Gtk::Action::create("HelpAbout", Gtk::Stock::ABOUT),
		sigc::mem_fun(*this, &MainWindow::on_menu_others));

	m_refUIManager = Gtk::UIManager::create();
	m_refUIManager->insert_action_group(m_refActionGroup);

	add_accel_group(m_refUIManager->get_accel_group());

	//Layout the actions in a menubar and toolbar
	Glib::ustring ui_info = 
		"<ui>"
		"	<menubar name='MenuBar'>"
		"		<menu action='FileMenu'>"
		"			<menu action='FileNew'>"
		"				<menuitem action='FileNewStandard'/>"
		"			</menu>"
		"			<menuitem action='FileOpen'/>"
		"			<menuitem action='FileSave'/>"
		"			<menuitem action='FileSaveAs'/>"
		"			<separator/>"
		"			<menuitem action='FileQuit'/>"
		"		</menu>"
		"		<menu action='EditMenu'>"
		"			<menuitem action='EditCopy'/>"
		"			<menuitem action='EditPaste'/>"
		"		</menu>"
		"		<menu action='OptionsMenu'>"
		"		</menu>"
		"		<menu action='ViewMenu'>"
		"			<menuitem action='ViewFullScreen'/>"
		"		</menu>"
		"		<menu action='HelpMenu'>"
		"			<menuitem action='HelpHelp'/>"
		"			<menuitem action='HelpAbout'/>"
		"		</menu>"
		"	</menubar>"
		"</ui>";

	try {

		m_refUIManager->add_ui_from_string(ui_info);

	}

	catch (const Glib::Error& ex) {

		std::cerr << "building menus failed: " << ex.what();

	}

	//Get the menubar widget, and add it to a container widget
	Gtk::Widget* pMenubar = m_refUIManager->get_widget("/MenuBar");
	m_Box.pack_start(*pMenubar, Gtk::PACK_SHRINK);

	show_all_children();

}

MainWindow::~MainWindow() {}

void MainWindow::on_menu_file_quit() {
	//Closes the main window to stop the Gtk::Main::run()
	hide();
}

void MainWindow::on_menu_file_new_generic() {

	std::cout << "A File|New menu item was selected." << std::endl;

}

void MainWindow::on_menu_others() {

	std::cout << "A menu item was selected." << std::endl;

}