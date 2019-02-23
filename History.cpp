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
#include "History.h"
#include <wx/stdpaths.h>

const char* HISTORY_FILE_NAME_ = "MySweeper.hist";

HistoryItem::HistoryItem(const BoardStats& stats, const wxDateTime& date){
  time_ = stats.time_ / 1000.f;
  bbbv_ = stats.bbbv_;
  zini_ = stats.ZiNi_;
  hzini_ = stats.hZiNi_;
  left_clicks_ = stats.left_clicks_;
  right_clicks_ = stats.right_clicks_;
  chord_clicks_ = stats.chord_clicks_;
  path_ = stats.path_;
  date_ = date;
  style_ = stats.style_;
}

bool HistoryItem::loadItem(std::ifstream& stream){
  stream.read(reinterpret_cast<char*>(&time_), sizeof(float));
  if (stream.eof())
    return true;
  stream.read(reinterpret_cast<char*>(&bbbv_), sizeof(int));
  stream.read(reinterpret_cast<char*>(&zini_), sizeof(int));
  stream.read(reinterpret_cast<char*>(&hzini_), sizeof(int));
  stream.read(reinterpret_cast<char*>(&left_clicks_), sizeof(int));
  stream.read(reinterpret_cast<char*>(&right_clicks_), sizeof(int));
  stream.read(reinterpret_cast<char*>(&chord_clicks_), sizeof(int));
  stream.read(reinterpret_cast<char*>(&path_), sizeof(float));
  unsigned long date_uint;
  stream.read(reinterpret_cast<char*>(&date_uint), sizeof(unsigned long));
  date_.SetFromDOS(date_uint);
  if (stream.eof()){
    wxMessageBox("Error while loading history! File will be repaired, but loss of data possible.", "History Loading Error", wxICON_ERROR);
    return false;
  }
  stream.read(reinterpret_cast<char*>(&style_), sizeof(int));

  if (stream.bad() || style_ < 0 || style_ > 2 || !date_.IsValid()){
    wxMessageBox("History file corrupted! File will be repaired, but loss of data possible.", "History Loading Error", wxICON_ERROR);
    return false;
  }
  return true;
}

bool HistoryItem::saveItem(std::ofstream& stream){
  stream.write(reinterpret_cast<const char*>(&time_), sizeof(float));
  stream.write(reinterpret_cast<const char*>(&bbbv_), sizeof(int));
  stream.write(reinterpret_cast<const char*>(&zini_), sizeof(int));
  stream.write(reinterpret_cast<const char*>(&hzini_), sizeof(int));
  stream.write(reinterpret_cast<const char*>(&left_clicks_), sizeof(int));
  stream.write(reinterpret_cast<const char*>(&right_clicks_), sizeof(int));
  stream.write(reinterpret_cast<const char*>(&chord_clicks_), sizeof(int));
  stream.write(reinterpret_cast<const char*>(&path_), sizeof(float));
  unsigned long date_uint = date_.GetAsDOS();
  stream.write(reinterpret_cast<const char*>(&date_uint), sizeof(unsigned long));
  stream.write(reinterpret_cast<const char*>(&style_), sizeof(int));

  if (stream.bad()){
    wxMessageBox("Error while saving to history! Nothing saved", "History Saving Error", wxICON_ERROR);
    return false;
  }
  return true;
}

void HistoryItem::addItemToFile(std::string filename){
  if (filename.empty())   //if no filename, use default filename
    filename = wxFileName(wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath(), HISTORY_FILE_NAME_).GetFullPath();
  std::ofstream stream(filename, std::ios_base::binary | std::ios_base::app);
  if (!stream.good()){
    wxMessageBox("Could not save to history!", "Warning", wxICON_WARNING);
  }
  saveItem(stream);
}

