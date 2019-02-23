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

#ifndef __SETTINGSDIALOG_H__
#define __SETTINGSDIALOG_H__

#include "stdafx.h"
#include "SettingsDialog_B.h"

class MainWindow;
class Board;
class Settings;

//class for the settings dialog
class SettingsDialog : public SettingsDialog_B{
  private:
    MainWindow* main_window_;
    Settings* settings_;

    void cancel(wxCommandEvent& event);
    void setDefault(wxCommandEvent& event);
    void apply();                           //set the values, but does not close the dialog (version needing no event)
    void apply(wxCommandEvent& event);      //set the values, but does not close the dialog
    void ok(wxCommandEvent& event);
    void OnNameText(wxCommandEvent& event);
    void OnFileText(wxCommandEvent& event);
    void EnableWindowLimits(wxCommandEvent& event);

    void updateGuiElementValues();

  public:
    SettingsDialog(Settings* settings, MainWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Settings"),
      const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
      long style = wxCAPTION | wxCLOSE_BOX | wxSTAY_ON_TOP | wxSYSTEM_MENU);

    //while playing videos, question mark settings change lead to problems -> so not possible
    void enableQuestionMarkSetting(bool enable){ questionmark_checkbox_->Enable(enable); }
};

#endif //__SETTINGSDIALOG_H__