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
#include "CustomDialog.h"
#include "MainWindow.h"
#include "Settings.h"

CustomDialog::CustomDialog(MainWindow* parent, wxWindowID id, const wxString& title,
  const wxPoint& pos, const wxSize& size, long style)
    : CustomDialog_B(parent, id, title, pos, size, style), main_window_(parent){
  width_edit_->SetValue(parent->getSettings()->custom_width_);
  height_edit_->SetValue(parent->getSettings()->custom_height_);
  mines_edit_->SetValue(parent->getSettings()->custom_mines_);
  mines_edit_->SetRange(1, (width_edit_->GetValue() - 1) * (height_edit_->GetValue() - 1));
}

void CustomDialog::apply(wxCommandEvent& event){
  main_window_->setCustomBoardStyle(width_edit_->GetValue(), height_edit_->GetValue(), mines_edit_->GetValue());
  EndModal(0);
}

void CustomDialog::cancel(wxCommandEvent& event){
  EndModal(0);
}

void CustomDialog::OnChangeSize(wxSpinEvent& event){
  OnChangeSize();
}
void CustomDialog::OnChangeSize(wxCommandEvent& event){
  OnChangeSize();
}

void CustomDialog::OnChangeSize(){
  mines_edit_->SetRange(1, (width_edit_->GetValue() - 1) * (height_edit_->GetValue() - 1));
  if (expert_density_checkbox_->IsChecked())
    mines_edit_->SetValue(ceil(0.20625 * width_edit_->GetValue() * height_edit_->GetValue()));
}

void CustomDialog::OnSizeChoice(wxCommandEvent& event){
  const static int special_sizes[10] = { 8, 9, 16, 30, 30, 8, 9, 16, 16, 24 };
  if (size_choice_->GetSelection() < 5){
    width_edit_->SetValue(special_sizes[size_choice_->GetSelection()]);
    height_edit_->SetValue(special_sizes[5 + size_choice_->GetSelection()]);
  }
  OnChangeSize();
}

void CustomDialog::OnExpertDensityCheckbox(wxCommandEvent& event){
  if (expert_density_checkbox_->IsChecked()){
    mines_edit_->Disable();
    mines_edit_->SetValue(ceil(0.20625 * width_edit_->GetValue() * height_edit_->GetValue()));
  }
  else{
    mines_edit_->Enable();
  }
}