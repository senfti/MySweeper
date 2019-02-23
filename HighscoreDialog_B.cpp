///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "HighscoreDialog_B.h"

///////////////////////////////////////////////////////////////////////////

HighscoreDialog_B::HighscoreDialog_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* main_sizer_;
	main_sizer_ = new wxBoxSizer( wxVERTICAL );
	
	notebook_ = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	highscores_page_ = new wxPanel( notebook_, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	highscore_grid_ = new wxGrid( highscores_page_, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	highscore_grid_->CreateGrid( 11, 4 );
	highscore_grid_->EnableEditing( false );
	highscore_grid_->EnableGridLines( true );
	highscore_grid_->SetGridLineColour( wxColour( 0, 0, 0 ) );
	highscore_grid_->EnableDragGridSize( false );
	highscore_grid_->SetMargins( 0, 0 );
	
	// Columns
	highscore_grid_->AutoSizeColumns();
	highscore_grid_->EnableDragColMove( false );
	highscore_grid_->EnableDragColSize( false );
	highscore_grid_->SetColLabelSize( 20 );
	highscore_grid_->SetColLabelValue( 0, wxT("Time") );
	highscore_grid_->SetColLabelValue( 1, wxT("3BV") );
	highscore_grid_->SetColLabelValue( 2, wxT(" 3BV/s") );
	highscore_grid_->SetColLabelValue( 3, wxT("Date") );
	highscore_grid_->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	highscore_grid_->AutoSizeRows();
	highscore_grid_->EnableDragRowSize( false );
	highscore_grid_->SetRowLabelSize( 150 );
	highscore_grid_->SetRowLabelValue( 0, wxT("Time Highscores") );
	highscore_grid_->SetRowLabelValue( 1, wxT("Beginner") );
	highscore_grid_->SetRowLabelValue( 2, wxT("Intermediate") );
	highscore_grid_->SetRowLabelValue( 3, wxT("Expert") );
	highscore_grid_->SetRowLabelValue( 4, wxT("Sum") );
	highscore_grid_->SetRowLabelValue( 5, wxT(" ") );
	highscore_grid_->SetRowLabelValue( 6, wxT("3BV/s Highscores") );
	highscore_grid_->SetRowLabelValue( 7, wxT("Beginner") );
	highscore_grid_->SetRowLabelValue( 8, wxT("Intermediate") );
	highscore_grid_->SetRowLabelValue( 9, wxT("Expert") );
	highscore_grid_->SetRowLabelValue( 10, wxT("Sum") );
	highscore_grid_->SetRowLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	
	// Label Appearance
	highscore_grid_->SetLabelBackgroundColour( wxColour( 208, 208, 208 ) );
	highscore_grid_->SetLabelTextColour( wxColour( 0, 0, 0 ) );
	
	// Cell Defaults
	highscore_grid_->SetDefaultCellBackgroundColour( wxColour( 240, 240, 240 ) );
	highscore_grid_->SetDefaultCellTextColour( wxColour( 0, 0, 0 ) );
	highscore_grid_->SetDefaultCellAlignment( wxALIGN_RIGHT, wxALIGN_CENTRE );
	bSizer3->Add( highscore_grid_, 0, wxALL, 5 );
	
	
	highscores_page_->SetSizer( bSizer3 );
	highscores_page_->Layout();
	bSizer3->Fit( highscores_page_ );
	notebook_->AddPage( highscores_page_, wxT("Highscores"), true );
	non_flagging_page_ = new wxPanel( notebook_, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxVERTICAL );
	
	non_flagging_grid_ = new wxGrid( non_flagging_page_, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	non_flagging_grid_->CreateGrid( 11, 4 );
	non_flagging_grid_->EnableEditing( false );
	non_flagging_grid_->EnableGridLines( true );
	non_flagging_grid_->SetGridLineColour( wxColour( 0, 0, 0 ) );
	non_flagging_grid_->EnableDragGridSize( false );
	non_flagging_grid_->SetMargins( 0, 0 );
	
	// Columns
	non_flagging_grid_->AutoSizeColumns();
	non_flagging_grid_->EnableDragColMove( false );
	non_flagging_grid_->EnableDragColSize( false );
	non_flagging_grid_->SetColLabelSize( 20 );
	non_flagging_grid_->SetColLabelValue( 0, wxT("Time") );
	non_flagging_grid_->SetColLabelValue( 1, wxT("3BV") );
	non_flagging_grid_->SetColLabelValue( 2, wxT(" 3BV/s") );
	non_flagging_grid_->SetColLabelValue( 3, wxT("Date") );
	non_flagging_grid_->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	non_flagging_grid_->AutoSizeRows();
	non_flagging_grid_->EnableDragRowSize( false );
	non_flagging_grid_->SetRowLabelSize( 150 );
	non_flagging_grid_->SetRowLabelValue( 0, wxT("Time Highscores") );
	non_flagging_grid_->SetRowLabelValue( 1, wxT("Beginner") );
	non_flagging_grid_->SetRowLabelValue( 2, wxT("Intermediate") );
	non_flagging_grid_->SetRowLabelValue( 3, wxT("Expert") );
	non_flagging_grid_->SetRowLabelValue( 4, wxT("Sum") );
	non_flagging_grid_->SetRowLabelValue( 5, wxT(" ") );
	non_flagging_grid_->SetRowLabelValue( 6, wxT("3BV/s Highscores") );
	non_flagging_grid_->SetRowLabelValue( 7, wxT("Beginner") );
	non_flagging_grid_->SetRowLabelValue( 8, wxT("Intermediate") );
	non_flagging_grid_->SetRowLabelValue( 9, wxT("Expert") );
	non_flagging_grid_->SetRowLabelValue( 10, wxT("Sum") );
	non_flagging_grid_->SetRowLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	
	// Label Appearance
	non_flagging_grid_->SetLabelBackgroundColour( wxColour( 208, 208, 208 ) );
	non_flagging_grid_->SetLabelTextColour( wxColour( 0, 0, 0 ) );
	
	// Cell Defaults
	non_flagging_grid_->SetDefaultCellBackgroundColour( wxColour( 240, 240, 240 ) );
	non_flagging_grid_->SetDefaultCellTextColour( wxColour( 0, 0, 0 ) );
	non_flagging_grid_->SetDefaultCellAlignment( wxALIGN_RIGHT, wxALIGN_CENTRE );
	bSizer31->Add( non_flagging_grid_, 0, wxALL, 5 );
	
	
	non_flagging_page_->SetSizer( bSizer31 );
	non_flagging_page_->Layout();
	bSizer31->Fit( non_flagging_page_ );
	notebook_->AddPage( non_flagging_page_, wxT("Non-Flagging"), false );
	flagging_page_ = new wxPanel( notebook_, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer311;
	bSizer311 = new wxBoxSizer( wxVERTICAL );
	
	flagging_grid_ = new wxGrid( flagging_page_, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	flagging_grid_->CreateGrid( 11, 4 );
	flagging_grid_->EnableEditing( false );
	flagging_grid_->EnableGridLines( true );
	flagging_grid_->SetGridLineColour( wxColour( 0, 0, 0 ) );
	flagging_grid_->EnableDragGridSize( false );
	flagging_grid_->SetMargins( 0, 0 );
	
	// Columns
	flagging_grid_->AutoSizeColumns();
	flagging_grid_->EnableDragColMove( false );
	flagging_grid_->EnableDragColSize( false );
	flagging_grid_->SetColLabelSize( 20 );
	flagging_grid_->SetColLabelValue( 0, wxT("Time") );
	flagging_grid_->SetColLabelValue( 1, wxT("3BV") );
	flagging_grid_->SetColLabelValue( 2, wxT(" 3BV/s") );
	flagging_grid_->SetColLabelValue( 3, wxT("Date") );
	flagging_grid_->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	flagging_grid_->AutoSizeRows();
	flagging_grid_->EnableDragRowSize( false );
	flagging_grid_->SetRowLabelSize( 150 );
	flagging_grid_->SetRowLabelValue( 0, wxT("Time Highscores") );
	flagging_grid_->SetRowLabelValue( 1, wxT("Beginner") );
	flagging_grid_->SetRowLabelValue( 2, wxT("Intermediate") );
	flagging_grid_->SetRowLabelValue( 3, wxT("Expert") );
	flagging_grid_->SetRowLabelValue( 4, wxT("Sum") );
	flagging_grid_->SetRowLabelValue( 5, wxT(" ") );
	flagging_grid_->SetRowLabelValue( 6, wxT("3BV/s Highscores") );
	flagging_grid_->SetRowLabelValue( 7, wxT("Beginner") );
	flagging_grid_->SetRowLabelValue( 8, wxT("Intermediate") );
	flagging_grid_->SetRowLabelValue( 9, wxT("Expert") );
	flagging_grid_->SetRowLabelValue( 10, wxT("Sum") );
	flagging_grid_->SetRowLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	
	// Label Appearance
	flagging_grid_->SetLabelBackgroundColour( wxColour( 208, 208, 208 ) );
	flagging_grid_->SetLabelTextColour( wxColour( 0, 0, 0 ) );
	
	// Cell Defaults
	flagging_grid_->SetDefaultCellBackgroundColour( wxColour( 240, 240, 240 ) );
	flagging_grid_->SetDefaultCellTextColour( wxColour( 0, 0, 0 ) );
	flagging_grid_->SetDefaultCellAlignment( wxALIGN_RIGHT, wxALIGN_CENTRE );
	bSizer311->Add( flagging_grid_, 0, wxALL, 5 );
	
	
	flagging_page_->SetSizer( bSizer311 );
	flagging_page_->Layout();
	bSizer311->Fit( flagging_page_ );
	notebook_->AddPage( flagging_page_, wxT("Flagging"), false );
	custom_page_ = new wxPanel( notebook_, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3111;
	bSizer3111 = new wxBoxSizer( wxVERTICAL );
	
	custom_grid_ = new wxGrid( custom_page_, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	custom_grid_->CreateGrid( 6, 4 );
	custom_grid_->EnableEditing( false );
	custom_grid_->EnableGridLines( true );
	custom_grid_->SetGridLineColour( wxColour( 0, 0, 0 ) );
	custom_grid_->EnableDragGridSize( false );
	custom_grid_->SetMargins( 0, 0 );
	
	// Columns
	custom_grid_->AutoSizeColumns();
	custom_grid_->EnableDragColMove( false );
	custom_grid_->EnableDragColSize( false );
	custom_grid_->SetColLabelSize( 20 );
	custom_grid_->SetColLabelValue( 0, wxT("Mines") );
	custom_grid_->SetColLabelValue( 1, wxT("Time") );
	custom_grid_->SetColLabelValue( 2, wxT("3BV") );
	custom_grid_->SetColLabelValue( 3, wxT("Date") );
	custom_grid_->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	custom_grid_->AutoSizeRows();
	custom_grid_->EnableDragRowSize( false );
	custom_grid_->SetRowLabelSize( 150 );
	custom_grid_->SetRowLabelValue( 0, wxT("8x8") );
	custom_grid_->SetRowLabelValue( 1, wxT("9x9") );
	custom_grid_->SetRowLabelValue( 2, wxT("16x16") );
	custom_grid_->SetRowLabelValue( 3, wxT("30x16") );
	custom_grid_->SetRowLabelValue( 4, wxT("30x24") );
	custom_grid_->SetRowLabelValue( 5, wxT("Sum") );
	custom_grid_->SetRowLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	
	// Label Appearance
	custom_grid_->SetLabelBackgroundColour( wxColour( 208, 208, 208 ) );
	custom_grid_->SetLabelTextColour( wxColour( 0, 0, 0 ) );
	
	// Cell Defaults
	custom_grid_->SetDefaultCellBackgroundColour( wxColour( 240, 240, 240 ) );
	custom_grid_->SetDefaultCellTextColour( wxColour( 0, 0, 0 ) );
	custom_grid_->SetDefaultCellAlignment( wxALIGN_RIGHT, wxALIGN_CENTRE );
	bSizer3111->Add( custom_grid_, 0, wxALL|wxEXPAND, 5 );
	
	size_grid_ = new wxGrid( custom_page_, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	size_grid_->CreateGrid( 1, 4 );
	size_grid_->EnableEditing( false );
	size_grid_->EnableGridLines( true );
	size_grid_->SetGridLineColour( wxColour( 0, 0, 0 ) );
	size_grid_->EnableDragGridSize( false );
	size_grid_->SetMargins( 0, 0 );
	
	// Columns
	size_grid_->AutoSizeColumns();
	size_grid_->EnableDragColMove( false );
	size_grid_->EnableDragColSize( false );
	size_grid_->SetColLabelSize( 20 );
	size_grid_->SetColLabelValue( 0, wxT("Size") );
	size_grid_->SetColLabelValue( 1, wxT("Time") );
	size_grid_->SetColLabelValue( 2, wxT("3BV") );
	size_grid_->SetColLabelValue( 3, wxT("Date") );
	size_grid_->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	size_grid_->AutoSizeRows();
	size_grid_->EnableDragRowSize( false );
	size_grid_->SetRowLabelSize( 150 );
	size_grid_->SetRowLabelValue( 0, wxT("Size") );
	size_grid_->SetRowLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	
	// Label Appearance
	size_grid_->SetLabelBackgroundColour( wxColour( 208, 208, 208 ) );
	size_grid_->SetLabelTextColour( wxColour( 0, 0, 0 ) );
	
	// Cell Defaults
	size_grid_->SetDefaultCellBackgroundColour( wxColour( 240, 240, 240 ) );
	size_grid_->SetDefaultCellTextColour( wxColour( 0, 0, 0 ) );
	size_grid_->SetDefaultCellAlignment( wxALIGN_RIGHT, wxALIGN_CENTRE );
	size_grid_->SetToolTip( wxT("Biggest board (measured in squares) soved with expert density (20.625% rounded up)") );
	
	bSizer3111->Add( size_grid_, 0, wxALL|wxEXPAND, 5 );
	
	
	custom_page_->SetSizer( bSizer3111 );
	custom_page_->Layout();
	bSizer3111->Fit( custom_page_ );
	notebook_->AddPage( custom_page_, wxT("Custom"), false );
	
	main_sizer_->Add( notebook_, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* control_sizer_;
	control_sizer_ = new wxBoxSizer( wxHORIZONTAL );
	
	
	control_sizer_->Add( 0, 0, 1, wxEXPAND, 5 );
	
	ok_button_ = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	ok_button_->SetDefault(); 
	control_sizer_->Add( ok_button_, 0, wxALL, 5 );
	
	
	main_sizer_->Add( control_sizer_, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( main_sizer_ );
	this->Layout();
	main_sizer_->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	ok_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( HighscoreDialog_B::OnOk ), NULL, this );
}

HighscoreDialog_B::~HighscoreDialog_B()
{
	// Disconnect Events
	ok_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( HighscoreDialog_B::OnOk ), NULL, this );
	
}
