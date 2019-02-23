///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "HelpDialog_B.h"

///////////////////////////////////////////////////////////////////////////

HelpDialog_B::HelpDialog_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Rules"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	m_staticText2->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer1->Add( m_staticText2, 0, wxALL, 10 );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	fgSizer1->Add( m_staticText5, 0, wxLEFT, 15 );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Uncover a mine, and the game ends"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer1->Add( m_staticText6, 0, wxLEFT, 5 );
	
	m_staticText51 = new wxStaticText( this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	fgSizer1->Add( m_staticText51, 0, wxLEFT, 15 );
	
	m_staticText61 = new wxStaticText( this, wxID_ANY, wxT("Uncover an empty square, and you keep playing."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText61->Wrap( -1 );
	fgSizer1->Add( m_staticText61, 0, wxLEFT, 5 );
	
	m_staticText52 = new wxStaticText( this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText52->Wrap( -1 );
	fgSizer1->Add( m_staticText52, 0, wxLEFT, 15 );
	
	m_staticText62 = new wxStaticText( this, wxID_ANY, wxT("Uncover a number, and it tells you how many mines lay hidden in the eight surrounding squares."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText62->Wrap( 400 );
	fgSizer1->Add( m_staticText62, 0, wxLEFT, 5 );
	
	
	bSizer1->Add( fgSizer1, 0, wxEXPAND|wxRIGHT, 10 );
	
	
	bSizer1->Add( 0, 10, 0, wxEXPAND, 5 );
	
	m_staticText21 = new wxStaticText( this, wxID_ANY, wxT("Usage"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	m_staticText21->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer1->Add( m_staticText21, 0, wxALL, 10 );
	
	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText53 = new wxStaticText( this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText53->Wrap( -1 );
	fgSizer11->Add( m_staticText53, 0, wxLEFT, 15 );
	
	m_staticText63 = new wxStaticText( this, wxID_ANY, wxT("Left mouse button: Uncover a square"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText63->Wrap( -1 );
	fgSizer11->Add( m_staticText63, 0, wxLEFT, 5 );
	
	m_staticText511 = new wxStaticText( this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText511->Wrap( -1 );
	fgSizer11->Add( m_staticText511, 0, wxLEFT, 15 );
	
	m_staticText611 = new wxStaticText( this, wxID_ANY, wxT("Right mouse button: Set a flag"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText611->Wrap( -1 );
	fgSizer11->Add( m_staticText611, 0, wxLEFT, 5 );
	
	m_staticText521 = new wxStaticText( this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText521->Wrap( -1 );
	fgSizer11->Add( m_staticText521, 0, wxLEFT, 15 );
	
	m_staticText621 = new wxStaticText( this, wxID_ANY, wxT("Left and right mouse buttons on an uncoverd square with all surrounding mines flagged: Uncover all surrounding squares which are not flagged. "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText621->Wrap( 400 );
	fgSizer11->Add( m_staticText621, 0, wxLEFT, 5 );
	
	m_staticText5211 = new wxStaticText( this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5211->Wrap( -1 );
	fgSizer11->Add( m_staticText5211, 0, wxLEFT, 15 );
	
	m_staticText6211 = new wxStaticText( this, wxID_ANY, wxT("Middle mouse button in scroll mode: move the board, also pressing \"Ctrl\" or the equivalent key on your system increases speed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6211->Wrap( 400 );
	fgSizer11->Add( m_staticText6211, 0, wxLEFT, 5 );
	
	
	bSizer1->Add( fgSizer11, 0, wxEXPAND|wxRIGHT, 10 );
	
	
	bSizer1->Add( 0, 10, 1, wxEXPAND, 5 );
	
	m_staticText211 = new wxStaticText( this, wxID_ANY, wxT("Community and Rankings"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText211->Wrap( -1 );
	m_staticText211->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer1->Add( m_staticText211, 0, wxALL, 10 );
	
	m_hyperlink1 = new wxHyperlinkCtrl( this, wxID_ANY, wxT("www.minesweeper.info"), wxT("http://www.minesweeper.info/"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer1->Add( m_hyperlink1, 0, wxLEFT, 20 );
	
	
	bSizer1->Add( 0, 10, 1, wxEXPAND, 5 );
	
	m_staticText2111 = new wxStaticText( this, wxID_ANY, wxT("Support"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2111->Wrap( -1 );
	m_staticText2111->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer1->Add( m_staticText2111, 0, wxALL, 10 );
	
	help_label_1 = new wxStaticText( this, wxID_ANY, wxT("Please report bugs to \"thomassenfter@gmx.at\""), wxDefaultPosition, wxDefaultSize, 0 );
	help_label_1->Wrap( 400 );
	bSizer1->Add( help_label_1, 0, wxLEFT, 20 );
	
	
	bSizer1->Add( 0, 16, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	ok_button_ = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	ok_button_->SetDefault(); 
	bSizer1->Add( ok_button_, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	ok_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( HelpDialog_B::ok ), NULL, this );
}

HelpDialog_B::~HelpDialog_B()
{
	// Disconnect Events
	ok_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( HelpDialog_B::ok ), NULL, this );
	
}
