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

#include "stdafx.h"
#include "BoardPanel.h"
#include "Board.h"
#include "Images.h"
#include "MainWindow.h"
#include "Settings.h"
#include "main.h"
#include "VideoRecorder.h"
#include "VideoPlayer.h"

#include <climits>

BoardPanel::BoardPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style, const wxString& name)
    : wxPanel(parent, id, pos, size, style, name), app_(NULL){

  SetBackgroundStyle(wxBG_STYLE_PAINT);   //needed for double buffered (flicker-free) drawing
    
  Connect(wxEVT_PAINT, wxPaintEventHandler(BoardPanel::paint), NULL, this);

  Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(BoardPanel::leftDown), NULL, this);
  Connect(wxEVT_LEFT_UP, wxMouseEventHandler(BoardPanel::leftUp), NULL, this);
  Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(BoardPanel::leftDown), NULL, this);

  Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(BoardPanel::rightDown), NULL, this);
  Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(BoardPanel::rightUp), NULL, this);
  Connect(wxEVT_RIGHT_DCLICK, wxMouseEventHandler(BoardPanel::rightDown), NULL, this);

  Connect(wxEVT_MIDDLE_DOWN, wxMouseEventHandler(BoardPanel::middleDown), NULL, this);
  Connect(wxEVT_MIDDLE_UP, wxMouseEventHandler(BoardPanel::middleUp), NULL, this);
  Connect(wxEVT_MIDDLE_DCLICK, wxMouseEventHandler(BoardPanel::middleDown), NULL, this);

  Connect(wxEVT_MOTION, wxMouseEventHandler(BoardPanel::mouseMove), NULL, this);
  Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(BoardPanel::mouseLeave), NULL, this);

  createBitmaps();
  hand_cursor_ = wxCursor(wxImage(xpm_hand));
}

BoardPanel::~BoardPanel(){
  Disconnect(wxEVT_PAINT, wxPaintEventHandler(BoardPanel::paint), NULL, this);
  Disconnect(wxEVT_LEFT_DOWN, wxMouseEventHandler(BoardPanel::leftDown), NULL, this);
  Disconnect(wxEVT_LEFT_UP, wxMouseEventHandler(BoardPanel::leftUp), NULL, this);
  Disconnect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(BoardPanel::leftDown), NULL, this);
  Disconnect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(BoardPanel::rightDown), NULL, this);
  Disconnect(wxEVT_RIGHT_UP, wxMouseEventHandler(BoardPanel::rightUp), NULL, this);
  Disconnect(wxEVT_RIGHT_DCLICK, wxMouseEventHandler(BoardPanel::rightDown), NULL, this);
  Disconnect(wxEVT_MIDDLE_DOWN, wxMouseEventHandler(BoardPanel::middleDown), NULL, this);
  Disconnect(wxEVT_MIDDLE_UP, wxMouseEventHandler(BoardPanel::middleUp), NULL, this);
  Disconnect(wxEVT_MOTION, wxMouseEventHandler(BoardPanel::mouseMove), NULL, this);
  Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(BoardPanel::mouseLeave), NULL, this);
}

wxPoint BoardPanel::calcSquareFromPosition(int x, int y){
  #ifdef __WXGTK__    //In wxGTK mouse clicks are one pixel too far right and down (maybe start counting at 1???)
    x--;
    y--;
  #endif

  if (x < board_border_thickness_ || x >= GetClientSize().x - board_border_thickness_ ||    //not on a square
      y < board_border_thickness_ || y >= GetClientSize().y - board_border_thickness_){
    return wxPoint(-1, -1);
  }
  
  //pay attention to the offset in scroll mode
  return wxPoint((x - board_border_thickness_ + origin_x_) / square_size_, (y - board_border_thickness_ + origin_y_) / square_size_);
}

