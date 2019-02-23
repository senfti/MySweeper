///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "HistoryDialog_B.h"

///////////////////////////////////////////////////////////////////////////

HistoryDialog_B::HistoryDialog_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 100,100 ), wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxString style_radio_box_Choices[] = { wxT("Beg"), wxT("Int"), wxT("Exp") };
	int style_radio_box_NChoices = sizeof( style_radio_box_Choices ) / sizeof( wxString );
	style_radio_box_ = new wxRadioBox( this, wxID_ANY, wxT("Style"), wxDefaultPosition, wxDefaultSize, style_radio_box_NChoices, style_radio_box_Choices, 3, wxRA_SPECIFY_COLS );
	style_radio_box_->SetSelection( 0 );
	bSizer1->Add( style_radio_box_, 0, wxALL|wxEXPAND, 5 );
	
	history_grid_ = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	history_grid_->CreateGrid( 1, 18 );
	history_grid_->EnableEditing( false );
	history_grid_->EnableGridLines( true );
	history_grid_->EnableDragGridSize( false );
	history_grid_->SetMargins( 0, 0 );
	
	// Columns
	history_grid_->AutoSizeColumns();
	history_grid_->EnableDragColMove( false );
	history_grid_->EnableDragColSize( false );
	history_grid_->SetColLabelSize( 30 );
	history_grid_->SetColLabelValue( 0, wxT("Time") );
	history_grid_->SetColLabelValue( 1, wxT("3BV") );
	history_grid_->SetColLabelValue( 2, wxT("3BV/s") );
	history_grid_->SetColLabelValue( 3, wxT("ZiNi") );
	history_grid_->SetColLabelValue( 4, wxT("ZiNi/s") );
	history_grid_->SetColLabelValue( 5, wxT("HZiNi") );
	history_grid_->SetColLabelValue( 6, wxT("HZiNi/s") );
	history_grid_->SetColLabelValue( 7, wxT("IOE") );
	history_grid_->SetColLabelValue( 8, wxT("RQP") );
	history_grid_->SetColLabelValue( 9, wxT("IOS") );
	history_grid_->SetColLabelValue( 10, wxT("Clicks") );
	history_grid_->SetColLabelValue( 11, wxT("L-Clicks") );
	history_grid_->SetColLabelValue( 12, wxT("R-Clicks") );
	history_grid_->SetColLabelValue( 13, wxT("Chords") );
	history_grid_->SetColLabelValue( 14, wxT("Clicks/s") );
	history_grid_->SetColLabelValue( 15, wxT("Path [squares]") );
	history_grid_->SetColLabelValue( 16, wxT("Path [pixel]") );
	history_grid_->SetColLabelValue( 17, wxT("Date") );
	history_grid_->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	history_grid_->AutoSizeRows();
	history_grid_->EnableDragRowSize( false );
	history_grid_->SetRowLabelSize( 0 );
	history_grid_->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	history_grid_->SetDefaultCellAlignment( wxALIGN_RIGHT, wxALIGN_CENTRE );
	bSizer1->Add( history_grid_, 1, wxALL|wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	ok_button_ = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	ok_button_->SetDefault(); 
	bSizer2->Add( ok_button_, 0, wxALL, 5 );
	
	
	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	style_radio_box_->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( HistoryDialog_B::ChangeStyle ), NULL, this );
	history_grid_->Connect( wxEVT_GRID_LABEL_LEFT_CLICK, wxGridEventHandler( HistoryDialog_B::sort ), NULL, this );
	history_grid_->Connect( wxEVT_GRID_LABEL_LEFT_DCLICK, wxGridEventHandler( HistoryDialog_B::sort ), NULL, this );
	ok_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( HistoryDialog_B::Close ), NULL, this );
}

HistoryDialog_B::~HistoryDialog_B()
{
	// Disconnect Events
	style_radio_box_->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( HistoryDialog_B::ChangeStyle ), NULL, this );
	history_grid_->Disconnect( wxEVT_GRID_LABEL_LEFT_CLICK, wxGridEventHandler( HistoryDialog_B::sort ), NULL, this );
	history_grid_->Disconnect( wxEVT_GRID_LABEL_LEFT_DCLICK, wxGridEventHandler( HistoryDialog_B::sort ), NULL, this );
	ok_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( HistoryDialog_B::Close ), NULL, this );
	
}
