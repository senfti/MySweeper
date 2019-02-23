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
#include "Video.h"

Video::Video(const Board* board){
  version_ = VERSION;
  setBoard(board);
  is_correct_ = false;
}

Video::Video(wxString filename){
  loadVideo(filename);
}

void Video::setBoard(const Board* board){
  width_ = board->getWidth();
  height_ = board->getHeight();
  mines_ = board->getMines();
  board_ = board;
}

void Video::addBoardEvent(BoardEvent& mouse_event){
  board_events_.push_back(mouse_event);
}

void Video::addMousePosition(MousePosition& mouse_position){
  mouse_positions_.push_back(mouse_position);
}

void Video::addAdditionalEvent(AdditionalEvent& additional_event){
  additional_events_.push_back(additional_event);
}

bool Video::checkVideo(){
  if (width_ < 8 || width_ > 10000)     //width must be between 8 and 10000
    return false;
  if (height_ < 8 || height_ > 10000)   //same for height
    return false;
  if (mines_ < 1 || mines_ > (width_ - 1)*(height_ - 1))    //limits for mines
    return false;
  for (int i = 0; i < width_*height_; i++){
    if (squares_[i].value_ < -1 || squares_[i].value_ > 8)      //value of square has to be -1 (mines) or number from 0 to 8
      return false;
  }

  if (board_events_.size() < 1)   //there has to be at least one board event
    return false;
  int time = 0;
  //validating board events
  for (unsigned i = 0; i < board_events_.size(); i++){
    //has to be on a valid square
    if (board_events_[i].x_ < -1 || board_events_[i].x_ > width_ - 1 || board_events_[i].y_ < -1 || board_events_[i].y_ > height_ - 1)
      return false;
    if (board_events_[i].type_ < 0 || board_events_[i].type_ >= BOARD_EVENT_NUMBER)     //a valid event type
      return false;
    if (board_events_[i].time_ < time)      //events must be ordered in time
      return false;
    time = board_events_[i].time_;
  }

  time = 0;
  //validation mouse positions
  for (unsigned i = 0; i < mouse_positions_.size(); i++){
    if (mouse_positions_[i].x_ < -1000 || mouse_positions_[i].x_ > 400 * width_ ||    //correct position? (-1000 for leave event, saved value is 384 * width in squares)
        mouse_positions_[i].y_ < -1000 || mouse_positions_[i].y_ > 400 * height_)
      return false;
    if (mouse_positions_[i].time_ < time)      //positions must be ordered in time
      return false;
    time = mouse_positions_[i].time_;
  }

  return true;
}

bool Video::loadVideo(wxString filename){
  is_correct_ = false;
  wxInt32* data = nullptr;
  int length = readData(filename, &data);   //read the data here
  if (length == 0){     //if nothing read, return
    delete[] data;
    return false;
  }
  
  int pos = 0;
  int pos_add = 0;
  time_ = data[pos++];    //first wxInt32 is time (version was read before)

  if (!(pos_add = loadBoard(data + pos, length - pos))){    //parse the board
    wxMessageBox("Video could not be loaded. File corrupted!", "Video Loading Error", wxICON_ERROR);
    delete[] data;
    return false;
  }
  pos += pos_add;

  if (!(pos_add = loadEvents(data + pos, length - pos))){
    wxMessageBox("Video could not be loaded. File corrupted!", "Video Loading Error", wxICON_ERROR);
    delete[] data;
    return false;
  }
  pos += pos_add;
  
  if (!(pos_add = loadMousePositions(data + pos, length - pos))){
    wxMessageBox("Video could not be loaded. File corrupted!", "Video Loading Error", wxICON_ERROR);
    delete[] data;
    return false;
  }
  pos += pos_add;

  if (!(pos_add = loadAdditionalEvents(data + pos, length - pos))){
    wxMessageBox("Video could not be loaded. File corrupted!", "Video Loading Error", wxICON_ERROR);
    delete[] data;
    return false;
  }

  if (!checkVideo()){
    wxMessageBox("Video could not be loaded. File corrupted!", "Video Loading Error", wxICON_ERROR);
    delete[] data;
    return false;
  }

  delete[] data;
  is_correct_ = true;
  return true;
}

