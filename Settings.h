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

#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "stdafx.h"
#include "My_SettingFile.h"
#include <queue>

#include "GlobalTypes.h"
#define STANDARD_SETTINGS_FILE "MySweeper.cfg"

//class which is used for loading, saving and accessing settings
class Settings{
  private:

  public:
    //game related settings
    MY::Setting<bool> question_marks_enabled_ = MY::Setting<bool>("question_marks_enabled", false);

    MY::Setting<bool> restart_doubleclick_ = MY::Setting<bool>("restart_doubleclick", false);
    MY::Setting<bool> restart_m_mouse_ = MY::Setting<bool>("restart_m_mouse", false);
    MY::Setting<bool> restart_spacebar_ = MY::Setting<bool>("restart_spacebar", false);
    MY::Setting<bool> restart_on_fail_ = MY::Setting<bool>("restart_on_fail", false);
    MY::Setting<bool> restart_on_upper_panel_ = MY::Setting<bool>("restart_on_upper_panel", false); 
    MY::Setting<bool> restart_on_click_after_delay_ = MY::Setting<bool>("restart_on_click_after_delay", false);

    MY::Setting<wxString> name_ = MY::Setting<wxString>("name", "Default Name");

    //Board related settings
    MY::Setting<int> width_ = MY::Setting<int>("width", 8);
    MY::Setting<int> height_ = MY::Setting<int>("height", 8);
    MY::Setting<int> mines_ = MY::Setting<int>("mines", 10);

    //Saving Custom default values
    MY::Setting<int> custom_width_ = MY::Setting<int>("custom_width", 30);
    MY::Setting<int> custom_height_ = MY::Setting<int>("custom_height", 16);
    MY::Setting<int> custom_mines_ = MY::Setting<int>("custom_mines", 99);

    //GUI related settings
    wxPoint position_ = wxPoint(300, 200);
    wxPoint counters_position_ = wxPoint(100,200);
    wxSize history_size_ = wxSize(800, 600);
    MY::Setting<int> square_size_ = MY::Setting<int>("square_size", 16);
    MY::Setting<bool> counters_shown_ = MY::Setting<bool>("counters_shown", true);
    MY::Setting<bool> update_counters_while_playing_ = MY::Setting<bool>("update_counters_while_playing", true);
    MY::Setting<bool> hide_counters_while_playing_ = MY::Setting<bool>("hide_counters_while_playing", false);
    MY::Setting<bool> counters_not_show_all_ = MY::Setting<bool>("counters_size", false);

    //Video settings
    MY::Setting<int> auto_save_option_ = MY::Setting<int>("auto_save_optinon", AUTO_SAVE_WON);
    MY::Setting<wxString> auto_save_location_ = MY::Setting<wxString>("auto_save_location", "/videos");
    MY::Setting<wxString> default_video_name_ = MY::Setting<wxString>("default_video_name", "$name_$style_$time.myswv");

    //Window Settings
    MY::Setting<bool> limit_window_size_ = MY::Setting<bool>("limit_window_size", false);
    MY::Setting<int> max_window_width_ = MY::Setting<int>("max_window_width", 1000);
    MY::Setting<int> max_window_height_ = MY::Setting<int>("max_window_height", 800);

    //Miscellaneous
    MY::Setting<bool> no_zini_on_big_board_ = MY::Setting<bool>("no_zini_on_big_board", false);

    Settings();
    Settings(const wxString& settings_file_name);
    ~Settings();

    void setDefault(int page = -1);   //page = -1: reset all settings, if page number given, just reset settings of this page
    void loadSettings(const wxString& settings_file_name);
    void saveSettings(const wxString& settings_file_name);

    void checkValues(bool while_loading);   //while loading another message is shown, and invalid directory is set to default
    bool checkDefaultDir(const wxString& value, bool while_loading);
    bool checkDefaultFileName(const wxString& value, bool while_loading, bool omit_dollar_char = false);    //in path '$' is valid, else it is used for accessing data (using '\' for that is no the best here)
    bool checkName(const wxString& value, bool while_loading);
};

#endif //__SETTINGS_H__