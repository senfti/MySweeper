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
#include "Highscores.h"
#include "BoardStats.h"
#include <wx/stdpaths.h>

SingleHighscore::SingleHighscore(const std::vector<std::string>& nodes, bool is_3bvs, HighscoreStyle highscore_style, 
  MY::SettingFileIn_Base* file) : nodes_(nodes), is_3bvs_(is_3bvs), highscore_style_(highscore_style)
{
  readFromMySettingFile(file);
}

SingleHighscore::SingleHighscore(std::vector<std::string>&& nodes, bool is_3bvs, HighscoreStyle highscore_style, 
  MY::SettingFileIn_Base* file) : is_3bvs_(is_3bvs), highscore_style_(highscore_style)
{
  nodes_ = nodes;
  readFromMySettingFile(file);
}

bool SingleHighscore::newScore(const BoardStats& stats){
  if ((stats.style_ == BOARD_STYLE_BEG && stats.bbbv_ < 2) ||     //boards with smaller 3BV are not valid for highscores
      (stats.style_ == BOARD_STYLE_INT && stats.bbbv_ < 30) ||
      (stats.style_ == BOARD_STYLE_EXP && stats.bbbv_ < 100))
    return false;

  if ((!is_3bvs_ && stats.time_ < (time_ * 1000)) || (is_3bvs_ && stats.bbbvs_ > bbbvs_)){    //if time or 3BV/s highscore, which is tested is defined with is_3bvs_
    std::string style_texts[] = { "Beginner ", "Intermediate ", "Expert " };
    std::string highscore_style_texts[] = { "", "NF ", "flagging " };
    time_ = static_cast<float>(stats.time_) / 1000;
    bbbv_ = stats.bbbv_;
    bbbvs_ = stats.bbbvs_;
    date_.SetToCurrent();
    wxMessageBox("New " + style_texts[stats.style_] + highscore_style_texts[highscore_style_] + (is_3bvs_ ? "3BV/s" : "time") + 
      " record: " + wxString::Format(wxT("%.3f"), (is_3bvs_ ? bbbvs_ : time_)), "New Record");
    return true;
  }
  return false;
}

bool SingleHighscore::writeToMySettingFile(MY::SettingFileOut_Base* file){
  std::queue<std::string> attr_names;
  attr_names.push("time");
  attr_names.push("BBBV");
  attr_names.push("BBBVs");
  attr_names.push("date");
  file->setValues(attr_names, &nodes_, time_, bbbv_, bbbvs_, date_.Format("%Y-%m-%d %X"));  //just set the data, no writing here

  return file->isError();
}

bool SingleHighscore::readFromMySettingFile(MY::SettingFileIn_Base* file){
  std::queue<std::string> attr_names;
  attr_names.push("time");
  attr_names.push("BBBV");
  attr_names.push("BBBVs");
  attr_names.push("date");
  wxString date_string;
  file->getValues(attr_names, &nodes_, time_, bbbv_, bbbvs_, date_string);
  date_.ParseFormat(date_string, "%Y-%m-%d %X");

  return file->isError();
}

CustomHighscore::CustomHighscore(const std::vector<std::string>& nodes, MY::SettingFileIn_Base* file, int widht, int height)
: nodes_(nodes), width_(widht), height_(height)
{
  readFromMySettingFile(file);
}

CustomHighscore::CustomHighscore(std::vector<std::string>&& nodes, MY::SettingFileIn_Base* file, int widht, int height)
: width_(widht), height_(height)
{
  nodes_ = nodes;
  readFromMySettingFile(file);
}

bool CustomHighscore::writeToMySettingFile(MY::SettingFileOut_Base* file){
  std::queue<std::string> attr_names;
  attr_names.push("time");
  attr_names.push("BBBV");
  attr_names.push("mines");
  attr_names.push("date");
  file->setValues(attr_names, &nodes_, time_, bbbv_, mines_, date_.Format("%Y-%m-%d %X"));

  return file->isError();
}

bool CustomHighscore::readFromMySettingFile(MY::SettingFileIn_Base* file){
  std::queue<std::string> attr_names;
  attr_names.push("time");
  attr_names.push("BBBV");
  attr_names.push("mines");
  attr_names.push("date");
  wxString date_string;
  file->getValues(attr_names, &nodes_, time_, bbbv_, mines_, date_string);
  date_.ParseFormat(date_string, "%Y-%m-%d %X");

  return file->isError();
}

bool CustomHighscore::newScore(const BoardStats& stats){
  if (width_ == stats.width_ && height_ == stats.height_ && stats.mines_ > mines_){
    time_ = static_cast<float>(stats.time_) / 1000;
    bbbv_ = stats.bbbv_;
    mines_ = stats.mines_;
    date_.SetToCurrent();
    wxMessageBox("New custom record: " + wxString::Format(wxT("%dx%d %d mines"), width_, height_, mines_), "New Record");
    return true;
  }
  return false;
}

SizeHighscore::SizeHighscore(const std::vector<std::string>& nodes, MY::SettingFileIn_Base* file) : nodes_(nodes){
  readFromMySettingFile(file);
}

