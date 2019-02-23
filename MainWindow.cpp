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
#include "MainWindow.h"
#include "SegmentDisplayPanel.h"
#include "BoardPanel.h"
#include "Board.h"
#include "SmileyButton.h"
#include "CustomDialog.h"
#include "SettingsDialog.h"
#include "Settings.h"
#include "Highscores.h"
#include "HighscoreDialog.h"
#include "Counters.h"
#include "VideoPlayer.h"
#include "VideoRecorder.h"
#include "VideoPlayerDialog.h"
#include "HelpDialog.h"
#include "AboutDialog.h"
#include "HistoryDialog.h"
#include "Images.h"

MainWindow::MainWindow(MyApp* app, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
  : MainWindow_B(parent, id, title, pos, size, style), timer_(this), app_(app)
{
  board_panel_->setMainWindowPointer(this);
  board_panel_->setAppPointer(app_);
  smiley_button_->setMainWindowPointer(this);
  #ifdef __WXMSW__
  SetIcon(xpm_icon_32p);    //in windows just 32p icon possible
  #else
  SetIcon(xpm_icon);
  #endif

  Connect(timer_.GetId(), wxEVT_TIMER, wxTimerEventHandler(MainWindow::OnTimer), NULL, this);
  
  if (app_->settings_->position_.x >= 0 && app_->settings_->position_.x < wxSystemSettings::GetMetric(wxSYS_SCREEN_X) - 32 &&
      app_->settings_->position_.y >= 0 && app_->settings_->position_.y < wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) - 32)
    SetPosition(app_->settings_->position_);
  Show(true);
  resize(app_->settings_->square_size_);
  SetStatusText("ready");
  show_counter_menu_item_->Check(app_->settings_->counters_shown_);

  //initialize additional digits (they are just hidden if not needed)
  for (int i = 0; i < 3; i++){
    additional_mines_digits_[i] = new SegmentDisplayPanel(mines_display_panel_, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxFULL_REPAINT_ON_RESIZE | wxNO_BORDER);
    additional_mines_digits_[i]->SetForegroundColour(wxColour(255, 0, 0));
    additional_mines_digits_[i]->SetBackgroundColour(wxColour(0, 0, 0));
    additional_mines_digits_[i]->SetMinSize(wxSize(12, -1));
    additional_mines_digits_[i]->Hide();

    additional_time_digits_[i] = new SegmentDisplayPanel(time_display_panel_, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxFULL_REPAINT_ON_RESIZE | wxNO_BORDER);
    additional_time_digits_[i]->SetForegroundColour(wxColour(255, 0, 0));
    additional_time_digits_[i]->SetBackgroundColour(wxColour(0, 0, 0));
    additional_time_digits_[i]->SetMinSize(wxSize(12, -1));
    additional_time_digits_[i]->Hide();
  }
}

MainWindow::~MainWindow(){
  Disconnect(timer_.GetId(), wxEVT_TIMER, wxTimerEventHandler(MainWindow::OnTimer), NULL, this);
}

void MainWindow::OnTimer(wxTimerEvent& event){
  displayed_time_++;
  setTimeDisplay(displayed_time_);
}

void MainWindow::OnUpperPanelEnter(wxMouseEvent& event){
  if (app_->settings_->restart_on_upper_panel_)
    smiley_button_->mouseEnter(event);
}

void MainWindow::OnUpperPanelLeave(wxMouseEvent& event){
  if (app_->settings_->restart_on_upper_panel_)
    smiley_button_->mouseLeave(event);
}

void MainWindow::OnUpperPanelLeftDown(wxMouseEvent& event){
  if (app_->settings_->restart_on_upper_panel_)
    smiley_button_->leftDown(event);
}

void MainWindow::OnUpperPanelLeftUp(wxMouseEvent& event){
  if (app_->settings_->restart_on_upper_panel_)
    smiley_button_->leftUp(event);
}

