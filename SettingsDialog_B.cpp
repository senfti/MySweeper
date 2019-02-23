///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "SettingsDialog_B.h"

///////////////////////////////////////////////////////////////////////////

SettingsDialog_B::SettingsDialog_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* main_sizer_;
	main_sizer_ = new wxBoxSizer( wxVERTICAL );
	
	notebook_ = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	game_page_ = new wxPanel( notebook_, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer2->Add( 0, 10, 1, wxEXPAND, 5 );
	
	questionmark_checkbox_ = new wxCheckBox( game_page_, wxID_ANY, wxT("Enable question marks"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( questionmark_checkbox_, 0, wxALL, 5 );
	
	m_staticline1 = new wxStaticLine( game_page_, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	restart_spacebar_checkbox_ = new wxCheckBox( game_page_, wxID_ANY, wxT("Restart with spacebar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( restart_spacebar_checkbox_, 0, wxALL, 5 );
	
	restart_m_mouse_checkbox_ = new wxCheckBox( game_page_, wxID_ANY, wxT("Restart with middle mouse"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( restart_m_mouse_checkbox_, 0, wxALL, 5 );
	
	restart_doubleclick_checkbox_ = new wxCheckBox( game_page_, wxID_ANY, wxT("Restart with doubleclick"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( restart_doubleclick_checkbox_, 0, wxALL, 5 );
	
	restart_on_fail_checkbox_ = new wxCheckBox( game_page_, wxID_ANY, wxT("Restart when failed"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( restart_on_fail_checkbox_, 0, wxALL, 5 );
	
	restart_on_upper_panel_checkbox_ = new wxCheckBox( game_page_, wxID_ANY, wxT("Restart when clicking in area beside smiley"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( restart_on_upper_panel_checkbox_, 0, wxALL, 5 );
	
	restart_on_click_after_delay_checkbox_ = new wxCheckBox( game_page_, wxID_ANY, wxT("Restart one second after end of game with any click"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( restart_on_click_after_delay_checkbox_, 0, wxALL, 5 );
	
	m_staticline2 = new wxStaticLine( game_page_, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	update_counters_checkbox_ = new wxCheckBox( game_page_, wxID_ANY, wxT("Update counters while playing"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( update_counters_checkbox_, 0, wxALL, 5 );
	
	hide_counters_until_finished_checkbox_ = new wxCheckBox( game_page_, wxID_ANY, wxT("Only show counters when finished"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( hide_counters_until_finished_checkbox_, 0, wxALL, 5 );
	
	m_staticline3 = new wxStaticLine( game_page_, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText3 = new wxStaticText( game_page_, wxID_ANY, wxT("Your name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer5->Add( m_staticText3, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	name_edit_ = new wxTextCtrl( game_page_, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( name_edit_, 1, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer2->Add( bSizer5, 0, wxEXPAND, 5 );
	
	
	bSizer2->Add( 0, 10, 1, wxEXPAND, 5 );
	
	
	game_page_->SetSizer( bSizer2 );
	game_page_->Layout();
	bSizer2->Fit( game_page_ );
	notebook_->AddPage( game_page_, wxT("Game"), true );
	video_page_ = new wxPanel( notebook_, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxString auto_save_radio_box_Choices[] = { wxT("all games"), wxT("finished games"), wxT("highscores"), wxT("none") };
	int auto_save_radio_box_NChoices = sizeof( auto_save_radio_box_Choices ) / sizeof( wxString );
	auto_save_radio_box_ = new wxRadioBox( video_page_, wxID_ANY, wxT("Video auto save options:"), wxDefaultPosition, wxDefaultSize, auto_save_radio_box_NChoices, auto_save_radio_box_Choices, 1, wxRA_SPECIFY_COLS );
	auto_save_radio_box_->SetSelection( 1 );
	auto_save_radio_box_->SetToolTip( wxT("all games: all games (won and lost) will be saved automatically\nfinished games: just won games will be saved automatically\nhigh scores: just highscores will be saved automatically\nnone: no automatic saving\n") );
	
	bSizer4->Add( auto_save_radio_box_, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText1 = new wxStaticText( video_page_, wxID_ANY, wxT("Default video location:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer4->Add( m_staticText1, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	auto_save_dir_picker_ = new wxDirPickerCtrl( video_page_, wxID_ANY, wxT("/value"), wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL );
	bSizer4->Add( auto_save_dir_picker_, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	m_staticText2 = new wxStaticText( video_page_, wxID_ANY, wxT("Default file name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer4->Add( m_staticText2, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	default_file_name_edit_ = new wxTextCtrl( video_page_, wxID_ANY, wxT("$name_$style_$time.myswv"), wxDefaultPosition, wxDefaultSize, 0 );
	default_file_name_edit_->SetMaxLength( 100 ); 
	default_file_name_edit_->SetToolTip( wxT("how to:\n  \"$name\" : your name\n  \"$style\" : BEG, INT, EXP, CUSTOM\n  \"$time\" : time of the game\n  \"$3bv\" : 3bv of the board\n\n.myswv will be added as extension, if missing") );
	
	bSizer4->Add( default_file_name_edit_, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	
	video_page_->SetSizer( bSizer4 );
	video_page_->Layout();
	bSizer4->Fit( video_page_ );
	notebook_->AddPage( video_page_, wxT("Video"), false );
	miscellaneous_page_ = new wxPanel( notebook_, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	limit_size_checkbox_ = new wxCheckBox( miscellaneous_page_, wxID_ANY, wxT("Limit window size"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( limit_size_checkbox_, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText4 = new wxStaticText( miscellaneous_page_, wxID_ANY, wxT("Max. width"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer7->Add( m_staticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	max_width_edit_ = new wxSpinCtrl( miscellaneous_page_, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), wxSP_ARROW_KEYS, 600, 10000, 1000 );
	max_width_edit_->Enable( false );
	
	bSizer7->Add( max_width_edit_, 0, wxALL, 5 );
	
	m_staticText5 = new wxStaticText( miscellaneous_page_, wxID_ANY, wxT("Max. height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer7->Add( m_staticText5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	max_height_edit_ = new wxSpinCtrl( miscellaneous_page_, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), wxSP_ARROW_KEYS, 500, 10000, 800 );
	max_height_edit_->Enable( false );
	
	bSizer7->Add( max_height_edit_, 0, wxALL, 5 );
	
	
	bSizer6->Add( bSizer7, 0, wxEXPAND, 5 );
	
	m_staticline4 = new wxStaticLine( miscellaneous_page_, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer6->Add( m_staticline4, 0, wxEXPAND | wxALL, 5 );
	
	no_zini_checkbox_ = new wxCheckBox( miscellaneous_page_, wxID_ANY, wxT("No ZiNi calculation on big custom boards"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( no_zini_checkbox_, 0, wxALL, 5 );
	
	m_staticline5 = new wxStaticLine( miscellaneous_page_, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer6->Add( m_staticline5, 0, wxEXPAND | wxALL, 5 );
	
	wxString counters_size_radiobox_Choices[] = { wxT("Show all stats"), wxT("Minimal counters") };
	int counters_size_radiobox_NChoices = sizeof( counters_size_radiobox_Choices ) / sizeof( wxString );
	counters_size_radiobox_ = new wxRadioBox( miscellaneous_page_, wxID_ANY, wxT("Counters:"), wxDefaultPosition, wxDefaultSize, counters_size_radiobox_NChoices, counters_size_radiobox_Choices, 1, wxRA_SPECIFY_ROWS );
	counters_size_radiobox_->SetSelection( 0 );
	bSizer6->Add( counters_size_radiobox_, 0, wxALL, 5 );
	
	
	miscellaneous_page_->SetSizer( bSizer6 );
	miscellaneous_page_->Layout();
	bSizer6->Fit( miscellaneous_page_ );
	notebook_->AddPage( miscellaneous_page_, wxT("Miscellaneous"), false );
	
	main_sizer_->Add( notebook_, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	cancel_button_ = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( cancel_button_, 0, wxALL, 5 );
	
	
	bSizer3->Add( 20, 0, 0, wxEXPAND, 5 );
	
	default_button_ = new wxButton( this, wxID_ANY, wxT("Default"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( default_button_, 0, wxALL, 5 );
	
	
	bSizer3->Add( 10, 0, 0, wxEXPAND, 5 );
	
	apply_button_ = new wxButton( this, wxID_ANY, wxT("Apply"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( apply_button_, 0, wxALL, 5 );
	
	
	bSizer3->Add( 20, 0, 0, wxEXPAND, 5 );
	
	ok_button_ = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	ok_button_->SetDefault(); 
	bSizer3->Add( ok_button_, 0, wxALL, 5 );
	
	
	main_sizer_->Add( bSizer3, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( main_sizer_ );
	this->Layout();
	main_sizer_->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	name_edit_->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SettingsDialog_B::OnNameText ), NULL, this );
	default_file_name_edit_->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SettingsDialog_B::OnFileText ), NULL, this );
	limit_size_checkbox_->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SettingsDialog_B::EnableWindowLimits ), NULL, this );
	cancel_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog_B::cancel ), NULL, this );
	default_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog_B::setDefault ), NULL, this );
	apply_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog_B::apply ), NULL, this );
	ok_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog_B::ok ), NULL, this );
}

SettingsDialog_B::~SettingsDialog_B()
{
	// Disconnect Events
	name_edit_->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SettingsDialog_B::OnNameText ), NULL, this );
	default_file_name_edit_->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SettingsDialog_B::OnFileText ), NULL, this );
	limit_size_checkbox_->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SettingsDialog_B::EnableWindowLimits ), NULL, this );
	cancel_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog_B::cancel ), NULL, this );
	default_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog_B::setDefault ), NULL, this );
	apply_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog_B::apply ), NULL, this );
	ok_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog_B::ok ), NULL, this );
	
}
