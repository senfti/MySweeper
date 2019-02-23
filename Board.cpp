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
#include "Board.h"
#include "MainWindow.h"
#include "Settings.h"
#include "main.h"
#include "Highscores.h"
#include "Counters.h"
#include "VideoRecorder.h"
#include "VideoPlayer.h"
#include "History.h"


Board::Board(){
  srand((unsigned int)time(NULL));    //seeding just when starting program
}

Board::Board(MyApp* app) : app_(app){
  setBoardStyle(BOARD_STYLE_BEG);
  srand((unsigned int)time(NULL));
  generateBoard();
}

Board::Board(MyApp* app, BoardStyle style) : app_(app){
  setBoardStyle(style);
  srand((unsigned int)time(NULL));
  generateBoard();
}

Board::Board(MyApp* app, int width, int height, int mines) : app_(app){
  setCustomBoard(width, height, mines);
  srand((unsigned int)time(NULL));
  generateBoard();
}

std::string Board::getStyleString() const{
  switch (style_)
  {
    case BOARD_STYLE_BEG:     return "BEG";             break;
    case BOARD_STYLE_INT:     return "INT";             break;
    case BOARD_STYLE_EXP:     return "EXP";             break;
    case BOARD_STYLE_CUSTOM:  return "CUSTOM";          break;
    default:                  return "UNDEFINED";       break;
  }
}

void Board::boardPreparingStuff(){
  if (app_->counters_)             //while constructing board, there is no counters_ yet
    app_->counters_->stopCounters();
  resetStats(true); //also calculate 3bv,zini,hzini
  stats_.setBoardDimensions(width_, height_, mines_);

  //reset board state values
  last_x_ = -1;
  last_y_ = -1;
  right_on_opened_ = false;
  block_open_square_ = false;
  mines_not_flagged_ = mines_;
  opened_squares_ = 0;
  
  if (app_->video_recorder_->isRecording())
    app_->video_recorder_->stopRecording(false);

  app_->main_window_->setMinesDisplay(mines_not_flagged_);
}

void Board::generateBoard(){
  try{
    squares_.resize(width_ * height_);
    is_3BV_square_.resize(width_ * height_, BitArray::DEFAULT_VALUE_0);
  }
  catch (std::bad_alloc&){
    wxMessageBox("Not enough memory for setting board!\n Set Board to beginner!", "Board Generating Error", wxICON_ERROR);
    setBoardStyle(BOARD_STYLE_BEG);   //set to Beginner, if too little memory (or terminate, if it´s not enough for Beginner)
    squares_.resize(width_ * height_);
    is_3BV_square_.resize(width_ * height_, BitArray::DEFAULT_VALUE_0);   //no 3BV squares
  }

  for (int i = width_ * height_ - 1; i >= 0; i--){
    squares_[i].value_ = -(i < mines_);
    squares_[i].state_ = SQUARE_UNOPENED;
  }

  //seed was in constructor
  std::random_shuffle(squares_.begin(), squares_.end());
  calcAllNumbers();  
  status_ = BOARD_STATUS_PREPARED;

  boardPreparingStuff();
}

void Board::setToLoadedBoard(int width, int height, int mines, const std::vector<Square>& squares){
  width_ = width;
  height_ = height;
  mines_ = mines;
  opened_squares_ = 0;

  squares_ = squares;
  is_3BV_square_.resize(width_ * height_, BitArray::DEFAULT_VALUE_0);

  if (width_ == 8 && height_ == 8 && mines_ == 10)
    style_ = BOARD_STYLE_BEG;
  else if (width_ == 16 && height_ == 16 && mines_ == 40)
    style_ = BOARD_STYLE_INT;
  else if (width_ == 30 && height_ == 16 && mines_ == 99)
    style_ = BOARD_STYLE_EXP;
  else
    style_ = BOARD_STYLE_CUSTOM;

  status_ = BOARD_STATUS_VIDEO_PREPARED;

  boardPreparingStuff();
  calcStats();
}

void Board::restartBoard(){
  status_ = BOARD_STATUS_VIDEO_PREPARED;

  for (int i = width_ * height_ - 1; i >= 0; i--)
    squares_[i].state_ = SQUARE_UNOPENED;

  if (app_->counters_)             //while constructing board, there is no counters_ yet
    app_->counters_->stopCounters();
  stats_.setBoardDimensions(width_, height_, mines_);

  last_x_ = -1;
  last_y_ = -1;
  right_on_opened_ = false;
  block_open_square_ = false;
  mines_not_flagged_ = mines_;
  opened_squares_ = 0;

  if (app_->video_recorder_->isRecording())
    app_->video_recorder_->stopRecording(false);

  app_->main_window_->setMinesDisplay(mines_not_flagged_);
  resetStats(false);    //no recalculation of 3BV, zini, hzini
}

void Board::setBoardStyle(BoardStyle style){
  style_ = style;
  switch (style_)
  {
    case BOARD_STYLE_BEG:   width_ = 8;  height_ = 8;  mines_ = 10;     break;
    case BOARD_STYLE_INT:   width_ = 16; height_ = 16; mines_ = 40;     break;
    case BOARD_STYLE_EXP:   width_ = 30; height_ = 16; mines_ = 99;     break;
    case BOARD_STYLE_CUSTOM:                                            break;
    default:                                                            break;
  }
}

void Board::setCustomBoard(int width, int height, int mines){
  style_ = BOARD_STYLE_CUSTOM;
  width_ = width;  
  if (width_ < 2)
    width_ = 2;
  height_ = height;  
  if (height_ < 2)
    height_ = 2;
  mines_ = mines;
  if (mines >= width_*height_ - 1)
    mines_ = width_*height_ - 1;

  //if a custom is beg, int or exp, say so
  if (width_ == 8 && height_ == 8 && mines_ == 10)
    style_ = BOARD_STYLE_BEG;
  if (width_ == 16 && height_ == 16 && mines_ == 40)
    style_ = BOARD_STYLE_INT;
  if (width_ == 30 && height_ == 16 && mines_ == 99)
    style_ = BOARD_STYLE_EXP;
}

