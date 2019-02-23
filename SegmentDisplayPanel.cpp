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
#include "SegmentDisplayPanel.h"

SegmentDisplayPanel::SegmentDisplayPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos,
  const wxSize& size, long style, const wxString& name)
  : wxPanel(parent, id, pos, size, style, name){
  SetBackgroundStyle(wxBG_STYLE_PAINT);   //for double buffered drawing
 
  Connect(wxEVT_PAINT, wxPaintEventHandler(SegmentDisplayPanel::paint), NULL, this);
}

SegmentDisplayPanel::~SegmentDisplayPanel(){
  Disconnect(wxEVT_PAINT, wxPaintEventHandler(SegmentDisplayPanel::paint), NULL, this);
}

void SegmentDisplayPanel::setValue(int value){
  value_ = value; 
  Refresh();    //repaint after value change
}

void SegmentDisplayPanel::paint(wxPaintEvent &event){
  wxAutoBufferedPaintDC dc(this);
  
  int width = GetClientSize().GetX();
  int height = GetClientSize().GetY();
  int line_width = width / 5 + 1;
  int space_width = width / 12;
  int half_space_width_down = width / 32 + 1;
  int half_space_width_up = (width + 12) / 32 + 1;

  wxPen dot_dark_red(wxPen(wxColor(width > 20 ? 0x350/width + 0x20: 0x50, 0, 0, 0), 1, wxPENSTYLE_BDIAGONAL_HATCH));
  wxPen normal_red(wxPen(wxColor(0xff, 0, 0, 0), 1, wxPENSTYLE_SOLID));

  dc.SetBrush(*wxBLACK_BRUSH);
  dc.SetPen(*wxBLACK_PEN);
  dc.DrawRectangle(0, 0, width, height);

  if (value_ == 1 || value_ == 2 || value_ == 3 || value_ == 7 || value_ == -1)                      //left upper line
    dc.SetPen(dot_dark_red);
  else 
    dc.SetPen(normal_red);
  for (int i = space_width; i < line_width + space_width; i++)
    dc.DrawLine(i, i + half_space_width_down, i, height / 2 - i + 2 - half_space_width_down);

  if (value_ == 1 || value_ == 3 || value_ == 4 || value_ == 5 || value_ == 7 || value_ == 9 || value_ == -1)  //left lower line
    dc.SetPen(dot_dark_red);
  else
    dc.SetPen(normal_red);
  for (int i = space_width; i < line_width + space_width; i++)
    dc.DrawLine(i, height / 2 + i - 1 + half_space_width_down, i, height - i - half_space_width_down);

  if (value_ == 5 || value_ == 6 || value_ == -1)                                                   //rigth upper line
    dc.SetPen(dot_dark_red);
  else
    dc.SetPen(normal_red);
  for (int i = space_width; i < line_width + space_width; i++)
    dc.DrawLine(width - i - 1, i + half_space_width_down, width - i - 1, height / 2 - i + 2 - half_space_width_down);

  if (value_ == 2 || value_ == -1)                                                                  //rigth lower line
    dc.SetPen(dot_dark_red);
  else
    dc.SetPen(normal_red);
  for (int i = space_width; i < line_width + space_width; i++)
    dc.DrawLine(width - i - 1, height / 2 + i - 1 + half_space_width_down, width - i - 1, height - i - half_space_width_down);

  if (value_ == 1 || value_ == 4 || value_ == -1)                                                   //upper line
    dc.SetPen(dot_dark_red);
  else
    dc.SetPen(normal_red);
  for (int i = space_width; i < line_width + space_width; i++)
    dc.DrawLine(i + half_space_width_up, i, width - i - half_space_width_up, i);

  if (value_ == 1 || value_ == 4 || value_ == 7 || value_ == -1)                                    //lower line
    dc.SetPen(dot_dark_red);
  else
    dc.SetPen(normal_red);
  for (int i = space_width; i < line_width + space_width; i++)
    dc.DrawLine(i + half_space_width_up, height - i - 1, width - i - half_space_width_up, height - i - 1);

  if (value_ == 1 || value_ == 7 || value_ == 0)                                                    //middle line
    dc.SetPen(dot_dark_red);
  else
    dc.SetPen(normal_red);
  dc.DrawLine(space_width + half_space_width_up, height / 2, width - space_width - half_space_width_up, height / 2);
  for (int i = 0; i < line_width / 1.4 - 0.4; i++){
    dc.DrawLine(i + space_width + half_space_width_up, height / 2 + i, width - i - space_width - half_space_width_up, height / 2 + i);
    dc.DrawLine(i + space_width + half_space_width_up, height / 2 - i, width - i - space_width - half_space_width_up, height / 2 - i);
  }
}