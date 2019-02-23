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
#include "VideoPlayer.h"
#include "Counters.h"
#include "MainWindow.h"
#include "Settings.h"
#include "VideoPlayerDialog.h"
#include "BoardStats.h"

VideoPlayer::VideoPlayer(MyApp* app) : timer_(this), app_(app){
  Connect(timer_.GetId(), wxEVT_TIMER, wxTimerEventHandler(VideoPlayer::OnTimer), NULL, this);
}

VideoPlayer::~VideoPlayer(){
  Disconnect(timer_.GetId(), wxEVT_TIMER, wxTimerEventHandler(VideoPlayer::OnTimer), NULL, this);
}

bool VideoPlayer::setBoard(){
  try{
    app_->board_->setToLoadedBoard(video_.getWidth(), video_.getHeight(), video_.getMines(), video_.getSquares());
  }
  catch (std::exception& exception){
    wxMessageBox("Not enough memory for setting board, no video will be played!", "Video Loading Error", wxICON_ERROR);
    return false;
  }
  app_->main_window_->changeBoardSize();
  app_->main_window_->updateBoardView();

  return true;
}

void VideoPlayer::restartBoard(){     //just setting squares to unopened and reset stats (without resetting 3bv, zini, hzini) 
  app_->board_->restartBoard();
  app_->main_window_->changeBoardSize();
  app_->main_window_->updateBoardView();
}

bool VideoPlayer::loadVideo(wxString filename){
  video_ = Video(filename);
  if (!video_.isCorrect())
    return false;

  speed_ = 1.f;
  if (!setBoard())
    return false;
  
  app_->main_window_->SetStatusText(wxFileName(filename).GetName());
  old_flag_state_ = app_->settings_->question_marks_enabled_;
  is_running_ = false;

  is_active_ = true;

  app_->board_->setStatsTime(video_.getTime());     //stats should work with the time from the video

  return true;
}

bool VideoPlayer::loadVideo(const Video* video){
  if (video == nullptr || !video->isCorrect()){
    wxMessageBox("No complete video available!", "Video Loading Error", wxICON_EXCLAMATION);
    return false;
  }

  video_ = (*video);      //copying video (is not great, because not necessarily needed, but just shallow copy of board for less memory needed)
  speed_ = 1.f;

  restartBoard();

  app_->main_window_->SetStatusText("Replay");
  old_flag_state_ = app_->settings_->question_marks_enabled_;
  is_running_ = false;
  is_active_ = true;

  app_->board_->setStatsTime(video_.getTime());

  return true;
}

void VideoPlayer::endVideo(){
  if (video_.isCorrect()){
    app_->main_window_->showVideoCursor(false);
    timer_.Stop();
    app_->board_->resetStats(true);
    app_->counters_->setStats(app_->board_->getStats());
    app_->main_window_->stopTime(0);
    app_->counters_->stopCounters();
    app_->settings_->question_marks_enabled_ = old_flag_state_;
    video_ = Video();
    is_running_ = false;
  }
  is_active_ = false;
}

void VideoPlayer::start(long time){
  if (!video_.isCorrect())
    return;

  app_->main_window_->setVideoCursor(wxPoint(video_.getMousePosition(0).x_, video_.getMousePosition(0).y_));
  app_->main_window_->showVideoCursor(true);
  restartBoard();
  
  board_event_position_ = 0;
  mouse_position_position_ = 0;
  additional_event_position_ = 0;
  time_ = time;
  timer_.Start(20);   // 50 fps
  watch_.Start(0);
  is_running_ = true;

  app_->counters_->startCounters();
  app_->main_window_->setTimeDisplay((time_ + 999) / 1000);
}

void VideoPlayer::pause(){
  timer_.Stop();
  app_->counters_->stopCounters();
  is_running_ = false;
}

void VideoPlayer::resume(){
  timer_.Start(20);
  watch_.Start(0);
  app_->counters_->startCounters(); 
  is_running_ = true;
}

void VideoPlayer::stop(){
  timer_.Stop();
  time_ = 0;
  app_->main_window_->setTimeDisplay(0);
  app_->board_->resetStats(false);
  app_->counters_->stopCounters();
  restartBoard();
  app_->main_window_->showVideoCursor(false);
  app_->main_window_->setSmileyFace(SMILEY_FACE_NORMAL);
  is_running_ = false;
}