void Board::calcNumber(int x, int y){
  if (squares_[getIndex(x,y)].value_ == -1)
    return;

  squares_[getIndex(x, y)].value_ = 0;
  for (int x_it = x - 1; x_it <= x + 1; x_it++){              //checks itself, but can´t be -1(a mine) itself
    for (int y_it = y - 1; y_it <= y + 1; y_it++){
      if (x_it >= 0 && x_it < width_ && y_it >= 0 && y_it < height_){
        if (squares_[getIndex(x_it, y_it)].value_ == -1)
          squares_[getIndex(x, y)].value_++;
      }
    }
  }
}

//look for mine and when found increase numbers around
void Board::calcAllNumbers(){
  int height_minus_1 = height_ - 1;
  int width_minus_1 = width_ - 1;
  int width_plus_1 = width_ + 1;
  int index;

  //first without outer squares (no border checking needed)
  for (int x = 1; x < width_minus_1; x++){
    for (int y = 1; y < height_minus_1; y++){
      index = getIndex(x,y);
      if (squares_[index].value_ == -1){
        squares_[index - width_plus_1].value_ += (squares_[index - width_plus_1].value_ != -1);
        squares_[index - width_].value_ += (squares_[index - width_].value_ != -1);
        squares_[index - width_minus_1].value_ += (squares_[index - width_minus_1].value_ != -1);

        squares_[index - 1].value_ += (squares_[index - 1].value_ != -1);
        squares_[index + 1].value_ += (squares_[index + 1].value_ != -1);

        squares_[index + width_minus_1].value_ += (squares_[index + width_minus_1].value_ != -1);
        squares_[index + width_].value_ += (squares_[index + width_].value_ != -1);
        squares_[index + width_plus_1].value_ += (squares_[index + width_plus_1].value_ != -1);
      }
    }
  }
  //upper and lower row without first and last
  index = getIndex(1, height_minus_1);
  for (int x = 1; x < width_minus_1; x++){
    if (squares_[x].value_ == -1){
      squares_[x - 1].value_ += (squares_[x - 1].value_ != -1);
      squares_[x + 1].value_ += (squares_[x + 1].value_ != -1);

      squares_[x + width_minus_1].value_ += (squares_[x + width_minus_1].value_ != -1);
      squares_[x + width_].value_ += (squares_[x + width_].value_ != -1);
      squares_[x + width_plus_1].value_ += (squares_[x + width_plus_1].value_ != -1);
    }

    if (squares_[index].value_ == -1){
      squares_[index - width_plus_1].value_ += (squares_[index - width_plus_1].value_ != -1);
      squares_[index - width_].value_ += (squares_[index - width_].value_ != -1);
      squares_[index - width_minus_1].value_ += (squares_[index - width_minus_1].value_ != -1);

      squares_[index - 1].value_ += (squares_[index - 1].value_ != -1);
      squares_[index + 1].value_ += (squares_[index + 1].value_ != -1);
    }
    index++;
  }
  //most left and most right column without first and last
  index = getIndex(0, 1);
  int index2 = getIndex(width_minus_1, 1);
  for (int i = 1; i < height_minus_1; i++){
    if (squares_[index].value_ == -1){
      squares_[index - width_].value_ += (squares_[index - width_].value_ != -1);
      squares_[index - width_minus_1].value_ += (squares_[index - width_minus_1].value_ != -1);

      squares_[index + 1].value_ += (squares_[index + 1].value_ != -1);

      squares_[index + width_].value_ += (squares_[index + width_].value_ != -1);
      squares_[index + width_plus_1].value_ += (squares_[index + width_plus_1].value_ != -1);
    }


    if (squares_[index2].value_ == -1){
      squares_[index2 - width_plus_1].value_ += (squares_[index2 - width_plus_1].value_ != -1);
      squares_[index2 - width_].value_ += (squares_[index2 - width_].value_ != -1);

      squares_[index2 - 1].value_ += (squares_[index2 - 1].value_ != -1);

      squares_[index2 + width_minus_1].value_ += (squares_[index2 + width_minus_1].value_ != -1);
      squares_[index2 + width_].value_ += (squares_[index2 + width_].value_ != -1);
    }
    index += width_;
    index2 += width_;
  }

  //corner squares
  if (squares_[0].value_ == -1){
    squares_[1].value_ += (squares_[1].value_ != -1);
    squares_[width_].value_ += (squares_[width_].value_ != -1);
    squares_[width_plus_1].value_ += (squares_[width_plus_1].value_ != -1);
  }
  if (squares_[width_minus_1].value_ == -1){
    squares_[width_minus_1 - 1].value_ += (squares_[width_minus_1 - 1].value_ != -1);
    squares_[width_minus_1 + width_minus_1].value_ += (squares_[width_minus_1 + width_minus_1].value_ != -1);
    squares_[width_minus_1 + width_].value_ += (squares_[width_minus_1 + width_].value_ != -1);
  }
  if (squares_[getIndex(0, height_minus_1)].value_ == -1){
    squares_[getIndex(0, height_ - 2)].value_ += (squares_[getIndex(0, height_ - 2)].value_ != -1);
    squares_[getIndex(1, height_ - 2)].value_ += (squares_[getIndex(1, height_ - 2)].value_ != -1);
    squares_[getIndex(1, height_minus_1)].value_ += (squares_[getIndex(1, height_minus_1)].value_ != -1);
  }
  if (squares_[getIndex(width_minus_1, height_minus_1)].value_ == -1){
    squares_[getIndex(width_ - 2, height_ - 2)].value_ += (squares_[getIndex(width_ - 2, height_ - 2)].value_ != -1);
    squares_[getIndex(width_minus_1, height_ - 2)].value_ += (squares_[getIndex(width_minus_1, height_ - 2)].value_ != -1);
    squares_[getIndex(width_ - 2, height_minus_1)].value_ += (squares_[getIndex(width_ - 2, height_minus_1)].value_ != -1);
  }
}