void MainWindow::OnClose(wxCloseEvent& event){
  app_->settings_->position_ = GetPosition();
  app_->settings_->square_size_ = board_panel_->getSquareSize();

  //don´t save window size, if it´s custom (because maybe you can´t open it again on slow machines, if generating a 10000x10000 board)
  if (app_->board_->getStyle() == BOARD_STYLE_CUSTOM){
    app_->settings_->width_ = 30;
    app_->settings_->height_ = 16;
    app_->settings_->mines_ = 99;
  }
  else{
    app_->settings_->width_ = app_->board_->getWidth();
    app_->settings_->height_ = app_->board_->getHeight();
    app_->settings_->mines_ = app_->board_->getMines();
  }
  if (app_->counters_->isShown())
    app_->settings_->counters_position_ = app_->counters_->GetPosition();
  app_->video_player_->endVideo();
  event.Skip();
}

void MainWindow::keyDown(wxKeyEvent& key){
  if (app_->settings_->restart_spacebar_ && key.GetKeyCode() == WXK_SPACE)
    newBoard();
  switch (key.GetKeyCode())
  {
    case WXK_NUMPAD1:         setBoardStyle(BOARD_STYLE_BEG);           break;
    case WXK_NUMPAD2:         setBoardStyle(BOARD_STYLE_INT);           break;
    case WXK_NUMPAD3:         setBoardStyle(BOARD_STYLE_EXP);           break;
    case WXK_NUMPAD4:         openCustomDialog();                       break;
    case WXK_NUMPAD_ADD:      increaseSize();                           break;
    case WXK_NUMPAD_SUBTRACT: decreaseSize();                           break;
    default:                                                            break;
  }
#ifdef __WXGTK__   //on linux hotkeys doesn´t work (don´t know if they do 
  switch (key.GetKeyCode())
  {
    case '1':           setBoardStyle(BOARD_STYLE_BEG);           break;
    case '2':           setBoardStyle(BOARD_STYLE_INT);           break;
    case '3':           setBoardStyle(BOARD_STYLE_EXP);           break;
    case '4':           openCustomDialog();                       break;
    case '+':           increaseSize();                           break;
    case '-':           decreaseSize();                           break;
    case WXK_F2:        newBoard();                               break;
    default:                                                      break;
  }
#endif
}

void MainWindow::startTime(float speed){
  displayed_time_ = 1;
  setTimeDisplay(displayed_time_);
  timer_.Start(1000 / speed);
}

void MainWindow::stopTime(int time){
  timer_.Stop();
  setTimeDisplay(time);
}

void MainWindow::adjustDigitNumber(){
  int old_digit_number = additional_digits_;
  //number of additional digits depends on number of mines ( >1000 -> 4, >10000 -> 5, >100000 -> 6)
  //here adding if needed
  if (app_->board_->getMines() >= 1000 && additional_digits_ < 1){
    mines_display_sizer_->Insert(0, additional_mines_digits_[0], 1, wxEXPAND);
    time_display_sizer_->Insert(0, additional_time_digits_[0], 1, wxEXPAND);
    additional_mines_digits_[0]->Show();
    additional_time_digits_[0]->Show();
    additional_digits_ = 1;
  }
  if (app_->board_->getMines() >= 10000 && additional_digits_ < 2){
    mines_display_sizer_->Insert(0, additional_mines_digits_[1], 1, wxEXPAND);
    time_display_sizer_->Insert(0, additional_time_digits_[1], 1, wxEXPAND);
    additional_mines_digits_[1]->Show();
    additional_time_digits_[1]->Show();
    additional_digits_ = 2;
  }
  if (app_->board_->getMines() >= 100000 && additional_digits_ < 3){
    mines_display_sizer_->Insert(0, additional_mines_digits_[2], 1, wxEXPAND);
    time_display_sizer_->Insert(0, additional_time_digits_[2], 1, wxEXPAND);
    additional_mines_digits_[2]->Show();
    additional_time_digits_[2]->Show();
    additional_digits_ = 3;
  }

  //here removing if needed
  if (app_->board_->getMines() < 100000 && additional_digits_ > 2){
    mines_display_sizer_->Remove(0);
    time_display_sizer_->Remove(0);
    additional_mines_digits_[2]->Hide();
    additional_time_digits_[2]->Hide();
    additional_digits_ = 2;
  }
  if (app_->board_->getMines() < 10000 && additional_digits_ > 1){
    mines_display_sizer_->Remove(0);
    time_display_sizer_->Remove(0);
    additional_mines_digits_[1]->Hide();
    additional_time_digits_[1]->Hide();
    additional_digits_ = 1;
  }
  if (app_->board_->getMines() < 1000 && additional_digits_ > 0){
    mines_display_sizer_->Remove(0);
    time_display_sizer_->Remove(0);
    additional_mines_digits_[0]->Hide();
    additional_time_digits_[0]->Hide();
    additional_digits_ = 0;
  }

  //rearranging GUI just if needed
  if (old_digit_number != additional_digits_){
    int square_size = board_panel_->getSquareSize();
    mines_display_panel_->SetMinClientSize(
      wxSize((15 + 5 * additional_digits_) * square_size / 8 + 6 + 2 * additional_digits_, 21 * square_size / 16 + 2));
    mines_display_panel_->Refresh();
    time_display_panel_->SetMinClientSize(
      wxSize((15 + 5 * additional_digits_) * square_size / 8 + 6 + 2 * additional_digits_, 21 * square_size / 16 + 2));
    time_display_panel_->Refresh();
    upper_panel_->Layout();
    upper_panel_->Refresh();
    main_panel_->Fit();
    Fit();
  }
}

