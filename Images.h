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

#ifndef __IMAGES_H_
#define __IMAGES_H_

//all xpm images

#include "xpm/1_16p.xpm"
#include "xpm/2_16p.xpm"
#include "xpm/3_16p.xpm"
#include "xpm/4_16p.xpm"
#include "xpm/5_16p.xpm"
#include "xpm/6_16p.xpm"
#include "xpm/7_16p.xpm"
#include "xpm/8_16p.xpm"
#include "xpm/flag_16p.xpm"
#include "xpm/mine_16p.xpm"
#include "xpm/killingmine_16p.xpm"
#include "xpm/questionmark_16p.xpm"

#include "xpm/1_24p.xpm"
#include "xpm/2_24p.xpm"
#include "xpm/3_24p.xpm"
#include "xpm/4_24p.xpm"
#include "xpm/5_24p.xpm"
#include "xpm/6_24p.xpm"
#include "xpm/7_24p.xpm"
#include "xpm/8_24p.xpm"
#include "xpm/flag_24p.xpm"
#include "xpm/mine_24p.xpm"
#include "xpm/killingmine_24p.xpm"
#include "xpm/questionmark_24p.xpm"

#include "xpm/1_32p.xpm"
#include "xpm/2_32p.xpm"
#include "xpm/3_32p.xpm"
#include "xpm/4_32p.xpm"
#include "xpm/5_32p.xpm"
#include "xpm/6_32p.xpm"
#include "xpm/7_32p.xpm"
#include "xpm/8_32p.xpm"
#include "xpm/flag_32p.xpm"
#include "xpm/mine_32p.xpm"
#include "xpm/killingmine_32p.xpm"
#include "xpm/questionmark_32p.xpm"

#include "xpm/smiley_normal.xpm"
#include "xpm/smiley_loose.xpm"
#include "xpm/smiley_win.xpm"
#include "xpm/smiley_click.xpm"
#include "xpm/smiley_normal_24p.xpm"
#include "xpm/smiley_loose_24p.xpm"
#include "xpm/smiley_win_24p.xpm"
#include "xpm/smiley_click_24p.xpm"

#include "xpm/cursor.xpm"
#include "xpm/play.xpm"
#include "xpm/pause.xpm"
#include "xpm/stop.xpm"
#include "xpm/hand.xpm"
#include "xpm/Icon.xpm"
#include "xpm/Icon_32p.xpm"

//for easier accessing of the images
static char** xpm_1[3] = { xpm_1_16p, xpm_1_24p, xpm_1_32p };
static char** xpm_2[3] = { xpm_2_16p, xpm_2_24p, xpm_2_32p };
static char** xpm_3[3] = { xpm_3_16p, xpm_3_24p, xpm_3_32p };
static char** xpm_4[3] = { xpm_4_16p, xpm_4_24p, xpm_4_32p };
static char** xpm_5[3] = { xpm_5_16p, xpm_5_24p, xpm_5_32p };
static char** xpm_6[3] = { xpm_6_16p, xpm_6_24p, xpm_6_32p };
static char** xpm_7[3] = { xpm_7_16p, xpm_7_24p, xpm_7_32p };
static char** xpm_8[3] = { xpm_8_16p, xpm_8_24p, xpm_8_32p };
static char*** xpm_numbers[8] = { xpm_1, xpm_2, xpm_3, xpm_4, xpm_5, xpm_6, xpm_7, xpm_8 };

static char** xpm_flag[3] = { xpm_flag_16p, xpm_flag_24p, xpm_flag_32p };
static char** xpm_mine[3] = { xpm_mine_16p, xpm_mine_24p, xpm_mine_32p };
static char** xpm_question_mark[3] = { xpm_questionmark_16p, xpm_questionmark_24p, xpm_questionmark_32p };
static char** xpm_killing_mine[3] = { xpm_killingmine_16p, xpm_killingmine_24p, xpm_killingmine_32p };

#endif //__IMAGES_H_