void Board::openSingleSquare(int x, int y){
  squares_[getIndex(x, y)].state_ = SQUARE_OPENED;
  opened_squares_++;
  if (is3BV(getIndex(x, y)))    //this is just used in video mode
    stats_.solved_3BV_++;
  adjustUpdateRegion(x, y);
}

void Board::setClickedSingleSquare(int x, int y){
  squares_[getIndex(x, y)].state_ = SQUARE_CLICKED;
  adjustUpdateRegion(x, y);
}

void Board::setUnopenedSingleSquare(int x, int y){
  squares_[getIndex(x, y)].state_ = SQUARE_UNOPENED;
  adjustUpdateRegion(x, y);
}

void Board::setFlaggedSingleSquare(int x, int y){
  squares_[getIndex(x,y)].state_ = SQUARE_FLAGGED;
  adjustUpdateRegion(x, y);
}

void Board::setQuestionSingleSquare(int x, int y){
  squares_[getIndex(x, y)].state_ = SQUARE_QUESTION_MARKED;
  adjustUpdateRegion(x, y);
}

void Board::openSquaresAround(int x, int y){  //iterative methode to avoid stack overflow
  std::queue<int> queue;  //put squares, where opening around is needed, in this queue
  queue.push((y << 16) | x);

  int x_it, y_it, index;
  while(!queue.empty()){
    x = queue.front() & 0x0000ffff;   //so i use just one int per index, but avoid an expensive divide and modulo to get x and y
    y = queue.front() >> 16;
    queue.pop();
    for (x_it = x - 1; x_it <= x + 1; x_it++){              
      for (y_it = y - 1; y_it <= y + 1; y_it++){
        if (x_it >= 0 && x_it < width_ && y_it >= 0 && y_it < height_ && (x_it != x || y_it != y)){
          index = getIndex(x_it, y_it);
          if (squares_[index].state_ == SQUARE_UNOPENED || squares_[index].state_ == SQUARE_CLICKED){
            if (squares_[index].value_ == 0)
              queue.push((y_it << 16) | x_it);
            openSingleSquare(x_it, y_it);
          }
        }
      }
    }
  }
}

void Board::unclick(int x, int y){
  for (int x_it = x - 1; x_it <= x + 1; x_it++){
    for (int y_it = y - 1; y_it <= y + 1; y_it++){
      if (x_it >= 0 && x_it < width_ && y_it >= 0 && y_it < height_){
        if (squares_[getIndex(x_it, y_it)].state_ == SQUARE_CLICKED){
          setUnopenedSingleSquare(x_it, y_it);
        }
      }
    }
  }
}

void Board::swapMine(int x, int y){
  int changed_square = rand() % (height_*width_);       //complex^^ calculation to avoid predictable results (likelier clusters) but ensure termination
  int offset = rand() % (height_*width_);
  while (squares_[changed_square].value_ == -1){
    changed_square = (changed_square + offset) % (height_*width_);
    offset = offset / 2 + 1;
  }
  squares_[changed_square].value_ = -1;
  squares_[getIndex(x,y)].value_ = 0;           //needed, else no number computation (for mines no number computation)
  calcNumber(x, y);
  int changed_x = changed_square % width_;
  int changed_y = changed_square / width_;
  for (int i = -1; i <= 1; i++){
    for (int j = -1; j <= 1; j++){
      if (x + i >= 0 && x + i < width_ && y + j >= 0 && y + j < height_ && (i != 0 || j != 0))
        calcNumber(x + i, y + j);
      if (changed_x + i >= 0 && changed_x + i < width_ && changed_y + j >= 0 && changed_y + j < height_ && (i != 0 || j != 0))
        calcNumber(changed_x + i, changed_y + j);
    }
  }
}

void Board::startBoard(int x, int y){
  if (squares_[getIndex(x, y)].value_ == -1){
    swapMine(x, y);
  }
  app_->counters_->updateCounters();
  if (app_->settings_->hide_counters_while_playing_)
    app_->counters_->showCounters(false);

  stats_.path_ = 0.f;
  watch_.Start();

  if (status_ == BOARD_STATUS_VIDEO_PREPARED){
    status_ = BOARD_STATUS_VIDEO_RUNNING;
  }
  else{
    status_ = BOARD_STATUS_STARTED;
    app_->main_window_->startTime();
    app_->counters_->startCounters();
    app_->main_window_->SetStatusText(app_->main_window_->isScrollMode() ?
      "Use middle mouse button to move the board. Also press \"Ctrl\" to increases speed" : "");
    app_->video_recorder_->startRecording(this);
  }
}

void Board::setBoardLost(){
  for (int i = width_*height_ - 1; i >= 0; i--){
    if (squares_[i].value_ == -1){
      if (squares_[i].state_ == SQUARE_OPENED)
        squares_[i].state_ = SQUARE_KILLING_MINE;
      if (squares_[i].state_ == SQUARE_UNOPENED)
        squares_[i].state_ = SQUARE_OPENED;
    }
    else{
      if (squares_[i].state_ == SQUARE_FLAGGED)
        squares_[i].state_ = SQUARE_WRONG_FLAGGED;
    }
  }
  if (status_ == BOARD_STATUS_VIDEO_RUNNING)
    status_ = BOARD_STATUS_VIDEO_END;
  else
    status_ = BOARD_STATUS_LOST;
  app_->main_window_->setSmileyFace(SMILEY_FACE_LOOSE);
}

