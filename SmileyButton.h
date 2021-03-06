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

#ifndef __SMILEY_BUTTON_H_
#define __SMILEY_BUTTON_H_

#include "stdafx.h"
#include "GlobalTypes.h"

class MainWindow;

//own class for the smiley button
class SmileyButton : public wxPanel{
private:
  //bitmaps of the different faces
  wxBitmap normal_bitmap_;
  wxBitmap click_bitmap_;
  wxBitmap win_bitmap_;
  wxBitmap loose_bitmap_;

  int size_ = 24;
  SmileyFace state_ = SMILEY_FACE_NORMAL;
  bool clicked_ = false;

  MainWindow* main_window_;

  void resizeBitmaps();

  void paint(wxPaintEvent &event);

public:
  SmileyButton(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = "smiley_button");
  ~SmileyButton();
  
  void setFace(SmileyFace face);
  void setMainWindowPointer(MainWindow* main_window){ main_window_ = main_window; }

  void resize(int size);
  void leftDown(wxMouseEvent &event);
  void leftUp(wxMouseEvent &event);
  void mouseLeave(wxMouseEvent &event);
  void mouseEnter(wxMouseEvent &event);
};

#endif //__SMILEY_BUTTON_H_