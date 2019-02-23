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

#ifndef __HIGHSCORE_H__
#define __HIGHSCORE_H__

#include "stdafx.h"
#include "My_SettingFile.h"
#include <queue>
class BoardStats;

#define HIGHSCORE_FILE_NAME "MySweeper.hisc"  //just the filename, no path

enum HighscoreStyle{ HIGHSCORE_STYLE_GENERAL = 0, HIGHSCORE_STYLE_NF = 1, HIGHSCORE_STYLE_FLAG = 2 };

//class for a time / 3bv/s highscore
class SingleHighscore{
  private:
  public:
    float time_ = 999.999f;
    int bbbv_ = 0;
    float bbbvs_ = 0.f;
    wxDateTime date_ = wxDateTime(wxLongLong());    //set to 0 (= something in 1970)
    std::vector<std::string> nodes_;                //for xml output
    bool is_3bvs_ = false;                          //is 3bvs highscore (true) or time highscore (false)
    HighscoreStyle highscore_style_ = HIGHSCORE_STYLE_GENERAL;  //general highscore, nf highscore or flagging highscore

    //construct empty highscore (with r_value reference)
    SingleHighscore(const std::vector<std::string>& nodes, bool is_3bvs, HighscoreStyle highscore_style) 
      : nodes_(nodes), is_3bvs_(is_3bvs), highscore_style_(highscore_style){}
    SingleHighscore(std::vector<std::string>&& nodes, bool is_3bvs, HighscoreStyle highscore_style) 
      : is_3bvs_(is_3bvs), highscore_style_(highscore_style){ nodes_ = nodes; }
    //construct loaded from file (with r_value reference)
    SingleHighscore(const std::vector<std::string>& nodes, bool is_3bvs, HighscoreStyle highscore_style, MY::SettingFileIn_Base* file);
    SingleHighscore(std::vector<std::string>&& nodes, bool is_3bvs, HighscoreStyle highscore_style, MY::SettingFileIn_Base* file);

    bool writeToMySettingFile(MY::SettingFileOut_Base* file);   //don´t worry about that it is called setting file (was first purpose of this setting file class)
    bool readFromMySettingFile(MY::SettingFileIn_Base* file);

    //checks, if it´s a highscore and changes highscores, if yes
    bool newScore(const BoardStats& stats);
};

//class for a custom highscore
class CustomHighscore{
private:
public:
  float time_ = 999.999f;
  int bbbv_ = 0;
  int mines_ = 0;
  wxDateTime date_ = wxDateTime(wxLongLong());
  std::vector<std::string> nodes_;
  int width_ = 8;
  int height_ = 8;

  CustomHighscore(const std::vector<std::string>& nodes, int widht, int height) : nodes_(nodes), width_(widht), height_(height){}
  CustomHighscore(std::vector<std::string>&& nodes, int widht, int height) : width_(widht), height_(height){ nodes_ = nodes; }
  CustomHighscore(const std::vector<std::string>& nodes, MY::SettingFileIn_Base* file, int widht, int height);
  CustomHighscore(std::vector<std::string>&& nodes, MY::SettingFileIn_Base* file, int widht, int height);

  bool writeToMySettingFile(MY::SettingFileOut_Base* file);
  bool readFromMySettingFile(MY::SettingFileIn_Base* file);

  bool newScore(const BoardStats& stats);
};

//class for a size highscore
class SizeHighscore{
private:
public:
  float time_ = 999.999f;
  int bbbv_ = 0;
  int size_ = 0;
  wxDateTime date_ = wxDateTime(wxLongLong());
  std::vector<std::string> nodes_;

  SizeHighscore(const std::vector<std::string>& nodes) : nodes_(nodes){}
  SizeHighscore(std::vector<std::string>&& nodes){ nodes_ = nodes; }
  SizeHighscore(const std::vector<std::string>& nodes, MY::SettingFileIn_Base* file);
  SizeHighscore(std::vector<std::string>&& nodes, MY::SettingFileIn_Base* file);

  bool writeToMySettingFile(MY::SettingFileOut_Base* file);
  bool readFromMySettingFile(MY::SettingFileIn_Base* file);

  bool newScore(const BoardStats& stats);
};


class Highscores{
  private:
    bool no_highscore_saving_ = false;                  //if file exists, but loading it is not possible, to not overwrite it with false data
    std::string filename_;
  public:
    SingleHighscore beg_time_highscore_;
    SingleHighscore int_time_highscore_;
    SingleHighscore exp_time_highscore_;

    SingleHighscore beg_3bvs_highscore_;
    SingleHighscore int_3bvs_highscore_;
    SingleHighscore exp_3bvs_highscore_;

    SingleHighscore nf_beg_time_highscore_;
    SingleHighscore nf_int_time_highscore_;
    SingleHighscore nf_exp_time_highscore_;

    SingleHighscore nf_beg_3bvs_highscore_;
    SingleHighscore nf_int_3bvs_highscore_;
    SingleHighscore nf_exp_3bvs_highscore_;

    SingleHighscore flag_beg_time_highscore_;
    SingleHighscore flag_int_time_highscore_;
    SingleHighscore flag_exp_time_highscore_;

    SingleHighscore flag_beg_3bvs_highscore_;
    SingleHighscore flag_int_3bvs_highscore_;
    SingleHighscore flag_exp_3bvs_highscore_;

    CustomHighscore custom_8_8_highscores_;
    CustomHighscore custom_9_9_highscores_;
    CustomHighscore custom_16_16_highscores_;
    CustomHighscore custom_30_16_highscores_;
    CustomHighscore custom_30_24_highscores_;

    SizeHighscore size_highscore_;

    SingleHighscore* highscores[18];      //for easy accessing single highscores
    CustomHighscore* custom_highscores[5];  //for easy accessing custom highscores

    Highscores();

    void loadHighscores(const std::string& filename);
    void saveHighscores(const std::string& filename = std::string());

    int newScore(const BoardStats& stats);     //returns true, if it´s a new highscore
};

#endif //__HIGHSCORE_H__