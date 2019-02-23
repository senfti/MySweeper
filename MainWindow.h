/*//////////////////////////////////////////////////////////////////////////////

Copyright(c) 2014, Thomas Senfter
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met :

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and / or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
/*//////////////////////////////////////////////////////////////////////////////

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include "stdafx.h"
#include "MainWindow_B.h"
#include "SmileyButton.h"
#include "main.h"
#include "Board.h"

//class for the main window (derives from wxFrame)
class MainWindow : public MainWindow_B 
{
	private:
    MyApp* app_;
    wxTimer timer_;     //timer for the time display

    int displayed_time_ = 1;    //as in windows minesweeper, the time starts by one (0.0 - 1.0 sec = 1)

    SegmentDisplayPanel* additional_mines_digits_[3];   //3 digits are allways shown (are in MainWindow_B) and up to 3 additional digits
    SegmentDisplayPanel* additional_time_digits_[3];

    int additional_digits_ = 0;   //default is, no additional digits

    void OnHelp(wxCommandEvent& event);     //shows help dialog
    void OnAbout(wxCommandEvent& event);    //shows about dialog
    void OnTimer(wxTimerEvent& event);      //timer event -> increase time in time display
    void keyDown(wxKeyEvent& event);        //for spacebar restart and hotkey under wxGTK
    void OnClose(wxCloseEvent& event);      //some cleanup code
    void OnUpperPanelEnter(wxMouseEvent& event);      //if clicking on upper panel should act like clicking on smiley_button, this function does this
    void OnUpperPanelLeave(wxMouseEvent& event);
    void OnUpperPanelLeftDown(wxMouseEvent& event);
    void OnUpperPanelLeftUp(wxMouseEvent& event);

	protected:

	public:
		
    MainWindow(MyApp* app, wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("MySweeper"), 
      const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1), 
      long style = wxCAPTION | wxCLOSE_BOX | wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCLIP_CHILDREN | wxRAISED_BORDER);
		
		~MainWindow();

    BoardStatus getBoardStatus(){ return app_->board_->getBoardStatus(); }

    int getSquareSize();
    void updateBoardView(int x1 = -1, int y1 = -1, int x2 = -1, int y2 = -1);   //if x1 != -1 update just the given region, else update all
    void instantBoardUpdate();      //calls Update and not Refresh (means immediate repaint and no just post a paint event)
    void changeBoardSize();         //if size of board changed, this is called to change GUI (incl. adjust digit number)
    void resize(int square_size);   //changes square size
    void increaseSize();            //calculates bigger square size and calls resize
    void increaseSize(wxCommandEvent& event){ increaseSize(); }   //if called from the gui
    void decreaseSize();           //calculates smaller square size and calls resize
    void decreaseSize(wxCommandEvent& event){ decreaseSize(); }

    void adjustDigitNumber();       //adds or removes additional digits

    void setTimeDisplay(int time);    //set time display value
    void setMinesDisplay(int mines);  //set mines display value
    void setSmileyFace(SmileyFace face);

    void showVideoCursor(bool show);    //show / hide cursor for video (forwarding to board_panel)
    void setVideoCursor(const wxPoint& pos);    //set the position of the video cursor (forwarding to board_panel)

    void focusOnCursorIfNotSeen();      //sets the origin of the view if cursor not seen in video mode in scroll mode (forwarding to board_panel)

    void newBoard(wxCommandEvent& event);
    void newBoard(bool change_size = false);   //does stuff if new board is generated
    void setBoardStyle(BoardStyle style);
    void setCustomBoardStyle(int width, int height, int mines);
    void setBoardBeginner(wxCommandEvent& event);
    void setBoardIntermediate(wxCommandEvent& event);
    void setBoardExpert(wxCommandEvent& event);

    void playVideo(wxCommandEvent& event);    //starts video playing

    void previewVideo(wxCommandEvent& event); //shows video generated in game before
    void actiatePreview(bool activate);       //enable preview and save video menu entries

    void saveVideo(wxCommandEvent& event);

    void startTime(float speed = 1.f);    //starts the timer which updates time display
    void stopTime(int time);              //stops the timer which updates time display

    void exit(wxCommandEvent& event);

    const Settings* getSettings(){ return app_->settings_; }    //get settings (child windows without app_ pointer need this) 

    //open the dialoges and do some stuff if needed
    void openCustomDialog();
    void openCustomDialog(wxCommandEvent& event){ openCustomDialog(); }
    void openSettingsDialog(wxCommandEvent& event);
    void showHighscores(int page);
    void showHighscores(wxCommandEvent& event);
    void showHistory(wxCommandEvent& event);
    void showCounters(wxCommandEvent& event);

    bool isScrollMode();
    int getMaxBoardPanelSizeX();      //calculates the board_panel size, where to change to scroll mode
    int getMaxBoardPanelSizeY();
};

#endif //__MAINWINDOW_H__
