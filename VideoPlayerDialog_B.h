///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __VIDEOPLAYERDIALOG_B_H__
#define __VIDEOPLAYERDIALOG_B_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/bmpbuttn.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/slider.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class VideoPlayerDialog_B
///////////////////////////////////////////////////////////////////////////////
class VideoPlayerDialog_B : public wxDialog 
{
	private:
	
	protected:
		wxBoxSizer* main_sizer_;
		wxBoxSizer* controls_sizer_;
		wxBitmapButton* play_button_;
		wxBitmapButton* pause_button_;
		wxBitmapButton* stop_button_;
		wxSlider* speed_slider_;
		wxStaticText* speed_text_;
		wxSlider* time_slider_;
		wxStaticText* time_text_;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void play( wxCommandEvent& event ) { event.Skip(); }
		virtual void pause( wxCommandEvent& event ) { event.Skip(); }
		virtual void stop( wxCommandEvent& event ) { event.Skip(); }
		virtual void setSpeed( wxScrollEvent& event ) { event.Skip(); }
		virtual void setTime( wxScrollEvent& event ) { event.Skip(); }
		
	
	public:
		
		VideoPlayerDialog_B( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Video Player"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxCLOSE_BOX|wxSYSTEM_MENU ); 
		~VideoPlayerDialog_B();
	
};

#endif //__VIDEOPLAYERDIALOG_B_H__
