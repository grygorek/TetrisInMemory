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

#ifndef __TETRIS_FIGURE_H__
#define __TETRIS_FIGURE_H__

#include "Block.h"
#include "ScreenDef.h"
#include <array>
#include <cstdint>

namespace Tetris
{

/// @brief Helper definition to move a figure left or right
enum Direction
{
  left  = -1,
  right = 1
};

/// @brief Type of drawing
/// 
/// Used when moving a figure. Before the new one is drawn, the old one has to be
/// removed from the screen.
enum class DrawMode
{
  clear, ///< Clear figure from the screen
  draw   ///< Show figure on the screen
};

/// @brief Base class of the figure. Defines an interface
class Figure
{
public:
  /// Out of how many blocks the figure is made of
  virtual std::int32_t BlocksCount() const = 0;
  /// Position of a figure
  virtual Position Pos() const             = 0;

  /// Move the figure
  ///
  /// @returns false if there is a colision and the figure cannot be translated
  virtual bool Translate(TetrisScreen &, Position direction) { return true; };
  /// Rotate the figure
  /// @returns false if there is a colision and the figure cannot be rotated
  virtual bool Rotate(TetrisScreen &, Direction) { return true; }
  /// Draw or clear the figure
  virtual void Draw(TetrisScreen &, DrawMode) = 0;

  virtual ~Figure() {}
};

} // namespace Tetris

#endif //__TETRIS_FIGURE_H__