void Board::setBoardWon(){
  for (int i = width_*height_ - 1; i >= 0; i--){
    if (squares_[i].value_ == -1)
      squares_[i].state_ = SQUARE_FLAGGED;
  }
  app_->main_window_->setSmileyFace(SMILEY_FACE_WIN);
  app_->main_window_->setMinesDisplay(0);

  if (status_ == BOARD_STATUS_VIDEO_RUNNING)
    status_ = BOARD_STATUS_VIDEO_END;
  else{
    status_ = BOARD_STATUS_WON;
    if (style_ != BOARD_STYLE_CUSTOM){
      wxDateTime date;
      date.SetToCurrent();
      HistoryItem history_item_(stats_, date);
      history_item_.addItemToFile();
    }
    app_->main_window_->instantBoardUpdate(); //without this, board doesn´t look finished while showing messages
    Highscores highscores;
    int highscore_return = highscores.newScore(stats_);
    if (highscore_return != -1){
      stats_.is_record_ = true;
      app_->main_window_->showHighscores(highscore_return);
    }
  }
}

void Board::finishBoard(bool won){
  stats_.time_ = watch_.Time();
  if (status_ != BOARD_STATUS_VIDEO_RUNNING){
    app_->main_window_->stopTime((stats_.time_ + 999) / 1000);
    calcStats();
    app_->counters_->stopCounters();
    wxString status_text = "Time: " + wxString::Format(wxT("%.3f"), static_cast<float>(stats_.time_) / 1000) +
      ", 3BV: " + wxString::Format(wxT("%d"), stats_.bbbv_) + ", 3BV/s: " + wxString::Format(wxT("%.3f"), stats_.bbbvs_);
    app_->main_window_->SetStatusText(status_text);
  }
  if (app_->settings_->hide_counters_while_playing_ && app_->settings_->counters_shown_)
    app_->counters_->showCounters(true);
  app_->counters_->updateCounters();

  if (won)
    setBoardWon();
  else
    setBoardLost();

  app_->counters_->updateCounters();

  if (isFinished() && status_ != BOARD_STATUS_VIDEO_END)
    app_->video_recorder_->stopRecording(true);

  app_->main_window_->updateBoardView();
}

void Board::preEventCalc(int x, int y, bool is_open_event, SmileyFace smiley_face, BoardEventType event_type){
  resetUpdateRegion(x, y);
  app_->main_window_->setSmileyFace(smiley_face);

  //to be sure, there are no clicked squares which should not be clicked any more
  if (last_x_ != -1){
    unclick(last_x_, last_y_);
  }
  last_x_ = -1;
  last_y_ = -1;

  if (is_open_event && (status_ == BOARD_STATUS_PREPARED || status_ == BOARD_STATUS_VIDEO_PREPARED))
    startBoard(x, y);

  app_->video_recorder_->addBoardEvent(BoardEvent(event_type, watch_.Time(), x, y));
}

void Board::postClickCalc(int x, int y){
  bool is_lost = false;
  //check, if a mine was opened (must be around or exact the square of the event)
  for (int x_it = std::max(x - 1, 0); x_it <= std::min(x + 1, width_ - 1); x_it++){
    for (int y_it = std::max(y - 1, 0); y_it <= std::min(y + 1, height_ - 1); y_it++){
      is_lost |= (squares_[getIndex(x_it, y_it)].value_ == -1 && squares_[getIndex(x_it, y_it)].state_ == SQUARE_OPENED);
    }
  }

  if (is_lost){
    finishBoard(false);
    if (app_->settings_->restart_on_fail_ && status_ != BOARD_STATUS_VIDEO_END)
      app_->main_window_->newBoard();
    return;
  }
  if (opened_squares_ == width_*height_ - mines_){
    finishBoard(true);
  }
}

void Board::leftClickSquare(int mouse_x, int mouse_y){
  preEventCalc(mouse_x, mouse_y, false, SMILEY_FACE_CLICK, BOARD_EVENT_LEFT_CLICK);

  if (squares_[getIndex(mouse_x, mouse_y)].state_ == SQUARE_UNOPENED){
    setClickedSingleSquare(mouse_x, mouse_y);
  }
  right_on_opened_ = false;
  last_x_ = mouse_x;
  last_y_ = mouse_y;

  app_->main_window_->updateBoardView(update_region_left_, update_region_top_, update_region_right_, update_region_bottom_);
}

void Board::moveClicked(int mouse_x, int mouse_y){
  preEventCalc(mouse_x, mouse_y, false, SMILEY_FACE_CLICK, BOARD_EVENT_MOVE_CLICKED);

  if (!block_open_square_ && squares_[getIndex(mouse_x, mouse_y)].state_ == SQUARE_UNOPENED)
    setClickedSingleSquare(mouse_x, mouse_y);

  right_on_opened_ = false;
  last_x_ = mouse_x;
  last_y_ = mouse_y;

  app_->main_window_->updateBoardView(update_region_left_, update_region_top_, update_region_right_, update_region_bottom_);
}

void Board::openSquare(int mouse_x, int mouse_y){
  preEventCalc(mouse_x, mouse_y, true, SMILEY_FACE_NORMAL, BOARD_EVENT_OPEN_SQUARE);

  if (!block_open_square_){   //after a chord, left up should not open a square and the click was counted for the chord
    stats_.left_clicks_++;

    if (squares_[getIndex(mouse_x, mouse_y)].state_ == SQUARE_CLICKED || squares_[getIndex(mouse_x, mouse_y)].state_ == SQUARE_UNOPENED){
      openSingleSquare(mouse_x, mouse_y);

      if (squares_[getIndex(mouse_x, mouse_y)].value_ == 0){
        openSquaresAround(mouse_x, mouse_y);
      }
      postClickCalc(mouse_x, mouse_y);
    }
  }
  else{
    block_open_square_ = false;
  }

  right_on_opened_ = false;
  last_x_ = mouse_x;
  last_y_ = mouse_y;
  app_->main_window_->updateBoardView(update_region_left_, update_region_top_, update_region_right_, update_region_bottom_);
}

