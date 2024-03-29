/// @file
///
/// @author: Piotr Grygorczuk grygorek@gmail.com
///
/// @copyright Copyright 2019 Piotr Grygorczuk
/// All rights reserved.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
///
/// o Redistributions of source code must retain the above copyright notice,
///   this list of conditions and the following disclaimer.
///
/// o Redistributions in binary form must reproduce the above copyright notice,
///   this list of conditions and the following disclaimer in the documentation
///   and/or other materials provided with the distribution.
///
/// o My name may not be used to endorse or promote products derived from this
///   software without specific prior written permission.
///
/// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
/// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
/// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
/// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
/// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
/// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
/// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
/// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
/// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
/// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
/// POSSIBILITY OF SUCH DAMAGE.
///
/// @brief Position of game objects

#ifndef __TETRIS_POSITION_H__
#define __TETRIS_POSITION_H__

#include <cstdint>

namespace Tetris
{
using RowIdx    = std::int32_t;
using ColumnIdx = std::int32_t;


/// @brief Position type of each element of tetris game
///
/// Each element in the game has position. This class represents it.
/// Position is made of indexes of a row and a column.
 class Position
{
 public:
  /// @brief Position is equal when row and colum are the same
  bool operator==(const Position &rhs) const
  {
    return rhs._row == _row && rhs._col == _col;
  }

  /// @brief Position is not equal when row or column is different
  bool operator!=(const Position &rhs) const { return !(*this == rhs); }

  /// @brief row+row, column+column
  Position operator+(Position p) const
  {
    return Position{_row + p._row, _col + p._col};
  }

  RowIdx _row;
  ColumnIdx _col;
};

} // namespace Tetris

#endif