void MainWindow::changeBoardSize(){
  adjustDigitNumber();
  board_panel_->changeBoardSize();
  main_panel_->Fit();
  Fit();
}

void MainWindow::instantBoardUpdate(){
  board_panel_->Refresh();
  board_panel_->Update();
}

void MainWindow::updateBoardView(int x1, int y1, int x2, int y2){
  board_panel_->updateBoard(x1, y1, x2, y2);
}

void MainWindow::resize(int square_size){
  if (square_size != -1){                                                       //-1 means, same square_size
    square_size = board_panel_->resizeSquares(square_size);
    main_panel_->Fit();
    mines_display_panel_->SetMinClientSize(
      wxSize((15 + 5 * additional_digits_) * square_size / 8 + 6 + 2 * additional_digits_, 21 * square_size / 16 + 2));
    mines_display_panel_->Refresh();
    time_display_panel_->SetMinClientSize(
      wxSize((15 + 5 * additional_digits_) * square_size / 8 + 6 + 2 * additional_digits_, 21 * square_size / 16 + 2));
    time_display_panel_->Refresh();
    smiley_button_->resize(3 * square_size / 2);
    smiley_button_->Refresh();
    upper_panel_->SetMinClientSize(wxSize(-1, 27 * square_size / 16 + 6));
  }
  upper_panel_->Refresh();
  main_panel_->Fit();
  Fit();

  //disalbe decrease size menu item if square size == 16
  if (square_size == 16)
    options_menu_->Enable(decrease_size_item_->GetId(), false);
  else
    options_menu_->Enable(decrease_size_item_->GetId(), true);
}

void MainWindow::setTimeDisplay(int time){
  time = std::min(time, static_cast<int>(1000 * pow(10, additional_digits_) - 1));    //if maximum reached, stay on all digits 9
  additional_time_digits_[2]->setValue((time / 100000) % 10);
  additional_time_digits_[1]->setValue((time / 10000) % 10);
  additional_time_digits_[0]->setValue((time / 1000) % 10);
  time_digit_100_->setValue((time / 100) % 10);
  time_digit_10_->setValue((time / 10) % 10);
  time_digit_1_->setValue(time % 10);
}

void MainWindow::setMinesDisplay(int mines){
  additional_mines_digits_[2]->setValue((mines / 100000) % 10);
  additional_mines_digits_[1]->setValue((mines / 10000) % 10);
  additional_mines_digits_[0]->setValue((mines / 1000) % 10);
  mines_digit_100_->setValue((mines / 100) % 10);
  mines_digit_10_->setValue((abs(mines) / 10) % 10);
  mines_digit_1_->setValue(abs(mines) % 10);
  if (mines < 0){
    if (additional_digits_ == 0)
      mines_digit_100_->setValue(-1);
    else
      additional_mines_digits_[additional_digits_ - 1]->setValue(-1);
  }
}

void MainWindow::setSmileyFace(SmileyFace face){
  smiley_button_->setFace(face);
}

void MainWindow::newBoard(wxCommandEvent& event){
  newBoard(event.GetEventObject() != new_menu_item_);
}

