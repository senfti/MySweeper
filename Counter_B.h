///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __COUNTER_B_H__
#define __COUNTER_B_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/font.h>
#include <wx/grid.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class Counters_B
///////////////////////////////////////////////////////////////////////////////
class Counters_B : public wxDialog 
{
	private:
	
	protected:
		wxBoxSizer* main_sizer_;
		wxGrid* counters_grid_;
	
	public:
		
		Counters_B( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Counters"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION ); 
		~Counters_B();
	
};

#endif //__COUNTER_B_H__
