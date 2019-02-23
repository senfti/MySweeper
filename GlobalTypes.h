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

#ifndef __GLOBAL_TYPES_H__
#define __GLOBAL_TYPES_H__

//Possible states of a square (last 2 are just for drawing at the end of a board)
enum SquareState{
  SQUARE_UNOPENED = 0, SQUARE_CLICKED, SQUARE_FLAGGED, SQUARE_QUESTION_MARKED,
  SQUARE_OPENED, SQUARE_WRONG_FLAGGED, SQUARE_KILLING_MINE
};

//status of a board (for video, different status needed, because no recording there recording)
enum BoardStatus{
  BOARD_STATUS_NOT_VALID = 0, BOARD_STATUS_PREPARED, BOARD_STATUS_STARTED,
  BOARD_STATUS_WON, BOARD_STATUS_LOST, BOARD_STATUS_VIDEO_PREPARED, BOARD_STATUS_VIDEO_RUNNING, BOARD_STATUS_VIDEO_END
};

// board styles
enum BoardStyle{ BOARD_STYLE_BEG = 0, BOARD_STYLE_INT, BOARD_STYLE_EXP, BOARD_STYLE_CUSTOM };

//when a video should be saved automatically (all, just won games, just highscore games, no auto saving)
enum AutoSaveOptions{ AUTO_SAVE_ALL = 0, AUTO_SAVE_WON = 1, AUTO_SAVE_HIGHSCORES = 2, AUTO_SAVE_NONE = 3 };

//smiley faces
enum SmileyFace{ SMILEY_FACE_NORMAL = 0, SMILEY_FACE_CLICK, SMILEY_FACE_WIN, SMILEY_FACE_LOOSE };

//number of events (for checking file needed, to avoid unknown event)
const int BOARD_EVENT_NUMBER = 10;

//event types open chord right up means, chord was made with a right up -> next left up should not be a open square
enum BoardEventType{
  BOARD_EVENT_LEFT_CLICK = 0, BOARD_EVENT_MOVE_CLICKED = 1, BOARD_EVENT_OPEN_SQUARE = 2,
  BOARD_EVENT_RIGHT_CLICK = 3, BOARD_EVENT_RIGHT_UP = 4,
  BOARD_EVENT_CHORD_CLICK = 5, BOARD_EVENT_MOVE_CHORDED = 6,
  BOARD_EVENT_OPEN_CHORD = 7, BOARD_EVENT_OPEN_CHORD_RIGHT_UP = 8,
  BOARD_EVENT_LEAVE_BOARD = 9
};

//additional events, like questionmark set (to ensure correct behavior if this settings is changed while playing)
enum AdditionalEventType{ ADDITIONAL_EVENT_QUESTIONMARK_SET = 0, ADDITIONAL_EVENT_SCROLL = 1 };


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//holds information about a square
struct Square{
public:
  SquareState state_ = SQUARE_UNOPENED;
  int value_ = 0;   //-1 = mine
};

#endif //__GLOBAL_TYPES_H__