void MainWindow::newBoard(bool change_size){
  if (app_->board_ == 0){
    wxMessageBox("No Board set. Please report bug", "Error");
    return;
  }
  app_->video_player_panel_->hide();
  app_->board_->generateBoard();
  board_panel_->setOrigin(0, 0);
  if (change_size)
    changeBoardSize();
  updateBoardView();
  setSmileyFace(SMILEY_FACE_NORMAL);
  stopTime(0);                                  //time must be stopped when old game is not finished
  app_->main_window_->actiatePreview(false);    //no preview and video saving possible
  SetStatusText("ready");
}

void MainWindow::setBoardStyle(BoardStyle style){
  if (app_->board_ == 0){
    wxMessageBox("No Board set. Please report bug", "Error");
    return;
  }
  app_->board_->setBoardStyle(style);
  resize(-1);

  newBoard(true);
}

void MainWindow::setCustomBoardStyle(int width, int height, int mines){
  if (app_->board_ == 0){
    wxMessageBox("No Board set. Please report bug", "Error");
    return;
  }
  app_->settings_->custom_width_ = width;
  app_->settings_->custom_height_ = height;
  app_->settings_->custom_mines_ = mines;
  app_->board_->setCustomBoard(width, height, mines);
  resize(-1);

  newBoard(true);
}

void MainWindow::setBoardBeginner(wxCommandEvent& event){
  setBoardStyle(BOARD_STYLE_BEG);
}

void MainWindow::setBoardIntermediate(wxCommandEvent& event){
  setBoardStyle(BOARD_STYLE_INT);
}

void MainWindow::setBoardExpert(wxCommandEvent& event){
  setBoardStyle(BOARD_STYLE_EXP);
}