void BoardPanel::setOrigin(int x, int y){
  //be sure, that nothing out of the board is shown
  origin_x_ = std::min(std::max(x, 0), app_->board_->getWidth()*square_size_ - GetClientSize().GetWidth() + 2 * board_border_thickness_);
  origin_y_ = std::min(std::max(y, 0), app_->board_->getHeight()*square_size_ - GetClientSize().GetHeight() + 2 * board_border_thickness_);
}

void BoardPanel::focusOnCursorIfNotSeen(){
  if (cursor_pos_.x < origin_x_ + board_border_thickness_ || cursor_pos_.y < origin_y_ + board_border_thickness_ ||
    cursor_pos_.x > origin_x_ + GetClientSize().x - board_border_thickness_ ||
    cursor_pos_.y > origin_y_ + GetClientSize().y - board_border_thickness_)
  {
    int old_x = origin_x_;
    int old_y = origin_y_;
    setOrigin(cursor_pos_.x - GetClientSize().x / 2, cursor_pos_.y - GetClientSize().y / 2);
    if (old_x != origin_x_ || old_y < origin_y_)
      updateBoard();
  }
}


void BoardPanel::changeBoardSize(){
  scroll_mode_ = false;     //scroll mode: too big at least in one axis
  int width = app_->board_->getWidth()*square_size_ + 2 * board_border_thickness_;
  int height = app_->board_->getHeight()*square_size_ + 2 * board_border_thickness_;

  if (width > main_window_->getMaxBoardPanelSizeX()){   //check, if board is too big for the screen
    width = main_window_->getMaxBoardPanelSizeX();
    main_window_->SetPosition(wxPoint(0, -1));
    scroll_mode_ = true;
  }
  if (height > main_window_->getMaxBoardPanelSizeY()){
    height = main_window_->getMaxBoardPanelSizeY();
    main_window_->SetPosition(wxPoint(-1, 0));
    scroll_mode_ = true;
  }

  origin_x_ = 0;
  origin_y_ = 0;
  last_x_ = -1;
  last_y_ = -1;

  SetMinClientSize(wxSize(width, height));
  Refresh();        //strange, but refresh needed before resize, else window too small (size and not client size)
}

void BoardPanel::updateBoard(int x1, int y1, int x2, int y2){
  if (app_->board_ == nullptr)
    return;
  if (x1 != -1){
    wxRect region;        //wxRect used, because it swaps values if needed and calcs the width
    region.SetLeft(x1);
    region.SetTop(y1);
    region.SetRight(x2);
    region.SetBottom(y2);
    RefreshRect(
      wxRect(region.GetLeft() * square_size_ + board_border_thickness_ - origin_x_, 
             region.GetTop() * square_size_ + board_border_thickness_ - origin_y_,
             region.GetWidth() * square_size_,
             region.GetHeight() * square_size_));
  }
  else
    Refresh();
}