void Board::rightClickSquare(int mouse_x, int mouse_y){
  preEventCalc(mouse_x, mouse_y, false, SMILEY_FACE_CLICK, BOARD_EVENT_RIGHT_CLICK);
  
  stats_.right_clicks_++;

  if (squares_[getIndex(mouse_x, mouse_y)].state_ == SQUARE_UNOPENED){
    setFlaggedSingleSquare(mouse_x, mouse_y);
    mines_not_flagged_--;
  }
  else if (squares_[getIndex(mouse_x, mouse_y)].state_ == SQUARE_FLAGGED){
    if (app_->settings_->question_marks_enabled_){
      setQuestionSingleSquare(mouse_x, mouse_y);
      mines_not_flagged_++;
    }
    else{
      setUnopenedSingleSquare(mouse_x, mouse_y);
      mines_not_flagged_++;
    }
  }
  else if (squares_[getIndex(mouse_x, mouse_y)].state_ == SQUARE_QUESTION_MARKED){
    setUnopenedSingleSquare(mouse_x, mouse_y);
  }

  if (squares_[getIndex(mouse_x, mouse_y)].state_ == SQUARE_OPENED)
    right_on_opened_ = true;
  else
    right_on_opened_ = false;

  last_x_ = mouse_x;
  last_y_ = mouse_y;

  app_->main_window_->setMinesDisplay(mines_not_flagged_);
  app_->main_window_->updateBoardView(update_region_left_, update_region_top_, update_region_right_, update_region_bottom_);
}

void Board::rightUp(){
  preEventCalc(0, 0, false, SMILEY_FACE_NORMAL, BOARD_EVENT_RIGHT_UP);  //just for smiley face setting normal
}

void Board::chordClickSquare(int mouse_x, int mouse_y){
  preEventCalc(mouse_x, mouse_y, false, SMILEY_FACE_CLICK, BOARD_EVENT_CHORD_CLICK);

  for (int x = mouse_x - 1; x <= mouse_x + 1; x++){
    for (int y = mouse_y - 1; y <= mouse_y + 1; y++){
      if (x >= 0 && x < width_ && y >= 0 && y < height_){ 
        if (squares_[getIndex(x, y)].state_ == SQUARE_UNOPENED){
          setClickedSingleSquare(x, y);
        }
      }
    }
  }
  last_x_ = mouse_x;
  last_y_ = mouse_y;
  block_open_square_ = false;

  app_->main_window_->updateBoardView(update_region_left_, update_region_top_, update_region_right_, update_region_bottom_);
}

//completely like chord click (this does the unclick anyway)
void Board::moveChorded(int mouse_x, int mouse_y){
  chordClickSquare(mouse_x, mouse_y);
}

//the right up is important, because after a chord with right mouse button up, a left button should not do anything
void Board::openChord(int mouse_x, int mouse_y, bool with_right_up){
  preEventCalc(mouse_x, mouse_y, true, SMILEY_FACE_NORMAL, with_right_up? BOARD_EVENT_OPEN_CHORD_RIGHT_UP : BOARD_EVENT_OPEN_CHORD);
  
  stats_.chord_clicks_++;
  if (right_on_opened_)
    stats_.right_clicks_--;

  //check, if on opened square with value at least 1
  if (squares_[getIndex(mouse_x, mouse_y)].state_ == SQUARE_OPENED && squares_[getIndex(mouse_x, mouse_y)].value_ > 0){     //count surrounding flags
    int flag_counter = 0;

    for (int x = mouse_x - 1; x <= mouse_x + 1; x++){
      for (int y = mouse_y - 1; y <= mouse_y + 1; y++){
        if (x >= 0 && x < width_ && y >= 0 && y < height_){  //if the code here is executed, the square must be unopened, so selfchecking no problem
          if (squares_[getIndex(x, y)].state_ == SQUARE_FLAGGED)
            flag_counter++;
        }
      }
    }
    if (flag_counter == squares_[getIndex(mouse_x, mouse_y)].value_){
      openSquaresAround(mouse_x, mouse_y);
      postClickCalc(mouse_x, mouse_y);
    }
  }

  last_x_ = mouse_x;
  last_y_ = mouse_y;
  right_on_opened_ = false;
  block_open_square_ = with_right_up;     //if chorded with right up, left stays down but with release of left no click possible

  app_->main_window_->updateBoardView(update_region_left_, update_region_top_, update_region_right_, update_region_bottom_);
}

void Board::leaveBoard(){
  preEventCalc(0, 0, false, SMILEY_FACE_NORMAL, BOARD_EVENT_LEAVE_BOARD);

  right_on_opened_ = false;       //both are resetted
  block_open_square_ = false;
  
  app_->main_window_->updateBoardView(update_region_left_, update_region_top_, update_region_right_, update_region_bottom_);
}

void Board::resetUpdateRegion(int x, int y){
  update_region_left_ = x;
  update_region_right_ = x;
  update_region_top_ = y;
  update_region_bottom_ = y;
}

void Board::adjustUpdateRegion(int x, int y){
  if (x < update_region_left_)
    update_region_left_ = x;
  if (x > update_region_right_)
    update_region_right_ = x;
  if (y < update_region_top_)
    update_region_top_ = y;
  if (y > update_region_bottom_)
    update_region_bottom_ = y;
}

bool Board::is3BV(int index) const{
  return is_3BV_square_.getBit(index);
}

