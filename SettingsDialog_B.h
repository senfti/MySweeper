///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __SETTINGSDIALOG_B_H__
#define __SETTINGSDIALOG_B_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/radiobox.h>
#include <wx/filepicker.h>
#include <wx/spinctrl.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class SettingsDialog_B
///////////////////////////////////////////////////////////////////////////////
class SettingsDialog_B : public wxDialog 
{
	private:
	
	protected:
		wxNotebook* notebook_;
		wxPanel* game_page_;
		wxCheckBox* questionmark_checkbox_;
		wxStaticLine* m_staticline1;
		wxCheckBox* restart_spacebar_checkbox_;
		wxCheckBox* restart_m_mouse_checkbox_;
		wxCheckBox* restart_doubleclick_checkbox_;
		wxCheckBox* restart_on_fail_checkbox_;
		wxCheckBox* restart_on_upper_panel_checkbox_;
		wxCheckBox* restart_on_click_after_delay_checkbox_;
		wxStaticLine* m_staticline2;
		wxCheckBox* update_counters_checkbox_;
		wxCheckBox* hide_counters_until_finished_checkbox_;
		wxStaticLine* m_staticline3;
		wxStaticText* m_staticText3;
		wxTextCtrl* name_edit_;
		wxPanel* video_page_;
		wxRadioBox* auto_save_radio_box_;
		wxStaticText* m_staticText1;
		wxDirPickerCtrl* auto_save_dir_picker_;
		wxStaticText* m_staticText2;
		wxTextCtrl* default_file_name_edit_;
		wxPanel* miscellaneous_page_;
		wxCheckBox* limit_size_checkbox_;
		wxStaticText* m_staticText4;
		wxSpinCtrl* max_width_edit_;
		wxStaticText* m_staticText5;
		wxSpinCtrl* max_height_edit_;
		wxStaticLine* m_staticline4;
		wxCheckBox* no_zini_checkbox_;
		wxStaticLine* m_staticline5;
		wxRadioBox* counters_size_radiobox_;
		wxButton* cancel_button_;
		wxButton* default_button_;
		wxButton* apply_button_;
		wxButton* ok_button_;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnNameText( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFileText( wxCommandEvent& event ) { event.Skip(); }
		virtual void EnableWindowLimits( wxCommandEvent& event ) { event.Skip(); }
		virtual void cancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void setDefault( wxCommandEvent& event ) { event.Skip(); }
		virtual void apply( wxCommandEvent& event ) { event.Skip(); }
		virtual void ok( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxString name_; 
		
		SettingsDialog_B( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~SettingsDialog_B();
	
};

#endif //__SETTINGSDIALOG_B_H__
