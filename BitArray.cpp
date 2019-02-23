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
#include "BitArray.h"

BitArray::BitArray(unsigned size, DefaultValue value){
  resize(size);
  if (value != DEFAULT_VALUE_DONT_CARE)   //set bits just when it´s needed
    setAll(value == DEFAULT_VALUE_1);
}

BitArray::~BitArray(){
  delete[] bits_;     //bits pointer is pointing on a array on the heap or it´s nullptr
}

void BitArray::resize(unsigned size, DefaultValue value){
  if ((size >> SHIFT_DISTANCE) == (size_ >> SHIFT_DISTANCE)){   //check, if resize is needed
    if (value != DEFAULT_VALUE_DONT_CARE)   //bit set is optional, can also be done when no resizing is needed
      setAll(value == DEFAULT_VALUE_1);
    return;
  }
  size_ = size;
  delete[] bits_;
  try{
    bits_ = new unsigned[(size_ >> SHIFT_DISTANCE) + 1];
  }
  catch (std::bad_alloc&){
    bits_ = nullptr;
    size = 0;
    throw;
  }
  if (value != DEFAULT_VALUE_DONT_CARE)
    setAll(value == DEFAULT_VALUE_1);
}

void BitArray::setAll(bool value){
  if (size_ > 0)    //just if BitArray is not empty
    memset(bits_, value ? UINT_MAX : 0, ((size_ >> SHIFT_DISTANCE) + 1) * sizeof(unsigned));
}