///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "BoardPanel.h"
#include "SegmentDisplayPanel.h"
#include "SmileyButton.h"

#include "MainWindow_B.h"

///////////////////////////////////////////////////////////////////////////

MainWindow_B::MainWindow_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );
	
	menu_bar_ = new wxMenuBar( 0 );
	file_menu_ = new wxMenu();
	new_menu_item_ = new wxMenuItem( file_menu_, wxID_NEW, wxString( wxT("New") ) + wxT('\t') + wxT("F2"), wxEmptyString, wxITEM_NORMAL );
	file_menu_->Append( new_menu_item_ );
	
	file_menu_->AppendSeparator();
	
	wxMenuItem* play_video_menu_item_;
	play_video_menu_item_ = new wxMenuItem( file_menu_, wxID_ANY, wxString( wxT("Play Video") ) + wxT('\t') + wxT("CTRL-P"), wxEmptyString, wxITEM_NORMAL );
	file_menu_->Append( play_video_menu_item_ );
	
	preview_video_menu_item_ = new wxMenuItem( file_menu_, wxID_ANY, wxString( wxT("Preview Video") ) + wxT('\t') + wxT("CTRL-R"), wxEmptyString, wxITEM_NORMAL );
	file_menu_->Append( preview_video_menu_item_ );
	preview_video_menu_item_->Enable( false );
	
	save_video_menu_item_ = new wxMenuItem( file_menu_, wxID_ANY, wxString( wxT("Save Video") ) + wxT('\t') + wxT("CTRL-S"), wxEmptyString, wxITEM_NORMAL );
	file_menu_->Append( save_video_menu_item_ );
	save_video_menu_item_->Enable( false );
	
	file_menu_->AppendSeparator();
	
	wxMenuItem* highscore_menu_item_;
	highscore_menu_item_ = new wxMenuItem( file_menu_, wxID_ANY, wxString( wxT("Highscores") ) , wxEmptyString, wxITEM_NORMAL );
	file_menu_->Append( highscore_menu_item_ );
	
	wxMenuItem* history_menu_item_;
	history_menu_item_ = new wxMenuItem( file_menu_, wxID_ANY, wxString( wxT("History") ) , wxEmptyString, wxITEM_NORMAL );
	file_menu_->Append( history_menu_item_ );
	
	file_menu_->AppendSeparator();
	
	wxMenuItem* exit_menu_item_;
	exit_menu_item_ = new wxMenuItem( file_menu_, wxID_CLOSE, wxString( wxT("Exit") ) + wxT('\t') + wxT("Alt-F4"), wxEmptyString, wxITEM_NORMAL );
	file_menu_->Append( exit_menu_item_ );
	
	menu_bar_->Append( file_menu_, wxT("File") ); 
	
	options_menu_ = new wxMenu();
	beginner_menu_item_ = new wxMenuItem( options_menu_, wxID_ANY, wxString( wxT("Beginner") ) + wxT('\t') + wxT("1"), wxEmptyString, wxITEM_NORMAL );
	options_menu_->Append( beginner_menu_item_ );
	
	intermediate_menu_item_ = new wxMenuItem( options_menu_, wxID_ANY, wxString( wxT("Intermediate") ) + wxT('\t') + wxT("2"), wxEmptyString, wxITEM_NORMAL );
	options_menu_->Append( intermediate_menu_item_ );
	
	expert_menu_item_ = new wxMenuItem( options_menu_, wxID_ANY, wxString( wxT("Expert") ) + wxT('\t') + wxT("3"), wxEmptyString, wxITEM_NORMAL );
	options_menu_->Append( expert_menu_item_ );
	
	wxMenuItem* cutstom_menu_item_;
	cutstom_menu_item_ = new wxMenuItem( options_menu_, wxID_ANY, wxString( wxT("Custom") ) + wxT('\t') + wxT("4"), wxEmptyString, wxITEM_NORMAL );
	options_menu_->Append( cutstom_menu_item_ );
	
	options_menu_->AppendSeparator();
	
	decrease_size_item_ = new wxMenuItem( options_menu_, wxID_ANY, wxString( wxT("decrease size") ) + wxT('\t') + wxT("-"), wxEmptyString, wxITEM_NORMAL );
	options_menu_->Append( decrease_size_item_ );
	
	wxMenuItem* increase_size_item_;
	increase_size_item_ = new wxMenuItem( options_menu_, wxID_ANY, wxString( wxT("increase size") ) + wxT('\t') + wxT("+"), wxEmptyString, wxITEM_NORMAL );
	options_menu_->Append( increase_size_item_ );
	
	options_menu_->AppendSeparator();
	
	show_counter_menu_item_ = new wxMenuItem( options_menu_, wxID_ANY, wxString( wxT("Show Counters") ) , wxEmptyString, wxITEM_CHECK );
	options_menu_->Append( show_counter_menu_item_ );
	
	wxMenuItem* settings_menu_item_;
	settings_menu_item_ = new wxMenuItem( options_menu_, wxID_ANY, wxString( wxT("Settings") ) , wxEmptyString, wxITEM_NORMAL );
	options_menu_->Append( settings_menu_item_ );
	
	menu_bar_->Append( options_menu_, wxT("Options") ); 
	
	help_menu_ = new wxMenu();
	wxMenuItem* help_menu_item_;
	help_menu_item_ = new wxMenuItem( help_menu_, wxID_ANY, wxString( wxT("Help") ) , wxEmptyString, wxITEM_NORMAL );
	help_menu_->Append( help_menu_item_ );
	
	wxMenuItem* about_menu_item_;
	about_menu_item_ = new wxMenuItem( help_menu_, wxID_ANY, wxString( wxT("About") ) , wxEmptyString, wxITEM_NORMAL );
	help_menu_->Append( about_menu_item_ );
	
	menu_bar_->Append( help_menu_, wxT("?") ); 
	
	this->SetMenuBar( menu_bar_ );
	
	status_bar_ = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	status_bar_->SetForegroundColour( wxColour( 0, 0, 0 ) );
	
	main_sizer_ = new wxBoxSizer( wxVERTICAL );
	
	main_panel_ = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxCLIP_CHILDREN|wxRAISED_BORDER );
	main_panel_->SetForegroundColour( wxColour( 189, 189, 189 ) );
	main_panel_->SetBackgroundColour( wxColour( 192, 192, 192 ) );
	
	main_panel_sizer_ = new wxBoxSizer( wxVERTICAL );
	
	upper_panel_ = new wxPanel( main_panel_, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER );
	upper_panel_->SetForegroundColour( wxColour( 192, 192, 192 ) );
	upper_panel_->SetBackgroundColour( wxColour( 192, 192, 192 ) );
	
	upper_sizer_ = new wxBoxSizer( wxHORIZONTAL );
	
	
	upper_sizer_->Add( 4, 0, 0, 0, 0 );
	
	mines_display_panel_ = new wxPanel( upper_panel_, wxID_ANY, wxDefaultPosition, wxSize( 40,27 ), wxSUNKEN_BORDER );
	mines_display_panel_->SetForegroundColour( wxColour( 192, 192, 192 ) );
	mines_display_panel_->SetBackgroundColour( wxColour( 192, 192, 192 ) );
	mines_display_panel_->SetMinSize( wxSize( 40,27 ) );
	
	mines_display_sizer_ = new wxBoxSizer( wxHORIZONTAL );
	
	mines_digit_100_ = new SegmentDisplayPanel( mines_display_panel_, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxFULL_REPAINT_ON_RESIZE|wxNO_BORDER );
	mines_digit_100_->SetForegroundColour( wxColour( 255, 0, 0 ) );
	mines_digit_100_->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	mines_digit_100_->SetMinSize( wxSize( 12,-1 ) );
	
	mines_display_sizer_->Add( mines_digit_100_, 1, wxEXPAND, 0 );
	
	mines_digit_10_ = new SegmentDisplayPanel( mines_display_panel_, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxFULL_REPAINT_ON_RESIZE|wxNO_BORDER );
	mines_digit_10_->SetForegroundColour( wxColour( 255, 0, 0 ) );
	mines_digit_10_->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	mines_digit_10_->SetMinSize( wxSize( 12,-1 ) );
	
	mines_display_sizer_->Add( mines_digit_10_, 1, wxEXPAND, 5 );
	
	mines_digit_1_ = new SegmentDisplayPanel( mines_display_panel_, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxFULL_REPAINT_ON_RESIZE|wxNO_BORDER );
	mines_digit_1_->SetForegroundColour( wxColour( 255, 0, 0 ) );
	mines_digit_1_->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	mines_digit_1_->SetMinSize( wxSize( 12,-1 ) );
	
	mines_display_sizer_->Add( mines_digit_1_, 1, wxEXPAND, 5 );
	
	
	mines_display_panel_->SetSizer( mines_display_sizer_ );
	mines_display_panel_->Layout();
	upper_sizer_->Add( mines_display_panel_, 0, wxALIGN_CENTER, 3 );
	
	
	upper_sizer_->Add( 0, 0, 5, wxEXPAND, 0 );
	
	smiley_button_ = new SmileyButton( upper_panel_, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxFULL_REPAINT_ON_RESIZE|wxNO_BORDER );
	smiley_button_->SetMinSize( wxSize( 26,26 ) );
	
	upper_sizer_->Add( smiley_button_, 0, wxALIGN_CENTER|wxBOTTOM|wxTOP, 3 );
	
	
	upper_sizer_->Add( 0, 0, 5, wxEXPAND, 0 );
	
	time_display_panel_ = new wxPanel( upper_panel_, wxID_ANY, wxDefaultPosition, wxSize( 40,27 ), wxSUNKEN_BORDER );
	time_display_panel_->SetForegroundColour( wxColour( 192, 192, 192 ) );
	time_display_panel_->SetBackgroundColour( wxColour( 192, 192, 192 ) );
	time_display_panel_->SetMinSize( wxSize( 40,27 ) );
	
	time_display_sizer_ = new wxBoxSizer( wxHORIZONTAL );
	
	time_digit_100_ = new SegmentDisplayPanel( time_display_panel_, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxFULL_REPAINT_ON_RESIZE|wxNO_BORDER );
	time_digit_100_->SetForegroundColour( wxColour( 255, 0, 0 ) );
	time_digit_100_->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	time_digit_100_->SetMinSize( wxSize( 12,-1 ) );
	
	time_display_sizer_->Add( time_digit_100_, 1, wxEXPAND, 5 );
	
	time_digit_10_ = new SegmentDisplayPanel( time_display_panel_, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxFULL_REPAINT_ON_RESIZE|wxNO_BORDER );
	time_digit_10_->SetForegroundColour( wxColour( 255, 0, 0 ) );
	time_digit_10_->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	time_digit_10_->SetMinSize( wxSize( 12,-1 ) );
	
	time_display_sizer_->Add( time_digit_10_, 1, wxEXPAND, 5 );
	
	time_digit_1_ = new SegmentDisplayPanel( time_display_panel_, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxFULL_REPAINT_ON_RESIZE|wxNO_BORDER );
	time_digit_1_->SetForegroundColour( wxColour( 255, 0, 0 ) );
	time_digit_1_->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	time_digit_1_->SetMinSize( wxSize( 12,-1 ) );
	
	time_display_sizer_->Add( time_digit_1_, 1, wxEXPAND, 5 );
	
	
	time_display_panel_->SetSizer( time_display_sizer_ );
	time_display_panel_->Layout();
	upper_sizer_->Add( time_display_panel_, 0, wxALIGN_CENTER, 3 );
	
	
	upper_sizer_->Add( 4, 0, 0, wxEXPAND, 0 );
	
	
	upper_panel_->SetSizer( upper_sizer_ );
	upper_panel_->Layout();
	upper_sizer_->Fit( upper_panel_ );
	main_panel_sizer_->Add( upper_panel_, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	board_panel_ = new BoardPanel( main_panel_, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxFULL_REPAINT_ON_RESIZE );
	board_panel_->SetForegroundColour( wxColour( 189, 189, 189 ) );
	board_panel_->SetBackgroundColour( wxColour( 189, 189, 189 ) );
	board_panel_->SetMinSize( wxSize( 64,64 ) );
	
	main_panel_sizer_->Add( board_panel_, 1, wxALL|wxEXPAND, 5 );
	
	
	main_panel_->SetSizer( main_panel_sizer_ );
	main_panel_->Layout();
	main_panel_sizer_->Fit( main_panel_ );
	main_sizer_->Add( main_panel_, 1, wxEXPAND, 1 );
	
	
	this->SetSizer( main_sizer_ );
	this->Layout();
	main_sizer_->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainWindow_B::OnClose ) );
	this->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ) );
	this->Connect( new_menu_item_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::newBoard ) );
	this->Connect( play_video_menu_item_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::playVideo ) );
	this->Connect( preview_video_menu_item_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::previewVideo ) );
	this->Connect( save_video_menu_item_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::saveVideo ) );
	this->Connect( highscore_menu_item_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::showHighscores ) );
	this->Connect( history_menu_item_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::showHistory ) );
	this->Connect( exit_menu_item_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::exit ) );
	this->Connect( beginner_menu_item_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::setBoardBeginner ) );
	this->Connect( intermediate_menu_item_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::setBoardIntermediate ) );
	this->Connect( expert_menu_item_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::setBoardExpert ) );
	this->Connect( cutstom_menu_item_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::openCustomDialog ) );
	this->Connect( decrease_size_item_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::decreaseSize ) );
	this->Connect( increase_size_item_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::increaseSize ) );
	this->Connect( show_counter_menu_item_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::showCounters ) );
	this->Connect( settings_menu_item_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::openSettingsDialog ) );
	this->Connect( help_menu_item_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::OnHelp ) );
	this->Connect( about_menu_item_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::OnAbout ) );
	status_bar_->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	main_panel_->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	upper_panel_->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( MainWindow_B::OnUpperPanelEnter ), NULL, this );
	upper_panel_->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	upper_panel_->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( MainWindow_B::OnUpperPanelLeave ), NULL, this );
	upper_panel_->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( MainWindow_B::OnUpperPanelLeftDown ), NULL, this );
	upper_panel_->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( MainWindow_B::OnUpperPanelLeftUp ), NULL, this );
	upper_panel_->Connect( wxEVT_MOTION, wxMouseEventHandler( MainWindow_B::OnUpperPanelEnter ), NULL, this );
	mines_display_panel_->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	mines_digit_100_->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	mines_digit_10_->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	mines_digit_1_->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	smiley_button_->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	time_display_panel_->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	time_digit_100_->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	time_digit_10_->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	time_digit_1_->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	board_panel_->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
}

