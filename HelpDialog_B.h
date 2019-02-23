///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __HELPDIALOG_B_H__
#define __HELPDIALOG_B_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/hyperlink.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class HelpDialog_B
///////////////////////////////////////////////////////////////////////////////
class HelpDialog_B : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText2;
		wxStaticText* m_staticText5;
		wxStaticText* m_staticText6;
		wxStaticText* m_staticText51;
		wxStaticText* m_staticText61;
		wxStaticText* m_staticText52;
		wxStaticText* m_staticText62;
		wxStaticText* m_staticText21;
		wxStaticText* m_staticText53;
		wxStaticText* m_staticText63;
		wxStaticText* m_staticText511;
		wxStaticText* m_staticText611;
		wxStaticText* m_staticText521;
		wxStaticText* m_staticText621;
		wxStaticText* m_staticText5211;
		wxStaticText* m_staticText6211;
		wxStaticText* m_staticText211;
		wxHyperlinkCtrl* m_hyperlink1;
		wxStaticText* m_staticText2111;
		wxStaticText* help_label_1;
		wxStaticLine* m_staticline1;
		wxButton* ok_button_;
		
		// Virtual event handlers, overide them in your derived class
		virtual void ok( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		HelpDialog_B( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Help"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~HelpDialog_B();
	
};

#endif //__HELPDIALOG_B_H__
