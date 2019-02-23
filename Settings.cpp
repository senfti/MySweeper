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
#include "Settings.h"
#include <wx/stdpaths.h>

const wxString error_texts[12] = { "", "File not found", "IO error", "Saving error", "Not enough memory",
  "Parsing error", "File not loaded correctly", "Attribute missing", "Node missing", "Wrong attribute type",
  "Not enough attribute names", "Writing error" };

Settings::Settings(){
  setDefault();
  wxString filename = wxFileName(wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath(), STANDARD_SETTINGS_FILE).GetFullPath();
  loadSettings(filename);
}

Settings::Settings(const wxString& settings_file_name){
  setDefault();
  loadSettings(settings_file_name);
}

Settings::~Settings(){
  wxString filename = wxFileName(wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath(), STANDARD_SETTINGS_FILE).GetFullPath();
  saveSettings(filename);
}

void Settings::loadSettings(const wxString& settings_file_name){
  if (!wxFileName(settings_file_name).Exists())
    return;

  //settings are stored in an .ini file
  MY::IniFileIn file(settings_file_name.ToStdString());
  if(file.isError()){    
    wxMessageBox("Could not open \"" + settings_file_name + "\"!\nReason: " + error_texts[file.popError()] +
      "\nUsing default settings!", "Settings Loading Error", wxICON_ERROR);
    if (file.isError())
      file.popError();
    return;
  }

  //loading all values
  file.getValue(question_marks_enabled_);
  file.getValue(restart_doubleclick_);
  file.getValue(restart_m_mouse_);
  file.getValue(restart_spacebar_);
  file.getValue(restart_on_fail_);
  file.getValue(restart_on_upper_panel_);
  file.getValue(restart_on_click_after_delay_);
  file.getValue(counters_shown_);
  file.getValue(update_counters_while_playing_);
  file.getValue(hide_counters_while_playing_);
  file.getValue(counters_not_show_all_);
  file.getValue(width_);
  file.getValue(height_);
  file.getValue(mines_);
  file.getValue(custom_width_);
  file.getValue(custom_height_);
  file.getValue(custom_mines_);
  file.getValue(square_size_);
  file.getValues(MY::getIndexedAttrNames("window_position", 2, MY::INDEX_WITH_x_y_z_w), position_.x, position_.y);
  file.getValues(MY::getIndexedAttrNames("counters_position", 2, MY::INDEX_WITH_x_y_z_w), counters_position_.x, counters_position_.y);
  file.getValue(name_);
  file.getValue(auto_save_option_);
  file.getValue(auto_save_location_);
  file.getValue(default_video_name_);
  file.getValue(limit_window_size_);
  file.getValue(max_window_width_);
  file.getValue(max_window_height_);
  file.getValue(no_zini_on_big_board_);
  file.getValues(MY::getIndexedAttrNames("history_size", 2, MY::INDEX_WITH_x_y_z_w), history_size_.x, history_size_.y);

  //check, if every item could be loaded
  if(file.isError()){    
    wxMessageBox("Settings file incomplete (maybe old version).\nMissing settings are set to default", 
      "Settings Loading Warning", wxICON_INFORMATION);
    if (file.isError())
      file.popError();
    return;
  }

  //check, if values are valid
  checkValues(true);
}

