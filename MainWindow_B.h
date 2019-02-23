///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __MAINWINDOW_B_H__
#define __MAINWINDOW_B_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
class BoardPanel;
class SegmentDisplayPanel;
class SmileyButton;

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MainWindow_B
///////////////////////////////////////////////////////////////////////////////
class MainWindow_B : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* menu_bar_;
		wxMenu* file_menu_;
		wxMenuItem* new_menu_item_;
		wxMenuItem* preview_video_menu_item_;
		wxMenuItem* save_video_menu_item_;
		wxMenu* options_menu_;
		wxMenuItem* beginner_menu_item_;
		wxMenuItem* intermediate_menu_item_;
		wxMenuItem* expert_menu_item_;
		wxMenuItem* decrease_size_item_;
		wxMenuItem* show_counter_menu_item_;
		wxMenu* help_menu_;
		wxStatusBar* status_bar_;
		wxBoxSizer* main_sizer_;
		wxPanel* main_panel_;
		wxBoxSizer* main_panel_sizer_;
		wxPanel* upper_panel_;
		wxBoxSizer* upper_sizer_;
		wxPanel* mines_display_panel_;
		wxBoxSizer* mines_display_sizer_;
		SegmentDisplayPanel* mines_digit_100_;
		SegmentDisplayPanel* mines_digit_10_;
		SegmentDisplayPanel* mines_digit_1_;
		SmileyButton* smiley_button_;
		wxPanel* time_display_panel_;
		wxBoxSizer* time_display_sizer_;
		SegmentDisplayPanel* time_digit_100_;
		SegmentDisplayPanel* time_digit_10_;
		SegmentDisplayPanel* time_digit_1_;
		BoardPanel* board_panel_;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void keyDown( wxKeyEvent& event ) { event.Skip(); }
		virtual void newBoard( wxCommandEvent& event ) { event.Skip(); }
		virtual void playVideo( wxCommandEvent& event ) { event.Skip(); }
		virtual void previewVideo( wxCommandEvent& event ) { event.Skip(); }
		virtual void saveVideo( wxCommandEvent& event ) { event.Skip(); }
		virtual void showHighscores( wxCommandEvent& event ) { event.Skip(); }
		virtual void showHistory( wxCommandEvent& event ) { event.Skip(); }
		virtual void exit( wxCommandEvent& event ) { event.Skip(); }
		virtual void setBoardBeginner( wxCommandEvent& event ) { event.Skip(); }
		virtual void setBoardIntermediate( wxCommandEvent& event ) { event.Skip(); }
		virtual void setBoardExpert( wxCommandEvent& event ) { event.Skip(); }
		virtual void openCustomDialog( wxCommandEvent& event ) { event.Skip(); }
		virtual void decreaseSize( wxCommandEvent& event ) { event.Skip(); }
		virtual void increaseSize( wxCommandEvent& event ) { event.Skip(); }
		virtual void showCounters( wxCommandEvent& event ) { event.Skip(); }
		virtual void openSettingsDialog( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpperPanelEnter( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnUpperPanelLeave( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnUpperPanelLeftDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnUpperPanelLeftUp( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainWindow_B( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("MySweeper"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxCLIP_CHILDREN|wxRAISED_BORDER );
		
		~MainWindow_B();
	
};

#endif //__MAINWINDOW_B_H__