bool compareTime(const HistoryItem& left, const HistoryItem& right){ 
  return left.getTime() < right.getTime(); 
}
bool compare3BV(const HistoryItem& left, const HistoryItem& right){ 
  return left.get3BV() < right.get3BV(); 
}
bool compare3BVs(const HistoryItem& left, const HistoryItem& right){ 
  return left.get3BVs() < right.get3BVs(); 
}
bool compareZiNi(const HistoryItem& left, const HistoryItem& right){ 
  return left.getZiNi() < right.getZiNi(); 
}
bool compareZiNis(const HistoryItem& left, const HistoryItem& right){ 
  return left.getZiNis() < right.getZiNis(); 
}
bool comparehZiNi(const HistoryItem& left, const HistoryItem& right){
  return left.gethZiNi() < right.gethZiNi();
}
bool comparehZiNis(const HistoryItem& left, const HistoryItem& right){
  return left.gethZiNis() < right.gethZiNis();
}
bool compareIOE(const HistoryItem& left, const HistoryItem& right){ 
  return left.getIOE() < right.getIOE(); 
}
bool compareRQP(const HistoryItem& left, const HistoryItem& right){ 
  return left.getRQP() < right.getRQP(); 
}
bool compareIOS(const HistoryItem& left, const HistoryItem& right){ 
  return left.getIOS() < right.getIOS(); 
}
bool compareClicks(const HistoryItem& left, const HistoryItem& right){
  return left.getClicks() < right.getClicks();
}
bool compareLClicks(const HistoryItem& left, const HistoryItem& right){ 
  return left.getLClicks() < right.getLClicks(); 
}
bool compareRClicks(const HistoryItem& left, const HistoryItem& right){ 
  return left.getRClicks() < right.getRClicks(); 
}
bool compareChords(const HistoryItem& left, const HistoryItem& right){ 
  return left.getChords() < right.getChords(); 
}
bool compareClickss(const HistoryItem& left, const HistoryItem& right){ 
  return left.getClickss() < right.getClickss(); 
}
bool comparePathsq(const HistoryItem& left, const HistoryItem& right){ 
  return left.getPathsq() < right.getPathsq(); 
}
bool comparePathpx(const HistoryItem& left, const HistoryItem& right){ 
  return left.getPathpx() < right.getPathpx(); 
}
bool compareDate(const HistoryItem& left, const HistoryItem& right){ 
  return left.getDate() < right.getDate(); 
}

//make a array for easier accessing
std::vector<bool(*)(const HistoryItem&, const HistoryItem&)> compareFunctions = { compareTime, compare3BV, compare3BVs, compareZiNi, compareZiNis, comparehZiNi, comparehZiNis,
  compareIOE, compareRQP, compareIOS, compareClicks, compareLClicks, compareRClicks, compareChords, compareClickss, 
  comparePathsq, comparePathpx, compareDate};

History::History(const std::string& filename) : filename_(filename){
  load(filename);
}

History::~History(){
}

void History::load(const std::string& filename){
  std::ifstream stream(filename, std::ios_base::binary);
  if (!stream.good()){
    wxMessageBox("Could not load history!", "Warning", wxICON_WARNING);
    return;
  }
  HistoryItem temp_item;
  while (1){
    if (!temp_item.loadItem(stream)){
      save(filename);
      return;
    }
    if (stream.eof())
      break;
    if (temp_item.get3BV() != -1 && temp_item.getStyle() < 3){
      items_[temp_item.getStyle()].push_back(temp_item);
    }
  }
  stream.close();
}

bool History::save(const std::string& filename){
  std::ofstream stream(filename, std::ios_base::binary);
  if (!stream.good()){
    wxMessageBox("Could not save history!", "Warning", wxICON_WARNING);
    return false;
  }
  for (unsigned i = 0; i < 3; i++){
    for (unsigned j = 0; j < items_[i].size(); j++){
      items_[i][j].saveItem(stream);
    }
  }
  stream.close();
  return true;
}

void History::addItem(const BoardStats& stats, const wxDateTime& date){
  if (stats.style_ < 3)
    items_[stats.style_].push_back(HistoryItem(stats, date));
}

void History::sortItems(unsigned style, unsigned column){
  if (style < 3 && column < compareFunctions.size())
    std::sort(items_[style].begin(), items_[style].end(), compareFunctions[column]);
}

void History::reverseItems(unsigned style, unsigned column){
  if (style < 3 && column < compareFunctions.size())
    std::reverse(items_[style].begin(), items_[style].end());
}