void BoardPanel::createBitmaps(){
  board_border_thickness_ = 3 * square_size_ / 16;

  int index;
  if (square_size_ % 32 == 0)   //use 32p images, if it´s multiple of 32
    index = 2;
  else if (square_size_ % 24 == 0)   //else use 24p images, if it´s multiple of 24
    index = 1;
  else                        //use 16p images
    index = 0;

  int normal_bitmap_size = 5 * square_size_ / 8;      //images are smaller as square_size (so 16p images are not really 16x16)
  int normal_bitmap_offset = (square_size_ - normal_bitmap_size + 1) / 2;
  int mine_bitmap_size;     //mine image is a little bit bigger
  if (square_size_ % 24 == 0)
    mine_bitmap_size = 20 * square_size_ / 24;
  else
    mine_bitmap_size = 13 * square_size_ / 16;
  int mine_bitmap_offset = (square_size_ - mine_bitmap_size + 1) / 2;

  wxMemoryDC dc;
  wxBrush light_gray_brush(wxColor(0xC0, 0xC0, 0xC0, 0), wxBRUSHSTYLE_SOLID);   //background color

  //unopened  
  unopened_square_.Create(square_size_, square_size_);
  dc.SelectObject(unopened_square_);
  dc.SetBackground(light_gray_brush);
  dc.Clear();
  paintSquareButton(dc);

  //flagged
  flagged_square_.Create(square_size_, square_size_);
  dc.SelectObject(flagged_square_);
  dc.SetBackground(light_gray_brush);
  dc.Clear();
  paintSquareButton(dc);
  dc.DrawBitmap(wxBitmap(wxImage(xpm_flag[index]).Rescale(normal_bitmap_size, normal_bitmap_size)), 
    normal_bitmap_offset, normal_bitmap_offset);

  //question marked
  question_marked_square_.Create(square_size_, square_size_);
  dc.SelectObject(question_marked_square_);
  dc.SetBackground(light_gray_brush);
  dc.Clear();
  paintSquareButton(dc);
  dc.DrawBitmap(wxBitmap(wxImage(xpm_question_mark[index]).Rescale(normal_bitmap_size, normal_bitmap_size)), 
    normal_bitmap_offset, normal_bitmap_offset);

  //clicked
  clicked_square_.Create(square_size_, square_size_);
  dc.SelectObject(clicked_square_);
  dc.SetBackground(light_gray_brush);
  dc.Clear();
  paintSquareGrid(dc);

  //numbers
  number_square_[0] = clicked_square_;
  for (int i = 1; i < 9; i++){
    number_square_[i].Create(square_size_, square_size_);
    dc.SelectObject(number_square_[i]);
    dc.SetBackground(light_gray_brush);
    dc.Clear();
    paintSquareGrid(dc);
    dc.DrawBitmap(wxBitmap(wxImage(xpm_numbers[i-1][index]).Rescale(normal_bitmap_size, normal_bitmap_size)),
      normal_bitmap_offset, normal_bitmap_offset);
  }

  //mine
  mine_square_.Create(square_size_, square_size_);
  dc.SelectObject(mine_square_);
  dc.SetBackground(light_gray_brush);
  dc.Clear();
  paintSquareGrid(dc);
  dc.DrawBitmap(wxBitmap(wxImage(xpm_mine[index]).Rescale(mine_bitmap_size, mine_bitmap_size)),
    mine_bitmap_offset, mine_bitmap_offset);

  //wrong flagged
  wrong_flagged_square_.Create(square_size_, square_size_);
  dc.SelectObject(wrong_flagged_square_);
  dc.SetBackground(light_gray_brush);
  dc.Clear();
  paintSquareGrid(dc);
  dc.DrawBitmap(wxBitmap(wxImage(xpm_mine[index]).Rescale(mine_bitmap_size, mine_bitmap_size)),
    mine_bitmap_offset, mine_bitmap_offset);
  paintRedCross(dc);

  //killing mine
  killing_mine_square_.Create(square_size_, square_size_);
  dc.SelectObject(killing_mine_square_);
  dc.SetBackground(*wxRED_BRUSH);
  dc.Clear();
  paintSquareGrid(dc);
  dc.DrawBitmap(wxBitmap(wxImage(xpm_killing_mine[index]).Rescale(mine_bitmap_size, mine_bitmap_size)),
    mine_bitmap_offset, mine_bitmap_offset);

  cursor_bitmap_ = 
    wxBitmap(wxImage(xpm_cursor).Rescale(15 * (square_size_ / 16), 23 * (square_size_ / 16), wxIMAGE_QUALITY_HIGH));
}