bool Board::calc3BV(int& bbbv, int& solved_3BV, BitArray& is_3BV_square, int* states, BitArray* tricky_squares) const{
  if (stats_.bbbv_ != 0){
    bbbv = stats_.bbbv_;
    return true;
  }
  bbbv = 0;
  solved_3BV = 0;

  is_3BV_square.setAll(false);
  
  memset(states, 0, width_ * height_ * sizeof(int));

  std::queue<int> queue;  //put squares, where opening around is needed, in this queue
  int x, y, x_it, y_it, index;

  int number_of_squares = width_ * height_;

  //because there is just unopened (=0) and opened, in states is the index of the zero, because of which it is opened + 1
  try{
    //openings
    for (int i = 0; i < number_of_squares; i++){
      if (squares_[i].value_ == 0 && states[i] == SQUARE_UNOPENED){
        states[i] = i + 1;

        queue.push(((i / width_) << 16) | (i % width_));      //openSquareAround code (here with states array instead of squares.state)
        while (!queue.empty()){
          x = queue.front() & 0x0000ffff;
          y = queue.front() >> 16;
          queue.pop();
          for (x_it = x - 1; x_it <= x + 1; x_it++){
            for (y_it = y - 1; y_it <= y + 1; y_it++){
              if (x_it >= 0 && x_it < width_ && y_it >= 0 && y_it < height_ && (x_it != x || y_it != y)){
                index = getIndex(x_it, y_it);
                if (states[index] == SQUARE_UNOPENED){
                  if (squares_[index].value_ == 0)
                    queue.push((y_it << 16) | x_it);
                  states[index] = i + 1;  //i+1 to store the square, which caused the opening (+1 because 0 means unopened, everything else means opened)
                }
                //a tricky square is a square, which has to openings around, if it has been opened by an other opening before, there is another value than i+1 in states and must be a tricky square
                else if (states[index] != i + 1)
                  tricky_squares->setBit(index); 
              }
            }
          }
        }
        bbbv++;
        solved_3BV += (squares_[i].state_ == SQUARE_OPENED);
        is_3BV_square.setBit(i);
      }
    }
    //rest of the squares
    for (int i = 0; i < number_of_squares; i++){
      if (states[i] == SQUARE_UNOPENED && squares_[i].value_ != -1){
        bbbv++;
        solved_3BV += squares_[i].state_ == SQUARE_OPENED;
        is_3BV_square.setBit(i);
      }
    }
  }
  catch (std::exception&){
    wxMessageBox("Not enough memory for 3BV calculation!", "Error", wxICON_ERROR);
    bbbv = 1;
    return false;;
  }
  return true;
}

//premium is number of unopened 3BV around - 1(chord click) - square to chord is unopened ? 1 : 0
int Board::calcPremium(int x, int y, const int* states, bool is_HZiNi, const BitArray& tricky_squares) const {
  int x_it, y_it;
  int premium = -1;   // =-1 because -1 in calculation algorithm
  int index = getIndex(x, y);
  bool unopended_zero_around = false;
  bool opened_zero_around = false;

  if (squares_[index].value_ <= 0)    //on mine and 0 no chord possible
    return -1;

  for (x_it = x - 1; x_it <= x + 1; x_it++){
    for (y_it = y - 1; y_it <= y + 1; y_it++){
      if (x_it >= 0 && x_it < width_ && y_it >= 0 && y_it < height_){
        index = getIndex(x_it, y_it);
        premium += (is3BV(index) && squares_[index].value_ != 0 //0 are treated different
          && (states[index] != SQUARE_OPENED));
        premium -= ((states[index] != SQUARE_FLAGGED) && (squares_[index].value_ == -1));
        if (squares_[index].value_ == 0 && states[index] == SQUARE_OPENED)
          opened_zero_around = true;
        else if (squares_[index].value_ == 0 && states[index] == SQUARE_UNOPENED)
          unopended_zero_around = true;
      }
    }
  }
  if (opened_zero_around && unopended_zero_around)    //when a opened and a unopened 0 around, then 1 3BV for the premium (was tricky square but one was opened)
    premium++;
  else if (unopended_zero_around)   //when unopened then is_tricky_square ? 2 : 1
    premium += 1 + tricky_squares.getBit(getIndex(x, y));

  premium -= (!is_HZiNi && (states[getIndex(x, y)] != SQUARE_OPENED));    //is click for open square needed (in hZiNi never needed)

  return std::max(premium, -1);   //just want no other negative numbers than -1
}

//calcs all premiums and inserts all premiums >= 0 into the set
bool Board::calcAllPremiums(const int* states, int* premiums, std::vector<std::set<int>>& premium_sets,
  const BitArray& tricky_squares) const
{
  int index = 0;
  try{
    for (int x = 0; x < width_; x++){
      for (int y = 0; y < height_; y++){
        index = getIndex(x, y);
        premiums[index] = calcPremium(x, y, states, false, tricky_squares);
        if (premiums[index] >= 0)
          premium_sets[premiums[index]].insert(premium_sets[premiums[index]].end(), (x << 16) | y);
      }
    }
  }
  catch (std::bad_alloc&){
    wxMessageBox("Not enough memory for ZiNi calculation!", "Error", wxICON_ERROR);
    return false;
  }

  return true;
}

