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
#include "SmileyButton.h"
#include "Images.h"
#include "MainWindow.h"

SmileyButton::SmileyButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, 
  long style, const wxString& name)
    : wxPanel(parent, id, pos, size, style, name){
  SetBackgroundStyle(wxBG_STYLE_PAINT);   //double buffered painting
  resizeBitmaps();

  Connect(wxEVT_PAINT, wxPaintEventHandler(SmileyButton::paint), NULL, this);
  Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(SmileyButton::leftDown), NULL, this);
  Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(SmileyButton::leftDown), NULL, this);
  Connect(wxEVT_LEFT_UP, wxMouseEventHandler(SmileyButton::leftUp), NULL, this);
  Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(SmileyButton::mouseLeave), NULL, this);
  Connect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(SmileyButton::mouseEnter), NULL, this);
  Connect(wxEVT_MOTION, wxMouseEventHandler(SmileyButton::mouseEnter), NULL, this);
}

SmileyButton::~SmileyButton(){
  Disconnect(wxEVT_PAINT, wxPaintEventHandler(SmileyButton::paint), NULL, this);
  Disconnect(wxEVT_LEFT_DOWN, wxMouseEventHandler(SmileyButton::leftDown), NULL, this);
  Disconnect(wxEVT_LEFT_UP, wxMouseEventHandler(SmileyButton::leftUp), NULL, this);
  Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(SmileyButton::mouseLeave), NULL, this);
  Disconnect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(SmileyButton::mouseEnter), NULL, this);
  Disconnect(wxEVT_MOTION, wxMouseEventHandler(SmileyButton::mouseEnter), NULL, this);
}

void SmileyButton::resizeBitmaps(){
  //two sizes of face_images are available
  if (size_ % 36 == 0){   //when sqare_size_ == 24
    normal_bitmap_ = wxBitmap(wxImage(xpm_smiley_normal_24p).Rescale(size_, size_));
    click_bitmap_ = wxBitmap(wxImage(xpm_smiley_click_24p).Rescale(size_, size_));
    win_bitmap_ = wxBitmap(wxImage(xpm_smiley_win_24p).Rescale(size_, size_));
    loose_bitmap_ = wxBitmap(wxImage(xpm_smiley_loose_24p).Rescale(size_, size_));
  }
  else{
    normal_bitmap_ = wxBitmap(wxImage(xpm_smiley_normal).Rescale(size_, size_));
    click_bitmap_ = wxBitmap(wxImage(xpm_smiley_click).Rescale(size_, size_));
    win_bitmap_ = wxBitmap(wxImage(xpm_smiley_win).Rescale(size_, size_));
    loose_bitmap_ = wxBitmap(wxImage(xpm_smiley_loose).Rescale(size_, size_));
  }
}

void SmileyButton::resize(int size){
  if (size == size_)
    return;

  size_ = size;
  resizeBitmaps();
  SetMinClientSize(wxSize(size_ + 2, size_ + 2));
  Refresh();
}

void SmileyButton::setFace(SmileyFace face){
  if (face == state_)
    return;

  state_ = face;
  Refresh();
}

void SmileyButton::paint(wxPaintEvent &event){
  static wxPen light_gray_pen(wxColor(0xC0, 0xC0, 0xC0, 0), 1, wxPENSTYLE_SOLID);
  static wxPen dark_gray_pen(wxColor(0x80, 0x80, 0x80, 0), 1, wxPENSTYLE_SOLID);
  static wxPen line_pen(wxColor(0x00, 0x00, 0x00, 0), 1, wxPENSTYLE_SOLID);
  static wxBrush light_gray_brush(wxColor(0xC0, 0xC0, 0xC0, 0), wxBRUSHSTYLE_SOLID);
  static wxBrush yellow_brush(wxColor(0xFF, 0xFF, 0x00, 0), wxBRUSHSTYLE_SOLID);

  wxAutoBufferedPaintDC dc(this);

  int border_thickness_ = size_ / 12;

  dc.SetBrush(light_gray_brush);
  dc.SetPen(light_gray_pen);
  dc.DrawRectangle(0, 0, size_ + 2, size_ + 2);

  dc.SetDeviceOrigin(1, 1);

  switch (state_)
  {
  case SMILEY_FACE_NORMAL:
    dc.DrawBitmap(normal_bitmap_, clicked_ ? border_thickness_ / 2 : 0, clicked_ ? border_thickness_ / 2 : 0);
    break;
  case SMILEY_FACE_CLICK:
    dc.DrawBitmap(click_bitmap_, clicked_ ? border_thickness_ / 2 : 0, clicked_ ? border_thickness_ / 2 : 0);
    break;
  case SMILEY_FACE_WIN:
    dc.DrawBitmap(win_bitmap_, clicked_ ? border_thickness_ / 2 : 0, clicked_ ? border_thickness_ / 2 : 0);
    break;
  case SMILEY_FACE_LOOSE:
    dc.DrawBitmap(loose_bitmap_, clicked_ ? border_thickness_ / 2 : 0, clicked_ ? border_thickness_ / 2 : 0);
    break;
  default:
    break;
  }

  dc.SetPen(*wxBLACK_PEN);                            //button socket
  dc.DrawLine(-1, -1, size_ + 1, -1);
  dc.DrawLine(-1, -1, -1, size_);
  dc.DrawLine(size_, size_, size_, -1);
  dc.DrawLine(size_, size_, -2, size_);


  if (clicked_){                                       //border (dependent of clicked)
    dc.SetPen(dark_gray_pen);
    for (int i = 0; i < border_thickness_; i++){
      dc.DrawLine(i, i, i, size_);
      dc.DrawLine(i, i, size_, i);
    }
  }
  else{
    dc.SetPen(*wxWHITE_PEN);
    for (int i = 0; i < border_thickness_; i++){
      dc.DrawLine(i, i, i, size_ - i - 1);
      dc.DrawLine(i, i, size_ - i - 1, i);
    }

    dc.SetPen(dark_gray_pen);
    for (int i = 0; i < border_thickness_; i++){
      dc.DrawLine(size_ - i - 1, size_ - i - 1, size_ - i - 1, i);
      dc.DrawLine(size_ - i - 1, size_ - i - 1, i, size_ - i - 1);
    }
  }
}

void SmileyButton::leftDown(wxMouseEvent &event){
  clicked_ = true;
  Refresh();
}

void SmileyButton::leftUp(wxMouseEvent &event){
  clicked_ = false;
  main_window_->newBoard();
  Refresh();
}

void SmileyButton::mouseEnter(wxMouseEvent &event){
  clicked_ = event.LeftIsDown();
  Refresh();
}

void SmileyButton::mouseLeave(wxMouseEvent &event){
  clicked_ = false;
  Refresh();
}