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
/// @brief Single building block

#ifndef __TETRIS_BLOCK_H__
#define __TETRIS_BLOCK_H__

#include "Position.h"
#include <cstdint>

namespace Tetris
{

/// @brief Definition of how figures will be filled in
enum class Colour : std::uint8_t
{
  red        = 0xDD, ///< `red` is fake, it is just a value in memory 
  background = 0     ///< make block empty
};

/// @brief Smallest building element
///
/// All objects in the tetris game are made of blocks.
/// Single block has position and information whether is empty on not.
///
/// Satisfies requirements:
///    [REQ_LineOfBlocks](https://github.com/grygorek/TetrisArch#REQ_LineOfBlocks)
class Block
{
public:
  Block() = default;

  /// @brief Single block at given position
  explicit Block(Position p)
      : _pos{p}
  {
  }

  /// @brief Read column (position) index
  ColumnIdx Column() const { return Pos()._col; }
  /// @brief Read row (position) index
  RowIdx Row() const { return Pos()._row; }
  /// @brief Block's position
  Position Pos() const { return _pos; }

  /// Two blocks are equal when they are empty
  bool operator==(const Block &b) const { return IsEmpty() == b.IsEmpty(); }

  /// Empty block has background colour
  bool IsEmpty() const { return _color == Colour::background; }

protected:
  Position _pos{};
  Colour _color{Colour::red};

  /// @brief Single block with given colour
  explicit Block(Colour c)
      : _color{c}
  {
  }

  /// @brief Single block with given colour and position
  /// @param p - block position
  /// @param c - colour of this block
  explicit Block(Position p, Colour c)
      : _pos{p}
      , _color{c}
  {
  }
};

/// @brief Helper class. Empty block has background colour
class EmptyBlock : public Block
{
public:
  EmptyBlock()
      : Block{Colour::background}
  {
  }

  /// @brief Single block with given position
  /// @param p - block position
  explicit EmptyBlock(Position p)
      : Block(p, Colour::background)
  {
  } 
};

} // namespace Tetris

#endif
