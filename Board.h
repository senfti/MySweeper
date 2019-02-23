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

#ifndef __BOARD_H__
#define __BOARD_H__

#include "stdafx.h"
#include "BoardStats.h"
#include "GlobalTypes.h"
#include "BitArray.h"

class MyApp;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//class contains all information about a given board, handles BoardEvents, does stats,...
class Board{
  private:
    int width_ = 8;     //width in squares
    int height_ = 8;
    int mines_ = 10;

    BoardStats stats_;              //time, 3bv, 3bv/s,...
    wxStopWatch watch_;             //time measured here counts

    BoardStyle style_ = BOARD_STYLE_BEG;    //Beg, Int, Exp, Custom
    BoardStatus status_ = BOARD_STATUS_NOT_VALID;

    std::vector<Square> squares_;   //holds state (openend, flagged,..) and value (-1 means mine); row-wise indexing
    BitArray is_3BV_square_;        //one bit for every square, says if it´s a 3BV square

    MyApp* app_;                    //pointer to the class holding all important objects (mainwindow, counters,...)

    int mines_not_flagged_;         //number of not flagged mines (seen upper left side in the window)
    int opened_squares_;            //counted, to find out if the board is finished, efficiently

    int last_x_ = -1;                   //are needed for resetting square states of last event before setting to new
    int last_y_ = -1;
    bool block_open_square_ = false;    //is set after open with chord -> no clicking possible when left stays pressed
    bool right_on_opened_ = false;      //when right click is begin for chord, it shouldn´t count as a click

    //store the region, which has to be updated (updating whole board is to slow on big boards)
    int update_region_left_, update_region_right_, update_region_top_, update_region_bottom_;
    
    void resetUpdateRegion(int x, int y);   //x|y will sure be updated (is square of event), so reset to this values

    int getIndex(int x, int y) const { return y*width_ + x; }   //calcs indices from coordinates 

    void calcNumber(int x, int y);      //calcs the number at x|y
    void calcAllNumbers();              //faster if calculating all (calculating per mine, not per square)
    void unclick(int x, int y);         //unclicks square and surrounding squares

    int calcPremium(int x, int y, const int* states, bool is_HZiNi, const BitArray& tricky_squares) const;
    bool calcAllPremiums(const int* states, int* premiums, std::vector<std::set<int>>& premium_sets, 
      const BitArray& tricky_squares) const;
    int performZiNi(int x, int y, int* states, int* premiums, std::vector<std::set<int>>& premium_sets,
      const BitArray& tricky_squares, bool normal_click, bool is_HZiNi) const;

    //change square state and update update_region
    void openSingleSquare(int x, int y);
    void setClickedSingleSquare(int x, int y);
    void setUnopenedSingleSquare(int x, int y);
    void setFlaggedSingleSquare(int x, int y);
    void setQuestionSingleSquare(int x, int y);

    void preEventCalc(int x, int y, bool is_open_event, SmileyFace smiley_face, BoardEventType event_type); //checks if to start, set smiley, resets update_region, unclicks if needed, pushes back event
    void postClickCalc(int x, int y);   //checks: if finished
    void swapMine(int x, int y);        //if first click on mine, this function moves the mine from this square to another and recalculates numbers
    void setBoardLost();                //does everything when lost board
    void setBoardWon();                 //does everything when won board

    void finishBoard(bool won);         //called when board finished
    void startBoard(int x, int y);      //called when board is started

  public:
    Board();                            //default constructor(does nothing)
    Board(MyApp* app);
    Board(MyApp* app, BoardStyle style);
    Board(MyApp* app, int width, int height, int mines);

    //just setting width, height, mines
    void setBoardStyle(BoardStyle style);
    void setCustomBoard(int width, int height, int mines);

    BoardStatus getBoardStatus() const { return status_; }

    void boardPreparingStuff(); //sets all for a new board (generating / setting to loaded call this)
    void setToLoadedBoard(int width, int height, int mines, const std::vector<Square>& squares);    //sets the board to given values
    void generateBoard();   //generates a new board
    void restartBoard();    //restart, but no changing mines

    //events
    void leftClickSquare(int mouse_x, int mouse_y);   //mouse_x / mouse_y in squares (not in pixel!)
    void moveClicked(int mouse_x, int mouse_y);
    void openSquare(int mouse_x, int mouse_y);

    void rightClickSquare(int mouse_x, int mouse_y);
    void rightUp();

    void chordClickSquare(int mouse_x, int mouse_y);
    void moveChorded(int mouse_x, int mouse_y);
    void openChord(int mouse_x, int mouse_y, bool with_right_up);
    void openSquaresAround(int x, int y);         //additional square parameter for reuse in calc3Bv

    void leaveBoard();


    inline bool is3BV(int index) const;

    //stats calculating functions
    void calc3BV_ZiNi_hZiNi();
    bool calc3BV(int& bbbv, int& solved_3BV, BitArray& is_3BV_square, int* states, BitArray* tricky_squares) const;     //calculates 3BV and the squares of 3BVs
    bool calcZiNi(int& ZiNi, int* states, const BitArray& tricky_squares) const;
    bool calcHZiNi(int& hZiNi, int* states, const BitArray& tricky_squares) const;
    void calcStats();       //calculates stats
    void updateStats(long time = -1);     //same as calcStats, but without 3BV calculation, time for calculation, if != -1
    void resetStats(bool reset3BVZiNihZiNi);  //parameter says, if 3bv,zini,hzini must be calculated new

    //makes the rectangel of update_region so big that every changed square is inside
    void adjustUpdateRegion(int x, int y);

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    int getMines() const { return mines_; }
    long getTime() const { return watch_.Time(); }
    const std::vector<Square>& getSquares() const { return squares_; }
    BoardStyle getStyle() const { return style_; }
    std::string getStyleString() const;
    const BoardStats* getStats() const { return &stats_; }
    const Square& getSquare(int x, int y) const { return squares_[getIndex(x, y)]; }
    const Square& getSquare(int index) const { return squares_[index]; }

    void setStatsTime(int time){ stats_.time_ = time; }   //this is needed for video to set the time to the time in the video
    void incrPath(float squares){ stats_.path_ += squares; }  //path measured in square_length

    bool isFinished() const { return (status_ == BOARD_STATUS_WON) || (status_ == BOARD_STATUS_LOST) || 
      (status_ == BOARD_STATUS_VIDEO_END); }
    bool isWon() const { return (status_ == BOARD_STATUS_WON); }
    bool isReadyForInput() const { return (status_ == BOARD_STATUS_PREPARED) || (status_ == BOARD_STATUS_STARTED); }
    bool isRunning() const { return (status_ == BOARD_STATUS_VIDEO_RUNNING) || (status_ == BOARD_STATUS_STARTED); }
};

#endif //__BOARD_H_