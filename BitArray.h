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

#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#include <cmath>


//BitArray: simple class to store a array of bits
//resize and fast reset possible
class BitArray{
private:
  unsigned size_ = 0;     //number of bits
  unsigned* bits_ = nullptr;  //storage for the bits

  const unsigned SHIFT_DISTANCE = log2(sizeof(unsigned)) + 3;     //5 if unsigned is 32bit, so 5 last bits for position within unsigned, rest for array index 
  const unsigned BIT_ACCESS_MASK = exp2(SHIFT_DISTANCE) - 1;      //mask to access the bits for bit position in unsingned
public:
  enum DefaultValue{ DEFAULT_VALUE_DONT_CARE = 0, DEFAULT_VALUE_0, DEFAULT_VALUE_1 };   //don´t care means, nothing is done, else set 0 or 1

  BitArray(unsigned size = 0, DefaultValue value = DEFAULT_VALUE_0);  //resizes and sets bits, if needed
  ~BitArray();  //deletes bits

  void resize(unsigned size, DefaultValue value = DEFAULT_VALUE_DONT_CARE); //resizes (WARNING! no copying, just set all bits or do nothing)
  void setAll(bool value);    //calls memset to set all bits 0 / 1

  //no bound checking here
  void setBit(unsigned index){ bits_[(index >> SHIFT_DISTANCE)] |= (1 << (index & BIT_ACCESS_MASK)); }    //set single bit
  void resetBit(unsigned index){ bits_[(index >> SHIFT_DISTANCE)] &= (~(1 << (index & BIT_ACCESS_MASK))); } //reset single bit
  bool getBit(unsigned index) const { return !!(bits_[(index >> SHIFT_DISTANCE)] & (1 << (index & BIT_ACCESS_MASK))); } //get single bit

  unsigned getSize() const { return size_; }  //get size (number of bits)
};

#endif //__BIT_ARRAY_H__