//does one zini perform (flag, open and chord or just open if no non-negative premium)
int Board::performZiNi(int x, int y, int* states, int* premiums, std::vector<std::set<int>>& premium_sets, 
  const BitArray& tricky_squares, bool normal_click, bool is_HZiNi) const
{
  int clicks = 0;   //how many clicks were needed
  int x_it, y_it;
  int index = getIndex(x, y);
  int update_left = std::max(x - 2, 0);   //the rectangle, where all squares lie, whose premium needs an update
  int update_right = std::min(x + 2, width_ - 1);
  int update_top = std::max(y - 2, 0);
  int update_bottom = std::min(y + 2, height_ - 1);
  std::queue<int> queue;    //for openings opening

  if (normal_click){
    clicks = 1;
    states[index] = SQUARE_OPENED;
    if (squares_[index].value_ == 0)
      queue.push((x << 16) | y);  //opening opening
  }
  else{
    clicks = 1 + (states[index] == SQUARE_UNOPENED);
    states[index] = SQUARE_OPENED;
    premium_sets[premiums[index]].erase((x << 16) | y);   //erase it from the premium set
    premiums[index] = -1;                                 //because premium is no -1

    for (x_it = x - 1; x_it <= x + 1; x_it++){
      for (y_it = y - 1; y_it <= y + 1; y_it++){
        if (x_it >= 0 && x_it < width_ && y_it >= 0 && y_it < height_ && (x_it != x || y_it != y)){
          index = getIndex(x_it, y_it);
          if (squares_[index].value_ == -1){    //flagging
            if (states[index] != SQUARE_FLAGGED){
              states[index] = SQUARE_FLAGGED;
              clicks++;
            }
          }
          else{                                 //and opening because of the chord
            states[index] = SQUARE_OPENED;
            if (squares_[index].value_ == 0)
              queue.push((x_it << 16) | y_it);
          }
        }
      }
    }
  }
  //opening the openings
  while (!queue.empty()){
    x = queue.front() >> 16;   //so i use just one int per index, but avoid an expensive divide and modulo to get x and y
    y = queue.front() & 0x0000ffff;
    queue.pop();
    for (x_it = x - 1; x_it <= x + 1; x_it++){
      for (y_it = y - 1; y_it <= y + 1; y_it++){
        if (x_it >= 0 && x_it < width_ && y_it >= 0 && y_it < height_ && (x_it != x || y_it != y)){
          index = getIndex(x_it, y_it);
          if (states[index] == SQUARE_UNOPENED){
            if (squares_[index].value_ == 0)
              queue.push((x_it << 16) | y_it);
            states[index] = SQUARE_OPENED;
            update_left = std::min(update_left, std::max(x_it - 1, 0));   //adjust the premium update region
            update_right = std::max(update_right, std::min(x_it + 1, width_ - 1));
            update_top = std::min(update_top, std::max(y_it - 1, 0));
            update_bottom = std::max(update_bottom, std::min(y_it + 1, height_ - 1));
          }
        }
      }
    }
  }
  //recalculate the premiums which need an update
  int temp_premium;
  for (x_it = update_left; x_it <= update_right; x_it++){
    for (y_it = update_top; y_it <= update_bottom; y_it++){
      index = getIndex(x_it, y_it);
      if (!is_HZiNi || states[index] == SQUARE_OPENED){
        temp_premium = calcPremium(x_it, y_it, states, is_HZiNi, tricky_squares);
        if (temp_premium != premiums[index]){   //update just if it changed
          if (premiums[index] >= 0)             //if < 0, there would be nothing to delete (would cause a wrong array index)
            premium_sets[premiums[index]].erase((x_it << 16) | y_it);
          if (temp_premium >= 0){            //if < 0, nothing to insert (would cause a wrong array index)
            premium_sets[temp_premium].insert((x_it << 16) | y_it);
          }
          premiums[index] = temp_premium;   //set the premium correct
        }
      }
    }
  }

  return clicks;
}

bool Board::calcZiNi(int& ZiNi, int* states, const BitArray& tricky_squares) const {
  if (stats_.ZiNi_ != 0){
    ZiNi = stats_.ZiNi_;
    return true;
  }
  ZiNi = 0;

  if (stats_.bbbv_ == 0){
    ZiNi = 1;
    return false;
  }

  memset(states, 0, width_ * height_ * sizeof(int));

  //possible premiums are from -1 to 7, but just 0 to 7 will result in a chord -> just store them
  //a set is used, because it sorts it´s elements (for zini/hzini, the top-left most square has to be "performed" first)
  std::vector<std::set<int>> premium_sets;
  int* premiums = nullptr;

  try{
    premiums = new int[width_ * height_];
    premium_sets.resize(8);
  }
  catch (std::exception&){
    wxMessageBox("Not enough memory for ZiNi calculation!", "Error", wxICON_ERROR);
    ZiNi = 1;
    return false;
  }

  //first calc all premiums
  if (!calcAllPremiums(states, premiums, premium_sets, tricky_squares)){
    delete[] premiums;
    return false;
  }

  int i = 0;
  int value = 0;
  int index = 0;
  int open_square_position_x = 0; //this are use that i don´t have to go through the whole board all the time (there cannnot be a unopened square before the square last opened with a normal click)
  int open_square_position_y = 0;
  int x = 0, y = 0;
  while (x < width_){
    //find the top-left most square (first in set) in the highest premium set and perform the zini there
    for (i = 7; i >= 0; i--){
      if (!premium_sets[i].empty()){
        value = *(premium_sets[i].begin());
        ZiNi += performZiNi(value >> 16, value & 0x0000ffff, states, premiums, premium_sets, tricky_squares, false, false);
        break;
      }
    }
    //if no premium >= 0 found, perform normal click
    if (i == -1){
      x = open_square_position_x;
      y = open_square_position_y;
      while (x < width_){   //if x==width_, all squares are opened
        index = getIndex(x, y);
        if (states[index] == SQUARE_UNOPENED && (is_3BV_square_.getBit(index) || squares_[index].value_ == 0)){    //just open unopened 3BV squares (also 0, because every 0 is a 3BV, but need not be in the BitArray)
          states[index] = SQUARE_OPENED;
          performZiNi(x, y, states, premiums, premium_sets, tricky_squares, true, false);
          ZiNi++;
          open_square_position_x = x;   //till this index, it´s sure every square is opened
          open_square_position_y = y;
          break;
        }
        y++;
        if (y >= height_){    //new column
          y -= height_;
          x++;
        }
      }
    }
  }

  delete[] premiums;
  return true;
}