SizeHighscore::SizeHighscore(std::vector<std::string>&& nodes, MY::SettingFileIn_Base* file){
  nodes_ = nodes;
  readFromMySettingFile(file);
}

bool SizeHighscore::writeToMySettingFile(MY::SettingFileOut_Base* file){
  std::queue<std::string> attr_names;
  attr_names.push("time");
  attr_names.push("BBBV");
  attr_names.push("size");
  attr_names.push("date");
  file->setValues(attr_names, &nodes_, time_, bbbv_, size_, date_.Format("%Y-%m-%d %X"));

  return file->isError();
}

bool SizeHighscore::readFromMySettingFile(MY::SettingFileIn_Base* file){
  std::queue<std::string> attr_names;
  attr_names.push("time");
  attr_names.push("BBBV");
  attr_names.push("size");
  attr_names.push("date");
  wxString date_string;
  file->getValues(attr_names, &nodes_, time_, bbbv_, size_, date_string);
  date_.ParseFormat(date_string, "%Y-%m-%d %X");

  return file->isError();
}

bool SizeHighscore::newScore(const BoardStats& stats){
  if (ceil(0.20625 * stats.width_*stats.height_) == stats.mines_ && (stats.width_*stats.height_) > size_){
    time_ = static_cast<float>(stats.time_) / 1000;
    bbbv_ = stats.bbbv_;
    size_ = stats.width_*stats.height_;
    date_.SetToCurrent();
    wxMessageBox("New size record: " + wxString::Format(wxT("%d (%dx%d) squares"), size_, stats.width_, stats.height_), "New Record");
    return true;
  }
  return false;
}


Highscores::Highscores() : 
  beg_time_highscore_(std::vector<std::string>({ "highscores", "BEG" }), false, HIGHSCORE_STYLE_GENERAL),
  int_time_highscore_(std::vector<std::string>({ "highscores", "INT" }), false, HIGHSCORE_STYLE_GENERAL),
  exp_time_highscore_(std::vector<std::string>({ "highscores", "EXP" }), false, HIGHSCORE_STYLE_GENERAL),
  beg_3bvs_highscore_(std::vector<std::string>({ "highscores", "BEG_3BVs" }), true, HIGHSCORE_STYLE_GENERAL),
  int_3bvs_highscore_(std::vector<std::string>({ "highscores", "INT_3BVs" }), true, HIGHSCORE_STYLE_GENERAL),
  exp_3bvs_highscore_(std::vector<std::string>({ "highscores", "EXP_3BVs" }), true, HIGHSCORE_STYLE_GENERAL),
  nf_beg_time_highscore_(std::vector<std::string>({ "nf_highscores", "BEG" }), false, HIGHSCORE_STYLE_NF),
  nf_int_time_highscore_(std::vector<std::string>({ "nf_highscores", "INT" }), false, HIGHSCORE_STYLE_NF),
  nf_exp_time_highscore_(std::vector<std::string>({ "nf_highscores", "EXP" }), false, HIGHSCORE_STYLE_NF),
  nf_beg_3bvs_highscore_(std::vector<std::string>({ "nf_highscores", "BEG_3BVs" }), true, HIGHSCORE_STYLE_NF),
  nf_int_3bvs_highscore_(std::vector<std::string>({ "nf_highscores", "INT_3BVs" }), true, HIGHSCORE_STYLE_NF),
  nf_exp_3bvs_highscore_(std::vector<std::string>({ "nf_highscores", "EXP_3BVs" }), true, HIGHSCORE_STYLE_NF),
  flag_beg_time_highscore_(std::vector<std::string>({ "flag_highscores", "BEG" }), false, HIGHSCORE_STYLE_FLAG),
  flag_int_time_highscore_(std::vector<std::string>({ "flag_highscores", "INT" }), false, HIGHSCORE_STYLE_FLAG),
  flag_exp_time_highscore_(std::vector<std::string>({ "flag_highscores", "EXP" }), false, HIGHSCORE_STYLE_FLAG),
  flag_beg_3bvs_highscore_(std::vector<std::string>({ "flag_highscores", "BEG_3BVs" }), true, HIGHSCORE_STYLE_FLAG),
  flag_int_3bvs_highscore_(std::vector<std::string>({ "flag_highscores", "INT_3BVs" }), true, HIGHSCORE_STYLE_FLAG),
  flag_exp_3bvs_highscore_(std::vector<std::string>({ "flag_highscores", "EXP_3BVs" }), true, HIGHSCORE_STYLE_FLAG),
  custom_8_8_highscores_(std::vector<std::string>({ "custom_highscores", "CUSTOM_8_8" }), 8, 8),
  custom_9_9_highscores_(std::vector<std::string>({ "custom_highscores", "CUSTOM_9_9" }), 9, 9),
  custom_16_16_highscores_(std::vector<std::string>({ "custom_highscores", "CUSTOM_16_16" }), 16, 16),
  custom_30_16_highscores_(std::vector<std::string>({ "custom_highscores", "CUSTOM_30_16" }), 30, 16),
  custom_30_24_highscores_(std::vector<std::string>({ "custom_highscores", "CUSTOM_30_24" }), 30, 24),
  size_highscore_(std::vector<std::string>({ "size_highscores", "SIZE" }))
{
  highscores[0]  = &beg_time_highscore_;      highscores[1]  = &int_time_highscore_;      highscores[2] = &exp_time_highscore_;
  highscores[3] = &beg_3bvs_highscore_;       highscores[4] = &int_3bvs_highscore_;       highscores[5] = &exp_3bvs_highscore_;
  highscores[6] = &nf_beg_time_highscore_;    highscores[7] = &nf_int_time_highscore_;    highscores[8] = &nf_exp_time_highscore_;
  highscores[9] = &nf_beg_3bvs_highscore_;    highscores[10] = &nf_int_3bvs_highscore_;   highscores[11] = &nf_exp_3bvs_highscore_;
  highscores[12] = &flag_beg_time_highscore_; highscores[13] = &flag_int_time_highscore_; highscores[14] = &flag_exp_time_highscore_;
  highscores[15] = &flag_beg_3bvs_highscore_; highscores[16] = &flag_int_3bvs_highscore_; highscores[17] = &flag_exp_3bvs_highscore_;

  custom_highscores[0] = &custom_8_8_highscores_;
  custom_highscores[1] = &custom_9_9_highscores_;
  custom_highscores[2] = &custom_16_16_highscores_;
  custom_highscores[3] = &custom_30_16_highscores_;
  custom_highscores[4] = &custom_30_24_highscores_;

  filename_ = wxFileName(wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath(), HIGHSCORE_FILE_NAME).GetFullPath();    //highscore file must be in the same direction as the executable
  loadHighscores(filename_);
}

