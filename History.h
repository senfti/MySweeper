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

#ifndef __HISTORY_H__
#define __HISTORY_H__

#include "stdafx.h"
#include "BoardStats.h"
#include "GlobalTypes.h"

//a single history entry
class HistoryItem{
  private:
    //needed values to store, the rest can be calculated
    float time_ = 999.999f;
    int bbbv_ = -1;
    int zini_ = -1;
    int hzini_ = -1;
    int left_clicks_ = -1;
    int right_clicks_ = -1;
    int chord_clicks_ = -1;
    float path_ = -1.f;
    wxDateTime date_;

    BoardStyle style_;

  public:
    HistoryItem() {};
    HistoryItem(const BoardStats& stats, const wxDateTime& date);   //creates a history item from stats
    bool loadItem(std::ifstream& stream);
    bool saveItem(std::ofstream& stream);

    void addItemToFile(std::string filename = "");    //append data to the history file
    
    //value getters
    float getTime() const { return time_; }
    int get3BV() const { return bbbv_; }
    float get3BVs() const { return bbbv_ / time_; }
    int getZiNi() const { return zini_; }
    float getZiNis() const { return zini_ / time_; }
    int gethZiNi() const { return hzini_; }
    float gethZiNis() const { return hzini_ / time_; }
    float getIOE() const { return static_cast<float>(bbbv_) / getClicks(); }
    float getRQP() const { return time_ * time_ / bbbv_; }
    float getIOS() const { return log10(static_cast<float>(bbbv_)) / log10(time_); }
    int getClicks() const { return left_clicks_ + right_clicks_ + chord_clicks_; }
    int getLClicks() const { return left_clicks_; }
    int getRClicks() const { return right_clicks_; }
    int getChords() const { return chord_clicks_; }
    float getClickss() const { return getClicks() / time_; }
    float getPathsq() const { return path_; }
    float getPathpx() const { return path_ * 16; }
    const wxDateTime& getDate() const { return date_; }

    BoardStyle getStyle() const { return style_; }

    //get strings for output
    wxString getTimeString() const { return wxString::Format("%.3f", time_); }
    wxString get3BVString() const { return wxString::Format("%d", bbbv_); }
    wxString get3BVsString() const { return wxString::Format("%.3f", get3BVs()); }
    wxString getZiNiString() const { return wxString::Format("%d", zini_); }
    wxString getZiNisString() const { return wxString::Format("%.3f", getZiNis()); }
    wxString gethZiNiString() const { return wxString::Format("%d", hzini_); }
    wxString gethZiNisString() const { return wxString::Format("%.3f", gethZiNis()); }
    wxString getIOEString() const { return wxString::Format("%.3f", getIOE()); }
    wxString getRQPString() const { return wxString::Format("%.3f", getRQP()); }
    wxString getIOSString() const { return wxString::Format("%.3f", getIOS()); }
    wxString getClicksString() const { return wxString::Format("%d", getClicks()); }
    wxString getLClicksString() const { return wxString::Format("%d", left_clicks_); }
    wxString getRClicksString() const { return wxString::Format("%d", right_clicks_); }
    wxString getChordsString() const { return wxString::Format("%d", chord_clicks_); }
    wxString getClickssString() const { return wxString::Format("%.3f", getClickss()); }
    wxString getPathsqString() const { return wxString::Format("%.3f", path_); }
    wxString getPathpxString() const { return wxString::Format("%.0f", getPathpx()); }
    wxString getDateString() const { return date_.Format("%Y-%m-%d %X"); }
};

class History{
  private:
    std::string filename_;
    std::vector<HistoryItem> items_[3];   //one for beg, int, exp

    void load(const std::string& filename);

  public:
    History(){}
    History(const std::string& filename);
    ~History();

    bool save(const std::string& filename);   //saves all items
    void addItem(const BoardStats& stats, const wxDateTime& date);    //adds the item to the history class (but not to the file)
    void sortItems(unsigned style, unsigned column);    //sort depending on given column
    void reverseItems(unsigned style, unsigned column); //reverses order

    int getItemsNumber(unsigned style) const { return (style < 3 ? items_[style].size() : -1); }
    HistoryItem getItem(unsigned style, unsigned index) const { return (style < 3 ? items_[style].at(index) : HistoryItem()); }
};

#endif //__HISTORY_H__