bool Board::calcHZiNi(int& hZiNi, int* states, const BitArray& tricky_squares) const{
  wxStopWatch temp_watch; //watch to measure, if it´s taking long
  bool question_to_ask = true;  //!(did the program already ask if calculate really)

  if (stats_.hZiNi_ != 0){
    hZiNi = stats_.hZiNi_;
    return true;
  }
  hZiNi = 0;
  if (stats_.bbbv_ == 0){
    hZiNi = 1;
    return false;
  }

  memset(states, 0, width_ * height_ * sizeof(int));

  std::vector<std::set<int>> premium_sets;
  int* premiums = nullptr;

  try{
    premiums = new int[width_ * height_];
    premium_sets.resize(8);
  }
  catch (std::exception&){
    wxMessageBox("Not enough memory for ZiNi calculation!", "Error", wxICON_ERROR);
    hZiNi = 1;
    return false;
  }

  int i;

  memset(premiums, -1, width_ * height_ * sizeof(int));   //set all premiums to negative value
  //first open all openings
  for (int i = width_* height_ - 1; i >= 0; i--){
    if (squares_[i].value_ == 0 && is_3BV_square_.getBit(i)){
      performZiNi(i % width_, i / width_, states, premiums, premium_sets, tricky_squares, true, true);
      hZiNi++;
    }
  }
  temp_watch.Start(); //start time here, because else percentage is wrong

  //now the same as in clacZiNi
  int value;
  int index;
  int open_square_position_x = 0;
  int open_square_position_y = 0;
  int x = 0, y = 0;
  while (x < width_){
    for (i = 7; i >= 0; i--){
      if (!premium_sets[i].empty()){
        value = *(premium_sets[i].begin());
        hZiNi += performZiNi(value >> 16, value & 0x0000ffff, states, premiums, premium_sets, tricky_squares, false, true);
        break;
      }
    }
    if (i == -1){
      x = open_square_position_x;
      y = open_square_position_y;
      while (x < width_){
        index = getIndex(x, y);
        if (states[index] == SQUARE_UNOPENED && is_3BV_square_.getBit(index)){
          states[index] = SQUARE_OPENED;
          performZiNi(x, y, states, premiums, premium_sets, tricky_squares, true, true);
          hZiNi++;
          open_square_position_x = x;
          open_square_position_y = y;
          break;
        }
        y++;
        if (y >= height_){
          y -= height_;
          x++;
        }
      }
    }
    if (question_to_ask && temp_watch.Time() > 1000){
      question_to_ask = false;
      if (wxMessageBox("Stop calculation of ZiNi and hZiNi? (this may take a while)\n\nApproximately " +
        wxString::Format("%.0f", 50.f * static_cast<float>(hZiNi) / mines_) + "% done", "MySweeper", wxYES_NO | wxICON_QUESTION) == wxYES)
      {
        hZiNi = 0;
        delete[] premiums;
        return false;
      }
    }
  }

  delete[] premiums;
  return true;
}

void Board::calc3BV_ZiNi_hZiNi(){
  int* states = nullptr;
  BitArray* tricky_squares = nullptr;    //these are squares with 2 adjecent openings
  try{
    states = new int[width_*height_];
    tricky_squares = new BitArray(width_*height_, BitArray::DEFAULT_VALUE_0);
  }
  catch (std::exception&){
    wxMessageBox("Not enough memory for ZiNi calculation!", "Error", wxICON_ERROR);
    delete states;
    return;
  }

  wxStopWatch temp_watch;
  temp_watch.Start();
  if (!calc3BV(stats_.bbbv_, stats_.solved_3BV_, is_3BV_square_, states, tricky_squares)){
    delete tricky_squares;
    delete[] states;
    return;
  }
  if (app_->settings_->no_zini_on_big_board_ && (width_ * height_) > 2500){
    stats_.ZiNi_ = 0;
    stats_.hZiNi_ = 0;
    delete tricky_squares;
    delete[] states;
    return;
  }
  if (temp_watch.Time() > 100){ //if calculating 3BV takes so long, zini and hzini will take really long (kill process will be needed to stop this then)
    if (wxMessageBox("Stop calculation of ZiNi and hZiNi? (recommended, because this may take a long time)", 
      "MySweeper", wxYES_NO | wxICON_QUESTION) == wxYES)
    {
      stats_.ZiNi_ = 0;
      stats_.hZiNi_ = 0;
      delete tricky_squares;
      delete[] states;
      return;
    }
  }
  if (!calcHZiNi(stats_.hZiNi_, states, *tricky_squares)){
    delete tricky_squares;
    delete[] states;
    return;
  }
  if (!calcZiNi(stats_.ZiNi_, states, *tricky_squares)){
    delete tricky_squares;
    delete[] states;
    return;
  }
  delete tricky_squares;
  delete[] states;
}

void Board::calcStats(){
  calc3BV_ZiNi_hZiNi();
  updateStats();
}

void Board::updateStats(long time){
  if(time == -1)    //if != -1 then use the given time
    time = (stats_.solved_3BV_ == stats_.bbbv_) ? stats_.time_ : getTime();
  stats_.style_ = style_;

  stats_.estimated_time_ = stats_.solved_3BV_ ? (static_cast<float>(time)* stats_.bbbv_ / stats_.solved_3BV_ / 1000.f) : 999.999;    //time_ is milliseconds
  stats_.bbbvs_ = static_cast<float>(stats_.solved_3BV_) * 1000 / time;
  
  stats_.ZiNis_ = (stats_.solved_3BV_ == stats_.bbbv_) ? 
    (static_cast<float>(stats_.ZiNi_) * 1000 / (stats_.time_ ? stats_.time_ : INT_MAX)) : 0;
  stats_.hZiNis_ = (stats_.solved_3BV_ == stats_.bbbv_) ? 
    (static_cast<float>(stats_.hZiNi_) * 1000 / (stats_.time_ ? stats_.time_ : INT_MAX)) : 0;
  stats_.ioe_ = stats_.getClicks() ? static_cast<float>(stats_.solved_3BV_) / stats_.getClicks() : 0;     //avoid devide by 0
  stats_.rqp_ = stats_.bbbvs_ ? stats_.estimated_time_ / stats_.bbbvs_ : 999.999;
  stats_.ios_ = log10(static_cast<float>(stats_.bbbv_)) / log10(stats_.estimated_time_);
}

void Board::resetStats(bool reset3BVZiNihZiNi){   //don´t reset 3BV,zini,hzini if this is false
  stats_.resetStats(reset3BVZiNihZiNi);
  if (reset3BVZiNihZiNi)
    is_3BV_square_.setAll(false);
}