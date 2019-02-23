///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __CUSTOMDIALOG_B_H__
#define __CUSTOMDIALOG_B_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/statline.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/sizer.h>
#include <wx/choice.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class CustomDialog_B
///////////////////////////////////////////////////////////////////////////////
class CustomDialog_B : public wxDialog 
{
	private:
	
	protected:
		wxStaticLine* m_staticline1;
		wxStaticText* width_label_;
		wxSpinCtrl* width_edit_;
		wxStaticText* heght_label_;
		wxSpinCtrl* height_edit_;
		wxStaticText* mines_label_;
		wxSpinCtrl* mines_edit_;
		wxStaticLine* m_staticline3;
		wxStaticText* size_text_;
		wxChoice* size_choice_;
		wxCheckBox* expert_density_checkbox_;
		wxStaticLine* m_staticline2;
		wxButton* cancel_button_;
		wxButton* ok_button_;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnChangeSize( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnChangeSize( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSizeChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExpertDensityCheckbox( wxCommandEvent& event ) { event.Skip(); }
		virtual void cancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void apply( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		CustomDialog_B( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Custom"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxCLOSE_BOX|wxSTAY_ON_TOP|wxSYSTEM_MENU ); 
		~CustomDialog_B();
	
};

#endif //__CUSTOMDIALOG_B_H__