void BoardPanel::paintSquareButton(wxMemoryDC& dc){
  int border_thickness = square_size_ / 8;

  dc.SetPen(*wxWHITE_PEN);

  for (int i = 0; i < border_thickness; i++){
    dc.DrawLine(i, i, i, square_size_ - 1 - i);
    dc.DrawLine(i, i, square_size_ - 1 - i, i);
  }

  wxPen gray_pen(wxColor(0x80, 0x80, 0x80, 0), 1, wxPENSTYLE_SOLID);
  dc.SetPen(gray_pen);

  for (int i = 0; i < border_thickness; i++){
    dc.DrawLine(square_size_ - 1 - i, square_size_ - 1 - i, square_size_ - 1 - i, i);
    dc.DrawLine(square_size_ - 1 - i, square_size_ - 1 - i, i, square_size_ - 1 - i);
  }
}

void BoardPanel::paintSquareGrid(wxMemoryDC& dc){
  int grid_lines_thickness = square_size_ / 16;

  wxPen grid_pen(wxColor(0x80, 0x80, 0x80, 0), 1, wxPENSTYLE_SOLID);
  dc.SetPen(grid_pen);

  for(int i = 0; i < grid_lines_thickness; i++){
    dc.DrawLine(i, 0, i, square_size_);
    dc.DrawLine(0, i, square_size_, i);
  }
}

void BoardPanel::paintRedCross(wxMemoryDC& dc){
  wxPen red_pen(wxColor(0xff, 0, 0), 1, wxPENSTYLE_SOLID);
  red_pen.SetWidth(square_size_ / 16);
  dc.SetPen(red_pen);
  dc.DrawLine(2, 3, square_size_ - 2, square_size_ - 1);
  dc.DrawLine(3, 3, square_size_ - 1, square_size_ - 1);
  dc.DrawLine(square_size_ - 3, 3, 1, square_size_ - 1);
  dc.DrawLine(square_size_ - 2, 3, 2, square_size_ - 1);
}

int BoardPanel::resizeSquares(int size){
  if (size < 24 || size > 31)           //just 24p and multiples of 16p supported
    size = ((size+15) / 16) * 16;       //round up
  else
    size = 24;

  if (square_size_ != size){
    square_size_ = size;
    createBitmaps();
  }

  if (app_ == nullptr || app_->board_ == nullptr)   //when construction of all classes is not finished
    return square_size_;

  changeBoardSize();

  return square_size_;
}

