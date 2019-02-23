///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Counter_B.h"

///////////////////////////////////////////////////////////////////////////

Counters_B::Counters_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetForegroundColour( wxColour( 208, 208, 208 ) );
	this->SetBackgroundColour( wxColour( 208, 208, 208 ) );
	
	main_sizer_ = new wxBoxSizer( wxVERTICAL );
	
	counters_grid_ = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER );
	
	// Grid
	counters_grid_->CreateGrid( 19, 2 );
	counters_grid_->EnableEditing( false );
	counters_grid_->EnableGridLines( true );
	counters_grid_->SetGridLineColour( wxColour( 0, 0, 0 ) );
	counters_grid_->EnableDragGridSize( false );
	counters_grid_->SetMargins( 0, 0 );
	
	// Columns
	counters_grid_->EnableDragColMove( false );
	counters_grid_->EnableDragColSize( false );
	counters_grid_->SetColLabelSize( 0 );
	counters_grid_->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	counters_grid_->EnableDragRowSize( false );
	counters_grid_->SetRowLabelSize( 0 );
	counters_grid_->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	counters_grid_->SetDefaultCellBackgroundColour( wxColour( 208, 208, 208 ) );
	counters_grid_->SetDefaultCellTextColour( wxColour( 0, 0, 0 ) );
	counters_grid_->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	counters_grid_->SetForegroundColour( wxColour( 208, 208, 208 ) );
	counters_grid_->SetBackgroundColour( wxColour( 208, 208, 208 ) );
	
	main_sizer_->Add( counters_grid_, 0, 0, 0 );
	
	
	this->SetSizer( main_sizer_ );
	this->Layout();
	main_sizer_->Fit( this );
}

Counters_B::~Counters_B()
{
}
