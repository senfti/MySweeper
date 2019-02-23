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

#ifndef __BOARD_STATS_H__
#define __BOARD_STATS_H__

#include "stdafx.h"
#include "GlobalTypes.h"
class Board;

//just container for stats
class BoardStats{
  public:
    long time_;

    int width_;
    int height_;
    int mines_;

    int right_clicks_;
    int left_clicks_;
    int chord_clicks_;

    float path_;    //in square length

    int bbbv_;
    int ZiNi_;
    int hZiNi_;

    float bbbvs_;
    float ZiNis_;
    float hZiNis_;
    float ioe_;
    float rqp_;
    float ios_;

    int solved_3BV_;
    float estimated_time_;

    bool is_record_ = false;

    BoardStyle style_;

    BoardStats();

    void resetStats(bool reset3BVZiNihZiNi);  //say, if 3bv,zini,hzini are also to reset
    void setBoardDimensions(int width, int height, int mines){ 
      width_ = width; 
      height_ = height; 
      mines_ = mines; 
    }
    int getClicks() const { return (right_clicks_ + left_clicks_ + chord_clicks_); }
    bool getNonFlagging() const { return !right_clicks_; }
    bool isFinished() const { return bbbv_ == solved_3BV_; }
    float getClicksPerSecond() const { return (time_ ? static_cast<float>(getClicks()) * 1000.f / time_ : 0); }
};

#endif //__BOARD_STATS_H__