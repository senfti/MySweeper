///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __HISTORYDIALOG_B_H__
#define __HISTORYDIALOG_B_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/radiobox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/grid.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class HistoryDialog_B
///////////////////////////////////////////////////////////////////////////////
class HistoryDialog_B : public wxDialog 
{
	private:
	
	protected:
		wxRadioBox* style_radio_box_;
		wxGrid* history_grid_;
		wxStaticLine* m_staticline1;
		wxButton* ok_button_;
		
		// Virtual event handlers, overide them in your derived class
		virtual void ChangeStyle( wxCommandEvent& event ) { event.Skip(); }
		virtual void sort( wxGridEvent& event ) { event.Skip(); }
		virtual void Close( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		HistoryDialog_B( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("History"), const wxPoint& pos = wxPoint( 0,0 ), const wxSize& size = wxSize( 800,600 ), long style = wxCAPTION|wxCLOSE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU ); 
		~HistoryDialog_B();
	
};

#endif //__HISTORYDIALOG_B_H__
