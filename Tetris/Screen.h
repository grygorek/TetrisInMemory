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
/// @brief

#ifndef __TETRIS_SCREEN_H__
#define __TETRIS_SCREEN_H__

#include "Position.h"
#include <algorithm>
#include <array>

namespace Tetris
{
/// @brief Define line type that makes the games screen
///
/// Tetris::Block is made of Tetris::Colour and Tetris::Position.
/// It is too expnesive to use position for each element of a line.
/// Only line's row is needed as a location. Colour is used as line's
/// colour. In that way, lines building block is equivalent to Block
/// and both can be compared. Hence this satisfies:
///   [REQ_LineOfBlocks](https://github.com/grygorek/TetrisArch#REQ_LineOfBlocks)
template <ColumnIdx LineLength>
using LineType = std::array<Colour, LineLength>;

/// @brief Lines collection type
template <RowIdx LinesCount, ColumnIdx LineLength>
using LinesCollection = std::array<LineType<LineLength>, LinesCount>;

/// @brief Line is not full if any line's block has background colour
///
/// Satisfies requirements:
///   [REQ_LineFull](https://github.com/grygorek/TetrisArch#REQ_LineFull)
///
/// @tparem SingleLineType - type of the line
/// @param line - line to check
/// @retval false - not full
/// @retval true - line is full
template <class SingleLineType>
bool IsLineFull(const SingleLineType &line)
{
  for (const auto &b : line)
    if (b == Colour::background)
      return false;
  return true;
}

/// @brief Remove full lines from the screen
///
/// Search for the full lines. It starts from the bottom.
/// The full line is overwritten by the line above it.
/// All lines are copied down. Once all lines are copied down,
/// the top line, when drops down leaves empty line.
///
/// Satisfies requirements:
///   [REQ_LineFull](https://github.com/grygorek/TetrisArch#REQ_LineFull)
/// 
/// @param lines - collection of lines
template <class CollectionType>
void RemoveFullLines(CollectionType &lines)
{
  auto move{[&lines](std::int32_t count) mutable {
    for (auto i{count}; i > 0; i--)
      lines[i] = lines[i - 1];
    /// Satisfies requirements:
    ///   [REQ_BlocksDrop](https://github.com/grygorek/TetrisArch#REQ_BlocksDrop)
    lines[0].fill(Colour::background);
  }};

  std::int32_t size = lines.size(); // changing type
  for (auto i{1}; i < size; i++)
    if (IsLineFull(lines[i]))
      /// Satisfies requirements:
      ///   [REQ_BlocksDrop](https://github.com/grygorek/TetrisArch#REQ_BlocksDrop)
      move(i);
}


/// @brief Game's screen
///
/// Screen is a lines' holder. Its main function is to remove full lines,
/// check colisions and provide access to screen boundaries.
template <RowIdx LinesCount, ColumnIdx LineLength>
class Screen
{
public:
  /// Screen width
  constexpr static auto Width() { return LineLength; }
  /// Screen depth
  constexpr static auto Depth() { return LinesCount; }

  /// Screen dimention
  constexpr static Position Dimention() { return Position{Depth(), Width()}; }

  /// Access single line's building element
  auto &operator[](Position p) { return _lines[p._row][p._col]; }
  const auto &operator[](Position p) const { return _lines[p._row][p._col]; }

  /// Check overlapping
  ///
  /// Satisfies requirements:
  ///   [REQ_BlocksNotOverlap](https://github.com/grygorek/TetrisArch#REQ_BlocksNotOverlap)
  ///
  /// @param p - check colision at this position
  /// @retval true - colision
  /// @retval false - no colision
  bool Colision(Position p) const
  {
    return p._col >= Width() || p._col < 0 || p._row >= Depth() || p._row < 0 ||
           (*this)[p] != Colour::background;
  }

  /// @brief Search for full lines and remove them.
  /// Satisfies requirements:
  ///   [REQ_LineFull](https://github.com/grygorek/TetrisArch#REQ_LineFull)
  void RemoveFullLines() { Tetris::RemoveFullLines(_lines); }

private:
  /// Screen is made of lines
  /// Satisfies requirements:
  ///   [REQ_ScreenSize](https://github.com/grygorek/TetrisArch#REQ_ScreenSize)
  LinesCollection<LinesCount, LineLength> _lines{};
};

} // namespace Tetris

#endif //__TETRIS_SCREEN_H__
