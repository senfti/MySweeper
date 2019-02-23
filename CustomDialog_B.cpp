///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "CustomDialog_B.h"

///////////////////////////////////////////////////////////////////////////

CustomDialog_B::CustomDialog_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* main_sizer_;
	main_sizer_ = new wxBoxSizer( wxVERTICAL );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	main_sizer_->Add( m_staticline1, 0, wxEXPAND, 5 );
	
	wxBoxSizer* upper_sizer_;
	upper_sizer_ = new wxBoxSizer( wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	width_label_ = new wxStaticText( this, wxID_ANY, wxT("Width:"), wxPoint( -1,-1 ), wxSize( -1,-1 ), 0 );
	width_label_->Wrap( -1 );
	fgSizer1->Add( width_label_, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5 );
	
	width_edit_ = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), wxSP_ARROW_KEYS, 8, 10000, 30 );
	width_edit_->SetForegroundColour( wxColour( 0, 0, 0 ) );
	width_edit_->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	fgSizer1->Add( width_edit_, 0, wxALL, 5 );
	
	heght_label_ = new wxStaticText( this, wxID_ANY, wxT("Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	heght_label_->Wrap( -1 );
	fgSizer1->Add( heght_label_, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5 );
	
	height_edit_ = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), wxSP_ARROW_KEYS, 8, 10000, 16 );
	height_edit_->SetForegroundColour( wxColour( 0, 0, 0 ) );
	height_edit_->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	fgSizer1->Add( height_edit_, 0, wxALL, 5 );
	
	mines_label_ = new wxStaticText( this, wxID_ANY, wxT("Mines:"), wxDefaultPosition, wxDefaultSize, 0 );
	mines_label_->Wrap( -1 );
	fgSizer1->Add( mines_label_, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5 );
	
	mines_edit_ = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), wxSP_ARROW_KEYS, 1, 99999999, 99 );
	mines_edit_->SetForegroundColour( wxColour( 0, 0, 0 ) );
	mines_edit_->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	fgSizer1->Add( mines_edit_, 0, wxALL, 5 );
	
	
	upper_sizer_->Add( fgSizer1, 1, wxEXPAND, 5 );
	
	m_staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	upper_sizer_->Add( m_staticline3, 0, wxEXPAND|wxLEFT|wxRIGHT, 15 );
	
	wxBoxSizer* additional_option_sizer_;
	additional_option_sizer_ = new wxBoxSizer( wxVERTICAL );
	
	size_text_ = new wxStaticText( this, wxID_ANY, wxT("Set to special size"), wxDefaultPosition, wxDefaultSize, 0 );
	size_text_->Wrap( -1 );
	additional_option_sizer_->Add( size_text_, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	wxString size_choice_Choices[] = { wxT("8x8"), wxT("9x9"), wxT("16x16"), wxT("30x16"), wxT("30x24") };
	int size_choice_NChoices = sizeof( size_choice_Choices ) / sizeof( wxString );
	size_choice_ = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, size_choice_NChoices, size_choice_Choices, 0 );
	size_choice_->SetSelection( 3 );
	size_choice_->SetForegroundColour( wxColour( 0, 0, 0 ) );
	size_choice_->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	additional_option_sizer_->Add( size_choice_, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );
	
	
	additional_option_sizer_->Add( 0, 0, 1, wxEXPAND, 5 );
	
	expert_density_checkbox_ = new wxCheckBox( this, wxID_ANY, wxT("Expert Density"), wxDefaultPosition, wxDefaultSize, 0 );
	expert_density_checkbox_->SetToolTip( wxT("Keeps mines density at expert density (20.625% rounded up)") );
	
	additional_option_sizer_->Add( expert_density_checkbox_, 0, wxALL, 5 );
	
	
	upper_sizer_->Add( additional_option_sizer_, 1, wxEXPAND, 5 );
	
	
	main_sizer_->Add( upper_sizer_, 1, wxEXPAND, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	main_sizer_->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* controls_sizer_;
	controls_sizer_ = new wxBoxSizer( wxHORIZONTAL );
	
	cancel_button_ = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	controls_sizer_->Add( cancel_button_, 0, wxALL, 5 );
	
	
	controls_sizer_->Add( 0, 0, 1, wxEXPAND, 5 );
	
	ok_button_ = new wxButton( this, wxID_ANY, wxT("OK"), wxPoint( -1,-1 ), wxSize( -1,-1 ), 0 );
	ok_button_->SetDefault(); 
	controls_sizer_->Add( ok_button_, 0, wxALL, 5 );
	
	
	main_sizer_->Add( controls_sizer_, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( main_sizer_ );
	this->Layout();
	main_sizer_->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	width_edit_->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CustomDialog_B::OnChangeSize ), NULL, this );
	width_edit_->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( CustomDialog_B::OnChangeSize ), NULL, this );
	height_edit_->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CustomDialog_B::OnChangeSize ), NULL, this );
	height_edit_->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( CustomDialog_B::OnChangeSize ), NULL, this );
	size_choice_->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( CustomDialog_B::OnSizeChoice ), NULL, this );
	expert_density_checkbox_->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( CustomDialog_B::OnExpertDensityCheckbox ), NULL, this );
	cancel_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CustomDialog_B::cancel ), NULL, this );
	ok_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CustomDialog_B::apply ), NULL, this );
}

CustomDialog_B::~CustomDialog_B()
{
	// Disconnect Events
	width_edit_->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CustomDialog_B::OnChangeSize ), NULL, this );
	width_edit_->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( CustomDialog_B::OnChangeSize ), NULL, this );
	height_edit_->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CustomDialog_B::OnChangeSize ), NULL, this );
	height_edit_->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( CustomDialog_B::OnChangeSize ), NULL, this );
	size_choice_->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( CustomDialog_B::OnSizeChoice ), NULL, this );
	expert_density_checkbox_->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( CustomDialog_B::OnExpertDensityCheckbox ), NULL, this );
	cancel_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CustomDialog_B::cancel ), NULL, this );
	ok_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CustomDialog_B::apply ), NULL, this );
	
}
