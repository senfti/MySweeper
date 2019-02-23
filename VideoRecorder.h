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



#ifndef __VIDEO_RECORDER_H__
#define __VIDEO_RECORDER_H__

#include "stdafx.h"
#include "Video.h"
#include "Board.h"

class MyApp;

//class for recording the videos
class VideoRecorder{
  private:
    MyApp* app_ = nullptr;
    Video* video_ = nullptr;
    bool record_ = false;

  public:
    VideoRecorder(MyApp* app);
    ~VideoRecorder();

    void startRecording(const Board* board);
    void stopRecording(bool video_correct);

    bool isRecording(){ return record_; }

    void addBoardEvent(BoardEvent board_event);
    void addMousePosition(MousePosition mouse_position);
    void addAdditionalEvent(AdditionalEvent additional_event);

    bool saveVideo(wxString filename);

    const Video* getVideo(){ return video_; }
};

#endif //__VIDEO_RECORDER_H_