void VideoPlayer::OnTimer(wxTimerEvent&){
  static wxPoint mouse_pos;
  if (app_ == nullptr)
    return;

  time_ += watch_.Time() * speed_;    //calculate new time
  watch_.Start(0);                    //setting watch to 0, because time is calculated with the time differece between 2 iterations
  app_->main_window_->setTimeDisplay((time_ + 999) / 1000);

  app_->video_player_panel_->setTimeSlider(static_cast<float>(time_) / video_.getTime());     //slider movement

  if (app_->board_ == nullptr)
    wxMessageBox("Unexpected Error: No Board constructed in VideoPlayer::OnTimer", "Unexpected Error", wxICON_ERROR);

  //performing board events, as long as the events have smaller time
  while (board_event_position_ < video_.getBoardEvents().size() && time_ >= video_.getBoardEvent(board_event_position_).time_){
    BoardEvent board_event = video_.getBoardEvent(board_event_position_);

    //it´s important to be in right order with BoardEvents and additional events, so checking if a additional event is before
    while (additional_event_position_ < video_.getAdditionalEvents().size() &&
        board_event.time_ > video_.getAdditionalEvent(additional_event_position_).time_){
      switch (video_.getAdditionalEvent(additional_event_position_).type_){
        case ADDITIONAL_EVENT_QUESTIONMARK_SET: 
          app_->settings_->question_marks_enabled_ = !!(video_.getAdditionalEvent(additional_event_position_).param1_);
          break;
        case ADDITIONAL_EVENT_SCROLL:
          break;
        default:
          break;
      }
      additional_event_position_++;
    }

    //perform right event
    switch (video_.getBoardEvent(board_event_position_).type_){
      case BOARD_EVENT_LEFT_CLICK: 
        app_->board_->leftClickSquare(board_event.x_, board_event.y_);
        break;
      case BOARD_EVENT_MOVE_CLICKED:
        app_->board_->moveClicked(board_event.x_, board_event.y_);
        break;
      case BOARD_EVENT_OPEN_SQUARE:
        app_->board_->openSquare(board_event.x_, board_event.y_);
        break;
      case BOARD_EVENT_RIGHT_CLICK:
        app_->board_->rightClickSquare(board_event.x_, board_event.y_);
        break;
      case BOARD_EVENT_RIGHT_UP:
        app_->board_->rightUp();
        break;
      case BOARD_EVENT_CHORD_CLICK:
        app_->board_->chordClickSquare(board_event.x_, board_event.y_);
        break;
      case BOARD_EVENT_MOVE_CHORDED:
        app_->board_->moveChorded(board_event.x_, board_event.y_);
        break;
      case BOARD_EVENT_OPEN_CHORD:
        app_->board_->openChord(board_event.x_, board_event.y_, false);
        break;
      case BOARD_EVENT_OPEN_CHORD_RIGHT_UP:
        app_->board_->openChord(board_event.x_, board_event.y_, true);
        break;
      case BOARD_EVENT_LEAVE_BOARD:
        app_->board_->leaveBoard();
        break;
      default: break;
    }
    board_event_position_++;
  }

  wxPoint mouse_pos_old = mouse_pos;    //old mouse position needed to repaint area where the mouse was before
  while (mouse_position_position_ < video_.getMousePositions().size() &&
    time_ >= video_.getMousePosition(mouse_position_position_).time_){
    mouse_pos = wxPoint(
      (video_.getMousePosition(mouse_position_position_).x_* app_->main_window_->getSquareSize()) / 384,   //384 because stored are mouse positions in squares * 384
      (video_.getMousePosition(mouse_position_position_).y_* app_->main_window_->getSquareSize()) / 384);
    if (video_.getMousePosition(mouse_position_position_).x_ != -1000 && mouse_position_position_ > 0){   //increment path, if no leave event (-1000) and if there was a position before
      int index = mouse_position_position_ - 1;
      while (index >= 0 && video_.getMousePosition(index).x_ == -1000)      //go back to the last position not from a leave event
        index--;
      app_->board_->incrPath(sqrtf(     //calculate new path
        (video_.getMousePosition(mouse_position_position_).x_ - video_.getMousePosition(index).x_) *
        (video_.getMousePosition(mouse_position_position_).x_ - video_.getMousePosition(index).x_) +
        (video_.getMousePosition(mouse_position_position_).y_ - video_.getMousePosition(index).y_) *
        (video_.getMousePosition(mouse_position_position_).y_ - video_.getMousePosition(index).y_)) / 384.f);   //384 because stored are mouse positions in squares * 384
    }
    mouse_position_position_++;
  }
  app_->main_window_->showVideoCursor(mouse_pos.x != -1000);      //if leave, hide cursor
  app_->main_window_->setVideoCursor(mouse_pos);      //set to position
  app_->main_window_->focusOnCursorIfNotSeen();       //if cursor is not in the area seen (in scroll mode) focus on cursor (change origin for that)

  //update area between old and new position (so both are updated)
  wxRect update_rect(mouse_pos / app_->main_window_->getSquareSize(), mouse_pos_old / app_->main_window_->getSquareSize());
  update_rect.SetLeft(update_rect.GetLeft() - 2);     //this is because cursor has some extend
  update_rect.SetRight(update_rect.GetRight() + 4);
  update_rect.SetTop(update_rect.GetTop() - 2);
  update_rect.SetBottom(update_rect.GetBottom() + 4);
  app_->main_window_->updateBoardView(update_rect.GetLeft(), update_rect.GetTop(), update_rect.GetRight(), update_rect.GetBottom());

  app_->board_->updateStats(time_);
  app_->board_->setStatsTime(time_);

  if (app_->board_->getBoardStatus() == BOARD_STATUS_VIDEO_END){      //if board finished
    pause();
    app_->board_->setStatsTime(video_.getTime());
    app_->main_window_->stopTime((video_.getTime() + 999) / 1000);
    app_->board_->updateStats(video_.getTime());
    app_->counters_->stopCounters();
    app_->counters_->updateCounters(video_.getTime());
    app_->video_player_panel_->setTimeLabel(video_.getTime() / 1000.f);
  }
}