void Highscores::loadHighscores(const std::string& filename){
  if (!wxFileExists(filename)){
    wxMessageBox("Highscore file does not exist. A new one will be created.", "Highscore File Message", wxICON_EXCLAMATION);
    std::ofstream highscore_file(filename);
    saveHighscores(filename);
    highscore_file.close();
    return;
  }
  MY::XmlFileIn highscore_file(filename);
  if (highscore_file.isError()){
    if (highscore_file.popError() == MY::FILE_ERROR_PARSING_ERROR){
      wxMessageBox("Highscore file corrupted!\nHighscores will be set to default", "Highscore File Error", wxICON_ERROR);
      saveHighscores(filename);
    }
    else{
      wxMessageBox("Error while loading highscores!\nNo changes will be saved!", "Highscore File Error", wxICON_ERROR);
      no_highscore_saving_ = true;
    }
    return;
  }
  for (int i = 0; i < 18; i++)
    highscores[i]->readFromMySettingFile(&highscore_file);
  for (int i = 0; i < 5; i++)
    custom_highscores[i]->readFromMySettingFile(&highscore_file);
  size_highscore_.readFromMySettingFile(&highscore_file);

  if (highscore_file.isError())
    wxMessageBox("Highscore file corrupted!\n", "Highscore File Error", wxICON_ERROR);
}

void Highscores::saveHighscores(const std::string& filename){
  std::string filename_temp = filename.empty() ? filename_ : filename;
  if (no_highscore_saving_){
    wxMessageBox("No update of highscores because file could not be loaded!\n", "Highscore File Message", wxICON_EXCLAMATION);
    return;
  }

  MY::XmlFileOut highscore_file(filename_temp);
  if (highscore_file.isError()){
    wxMessageBox("Error while saving highscores!", "Highscore File Error", wxICON_ERROR);
    return;
  }
  for (int i = 0; i < 18; i++)
    highscores[i]->writeToMySettingFile(&highscore_file);
  for (int i = 0; i < 5; i++)
    custom_highscores[i]->writeToMySettingFile(&highscore_file);
  size_highscore_.writeToMySettingFile(&highscore_file);

  if (highscore_file.isError()){
    wxMessageBox("Error while saving highscores!", "Highscore File Error", wxICON_ERROR);
    return;
  }

  highscore_file.save();
  if (highscore_file.isError()){
    wxMessageBox("Error while saving highscores!", "Highscore File Error", wxICON_ERROR);
    return;
  }
}

int Highscores::newScore(const BoardStats& stats){
  int new_highscore = -1;

  //in reverse order of preference, which page to show
  for (int i = 0; i < 5; i++){
    if (custom_highscores[i]->newScore(stats))
      new_highscore = 3;
  }
  if (size_highscore_.newScore(stats))
    new_highscore = 3;

  if (stats.style_ != BOARD_STYLE_CUSTOM){
    if (highscores[stats.style_ + (stats.right_clicks_ ? 12 : 6)]->newScore(stats))
      new_highscore = (stats.right_clicks_ ? 2 : 1);
    if (highscores[stats.style_ + (stats.right_clicks_ ? 15 : 9)]->newScore(stats))    // flag / nf 3BV/s
      new_highscore = (stats.right_clicks_ ? 2 : 1);
    if (highscores[stats.style_]->newScore(stats))      //time
      new_highscore = 0;
    if (highscores[stats.style_ + 3]->newScore(stats))  //3BV/s
      new_highscore = 0;
  }

  if (new_highscore != -1)
    saveHighscores(filename_);

  return new_highscore;
}