//changed for public version
int Video::readData(wxString filename, wxInt32** data){
  wxFileInputStream file(filename);
  if (!file.IsOk()){
    wxMessageBox("Video file not found or could not be loaded!", "Video Loading Error", wxICON_ERROR);
    return 0;
  }
  file.Read(&version_, sizeof(int));
  if (file.Eof()){
    wxMessageBox("Video could not be loaded. File empty!", "Video Loading Error", wxICON_ERROR);
    return false;
  }

  wxDataInputStream data_input(file);

  int length;
  data_input.Read32(reinterpret_cast<wxUint32*>(&length), 1);   //read length of the file

  try{
    (*data) = new wxInt32[length];
  }
  catch (std::bad_alloc& exception){
    wxMessageBox("Not enough memory for loading video!", "Video Loading Error", wxICON_ERROR);
    return 0;
  }
  data_input.Read32(reinterpret_cast<wxUint32*>(*data), length);    //read rest of the file (actual data is this)
  if (file.Eof()){
    wxMessageBox("Video could not be loaded. File corrupted!", "Video Loading Error", wxICON_ERROR);
    return false;
  }  

  return length;
}

int Video::loadBoard(const wxInt32* data, int remaining_file_length){
  if (remaining_file_length < 3)    //width_, height and mines have to be stored
    return 0;

  int pos = 0;
  width_ = data[pos++];
  height_ = data[pos++];
  mines_ = data[pos++];

  if (remaining_file_length < (3 + width_*height_)) //3 for width, height, mines
    return 0;

  try{
    squares_.resize(width_ * height_);
  }
  catch (std::exception& exception){
    wxMessageBox("Not enough memory for loading video!", "Video Loading Error", wxICON_ERROR);
    return 0;
  }  

  //values are stored, states set to default
  for (int i = 0; i < width_*height_; i++){
    squares_[i].value_ = data[pos++];
    squares_[i].state_ = SQUARE_UNOPENED;
  }

  return pos;
}

int Video::loadEvents(const wxInt32* data, int remaining_file_length){
  if (remaining_file_length < 1)    //1 for the number of events
    return 0;

  int pos = 0;
  int number = data[pos++];

  if (remaining_file_length < (1 + number * 4))     //4 ints per event + 1 for the number of events
    return 0;

  try{
    board_events_.resize(number);
  }
  catch (std::exception& exception){
    wxMessageBox("Not enough memory for loading video!", "Video Loading Error", wxICON_ERROR);
    return 0;
  }
  
  for (int i = 0; i < number; i++){
    board_events_[i].type_ = data[pos++];
    board_events_[i].time_ = data[pos++];
    board_events_[i].x_ = data[pos++];
    board_events_[i].y_ = data[pos++];
  }

  return pos;
}

int Video::loadMousePositions(const wxInt32* data, int remaining_file_length){
  if (remaining_file_length < 1)
    return 0;

  int pos = 0;
  int number = data[pos++];

  if (remaining_file_length < (1 + number * 3))   //1 for number of positions, 3 per position
    return 0;

  try{
    mouse_positions_.resize(number);
  }
  catch (std::exception& exception){
    wxMessageBox("Not enough memory for loading video!", "Video Loading Error", wxICON_ERROR);
    return 0;
  }
  
  for (int i = 0; i < number; i++){
    mouse_positions_[i].time_ = data[pos++];
    mouse_positions_[i].x_ = data[pos++];
    mouse_positions_[i].y_ = data[pos++];
  }

  return pos;
}

int Video::loadAdditionalEvents(const wxInt32* data, int remaining_file_length){
  if (remaining_file_length < 1)
    return 0;

  int pos = 0;
  int number = data[pos++];

  if (remaining_file_length < (1 + number * 4))   //1 for number of positions, 4 per event
    return 0;

  try{
    additional_events_.resize(number);
  }
  catch (std::exception& exception){
    wxMessageBox("Not enough memory for loading video!", "Video Loading Error", wxICON_ERROR);
    return 0;
  }

  for (int i = 0; i < number; i++){
    additional_events_[i].type_ = data[pos++];
    additional_events_[i].time_ = data[pos++];
    additional_events_[i].param1_ = data[pos++];
    additional_events_[i].param2_ = data[pos++];
  }

  return pos;
}

