///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __HIGHSCOREDIALOG_B_H__
#define __HIGHSCOREDIALOG_B_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/font.h>
#include <wx/grid.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class HighscoreDialog_B
///////////////////////////////////////////////////////////////////////////////
class HighscoreDialog_B : public wxDialog 
{
	private:
	
	protected:
		wxNotebook* notebook_;
		wxPanel* highscores_page_;
		wxGrid* highscore_grid_;
		wxPanel* non_flagging_page_;
		wxGrid* non_flagging_grid_;
		wxPanel* flagging_page_;
		wxGrid* flagging_grid_;
		wxPanel* custom_page_;
		wxGrid* custom_grid_;
		wxGrid* size_grid_;
		wxButton* ok_button_;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		HighscoreDialog_B( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Highscores"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~HighscoreDialog_B();
	
};

#endif //__HIGHSCOREDIALOG_B_H__
