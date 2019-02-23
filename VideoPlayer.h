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



#ifndef __VIDEO_PLAYER_H__
#define __VIDEO_PLAYER_H__

#include "stdafx.h"
#include "Video.h"
#include "main.h"

//class for video playing (but not the gui for that)
class VideoPlayer : wxEvtHandler{
private:
  Video video_;     //video is loaded there (from file or preview)
  MyApp* app_ = nullptr;

  long time_;     //no real time, but the time for the video player (which can run slower or faster)
  unsigned board_event_position_ = 0;             //what index is the next event
  unsigned mouse_position_position_ = 0;
  unsigned additional_event_position_ = 0;

  float speed_ = 1.f;           //speed of video playing
  bool is_running_ = false;     

  bool old_flag_state_;         //stores if flags were enabled before playing video (to restore it after video) 
  bool is_active_ = false;      //if it´s in video playing mode (video playing dialog shown)

  wxTimer timer_;               //timer (used to avoid just looping (which would block other events and consume much spu power)
  wxStopWatch watch_;           //watch to stop the time since last iteration
  void OnTimer(wxTimerEvent& event);    //does the actual stuff

  bool setBoard();
  void restartBoard();

public:
  VideoPlayer(MyApp* app);
  ~VideoPlayer();

  bool loadVideo(wxString filename);      //from file
  bool loadVideo(const Video* video);     //preview
  void endVideo();

  void start(long time = 0);      //start from what time on
  void pause();
  void resume();
  void stop();

  void setSpeed(float speed = 1.f){ speed_ = speed; }

  float getVideoPosition(){ return static_cast<float>(time_) / video_.getTime(); }
  float getActualTime(){ return static_cast<float>(time_) / 1000; }
  int calcTimeToPosition(float position){ return video_.getTime() * position; }
  bool isRunning(){ return is_running_; }
  bool isActive(){ return is_active_; }
  bool isAuthentic(){ return video_.isAuthentic(); }
};

#endif //__VIDEO_PLAYER_H__