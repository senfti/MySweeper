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
#include "VideoPlayerDialog.h"
#include "MainWindow.h"
#include "VideoPlayer.h"
#include "Images.h"

const unsigned speed_values_number = 21;    //21 different speed values, in an array for easy accessing (slider gives ints from 0 to 20)
const float speed_values[speed_values_number] = { 0.1f, 0.15f, 0.2f, 0.25f, 0.33f, 0.4f, 0.5f, 0.66f, 0.75f, 0.9f, 1.0f,
  1.1f, 1.25f, 1.33f, 1.5f, 1.75f, 2.0f, 2.5f, 3.0f, 5.0f, 10.0f };

VideoPlayerDialog::VideoPlayerDialog(VideoPlayer* video_player, MainWindow* main_window) 
  : VideoPlayerDialog_B(main_window), video_player_(video_player), main_window_(main_window),
    play_bitmap_(xpm_play), pause_bitmap_(xpm_pause), stop_bitmap_(xpm_stop){
  play_button_->SetBitmap(play_bitmap_);
  pause_button_->SetBitmap(pause_bitmap_);
  stop_button_->SetBitmap(stop_bitmap_);

  //just check this in debug mode
#if _DEBUG
  if (speed_slider_->GetMax() > (speed_values_number - 1))
    wxMessageBox("Not enough speed_values in VideoPlayerDialog.cpp\n", "Error while changing the program", wxICON_ERROR);
#endif
}

VideoPlayerDialog::~VideoPlayerDialog(){
}

void VideoPlayerDialog::play(wxCommandEvent& event){
  if (video_player_->isRunning()){      //if already running, restart
    video_player_->start(video_player_->calcTimeToPosition(0));
  }
  else{
    if (video_player_->getVideoPosition() >= 1.f || video_player_->getVideoPosition() == 0.f)   //if not running because finished / not started, also restart
      video_player_->start(0);
    else
      video_player_->resume();      //else resume (was paused)
  }
}

void VideoPlayerDialog::pause(wxCommandEvent& event){
  if (video_player_->isRunning())   //if running -> pause
    video_player_->pause();
  else if (video_player_->getVideoPosition() < 1.f && video_player_->getVideoPosition() > 0.f)   //if not running and not finished / started, also restart
    video_player_->resume();
}

void VideoPlayerDialog::stop(wxCommandEvent& event){
  time_slider_->SetValue(0);
  video_player_->stop();
}

void VideoPlayerDialog::setSpeed(wxScrollEvent& event){
  video_player_->setSpeed(speed_values[speed_slider_->GetValue()]);
  speed_text_->SetLabelText(wxString::Format(wxT("%.2fx"), speed_values[speed_slider_->GetValue()]));
}

void VideoPlayerDialog::setTime(wxScrollEvent& event){
  video_player_->stop();    //if jumping to given time (through the slider), stop first (resetting, needed if jumping backwards)
  video_player_->start(video_player_->calcTimeToPosition(static_cast<float>(time_slider_->GetValue()) / time_slider_->GetMax())); //and then start from time given
  time_text_->SetLabelText(wxString::Format(wxT("%.3f"), video_player_->getActualTime()));
}

void VideoPlayerDialog::setTimeSlider(float video_position){
  time_slider_->SetValue(video_position * time_slider_->GetMax());
  time_text_->SetLabelText(wxString::Format(wxT("%.3f"), video_player_->getActualTime()));
}

void VideoPlayerDialog::setTimeLabel(float time){
  time_text_->SetLabelText(wxString::Format(wxT("%.3f"), time));
}

void VideoPlayerDialog::show(){
  Show(true);
  //getting position in the screen
  wxPoint position;
  position.x = main_window_->GetPosition().x;
  if (main_window_->GetPosition().y >= GetSize().y)
    position.y = main_window_->GetPosition().y - GetSize().y;
  else if (main_window_->GetPosition().y + main_window_->GetSize().y + 16 < wxSystemSettings::GetMetric(wxSYS_SCREEN_Y))
    position.y = main_window_->GetPosition().y + main_window_->GetSize().y;
  else
    position.y = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) / 2;
  SetPosition(position);
  Fit();

  speed_slider_->SetValue(10);
  video_player_->setSpeed(1.f);
  time_slider_->SetValue(0);

  time_text_->SetLabelText(wxString::Format(wxT("%.3f"), 0.f));
  speed_text_->SetLabelText(wxString::Format(wxT("%.2fx"), 1.f));
  video_player_->start(0);    //if show, start video
}

void VideoPlayerDialog::show(wxString filename){
  if (!video_player_->loadVideo(filename))
    return;

  show();
  if (!video_player_->isAuthentic()){
    wxMessageBox("Video is not authentic!", "Video Authentication failed", wxICON_INFORMATION);
  }
}

void VideoPlayerDialog::show(const Video* video){
  if (!video_player_->loadVideo(video))
    return;
  show();
}

void VideoPlayerDialog::hide(){
  video_player_->endVideo();
  Show(false);
}

void VideoPlayerDialog::OnClose(wxCloseEvent& event){
  main_window_->newBoard(true);
  event.Skip();   //further processing needed
}