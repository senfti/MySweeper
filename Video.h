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


#ifndef __VIDEO_H__
#define __VIDEO_H__

#include "stdafx.h"
#include "Board.h"
#include "VideoEvents.h"

const int VERSION = 100;    //change version number if video file changes

//this video class does no authentication!!!
class Video{
  private:
    int version_;       //version of the file

    const Board* board_;      //pointer to the board, which will be save in video
    int width_; 
    int height_;
    int mines_;
    std::vector<Square> squares_;              //not complete board is loaded, just squares 
    std::vector<BoardEvent> board_events_;
    std::vector<MousePosition> mouse_positions_;
    std::vector<AdditionalEvent> additional_events_;

    int time_;      //time loaded from file

    bool is_authentic_ = false;     //if it´s a correct official video
    bool is_correct_ = false;       //if it´s correct loaded
  
  public:
    Video(){}
    Video(const Board* board);    //creating video from board
    Video(wxString filename);     //creating video from file

    void setBoard(const Board* board);
    void addBoardEvent(BoardEvent& board_event);
    void addMousePosition(MousePosition& mouse_position);
    void addAdditionalEvent(AdditionalEvent& additional_event);

    const BoardEvent& getBoardEvent(int index){ return board_events_[index]; }
    const std::vector<BoardEvent>& getBoardEvents() const { return board_events_; }
    const MousePosition& getMousePosition(int index){ return mouse_positions_[index]; }
    const std::vector<MousePosition>& getMousePositions() const { return mouse_positions_; }
    const AdditionalEvent& getAdditionalEvent(int index){ return additional_events_[index]; }
    const std::vector<AdditionalEvent>& getAdditionalEvents() const { return additional_events_; }

    bool loadVideo(wxString filename);
    bool saveVideo(wxString filename);

    bool checkVideo();    //checks, if loaded values are valid

    int readData(wxString filename, wxInt32** data);      //loading from file done here
    //data loaded, now "parse" it
    int loadBoard(const wxInt32* data, int remaining_file_length);      
    int loadEvents(const wxInt32* data, int remaining_file_length);
    int loadMousePositions(const wxInt32* data, int remaining_file_length);
    int loadAdditionalEvents(const wxInt32* data, int remaining_file_length);

    bool writeData(wxString filename, wxInt32* data, int length);   //saving to file
    //preparing data to save
    int saveBoard(wxInt32* data);
    int saveEvents(wxInt32* data);
    int saveMousePositions(wxInt32* data);
    int saveAdditionalEvents(wxInt32* data);

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    int getMines() const { return mines_; }
    long getTime() const { return time_; }
    const std::vector<Square>& getSquares(){ return squares_; }

    void setTime(long time){ time_ = time; }
    
    void setCorrect(bool correct){ is_correct_ = correct; }
    bool isCorrect() const { return is_correct_; }
    bool isAuthentic() const { return is_authentic_; }
};

#endif //__VIDEO_H__
