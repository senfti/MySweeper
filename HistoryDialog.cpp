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
#include "HistoryDialog.h"
#include "main.h"
#include "Settings.h"
#include <wx/stdpaths.h>

const char* HISTORY_FILE_NAME = "MySweeper.hist";

HistoryDialog::HistoryDialog(MyApp* app, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) 
  : HistoryDialog_B(parent, id, title, pos, size, style), app_(app)
{
  std::string filename = wxFileName(wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath(), HISTORY_FILE_NAME).GetFullPath().ToStdString();
  history_ = History(filename);
  
  history_grid_->SetColLabelValue(0, L"time \u25BE");     //the unicode character for the sort ascending symbol
  history_.sortItems(BOARD_STYLE_BEG, 0);
  history_.sortItems(BOARD_STYLE_INT, 0);
  history_.sortItems(BOARD_STYLE_EXP, 0);
  setValues();

  SetSize(app_->settings_->history_size_);
  SetPosition(wxPoint(100, 100));
}

HistoryDialog::~HistoryDialog(){
  app_->settings_->history_size_ = GetSize();
}

void HistoryDialog::setValues(){
  int style = style_radio_box_->GetSelection();
  int rows = history_.getItemsNumber(style);
  if (rows > history_grid_->GetNumberRows())
    history_grid_->AppendRows(rows - history_grid_->GetNumberRows());
  if (rows < history_grid_->GetNumberRows())
    history_grid_->DeleteRows(0, history_grid_->GetNumberRows() - rows);

  for (int i = 0; i < rows; i++)
    setRowValues(i, history_.getItem(style, i));

  history_grid_->AutoSize();
  Layout();
}

void HistoryDialog::setRowValues(int row, const HistoryItem& history_item){
  history_grid_->SetCellValue(row, 0, history_item.getTimeString());
  history_grid_->SetCellValue(row, 1, history_item.get3BVString());
  history_grid_->SetCellValue(row, 2, history_item.get3BVsString());
  history_grid_->SetCellValue(row, 3, history_item.getZiNiString());
  history_grid_->SetCellValue(row, 4, history_item.getZiNisString());
  history_grid_->SetCellValue(row, 5, history_item.gethZiNiString());
  history_grid_->SetCellValue(row, 6, history_item.gethZiNisString());
  history_grid_->SetCellValue(row, 7, history_item.getIOEString());
  history_grid_->SetCellValue(row, 8, history_item.getRQPString());
  history_grid_->SetCellValue(row, 9, history_item.getIOSString());
  history_grid_->SetCellValue(row,10, history_item.getClicksString());
  history_grid_->SetCellValue(row,11, history_item.getLClicksString());
  history_grid_->SetCellValue(row,12, history_item.getRClicksString());
  history_grid_->SetCellValue(row,13, history_item.getChordsString());
  history_grid_->SetCellValue(row,14, history_item.getClickssString());
  history_grid_->SetCellValue(row,15, history_item.getPathsqString());
  history_grid_->SetCellValue(row,16, history_item.getPathpxString());
  history_grid_->SetCellValue(row,17, history_item.getDateString());
}

void HistoryDialog::sort(wxGridEvent& event){
  if (sorted_column == event.GetCol()){   //if sorting on same column again, this means reverse items
    ascending = !ascending;
    history_grid_->SetColLabelValue(sorted_column, history_grid_->GetColLabelValue(sorted_column).RemoveLast() + 
      (ascending ? L"\u25BE" : L"\u25B4"));
    history_.reverseItems(BOARD_STYLE_BEG, sorted_column);
    history_.reverseItems(BOARD_STYLE_INT, sorted_column);
    history_.reverseItems(BOARD_STYLE_EXP, sorted_column);
  }
  else{
    ascending = true;
    history_grid_->SetColLabelValue(sorted_column, history_grid_->GetColLabelValue(sorted_column).RemoveLast(2));
    sorted_column = event.GetCol();
    history_grid_->SetColLabelValue(sorted_column, history_grid_->GetColLabelValue(sorted_column) + L" \u25BE");
    history_.sortItems(BOARD_STYLE_BEG, sorted_column);
    history_.sortItems(BOARD_STYLE_INT, sorted_column);
    history_.sortItems(BOARD_STYLE_EXP, sorted_column);
  }
  setValues();
}