void MainWindow::playVideo(wxCommandEvent& event){
  wxFileDialog play_video_dialog(this, "Play Video", app_->settings_->auto_save_location_, "",    //open file dialog
    "MySweeper Video Files (*.myswv)|*.myswv", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
  if (play_video_dialog.ShowModal() == wxID_CANCEL)
    return; 

  app_->video_player_panel_->show(play_video_dialog.GetPath());
}

void MainWindow::actiatePreview(bool activate){
  preview_video_menu_item_->Enable(activate);
  save_video_menu_item_->Enable(activate);
}

void MainWindow::previewVideo(wxCommandEvent& event){
  app_->video_player_panel_->show(app_->video_recorder_->getVideo());
}

void MainWindow::saveVideo(wxCommandEvent& event){
  if (app_->video_recorder_->getVideo()->isCorrect()){
    wxString filename = app_->settings_->default_video_name_;   //construct the default video name
    filename.Replace("$name", app_->settings_->name_.getValue());
    filename.Replace("$time", wxString::Format("%.3f", static_cast<float>(app_->board_->getStats()->time_) / 1000));
    filename.Replace("$3bv", wxString::Format("%d", app_->board_->getStats()->bbbv_));
    filename.Replace("$style", app_->board_->getStyleString());

    wxFileDialog save_video_dialog(this, "Play Video", app_->settings_->auto_save_location_, filename,
      "MySweeper Video Files (*.myswv)|*.myswv", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (save_video_dialog.ShowModal() == wxID_CANCEL)
      return;

    filename = save_video_dialog.GetPath();
    if (wxFileName(filename).Exists())      //remove if file with same name exists (override), else index would be applied
      wxRemoveFile(filename);

    if (!filename.EndsWith(".myswv"))     //add this extension
      filename += ".myswv";
    app_->video_recorder_->saveVideo(filename);
  }
}

void MainWindow::openCustomDialog(){
  CustomDialog* custom_dialog = new CustomDialog(this);
  custom_dialog->ShowModal();
  custom_dialog->Destroy();
}

void MainWindow::openSettingsDialog(wxCommandEvent& event){
  bool question_mark_setting = app_->settings_->question_marks_enabled_; 
  SettingsDialog* settings_dialog = new SettingsDialog(app_->settings_, this);
  settings_dialog->enableQuestionMarkSetting(!app_->video_player_->isActive()); //while playing video, should not be enabled (causes problems while video)
  settings_dialog->ShowModal();
  settings_dialog->Destroy();
  if (question_mark_setting != app_->settings_->question_marks_enabled_ && app_->video_recorder_->isRecording())
    app_->video_recorder_->addAdditionalEvent(   //save a event, if changed while recording
      AdditionalEvent(ADDITIONAL_EVENT_QUESTIONMARK_SET, app_->board_->getTime(), app_->settings_->question_marks_enabled_));
  app_->counters_->setSize(!app_->settings_->counters_not_show_all_);   //if counters are changed (small / complete version)
  if (show_counter_menu_item_->IsChecked() && (!(app_->settings_->hide_counters_while_playing_ && app_->board_->isRunning())))
    app_->counters_->showCounters(true);
  else
    app_->counters_->showCounters(false);
  resize(board_panel_->getSquareSize());    //this is needed, if maximum window size is changed
}

void MainWindow::showHighscores(int page){
  Highscores highscores;
  HighscoreDialog* highscores_dialog = new HighscoreDialog(&highscores, this);
  highscores_dialog->show(page);
  highscores_dialog->Destroy();
}

void MainWindow::showHistory(wxCommandEvent& event){
  HistoryDialog* history_dialog = new HistoryDialog(app_, this);
  history_dialog->ShowModal();
  history_dialog->Destroy();
}

void MainWindow::showVideoCursor(bool show){ 
  board_panel_->showCursor(show); 
}

void MainWindow::setVideoCursor(const wxPoint& pos){
  board_panel_->setCursor(pos);
}

void MainWindow::focusOnCursorIfNotSeen(){
  board_panel_->focusOnCursorIfNotSeen();
}

void MainWindow::showHighscores(wxCommandEvent& event){
  showHighscores(0);
}

void MainWindow::showCounters(wxCommandEvent& event){
  app_->settings_->counters_shown_ = event.IsChecked();
  if (app_->settings_->counters_shown_ && (!(app_->settings_->hide_counters_while_playing_ && app_->board_->isRunning())))
    app_->counters_->showCounters(true);
  else
    app_->counters_->showCounters(false);
}

void MainWindow::OnHelp(wxCommandEvent& event){
  HelpDialog* help_dialog = new HelpDialog();
  help_dialog->ShowModal();
  help_dialog->Destroy();
}

void MainWindow::OnAbout(wxCommandEvent& event){
  AboutDialog* help_dialog = new AboutDialog();
  help_dialog->ShowModal();
  help_dialog->Destroy();
}


void MainWindow::exit(wxCommandEvent& event){
  Close(true);
}

int MainWindow::getSquareSize(){
  return board_panel_->getSquareSize();
}

void MainWindow::increaseSize(){
  int square_size = board_panel_->getSquareSize();
  if (square_size < 32)
    square_size += 8;
  else if (square_size < 64)
    square_size += 16;
  else
    square_size += 32;

  resize(square_size);
}

void MainWindow::decreaseSize(){
  int square_size = board_panel_->getSquareSize();
  if (square_size <= 16)
    return;

  if (square_size > 64)
    square_size -= 32;
  else if (square_size > 32)
    square_size -= 16;
  else
    square_size -= 8;

  resize(square_size);
}

bool MainWindow::isScrollMode(){
  return board_panel_->isScrollMode();
}

int MainWindow::getMaxBoardPanelSizeX(){
  if (app_->settings_->limit_window_size_)
    return std::min(wxSystemSettings::GetMetric(wxSYS_SCREEN_X), static_cast<int>(app_->settings_->max_window_width_)) -
      (GetSize().GetWidth() - board_panel_->GetClientSize().GetWidth());

  //screen size - (difference of main window - board_panel (is the border))
  return wxSystemSettings::GetMetric(wxSYS_SCREEN_X) -
    (GetSize().GetWidth() - board_panel_->GetClientSize().GetWidth());
}

int MainWindow::getMaxBoardPanelSizeY(){
  if (app_->settings_->limit_window_size_)
    return std::min(wxSystemSettings::GetMetric(wxSYS_SCREEN_Y), static_cast<int>(app_->settings_->max_window_height_)) -
    (GetSize().GetHeight() - board_panel_->GetClientSize().GetHeight() +
    (27 * board_panel_->getSquareSize() / 16 + 6 - upper_panel_->GetClientSize().GetY()));      //this line represents the change in upper panel size
     
  //screen size - (difference of main window - board_panel (is the border) + how the upper panel changes)
  return wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) -
    (GetSize().GetHeight() - board_panel_->GetClientSize().GetHeight() + 
    (27 * board_panel_->getSquareSize() / 16 + 6 - upper_panel_->GetClientSize().GetY()));      //this line represents the change in upper panel size
}
