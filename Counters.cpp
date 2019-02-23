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
#include "Counters.h"
#include "main.h"
#include "MainWindow.h"
#include "Settings.h"

//list of show stats texts
const std::vector<wxString> COUNTERS_TEXTS = { "Time", "Est.time", "3BV", "3BV/s", "ZiNi", "ZiNi/s", "HZiNi", "HZiNi/s", "NF", "IOE", "RQP", "IOS",
"Clicks", "Left", "Right", "Chord", "Clicks/s", "Path[squares]", "Path[pixel]" };

Counters::Counters(MyApp* app, const BoardStats* stats) 
    : Counters_B(app->main_window_), app_(app), stats_(stats), timer_(this){
  counters_grid_->SetCellHighlightPenWidth(0);
  counters_grid_->SetDoubleBuffered(true);    //flicker free

  shown_ = app_->settings_->counters_shown_;
  if (shown_)
    showCounters();

  setSize(!app_->settings_->counters_not_show_all_);    //if the limited counter view is selected

  Connect(timer_.GetId(), wxEVT_TIMER, wxTimerEventHandler(Counters::OnTimer), NULL, this);
}

void Counters::setStats(const BoardStats* stats){
  stats_ = stats;
}

void Counters::OnTimer(wxTimerEvent& event){
  if (shown_)
    updateCounters();
}

void Counters::showCounters(bool show){
  if (show){
    //positioning, set to different values, if the counters would be displayed outside the screen
    if (app_->settings_->counters_position_.x >= 0 && 
        app_->settings_->counters_position_.x < wxSystemSettings::GetMetric(wxSYS_SCREEN_X) - 32 &&
        app_->settings_->counters_position_.y >= 0 &&
        app_->settings_->counters_position_.y < wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) - 32){
      SetPosition(app_->settings_->counters_position_);
    }
    else if (app_->main_window_->GetPosition().x > 50 && app_->main_window_->GetPosition().y >= 0)
      SetPosition(wxPoint(app_->main_window_->GetPosition().x - GetSize().x - 16, app_->main_window_->GetPosition().y));
    else if (app_->main_window_->GetPosition().x < wxSystemSettings::GetMetric(wxSYS_SCREEN_X) - 50 
        && app_->main_window_->GetPosition().y >= 0)
        SetPosition(wxPoint(app_->main_window_->GetPosition().x + app_->main_window_->GetSize().x + 16, 
          app_->main_window_->GetPosition().y));
    else
      SetPosition(wxPoint(0,0));

    ShowWithoutActivating();
    counters_grid_->SetCellValue(0, 1, "9999/9999");      //wxGTK needs this to adjst size after show
    counters_grid_->AutoSize();
    Fit();
    Show(false);                                          //strange behavior but it´s needed in wxGTK because Fit() doesn´t work else
    ShowWithoutActivating();
  }
  else{
    Show(false);
    app_->settings_->counters_position_ = GetPosition();
  }
  
  shown_ = show; 

  updateCounters();
}

void Counters::setSize(bool full){
  int rows = full ? COUNTERS_TEXTS.size() : 4;        //show all or just time, est. time, 3bv and 3bv/s, if set so
  if (rows > counters_grid_->GetNumberRows())        //easy change of number of values possible (no change in Counter_B.cpp needed)
    counters_grid_->AppendRows(rows - counters_grid_->GetNumberRows());
  else if (rows < counters_grid_->GetNumberRows())
    counters_grid_->DeleteRows(rows - 1, counters_grid_->GetNumberRows() - rows);

  for (int i = 0; i < rows; i++)
    counters_grid_->SetCellValue(i, 0, COUNTERS_TEXTS[i]);

  counters_grid_->SetCellValue(0, 1, "9999/9999");
  counters_grid_->AutoSize();
  Fit();
  updateCounters();
}

void Counters::startCounters(){
  timer_.Start(50);
  watch_.Start();
  updateCounters();
}

void Counters::stopCounters(){
  timer_.Stop();
}

void Counters::updateCounters(long video_time){
  if (app_->board_->getBoardStatus() == BOARD_STATUS_STARTED && !app_->settings_->update_counters_while_playing_)
    return;

  float time = video_time / 1000.f;
  if (video_time == -1)
    time = (app_->board_->getBoardStatus() == BOARD_STATUS_STARTED ? watch_.Time() : stats_->time_) / 1000.f;
  float clicks_per_sec = app_->board_->isRunning() ? stats_->getClicks() / time : stats_->getClicksPerSecond();
  
  wxGridUpdateLocker grid_update_locker(counters_grid_);      //no update until this is destroyed

  counters_grid_->SetCellValue(0, 1, wxString::Format(wxT("%.3f"), time)); 
  counters_grid_->SetCellValue(1, 1, wxString::Format(wxT("%.3f"), stats_->estimated_time_));
  counters_grid_->SetCellValue(2, 1,
    wxString::Format(wxT("%d"), stats_->solved_3BV_) + "/" + wxString::Format(wxT("%d"), stats_->bbbv_));
  counters_grid_->SetCellValue(3, 1, wxString::Format(wxT("%.3f"), stats_->bbbvs_));
  if (counters_grid_->GetNumberRows() > 4){
    counters_grid_->SetCellValue(4, 1, wxString::Format(wxT("%d"), stats_->ZiNi_));
    counters_grid_->SetCellValue(5, 1, wxString::Format(wxT("%.3f"), stats_->ZiNis_));
    counters_grid_->SetCellValue(6, 1, wxString::Format(wxT("%d"), stats_->hZiNi_));
    counters_grid_->SetCellValue(7, 1, wxString::Format(wxT("%.3f"), stats_->hZiNis_));
    counters_grid_->SetCellValue(8, 1, stats_->getNonFlagging() ? "Yes" : "No");
    counters_grid_->SetCellValue(9, 1, wxString::Format(wxT("%.3f"), stats_->ioe_));
    counters_grid_->SetCellValue(10, 1, wxString::Format(wxT("%.3f"), stats_->rqp_));
    counters_grid_->SetCellValue(11, 1, wxString::Format(wxT("%.3f"), stats_->ios_));
    counters_grid_->SetCellValue(12, 1, wxString::Format(wxT("%d"), stats_->getClicks()));
    counters_grid_->SetCellValue(13, 1, wxString::Format(wxT("%d"), stats_->left_clicks_));
    counters_grid_->SetCellValue(14, 1, wxString::Format(wxT("%d"), stats_->right_clicks_));
    counters_grid_->SetCellValue(15, 1, wxString::Format(wxT("%d"), stats_->chord_clicks_));
    counters_grid_->SetCellValue(16, 1, wxString::Format(wxT("%.3f"), clicks_per_sec));
    counters_grid_->SetCellValue(17, 1, wxString::Format(wxT("%.1f"), stats_->path_));
    counters_grid_->SetCellValue(18, 1, wxString::Format(wxT("%.0f"), stats_->path_ * app_->main_window_->getSquareSize()));
  }
}
