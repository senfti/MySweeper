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

#ifndef __BOARD_PANEL_H_
#define __BOARD_PANEL_H_

#include "stdafx.h"

class Board;
class MyApp;
class MainWindow;

//the window, in which the board is painted, also important for input
class BoardPanel : public wxPanel{
  private:
    MyApp* app_;
    MainWindow* main_window_;
    int square_size_ = 16;    //length of a square in pixel

    bool show_cursor_ = false;    //if to show video cursor
    wxPoint cursor_pos_;          //position of the video cursor

    int board_border_thickness_;  //thickness of self drawn boarder of the board

    bool scroll_mode_ = false;    //if board is too big, just show part of the board ( = scroll_mode)
    int origin_x_ = 0;            //position in scroll mode (how many pixel is the board moved) 
    int origin_y_ = 0;
    int last_x_ = -1;             //old mouse position for calculation of how far to move the board
    int last_y_ = -1;

    wxPoint last_mouse_position_; //old mouse position for path calculation

    //wxBitmaps for all possible square types (so not drawing stuff everytime, draw when changing size and then just use the bitmap)
    wxBitmap unopened_square_;
    wxBitmap clicked_square_;
    wxBitmap flagged_square_;
    wxBitmap question_marked_square_;
    wxBitmap wrong_flagged_square_;
    wxBitmap killing_mine_square_;
    wxBitmap mine_square_;
    wxBitmap number_square_[9];   //0 to 8 (0 is there because it´s easier so)

    wxBitmap cursor_bitmap_;    //bitmap of the video cursor
    wxCursor hand_cursor_;      //hand cursor shown when moving board in scroll mode

    //methodes for painting the bitmaps above
    void createBitmaps();
    void paintSquareButton(wxMemoryDC& dc);
    void paintSquareGrid(wxMemoryDC& dc);
    void paintRedCross(wxMemoryDC& dc);

    //mouse events processed
    void leftDown(wxMouseEvent &event);
    void leftUp(wxMouseEvent &event);
    void rightDown(wxMouseEvent &event);
    void rightUp(wxMouseEvent &event);
    void middleDown(wxMouseEvent &event);
    void middleUp(wxMouseEvent &event);
    void mouseMove(wxMouseEvent &event);
    void mouseLeave(wxMouseEvent &event);

    //returns square of the given mouse position (wxPoint.x == -1 means, no square (border) )
    wxPoint calcSquareFromPosition(int x, int y);

  public:
    BoardPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
      const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = "panel");
    ~BoardPanel();

    int resizeSquares(int size); //changes square size and returns the size (could be changed to a valid number)
    void changeBoardSize();     //size change when changing width/height of board
    void updateBoard(int x1 = -1, int y1 = -1, int x2 = -1, int y2 = -1);     //if x1 == -1, repaint part of the board show, else just given rectangle
    void paint(wxPaintEvent &event);  //paint function

    int getSquareSize(){ return square_size_; }
    int getBoardBoarderThickness(){ return board_border_thickness_; }

    void setAppPointer(MyApp* app){ app_ = app; }     //set after construction (else there were problems)
    void setMainWindowPointer(MainWindow* main_window){ main_window_ = main_window; }   //needed because wxWindow* parent can´t be casted to MainWindow* in constructor (the main_window is not fully constructed at this point)

    void showCursor(bool show){ show_cursor_ = show; }
    void setCursor(const wxPoint& pos){ cursor_pos_ = pos; }

    void setOrigin(int x, int y);   //when moving, set the origin
    void focusOnCursorIfNotSeen();  //when in video mode cursor out of the seen board part, set origin that the cursor is in the middle

    bool isScrollMode(){ return scroll_mode_; }
};

#endif //__BOARD_PANEL_H_