void Settings::saveSettings(const wxString& settings_file_name){
  //settings are stored in an .ini file
  MY::IniFileOut file(settings_file_name.ToStdString());
  if (file.isError()){
    wxMessageBox("Could not open \"" + settings_file_name + "\"!\nReason: " + error_texts[file.popError()] +
      "\nUsing default settings!", "Settings Saving Error", wxICON_ERROR);
    if (file.isError())
      file.popError();
    return;
  }

  //save settings (not written into the file yet, just in the class)
  file.setValue(question_marks_enabled_);
  file.setValue(restart_doubleclick_);
  file.setValue(restart_m_mouse_);
  file.setValue(restart_spacebar_);
  file.setValue(restart_on_fail_);
  file.setValue(restart_on_upper_panel_);
  file.setValue(restart_on_click_after_delay_);
  file.setValue(counters_shown_);
  file.setValue(update_counters_while_playing_);
  file.setValue(hide_counters_while_playing_);
  file.setValue(counters_not_show_all_);
  file.setValue(width_);
  file.setValue(height_);
  file.setValue(mines_);
  file.setValue(custom_width_);
  file.setValue(custom_height_);
  file.setValue(custom_mines_);
  file.setValue(square_size_);
  file.setValues(MY::getIndexedAttrNames("window_position", 2, MY::INDEX_WITH_x_y_z_w), position_.x, position_.y);
  file.setValues(MY::getIndexedAttrNames("counters_position", 2, MY::INDEX_WITH_x_y_z_w), counters_position_.x, counters_position_.y);
  file.setValue(name_);
  file.setValue(auto_save_option_);
  file.setValue(auto_save_location_);
  file.setValue(default_video_name_);
  file.setValue(limit_window_size_);
  file.setValue(max_window_width_);
  file.setValue(max_window_height_);
  file.setValue(no_zini_on_big_board_);
  file.setValues(MY::getIndexedAttrNames("history_size", 2, MY::INDEX_WITH_x_y_z_w), history_size_.x, history_size_.y);

  //check for errors
  if (file.isError()){
    wxMessageBox("Error while saving settings", "Settings Saving Warning", wxICON_ERROR);
    if (file.isError())
      file.popError();
    return;
  }

  //this saves settings to file
  file.save(settings_file_name.ToStdString());

  if (file.isError()){
    wxMessageBox("Error while saving settings. No settings are saved", "Settings Saving Warning", wxICON_ERROR);
    if (file.isError())
      file.popError();
    return;
  }
}

void Settings::setDefault(int page){
  if (page == -1 || page == 0){
    question_marks_enabled_ = false;
    restart_doubleclick_ = false;
    restart_m_mouse_ = false;
    restart_spacebar_ = false;
    restart_on_fail_ = false;

    name_ = "DefaultName";
    update_counters_while_playing_ = true;
    hide_counters_while_playing_ = false;
    restart_on_upper_panel_ = false;
    restart_on_click_after_delay_ = false;
  }
  if (page == -1 || page == 1){
    auto_save_option_ = AUTO_SAVE_WON;
    //auto save location is video folder in the executable path
    auto_save_location_ = wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath() + wxFileName::GetPathSeparator() + "videos";
    default_video_name_ = "$name_$style_$time.myswv";
  }
  if (page == -1 || page == 2){
    limit_window_size_ = false;
    max_window_width_ = 1000;
    max_window_height_ = 800;
    counters_not_show_all_ = false;
    no_zini_on_big_board_ = false;
  }
  if (page == -1){
    position_ = wxPoint(300, 200);
    counters_position_ = wxPoint(100, 200);
    history_size_ = wxSize(800, 600);
    square_size_ = 16;
    counters_shown_ = true;
  }
}

bool Settings::checkDefaultDir(const wxString& value, bool while_loading){
  wxString wxtemp = wxFileName().GetForbiddenChars();   //get characters forbidden in directory path

  //these is for windows (it says they are forbidden but actually are not)
  if (wxtemp.Find('\\') != wxNOT_FOUND)
    wxtemp.Remove(wxtemp.Find('\\'), 1);
  if (wxtemp.Find('/') != wxNOT_FOUND)
    wxtemp.Remove(wxtemp.Find('/'), 1);
  if (wxtemp.Find(':') != wxNOT_FOUND)
    wxtemp.Remove(wxtemp.Find(':'), 1);

  //if a forbidden character is in the directory path
  if (value.find_first_of(wxtemp) != wxNOT_FOUND){
    wxString message = "Default video location \"" + value + "\"is not valid on this platform!: Forbidden characters (" + wxtemp + ")";
    if (while_loading){
      //when happening while loading, set to default
      auto_save_location_ = wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath() + wxFileName::GetPathSeparator() + "videos";
      message += "\nLocation is set to default \"" + auto_save_location_ + "\"";
      if (!(wxFileName(auto_save_location_, "dummy").DirExists())){   //looks strange, there is no dummy file generated, just a trick to make the directory
        wxFileName(auto_save_location_, "dummy").Mkdir(wxS_DIR_DEFAULT);
      }
    }
    wxMessageBox(message, "Settings Warning", wxICON_INFORMATION);
    return false;
  }
  return true;
}

