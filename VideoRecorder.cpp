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
#include "VideoRecorder.h"
#include "main.h"
#include "Settings.h"
#include "MainWindow.h"

VideoRecorder::VideoRecorder(MyApp* app) : app_(app), video_(nullptr){
}

VideoRecorder::~VideoRecorder(){
  delete video_;
}

void VideoRecorder::startRecording(const Board* board){
  app_->main_window_->actiatePreview(false);
  //delete old video and create new
  delete video_;
  try{
    video_ = new Video(board);
  }
  catch (std::bad_alloc& exception){
    record_ = false;
    return;
  }
  record_ = true;
  addAdditionalEvent(AdditionalEvent(ADDITIONAL_EVENT_QUESTIONMARK_SET,     //first a question mark event to be sure, it is set right
    app_->board_->getTime(), app_->settings_->question_marks_enabled_));
}

void VideoRecorder::stopRecording(bool video_correct){
  record_ = false;
  video_->setCorrect(video_correct);
  if (!video_correct)
    return;

  video_->setTime(app_->board_->getStats()->time_);
  app_->main_window_->actiatePreview(true);

  wxFileName filename(app_->settings_->auto_save_location_, app_->settings_->default_video_name_);

  //do autosaving, if it´s needed
  if (app_->settings_->auto_save_option_ == AUTO_SAVE_ALL)
    saveVideo(filename.GetFullPath());
  if (app_->settings_->auto_save_option_ == AUTO_SAVE_WON && app_->board_->getBoardStatus() == BOARD_STATUS_WON)
    saveVideo(filename.GetFullPath());
  if (app_->settings_->auto_save_option_ == AUTO_SAVE_HIGHSCORES && app_->board_->getStats()->is_record_)
    saveVideo(filename.GetFullPath());
}

void VideoRecorder::addBoardEvent(BoardEvent board_event){
  if (record_){
    video_->addBoardEvent(board_event);
  }
}

void VideoRecorder::addMousePosition(MousePosition mouse_position){
  if (record_){
    video_->addMousePosition(mouse_position);
  }
}

void VideoRecorder::addAdditionalEvent(AdditionalEvent additional_event){
  video_->addAdditionalEvent(additional_event);
}

bool VideoRecorder::saveVideo(wxString filename){
  //generating the video name
  filename.Replace("$name", app_->settings_->name_.getValue());
  filename.Replace("$time", wxString::Format("%.3f", static_cast<float>(app_->board_->getStats()->time_) / 1000));
  filename.Replace("$3bv", wxString::Format("%d", app_->board_->getStats()->bbbv_));
  filename.Replace("$style", app_->board_->getStyleString());

  if (wxFileName(filename).Exists()){
    int i = 1;
    wxString filename_old = filename;
    while (wxFileName(filename).Exists()){      //indexing, if video with same name exists
      i++;
      filename = filename_old;
      filename.Replace(".myswv", "_" + wxString::Format("%d", i) + ".myswv");
    }
  }
  return video_->saveVideo(filename);
}