void BoardPanel::paint(wxPaintEvent &event){
  if (app_ == nullptr || app_->board_ == nullptr)
    return;

  wxAutoBufferedPaintDC dc(this);   //for double buffered drawing

  int width = GetClientSize().GetX();
  int height = GetClientSize().GetY();
  wxRect update_region = GetUpdateClientRect();   //just draw in the update region, to increase performance

  static wxPen dark_gray_pen(wxColor(0x80, 0x80, 0x80, 0), 1, wxPENSTYLE_SOLID);
  static wxPen red_pen(wxColor(0xff, 0, 0), 1, wxPENSTYLE_SOLID);
  static wxPen grid_pen(wxColor(0x80, 0x80, 0x80, 0), 1, wxPENSTYLE_SOLID);
  static wxPen thick_red_pen(wxColor(0xff, 0, 0), 2, wxPENSTYLE_SOLID);
  static wxPen thick_black_pen(wxColor(0x00, 0, 0), 3, wxPENSTYLE_SOLID);

  if (update_region.GetLeft() < board_border_thickness_ || update_region.GetTop() < board_border_thickness_ ||  //just if repaint needed
    update_region.GetRight() > (width - board_border_thickness_) && update_region.GetBottom() > (height - board_border_thickness_))
  {
    dc.SetPen(dark_gray_pen);                                //make border thicker (own boarder drawing needed)
    for (int i = 0; i < board_border_thickness_; i++){
      dc.DrawLine(i, i, i, height - i);
      dc.DrawLine(i, i, width - i, i);
    }
    dc.SetPen(*wxWHITE_PEN);
    for (int i = 0; i < board_border_thickness_; i++){
      dc.DrawLine(width - i - 1, height - i - 1, width - i - 1, i - 1);
      dc.DrawLine(width - i - 1, height - i - 1, i - 1, height - i - 1);
    }
  }
  
  dc.SetDeviceOrigin(board_border_thickness_ - origin_x_, board_border_thickness_ - origin_y_);   //change origin 
  //clipping needed, so i don´t draw not over the selfdrawn border
  dc.SetClippingRegion(wxPoint(origin_x_, origin_y_), wxSize(width - 2 * board_border_thickness_, height - 2 * board_border_thickness_));

  //get squares which need a redraw
  int x_min = std::max((update_region.GetLeft() - board_border_thickness_ + origin_x_) / square_size_, 0);
  int x_max = std::min((update_region.GetRight() - board_border_thickness_ + origin_x_) / square_size_ + 1,
    app_->board_->getWidth());
  int y_min = std::max((update_region.GetTop() - board_border_thickness_ + origin_y_) / square_size_, 0);
  int y_max = std::min((update_region.GetBottom() - board_border_thickness_ + origin_y_) / square_size_ + 1,
    app_->board_->getHeight());

  for (int y = y_min; y < y_max; y++){
    for (int x = x_min; x < x_max; x++){
      switch (app_->board_->getSquare(x, y).state_)
      {
      case SQUARE_UNOPENED:
        dc.DrawBitmap(unopened_square_, x*square_size_, y*square_size_);
        break;
      case SQUARE_CLICKED:
        dc.DrawBitmap(clicked_square_, x*square_size_, y*square_size_);
        break;
      case SQUARE_FLAGGED:
        dc.DrawBitmap(flagged_square_, x*square_size_, y*square_size_);
        break;
      case SQUARE_QUESTION_MARKED:
        dc.DrawBitmap(question_marked_square_, x*square_size_, y*square_size_);
        break;
      case SQUARE_OPENED:
        if (app_->board_->getSquare(x, y).value_ == -1)
          dc.DrawBitmap(mine_square_, x*square_size_, y*square_size_);
        else
          dc.DrawBitmap(number_square_[app_->board_->getSquare(x, y).value_], x*square_size_, y*square_size_);
        break;
      case SQUARE_WRONG_FLAGGED:
        dc.DrawBitmap(wrong_flagged_square_, x*square_size_, y*square_size_);
        break;
      case SQUARE_KILLING_MINE:
        dc.DrawBitmap(killing_mine_square_, x*square_size_, y*square_size_);
        break;
      default:
        break;
      }
    }
  }
  //cursor for video
  if (show_cursor_){
    dc.DrawBitmap(cursor_bitmap_, cursor_pos_.x, cursor_pos_.y, true);
  }

  //the insert, where on the board you are, if in scroll mode
  if (scroll_mode_ && wxGetMouseState().MiddleIsDown()){
    width -= 2 * board_border_thickness_;
    height -= 2 * board_border_thickness_;
    int board_width = app_->board_->getWidth() * square_size_;
    int board_height = app_->board_->getHeight() * square_size_;
    dc.SetBrush(*wxWHITE_BRUSH);
    dc.SetPen(thick_black_pen);
    dc.DrawRectangle(   //whole board representation
      origin_x_ + width - 123,
      origin_y_ + height - 23 - ceil((100.f * board_height) / board_width),
      104, 
      ceil((100.f * board_height) / board_width) + 4);
    dc.SetPen(thick_red_pen);
    dc.DrawRectangle(   //representation of the seen part
      origin_x_ + width - 120 + (100 * origin_x_) / board_width,
      origin_y_ + height - 20 - ceil((100.f * board_height) / board_width) + ceil((100.f * origin_y_ ) / board_width),
      std::max(100.f * (static_cast<float>(width) / board_width), 2.f),   //after some math^^
      std::max(static_cast<float>((ceil((100.f * height) / board_width) - 1)), 2.f));
  }
}