bool Video::saveVideo(wxString filename){
  if (board_ == nullptr){
    wxMessageBox("No video available", "Video Saving Error", wxICON_ERROR);
    return false;
  }
  int* data;
  try{
    data = new int[1      //time
      + 3 + width_ * height_        //3 for width, height and mines + 1 per square
      + 1 + 4 * board_events_.size()  //1 for number of events + 4 per event
      + 1 + 3 * mouse_positions_.size()  //1 for number of positions + 3 per position
      + 1 + 4 * additional_events_.size()];  //1 for number of events + 4 per event
  }
  catch (std::exception& exception){
    wxMessageBox("Not enough memory for saving video!", "Video Saving Error", wxICON_ERROR);
    return false;
  }

  int pos = 0;    //stores the length of data

  data[pos++] = time_;

  pos += saveBoard(data + pos);
  pos += saveEvents(data + pos);
  pos += saveMousePositions(data + pos); 
  pos += saveAdditionalEvents(data + pos);

  writeData(filename, data, pos);

  delete[] data;
  return true;
}

int Video::saveBoard(wxInt32* data){
  int pos = 0;
  data[pos++] = width_;
  data[pos++] = height_;
  data[pos++] = mines_;

  for (int i = 0; i < width_*height_; i++){
    data[pos++] = board_->getSquare(i).value_;
  }
  return pos;
}

int Video::saveEvents(wxInt32* data){
  int pos = 0;
  data[pos++] = board_events_.size();

  for (unsigned i = 0; i < board_events_.size(); i++){
    data[pos++] = board_events_[i].type_;
    data[pos++] = board_events_[i].time_;
    data[pos++] = board_events_[i].x_;
    data[pos++] = board_events_[i].y_;
  }

  return pos;
}

int Video::saveMousePositions(wxInt32* data){
  int pos = 0;
  data[pos++] = mouse_positions_.size();

  for (unsigned i = 0; i < mouse_positions_.size(); i++){
    data[pos++] = mouse_positions_[i].time_; 
    data[pos++] = mouse_positions_[i].x_;
    data[pos++] = mouse_positions_[i].y_;
  }

  return pos;
}

int Video::saveAdditionalEvents(wxInt32* data){
  int pos = 0;
  data[pos++] = additional_events_.size();

  for (unsigned i = 0; i < additional_events_.size(); i++){
    data[pos++] = additional_events_[i].type_;
    data[pos++] = additional_events_[i].time_;
    data[pos++] = additional_events_[i].param1_;
    data[pos++] = additional_events_[i].param2_;
  }

  return pos;
}

//changed for public version
bool Video::writeData(wxString filename, wxInt32* data, int length){
  if (!(wxFileName(filename, "dummy").DirExists()))     //if directory doesn´t exist, make it
    wxFileName(filename).Mkdir(511, wxPATH_MKDIR_FULL);

  wxFileOutputStream file(filename);
  if (!file.IsOk()){
    wxMessageBox("Error while trying to open file for writing!", "Video Saving Error", wxICON_ERROR);
    return false;
  }
  file.Write(&version_, sizeof(int));     //write version first
  if (!file.IsOk()){
    wxMessageBox("Error while writing file!", "Video Saving Error", wxICON_ERROR);
    wxRemoveFile(filename);
    return false;
  }  

  wxDataOutputStream data_stream(file);

  data_stream.Write32(reinterpret_cast<wxUint32*>(&length), 1);
  data_stream.Write32(reinterpret_cast<wxUint32*>(data), length);

  if (!data_stream.IsOk()){
    wxMessageBox("Error while writing file!", "Video Saving Error", wxICON_ERROR);
    wxRemoveFile(filename);
    return false;
  }

  return true;
}