bool Settings::checkDefaultFileName(const wxString& value, bool while_loading, bool omit_dollar_char){
  wxString wxtemp = wxFileName().GetForbiddenChars();
  if (wxtemp.Find('/') == wxNOT_FOUND)    //add '/' and '\', because they are valid for path, but not for the filename
    wxtemp += '/';
  if (wxtemp.Find('\\') == wxNOT_FOUND)
    wxtemp += '\\';

  if (!omit_dollar_char && value.Find('$') && wxtemp.Find('$')){           //if in value and forbidden
    for (int i = 0; i < value.Length() - 1; i++){   //here checking, if '$' is used right
      if (value[i] == '$' &&
        (value.Find("name") != i + 1 && value.Find("time") != i + 1 &&
        value.Find("style") != i + 1 && value.Find("3bv") != i + 1))
      {
        wxMessageBox("Default video name \"" + value + "\"is not valid on this platform: Unknown tag and character \'$\' forbidden");
        return false;
      }
    }
  }
  if (wxtemp.Find('$') != wxNOT_FOUND)           //$ was checked before or omitted
    wxtemp.Remove(wxtemp.Find('$'), 1);

  //check rest of forbidden chars
  if (value.find_first_of(wxtemp) != wxNOT_FOUND){
    wxString message = "Default file name \"" + value + "\"is not valid on this platform : Forbidden characters (" + wxtemp + ")";
    if (while_loading)
      message += "\nDefault file name is set to default \"/videos\"";
    wxMessageBox(message, "Warning", wxICON_INFORMATION);
    return false;
  }

  return true;
}

bool Settings::checkName(const wxString& value, bool while_loading){
  wxString wxtemp = wxFileName().GetForbiddenChars() + '$'; //no '$' in name allowed, because then problems in default name possible

  if (value.find_first_of(wxtemp) != wxNOT_FOUND){
    wxString message = "Name \"" + value + "\"is not valid on this platform : Forbidden characters (" + wxtemp + ")";
    if (while_loading)
      message += "\nName is set to default \"DefaultName\"";
    wxMessageBox(message, "Warning", wxICON_INFORMATION);
    return false;
  }
  return true;
}

void Settings::checkValues(bool while_loading){
  wxString label_text;
  if (while_loading)
    label_text = "Settings Loading Warning";
  else
    label_text = "Settings Warning";

  if (!checkDefaultDir(auto_save_location_.getValue(), while_loading))
    auto_save_location_ = wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath() + wxFileName::GetPathSeparator() + "videos";

  if (!checkDefaultFileName(default_video_name_.getValue(), while_loading))
    default_video_name_ = "$name_$style_$time.myswv";

  if (!checkName(name_.getValue(), while_loading))
    name_ = "DefaultName";

  //check if auto save directory exists
  if (!(wxFileName(auto_save_location_, "dummy").DirExists())){
    wxString message = "Default video location \"" + auto_save_location_ + "\"does not exist!\n";
    auto_save_location_ = wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath() + wxFileName::GetPathSeparator() + "videos";
    wxMessageBox(message + "Location is set to default \""+ auto_save_location_ + "\"", label_text, wxICON_INFORMATION);
    if (!(wxFileName(auto_save_location_, "dummy").DirExists()))
      wxFileName(auto_save_location_, "dummy").Mkdir(wxS_DIR_DEFAULT);
  }
}