MainWindow_B::~MainWindow_B()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainWindow_B::OnClose ) );
	this->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ) );
	this->Disconnect( wxID_NEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::newBoard ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::playVideo ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::previewVideo ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::saveVideo ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::showHighscores ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::showHistory ) );
	this->Disconnect( wxID_CLOSE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::exit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::setBoardBeginner ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::setBoardIntermediate ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::setBoardExpert ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::openCustomDialog ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::decreaseSize ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::increaseSize ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::showCounters ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::openSettingsDialog ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::OnHelp ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow_B::OnAbout ) );
	status_bar_->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	main_panel_->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	upper_panel_->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( MainWindow_B::OnUpperPanelEnter ), NULL, this );
	upper_panel_->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	upper_panel_->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( MainWindow_B::OnUpperPanelLeave ), NULL, this );
	upper_panel_->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( MainWindow_B::OnUpperPanelLeftDown ), NULL, this );
	upper_panel_->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( MainWindow_B::OnUpperPanelLeftUp ), NULL, this );
	upper_panel_->Disconnect( wxEVT_MOTION, wxMouseEventHandler( MainWindow_B::OnUpperPanelEnter ), NULL, this );
	mines_display_panel_->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	mines_digit_100_->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	mines_digit_10_->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	mines_digit_1_->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	smiley_button_->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	time_display_panel_->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	time_digit_100_->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	time_digit_10_->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	time_digit_1_->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	board_panel_->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainWindow_B::keyDown ), NULL, this );
	
}