void BoardPanel::leftDown(wxMouseEvent &event){
  if (main_window_->getSettings()->restart_doubleclick_ && event.ButtonDClick() && app_->board_->isFinished()){ //double click restart
    main_window_->newBoard();
    return;
  }

  if (!app_->board_->isReadyForInput())
    return;

  wxPoint square = calcSquareFromPosition(event.GetX(), event.GetY());
  if (square.x == -1)                                                                 //means not on a square
    return;

  if (event.MiddleIsDown()) //middle overwrites all
    return;

  if (event.RightIsDown())
    app_->board_->chordClickSquare(square.x, square.y);
  else
    app_->board_->leftClickSquare(square.x, square.y);
}

void BoardPanel::leftUp(wxMouseEvent &event){
  if (main_window_->getSettings()->restart_on_click_after_delay_ &&   //if restart after delay enabled, restart
    (app_->board_->getBoardStatus() == BOARD_STATUS_LOST || app_->board_->getBoardStatus() == BOARD_STATUS_WON) &&
    (app_->board_->getStats()->time_ + 1000) < app_->board_->getTime())
  {
    main_window_->newBoard();
    return;
  }

  if (!app_->board_->isReadyForInput())
    return;

  wxPoint square = calcSquareFromPosition(event.GetX(), event.GetY());
  if (square.x == -1)                                                                 //means not on a square
    return;

  if (event.MiddleIsDown())                                                        //middle mouse has highest priority
    return;

  if (event.RightIsDown())
    app_->board_->openChord(square.x, square.y, false);
  else
    app_->board_->openSquare(square.x, square.y);
}

void BoardPanel::rightDown(wxMouseEvent &event){
  if (!app_->board_->isReadyForInput())
    return;

  wxPoint square = calcSquareFromPosition(event.GetX(), event.GetY());
  if (square.x == -1)                                                                 //means not on a square
    return;

  if (event.MiddleIsDown())                                                          //middle mouse has highest priority
    return;

  if (event.LeftIsDown())
    app_->board_->chordClickSquare(square.x, square.y);
  else
    app_->board_->rightClickSquare(square.x, square.y);
}

void BoardPanel::rightUp(wxMouseEvent &event){
  if (main_window_->getSettings()->restart_on_click_after_delay_ &&   //if restart after delay enabled, restart
    (app_->board_->getBoardStatus() == BOARD_STATUS_LOST || app_->board_->getBoardStatus() == BOARD_STATUS_WON) &&
    (app_->board_->getStats()->time_ + 1000) < app_->board_->getTime())
  {
    main_window_->newBoard();
    return;
  }

  if (!app_->board_->isReadyForInput())
    return;

  wxPoint square = calcSquareFromPosition(event.GetX(), event.GetY());
  if (square.x == -1)                                                                 //means not on a square
    return;

  if (event.MiddleIsDown())                                                           //middle mouse has highest priority
    return;  
  if (event.LeftIsDown())
    app_->board_->openChord(square.x, square.y, true);
  else
    app_->board_->rightUp();            //all other smiley sets while game in Board.cpp
}

void BoardPanel::middleDown(wxMouseEvent &event){
  if (scroll_mode_){
    SetCursor(hand_cursor_);
    last_x_ = event.GetX();
    last_y_ = event.GetY();
    updateBoard();
    return;
  }

  if (main_window_->getSettings()->restart_m_mouse_){   //if restart with mouse enabled, restart
    main_window_->newBoard();
    return;
  }

  if (!app_->board_->isReadyForInput())
    return;

  wxPoint square = calcSquareFromPosition(event.GetX(), event.GetY());
  if (square.x == -1)                                                                 //means not on a square
    return;

  app_->board_->chordClickSquare(square.x, square.y);
}

