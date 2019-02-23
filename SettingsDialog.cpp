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
#include "SettingsDialog.h"
#include "MainWindow.h"
#include "Settings.h"

SettingsDialog::SettingsDialog(Settings* settings, MainWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos,
  const wxSize& size, long style) 
    : SettingsDialog_B(parent, id, title, pos, size, style), main_window_(parent), settings_(settings){
  updateGuiElementValues();
}

void SettingsDialog::cancel(wxCommandEvent& event){
  EndModal(0);
}

void SettingsDialog::updateGuiElementValues(){
  //setting all gui elements to the right values
  questionmark_checkbox_->SetValue(settings_->question_marks_enabled_);
  restart_doubleclick_checkbox_->SetValue(settings_->restart_doubleclick_);
  restart_m_mouse_checkbox_->SetValue(settings_->restart_m_mouse_);
  restart_spacebar_checkbox_->SetValue(settings_->restart_spacebar_);
  restart_on_fail_checkbox_->SetValue(settings_->restart_on_fail_);
  update_counters_checkbox_->SetValue(settings_->update_counters_while_playing_);
  hide_counters_until_finished_checkbox_->SetValue(settings_->hide_counters_while_playing_);
  name_edit_->SetValue(settings_->name_);
  auto_save_radio_box_->SetSelection(settings_->auto_save_option_);
  auto_save_dir_picker_->SetPath(settings_->auto_save_location_);
  default_file_name_edit_->SetValue(settings_->default_video_name_);
  restart_on_upper_panel_checkbox_->SetValue(settings_->restart_on_upper_panel_);
  restart_on_click_after_delay_checkbox_->SetValue(settings_->restart_on_click_after_delay_);
  limit_size_checkbox_->SetValue(settings_->limit_window_size_);
  max_width_edit_->SetValue(settings_->max_window_width_);
  max_height_edit_->SetValue(settings_->max_window_height_);
  counters_size_radiobox_->SetSelection(settings_->counters_not_show_all_);

  max_width_edit_->Enable(limit_size_checkbox_->GetValue());
  max_height_edit_->Enable(limit_size_checkbox_->GetValue());
  no_zini_checkbox_->SetValue(settings_->no_zini_on_big_board_);
}

//sets settings to default plus updating all gui elements
void SettingsDialog::setDefault(wxCommandEvent& event){  
  settings_->setDefault(notebook_->GetSelection());

  updateGuiElementValues();
}

//checks if everything is valid and then changes the settings
void SettingsDialog::apply(){
  if (!settings_->checkDefaultFileName(default_file_name_edit_->GetValue(), false, false)){
    return;
  }
  if (!settings_->checkDefaultDir(auto_save_dir_picker_->GetPath(), false)){
    return;
  }
  if (!wxFileName(auto_save_dir_picker_->GetPath()).Exists()){
    if (wxMessageBox("Auto save path does not exist.\nCreate this path?", "Settings Information", wxYES_NO) == wxYES){
      if (!wxFileName(auto_save_dir_picker_->GetPath(), "dummy").Mkdir(wxS_DIR_DEFAULT)){
        wxMessageBox("Could not create this path", "SettingsError", wxICON_ERROR);
        return;
      }
    }
    else
      return;
  }
  settings_->question_marks_enabled_ = questionmark_checkbox_->GetValue();
  settings_->restart_doubleclick_ = restart_doubleclick_checkbox_->GetValue();
  settings_->restart_m_mouse_ = restart_m_mouse_checkbox_->GetValue();
  settings_->restart_spacebar_ = restart_spacebar_checkbox_->GetValue();
  settings_->restart_on_fail_ = restart_on_fail_checkbox_->GetValue();
  settings_->update_counters_while_playing_ = update_counters_checkbox_->GetValue();
  settings_->hide_counters_while_playing_ = hide_counters_until_finished_checkbox_->GetValue();
  settings_->name_ = name_edit_->GetValue();
  settings_->auto_save_option_ = auto_save_radio_box_->GetSelection();
  settings_->auto_save_location_ = auto_save_dir_picker_->GetPath();
  settings_->default_video_name_ = default_file_name_edit_->GetValue();
  settings_->restart_on_upper_panel_ = restart_on_upper_panel_checkbox_->GetValue();
  settings_->restart_on_click_after_delay_ = restart_on_click_after_delay_checkbox_->GetValue();
  settings_->limit_window_size_ = limit_size_checkbox_->GetValue();
  settings_->max_window_width_ = max_width_edit_->GetValue();
  settings_->max_window_height_ = max_height_edit_->GetValue();
  settings_->counters_not_show_all_ = !!counters_size_radiobox_->GetSelection();
  settings_->no_zini_on_big_board_ = no_zini_checkbox_->GetValue();
}

void SettingsDialog::apply(wxCommandEvent& event){
  apply();
}

void SettingsDialog::ok(wxCommandEvent& event){
  apply();
  EndModal(0);
}

void SettingsDialog::OnNameText(wxCommandEvent& event){
  //immediate validation of the name
  if (!settings_->checkName(name_edit_->GetValue(), false)){
    name_edit_->SetValue(name_edit_->GetValue().RemoveLast());
  }
}

void SettingsDialog::OnFileText(wxCommandEvent& event){
  //immediate validation of the file name
  if (!settings_->checkDefaultFileName(default_file_name_edit_->GetValue(), false, true)){
    default_file_name_edit_->SetValue(default_file_name_edit_->GetValue().RemoveLast());
  }
}

void SettingsDialog::EnableWindowLimits(wxCommandEvent& event){
  max_width_edit_->Enable(limit_size_checkbox_->GetValue());
  max_height_edit_->Enable(limit_size_checkbox_->GetValue());
}