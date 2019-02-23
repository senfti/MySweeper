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
#include "HighscoreDialog.h"
#include "Highscores.h"

HighscoreDialog::HighscoreDialog(const Highscores* highscores, wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style)
    : HighscoreDialog_B(parent, id, title, pos, size, style){  
  setGridValues(highscore_grid_, &(highscores->highscores[0]));
  setGridValues(non_flagging_grid_, &(highscores->highscores[6]));
  setGridValues(flagging_grid_, &(highscores->highscores[12]));
  setCustomPageValues(highscores->custom_highscores, highscores->size_highscore_);

  formatGrid(highscore_grid_);
  formatGrid(non_flagging_grid_);
  formatGrid(flagging_grid_);
  formatCustomPage();

  for (int i = 0; i < 4; i++){
    int max_width = highscore_grid_->GetColSize(i);
    max_width = std::max(max_width, non_flagging_grid_->GetColSize(i));
    max_width = std::max(max_width, flagging_grid_->GetColSize(i));
    max_width = std::max(max_width, custom_grid_->GetColSize(i));
    max_width = std::max(max_width, size_grid_->GetColSize(i));

    highscore_grid_->SetColSize(i, max_width);
    non_flagging_grid_->SetColSize(i, max_width);
    flagging_grid_->SetColSize(i, max_width);
    custom_grid_->SetColSize(i, max_width);
    size_grid_->SetColSize(i, max_width);
    highscore_grid_->Refresh();
    non_flagging_grid_->Refresh();
    flagging_grid_->Refresh();
    custom_grid_->Refresh();
    size_grid_->Refresh();
  }
  Fit();
  SetMinSize(wxSize(GetSize().x + 5, GetSize().y + 5));
}

void HighscoreDialog::show(int page){     //page says, which page to show when dialog pops up
  notebook_->SetSelection(page);
  Show(true);                             //seems like it´s needed in wxGTK
  Show(false);
  ShowModal();
}

void HighscoreDialog::setGridValues(wxGrid* grid, const SingleHighscore* const * highscores){
  setRowValues(grid, *(highscores[0]), 1);
  setRowValues(grid, *(highscores[1]), 2);
  setRowValues(grid, *(highscores[2]), 3);
  grid->SetCellValue(4, 0, wxString::Format(wxT("%.3f"),
    (highscores[0])->time_ + highscores[1]->time_ + highscores[2]->time_));

  setRowValues(grid, *(highscores[3]), 7);
  setRowValues(grid, *(highscores[4]), 8);
  setRowValues(grid, *(highscores[5]), 9);
  grid->SetCellValue(10, 2, wxString::Format(wxT("%.3f"),
    (highscores[3])->bbbvs_ + highscores[4]->bbbvs_ + highscores[5]->bbbvs_));
}

void HighscoreDialog::setRowValues(wxGrid* grid, const SingleHighscore& highscore, int row){
  grid->SetCellValue(row, 0, wxString::Format(wxT("%.3f"), highscore.time_));
  grid->SetCellValue(row, 1, wxString::Format(wxT("%d"), highscore.bbbv_));
  grid->SetCellValue(row, 2, wxString::Format(wxT("%.3f"), highscore.bbbvs_));
  grid->SetCellValue(row, 3, highscore.date_.Format("%Y-%m-%d %X"));
  grid->AutoSize();
  Fit();
}

void HighscoreDialog::formatGrid(wxGrid* grid){
  grid->AutoSize();
  grid->SetCellHighlightPenWidth(0);
  grid->SetCellBackgroundColour(5, 0, highscore_grid_->GetLabelBackgroundColour());
  grid->SetCellBackgroundColour(5, 1, highscore_grid_->GetLabelBackgroundColour());
  grid->SetCellBackgroundColour(5, 2, highscore_grid_->GetLabelBackgroundColour());
  grid->SetCellBackgroundColour(5, 3, highscore_grid_->GetLabelBackgroundColour());

  grid->SetCellBackgroundColour(1, 0, wxColor(0xa0, 0xff, 0xa0));
  grid->SetCellBackgroundColour(2, 0, wxColor(0xa0, 0xff, 0xa0));
  grid->SetCellBackgroundColour(3, 0, wxColor(0xa0, 0xff, 0xa0));
  grid->SetCellBackgroundColour(4, 0, wxColor(0xa0, 0xff, 0xa0));
  grid->SetCellBackgroundColour(7, 2, wxColor(0xa0, 0xff, 0xa0));
  grid->SetCellBackgroundColour(8, 2, wxColor(0xa0, 0xff, 0xa0));
  grid->SetCellBackgroundColour(9, 2, wxColor(0xa0, 0xff, 0xa0));
  grid->SetCellBackgroundColour(10, 2, wxColor(0xa0, 0xff, 0xa0));
  Fit();
}

void HighscoreDialog::setCustomPageValues(const CustomHighscore* const * custom_highscores, const SizeHighscore& size_highscore){
  for (int i = 0; i < 5; i++){
    custom_grid_->SetCellValue(i, 0, wxString::Format(wxT("%d"), custom_highscores[i]->mines_));
    custom_grid_->SetCellValue(i, 1, wxString::Format(wxT("%.3f"), custom_highscores[i]->time_));
    custom_grid_->SetCellValue(i, 2, wxString::Format(wxT("%d"), custom_highscores[i]->bbbv_));
    custom_grid_->SetCellValue(i, 3, custom_highscores[i]->date_.Format("%Y-%m-%d %X"));
  }
  custom_grid_->SetCellValue(5, 0, wxString::Format(wxT("%d"), custom_highscores[0]->mines_ + custom_highscores[1]->mines_
    + custom_highscores[2]->mines_ + custom_highscores[3]->mines_ + custom_highscores[4]->mines_));
  custom_grid_->AutoSize();
  Fit();

  size_grid_->SetCellValue(0, 0, wxString::Format(wxT("%d"), size_highscore.size_));
  size_grid_->SetCellValue(0, 1, wxString::Format(wxT("%.3f"), size_highscore.time_));
  size_grid_->SetCellValue(0, 2, wxString::Format(wxT("%d"), size_highscore.bbbv_));
  size_grid_->SetCellValue(0, 3, size_highscore.date_.Format("%Y-%m-%d %X"));
  size_grid_->AutoSize();
  Fit();
}

void HighscoreDialog::formatCustomPage(){
  custom_grid_->AutoSize();
  custom_grid_->SetCellHighlightPenWidth(0);
  custom_grid_->SetCellBackgroundColour(0, 0, wxColor(0xa0, 0xff, 0xa0));
  custom_grid_->SetCellBackgroundColour(1, 0, wxColor(0xa0, 0xff, 0xa0));
  custom_grid_->SetCellBackgroundColour(2, 0, wxColor(0xa0, 0xff, 0xa0));
  custom_grid_->SetCellBackgroundColour(3, 0, wxColor(0xa0, 0xff, 0xa0));
  custom_grid_->SetCellBackgroundColour(4, 0, wxColor(0xa0, 0xff, 0xa0));
  custom_grid_->SetCellBackgroundColour(5, 0, wxColor(0xa0, 0xff, 0xa0));

  size_grid_->AutoSize(); 
  size_grid_->SetCellHighlightPenWidth(0);
  size_grid_->SetCellBackgroundColour(0, 0, wxColor(0xa0, 0xff, 0xa0));
}

void HighscoreDialog::OnOk(wxCommandEvent& event){
  EndModal(0);
}