void BoardPanel::middleUp(wxMouseEvent &event){
  if (scroll_mode_){
#ifdef __WXGTK__
    SetCursor(wxCURSOR_DEFAULT);    //wxGTK has different default cursor
#else
    SetCursor(wxCURSOR_ARROW);
#endif
    last_x_ = -1;
    last_y_ = -1;
    updateBoard();
    return;
  }

  if (main_window_->getSettings()->restart_m_mouse_){   //middle mouse just for restart
    return;
  }
  if (main_window_->getSettings()->restart_on_click_after_delay_ &&   //if restart after delay enabled, restart
    (app_->board_->getBoardStatus() == BOARD_STATUS_LOST || app_->board_->getBoardStatus() == BOARD_STATUS_WON) &&
    (app_->board_->getStats()->time_ + 1000) < app_->board_->getTime())
  {
    main_window_->newBoard();
    return;
  }

  if (!app_->board_->isReadyForInput())
    return;

  wxPoint square = calcSquareFromPosition(event.GetX(), event.GetY());
  if (square.x == -1)                                                                 //means not on a square
    return;

  app_->board_->openChord(square.x, square.y, false);
}

void BoardPanel::mouseMove(wxMouseEvent &event){
  if (scroll_mode_){
    if (event.MiddleIsDown() && last_x_ != -1 && !app_->video_player_->isRunning()){
      setOrigin(origin_x_ + (last_x_ - event.GetX()) * (1 + 4 * event.CmdDown()),   //if "Cmd"-Key down, scroll faster
        origin_y_ + (last_y_ - event.GetY()) * (1 + 4 * event.CmdDown()));
      updateBoard();
      last_x_ = event.GetX();
      last_y_ = event.GetY();
      return;
    }
    else{
#ifdef __WXGTK__
      SetCursor(wxCURSOR_DEFAULT);   //wxGTK has different default cursor
#else
      SetCursor(wxCURSOR_ARROW);
#endif      
      last_x_ = -1;
      last_y_ = -1;
      updateBoard();
    }
  }
  //mouse path recording and calculation
  if (app_->video_recorder_->isRecording()){
    app_->video_recorder_->addMousePosition(
      MousePosition(app_->board_->getTime(),
      (event.GetX() - board_border_thickness_ + origin_x_) * (384 / square_size_),
      (event.GetY() - board_border_thickness_ + origin_y_) * (384 / square_size_)));
  }
  if (app_->board_->getBoardStatus() == BOARD_STATUS_STARTED){
    app_->board_->incrPath(sqrtf(
      (last_mouse_position_.x - event.GetX()) * (last_mouse_position_.x - event.GetX()) +
      (last_mouse_position_.y - event.GetY()) * (last_mouse_position_.y - event.GetY())) / app_->main_window_->getSquareSize());
    last_mouse_position_ = event.GetPosition();
  }
  else
    last_mouse_position_ = event.GetPosition();

  if (!app_->board_->isReadyForInput())
    return;

  wxPoint square = calcSquareFromPosition(event.GetX(), event.GetY());
  if (square.x == -1){                              //mouse on the border (not on a square)
    app_->board_->leaveBoard();
    return;
  }

  if (event.MiddleIsDown()){
    if (main_window_->getSettings()->restart_m_mouse_){
      return;
    }
    app_->board_->moveChorded(square.x, square.y);
    return;
  }

  if (event.LeftIsDown() && event.RightIsDown()){
    app_->board_->moveChorded(square.x, square.y);
    return;
  }

  if (event.LeftIsDown()){
    app_->board_->moveClicked(square.x, square.y);
  }
}

void BoardPanel::mouseLeave(wxMouseEvent &event){       //called when mouse leaves board panel
#ifdef __WXGTK__
  SetCursor(wxCURSOR_DEFAULT);
#else
  SetCursor(wxCURSOR_ARROW);
  last_x_ = -1;
  last_y_ = -1;
  updateBoard();
#endif
  if (app_->video_recorder_->isRecording()){
    app_->video_recorder_->addMousePosition(
      MousePosition(app_->board_->getTime(), -1000, -1000));  //outside
  }

  if (app_->board_->isReadyForInput())
    app_->board_->leaveBoard();
}
