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
#include "main.h"
#include "Board.h"
#include "MainWindow.h"
#include "Settings.h"
#include "Highscores.h"
#include "Counters.h"
#include "VideoRecorder.h"
#include "VideoPlayer.h"
#include "VideoPlayerDialog.h"
#include "wx/cmdline.h"

MyApp* my_app;
IMPLEMENT_APP(MyApp)

//command line parser needs this to parse the filename if you open a file with MySweeper
static const wxCmdLineEntryDesc cmd_line_desc[] =
{
  { wxCMD_LINE_PARAM, NULL, NULL, "input file", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
  { wxCMD_LINE_NONE }
};

bool MyApp::OnInit(){
  my_app = this;

  try{
    settings_ = new Settings();
    video_recorder_ = new VideoRecorder(this);
    main_window_ = new MainWindow(this, NULL);
    board_ = new Board(this, settings_->width_, settings_->height_, settings_->mines_);
    video_player_ = new VideoPlayer(this);
    counters_ = new Counters(this, board_->getStats());       //needs constructed main_window_ for positioning
    video_player_panel_ = new VideoPlayerDialog(video_player_, main_window_);
  }
  catch (std::bad_alloc& exception){
    wxMessageBox("Not enough memory!", "Fatal Error", wxICON_ERROR);
    delete settings_;
    delete video_recorder_;
    delete board_;
    return false;
  }
  main_window_->changeBoardSize();
  main_window_->updateBoardView();

  main_window_->newBoard(true);   //bug fix (didn´t show window in correct size after starting with Beg board)

  //parsing commandline params for a filename to open
  wxCmdLineParser cmd_parser(cmd_line_desc, argc, argv);
  int res = cmd_parser.Parse(false);
  if (res != 0 || cmd_parser.GetParamCount() > 1)
    wxMessageBox("Wrong command line parameters!", "Error", wxICON_ERROR);

  if (cmd_parser.GetParamCount() > 0)
  {
    wxFileName filename(cmd_parser.GetParam(0));
    filename.Normalize(wxPATH_NORM_LONG | wxPATH_NORM_DOTS | wxPATH_NORM_TILDE | wxPATH_NORM_ABSOLUTE);
    video_player_panel_->show(filename.GetFullPath());
  }

	return true;
}

int MyApp::OnExit(){
  //windows are destroy themself 
  delete video_player_;
  delete video_recorder_;
  delete board_;
  delete settings_;
  return 0;
}