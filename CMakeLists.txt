cmake_minimum_required(VERSION 2.6.2)
project(MySweeper)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")
find_package(wxWidgets COMPONENTS core base adv REQUIRED)
include( "${wxWidgets_USE_FILE}" )
set(SRCS AboutDialog.cpp AboutDialog_B.cpp BitArray.cpp Board.cpp BoardPanel.cpp BoardStats.cpp Counter_B.cpp Counters.cpp CustomDialog.cpp CustomDialog_B.cpp HelpDialog.cpp HelpDialog_B.cpp HighScoreDialog.cpp HighscoreDialog_B.cpp Highscores.cpp History.cpp HistoryDialog.cpp HistoryDialog_B.cpp main.cpp MainWindow.cpp MainWindow_B.cpp SegmentDisplayPanel.cpp Settings.cpp SettingsDialog.cpp SettingsDialog_B.cpp SmileyButton.cpp stdafx.cpp Video.cpp VideoPlayer.cpp VideoEvents.cpp VideoPlayerDialog.cpp VideoPlayerDialog_B.cpp VideoRecorder.cpp My_SettingFile.cpp)

if(WIN32)
  set(SRCS ${SRCS} minimal.rc)
endif(WIN32)

ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    -O3
    # Other flags
)

add_executable(MySweeper WIN32 ${SRCS})

target_link_libraries(MySweeper ${wxWidgets_LIBRARIES} -no-pie libpugixml.a)
