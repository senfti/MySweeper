///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __ABOUTDIALOG_B_H__
#define __ABOUTDIALOG_B_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class AboutDialog_B
///////////////////////////////////////////////////////////////////////////////
class AboutDialog_B : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText2;
		wxStaticLine* m_staticline2;
		wxStaticText* m_staticText21;
		wxStaticLine* m_staticline3;
		wxStaticText* m_staticText3;
		wxStaticLine* m_staticline1;
		wxButton* ok_button;
		
		// Virtual event handlers, overide them in your derived class
		virtual void ok( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		AboutDialog_B( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("About"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~AboutDialog_B();
	
};

#endif //__ABOUTDIALOG_B_H__
