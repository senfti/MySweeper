///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "VideoPlayerDialog_B.h"

///////////////////////////////////////////////////////////////////////////

VideoPlayerDialog_B::VideoPlayerDialog_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	main_sizer_ = new wxBoxSizer( wxVERTICAL );
	
	controls_sizer_ = new wxBoxSizer( wxHORIZONTAL );
	
	play_button_ = new wxBitmapButton( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 26,26 ), wxBU_AUTODRAW );
	play_button_->SetDefault(); 
	controls_sizer_->Add( play_button_, 0, wxALL, 5 );
	
	pause_button_ = new wxBitmapButton( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 26,26 ), wxBU_AUTODRAW );
	controls_sizer_->Add( pause_button_, 0, wxALL, 5 );
	
	stop_button_ = new wxBitmapButton( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 26,26 ), wxBU_AUTODRAW );
	controls_sizer_->Add( stop_button_, 0, wxALL, 5 );
	
	speed_slider_ = new wxSlider( this, wxID_ANY, 10, 0, 20, wxDefaultPosition, wxSize( 100,24 ), wxSL_BOTH|wxSL_HORIZONTAL );
	controls_sizer_->Add( speed_slider_, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxLEFT|wxTOP, 5 );
	
	speed_text_ = new wxStaticText( this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxSize( -1,-1 ), wxST_NO_AUTORESIZE );
	speed_text_->Wrap( -1 );
	controls_sizer_->Add( speed_text_, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 32 );
	
	time_slider_ = new wxSlider( this, wxID_ANY, 0, 0, 1000, wxDefaultPosition, wxSize( 400,24 ), wxSL_BOTH|wxSL_HORIZONTAL );
	controls_sizer_->Add( time_slider_, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxLEFT|wxTOP, 5 );
	
	time_text_ = new wxStaticText( this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	time_text_->Wrap( -1 );
	controls_sizer_->Add( time_text_, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 5 );
	
	
	controls_sizer_->Add( 10, 0, 1, wxEXPAND, 5 );
	
	
	main_sizer_->Add( controls_sizer_, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( main_sizer_ );
	this->Layout();
	main_sizer_->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( VideoPlayerDialog_B::OnClose ) );
	play_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( VideoPlayerDialog_B::play ), NULL, this );
	pause_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( VideoPlayerDialog_B::pause ), NULL, this );
	stop_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( VideoPlayerDialog_B::stop ), NULL, this );
	speed_slider_->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( VideoPlayerDialog_B::setSpeed ), NULL, this );
	speed_slider_->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( VideoPlayerDialog_B::setSpeed ), NULL, this );
	speed_slider_->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( VideoPlayerDialog_B::setSpeed ), NULL, this );
	speed_slider_->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( VideoPlayerDialog_B::setSpeed ), NULL, this );
	speed_slider_->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( VideoPlayerDialog_B::setSpeed ), NULL, this );
	speed_slider_->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( VideoPlayerDialog_B::setSpeed ), NULL, this );
	speed_slider_->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( VideoPlayerDialog_B::setSpeed ), NULL, this );
	speed_slider_->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( VideoPlayerDialog_B::setSpeed ), NULL, this );
	speed_slider_->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( VideoPlayerDialog_B::setSpeed ), NULL, this );
	time_slider_->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( VideoPlayerDialog_B::setTime ), NULL, this );
	time_slider_->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( VideoPlayerDialog_B::setTime ), NULL, this );
	time_slider_->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( VideoPlayerDialog_B::setTime ), NULL, this );
	time_slider_->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( VideoPlayerDialog_B::setTime ), NULL, this );
	time_slider_->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( VideoPlayerDialog_B::setTime ), NULL, this );
	time_slider_->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( VideoPlayerDialog_B::setTime ), NULL, this );
	time_slider_->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( VideoPlayerDialog_B::setTime ), NULL, this );
	time_slider_->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( VideoPlayerDialog_B::setTime ), NULL, this );
	time_slider_->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( VideoPlayerDialog_B::setTime ), NULL, this );
}

VideoPlayerDialog_B::~VideoPlayerDialog_B()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( VideoPlayerDialog_B::OnClose ) );
	play_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( VideoPlayerDialog_B::play ), NULL, this );
	pause_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( VideoPlayerDialog_B::pause ), NULL, this );
	stop_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( VideoPlayerDialog_B::stop ), NULL, this );
	speed_slider_->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( VideoPlayerDialog_B::setSpeed ), NULL, this );
	speed_slider_->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( VideoPlayerDialog_B::setSpeed ), NULL, this );
	speed_slider_->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( VideoPlayerDialog_B::setSpeed ), NULL, this );
	speed_slider_->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( VideoPlayerDialog_B::setSpeed ), NULL, this );
	speed_slider_->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( VideoPlayerDialog_B::setSpeed ), NULL, this );
	speed_slider_->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( VideoPlayerDialog_B::setSpeed ), NULL, this );
	speed_slider_->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( VideoPlayerDialog_B::setSpeed ), NULL, this );
	speed_slider_->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( VideoPlayerDialog_B::setSpeed ), NULL, this );
	speed_slider_->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( VideoPlayerDialog_B::setSpeed ), NULL, this );
	time_slider_->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( VideoPlayerDialog_B::setTime ), NULL, this );
	time_slider_->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( VideoPlayerDialog_B::setTime ), NULL, this );
	time_slider_->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( VideoPlayerDialog_B::setTime ), NULL, this );
	time_slider_->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( VideoPlayerDialog_B::setTime ), NULL, this );
	time_slider_->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( VideoPlayerDialog_B::setTime ), NULL, this );
	time_slider_->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( VideoPlayerDialog_B::setTime ), NULL, this );
	time_slider_->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( VideoPlayerDialog_B::setTime ), NULL, this );
	time_slider_->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( VideoPlayerDialog_B::setTime ), NULL, this );
	time_slider_->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( VideoPlayerDialog_B::setTime ), NULL, this );
	
}
