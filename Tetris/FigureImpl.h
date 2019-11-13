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
/// @brief Tetris game figures definition

#ifndef __TETRIS_FIGURE_IMPL_H__
#define __TETRIS_FIGURE_IMPL_H__

#include "Block.h"
#include "Figure.h"
#include "ScreenDef.h"
#include <array>
#include <cstdint>

namespace Tetris
{
/// @brief Draw blocks on a screen
///
/// @tparam BlocksArray - array type
/// @param blocks - array of blocks to draw
/// @param screen - screen with the game; blocks will be drawn on it
/// @param mode - drawing mode
template <class BlocksArray>
void Draw(BlocksArray &blocks, TetrisScreen &screen, DrawMode mode)
{
  if (mode == DrawMode::clear)
  {
    for (auto &block : blocks)
      screen[block.Pos()] = Colour::background;
  }
  else if (mode == DrawMode::draw)
  {
    for (auto &block : blocks)
      screen[block.Pos()] = Colour::red;
  }
}

/// @brief Translate figure on a screen
///
/// Function checks colision with screen boundary
/// and with other blocks already present on the screen.
///
/// Satisfies requirements:
///   [REQ_MoveLimit](https://github.com/grygorek/TetrisArch#REQ_MoveLimit)
///   [REQ_BlocksNotOverlap](https://github.com/grygorek/TetrisArch#REQ_BlocksNotOverlap)
///
/// @tparem FigureType - type of a figure to translate
/// @param fig - figure to translate
/// @param screen - screen with the game
/// @param vec - direction of translation
/// @retval true - figure has been translated
/// @retval false - figure could not be translated due to colision with
///    a different object on the screen
template <class FigureType>
bool Translate(FigureType &fig, TetrisScreen &screen, Position vect)
{
  FigureType f{fig.Pos() + vect};
  for (const auto &b : f._blocks)
    if (screen.Colision(b.Pos()))
      return false;
  fig = f;
  return true;
}

/// @brief Rotate figure on a screen
///
/// Function checks colision with screen boundary
/// and with other blocks already present on the screen.
///
/// Satisfies requirements:
///   [REQ_MoveLimit](https://github.com/grygorek/TetrisArch#REQ_MoveLimit)
///   [REQ_BlocksNotOverlap](https://github.com/grygorek/TetrisArch#REQ_BlocksNotOverlap)
///
/// @tparem FigureType - type of a figure to rotate
/// @param fig - figure to rotate
/// @param screen - screen with the game
/// @param dir - direction of rotation
/// @retval true - figure has been rotated
/// @retval false - figure could not be rotated due to colision with
///    a different object on the screen
template <class FigureType>
bool Rotate(FigureType &fig, TetrisScreen &screen, Direction dir)
{
  FigureType b{dir};

  for (auto &bl : b._blocks)
  {
    bl = Block{bl.Pos() + fig.Pos()};
    if (screen.Colision(bl.Pos()))
      return false;
  }
  b._pos = fig.Pos();
  fig    = b;
  return true;
}

/// @brief Bar T figure
///
/// Satisfies requirements:
///   [REQ_FiguresType](https://github.com/grygorek/TetrisArch#REQ_FiguresType)
class BarT final : public Figure
{
  friend bool Tetris::Translate<BarT>(BarT &, TetrisScreen &screen,
                                      Position direction);
  friend bool Tetris::Rotate<BarT>(BarT &fig, TetrisScreen &screen,
                                   Direction dir);

public:
  /// Create figure at given position
  /// @param p - positon
  explicit BarT(Position p)
      : _pos{p}
  {
    for (auto &b : _blocks)
      b = Block{b.Pos() + p};
  }

  Position Pos() const override { return _pos; }
  std::int32_t BlocksCount() const override { return _blocks.size(); }

  /// @brief Translate the figure on a screen in given direction
  /// @param screen - game screen
  /// @param direction - direction to translate
  /// @returns true on success, false on colision
  bool Translate(TetrisScreen &screen, Position direction) override
  {
    return Tetris::Translate<BarT>(*this, screen, direction);
  }

  /// @brief Draw the figure on a screen with given mode
  /// @param screen - game screen
  /// @param mode - drawing mode (show or hide the figure)
  void Draw(TetrisScreen &screen, DrawMode mode) override
  {
    Tetris::Draw(_blocks, screen, mode);
  }

  /// @brief Rotate the figure on a screen in given direction
  /// @param screen - game screen
  /// @param dir - rotation direction
  /// @returns true on success, false on colision
  bool Rotate(TetrisScreen &screen, Direction dir) override
  {
    return Tetris::Rotate(*this, screen, dir);
  }

private:
  /// @brief Figures array
  ///
  /// This is a static implementation.
  /// Array holds figures of all possible rotations.
  /// Rotation of a figure is just simply selecting different index
  /// in the array.
  static const std::array<std::array<Block, 4>, 4> _figure;

  Position _pos{};
  std::int32_t _idx{0};
  std::array<Block, 4> _blocks{_figure[0]};

  explicit BarT(Direction dir)
  {
    std::int32_t size{_figure.size()};
    _idx += dir;
    if (_idx >= size)
      _idx = 0;
    else if (_idx < 0)
      _idx = size - 1;

    _blocks = _figure[_idx];
  }
};

/// @brief Square figure
///
/// Satisfies requirements:
///   [REQ_FiguresType](https://github.com/grygorek/TetrisArch#REQ_FiguresType)
class Square final : public Figure
{
  friend bool Tetris::Translate<Square>(Square &, TetrisScreen &screen,
                                        Position direction);

public:
  explicit Square(Position p)
      : _blocks{std::array<Block, 1>{Block{p}}}
  {
  }

  Position Pos() const override { return _blocks[0].Pos(); }
  std::int32_t BlocksCount() const override { return _blocks.size(); }

  bool Translate(TetrisScreen &screen, Position direction) override
  {
    return Tetris::Translate<Square>(*this, screen, direction);
  }

  void Draw(TetrisScreen &screen, DrawMode mode) override
  {
    Tetris::Draw(_blocks, screen, mode);
  }

private:
  std::array<Block, 1> _blocks;
};

/// @brief Big Square figure
///
/// Satisfies requirements:
///   [REQ_FiguresType](https://github.com/grygorek/TetrisArch#REQ_FiguresType)
class BigSquare final : public Figure
{
  friend bool Tetris::Translate<BigSquare>(BigSquare &, TetrisScreen &screen,
                                           Position direction);

public:
  explicit BigSquare(Position p)
      : _blocks{std::array<Block, 4>{
            Block{{p._row, p._col}}, Block{{p._row, p._col + 1}},
            Block{{p._row + 1, p._col}}, Block{{p._row + 1, p._col + 1}}}}
  {
  }

  Position Pos() const override { return _blocks[0].Pos(); }
  std::int32_t BlocksCount() const override { return _blocks.size(); }

  bool Translate(TetrisScreen &screen, Position direction) override
  {
    return Tetris::Translate<BigSquare>(*this, screen, direction);
  }

  void Draw(TetrisScreen &screen, DrawMode mode) override
  {
    Tetris::Draw(_blocks, screen, mode);
  }

private:
  std::array<Block, 4> _blocks;
};

/// @brief Simple Bar figure
///
/// Satisfies requirements:
///   [REQ_FiguresType](https://github.com/grygorek/TetrisArch#REQ_FiguresType)
class Bar final : public Figure
{
  friend bool Tetris::Translate<Bar>(Bar &, TetrisScreen &screen,
                                     Position direction);
  friend bool Tetris::Rotate<Bar>(Bar &fig, TetrisScreen &screen,
                                  Direction dir);

public:
  explicit Bar(Position p)
      : _pos{p}
  {
    for (auto &b : _blocks)
      b = Block{b.Pos() + p};
  }

  Position Pos() const override { return _pos; }
  std::int32_t BlocksCount() const override { return _blocks.size(); }

  bool Translate(TetrisScreen &screen, Position direction) override
  {
    return Tetris::Translate<Bar>(*this, screen, direction);
  }

  void Draw(TetrisScreen &screen, DrawMode mode) override
  {
    Tetris::Draw(_blocks, screen, mode);
  }

  bool Rotate(TetrisScreen &screen, Direction dir) override
  {
    return Tetris::Rotate(*this, screen, dir);
  }

private:
  /// @brief Figures array
  ///
  /// This is a static implementation.
  /// Array holds figures of all possible rotations.
  /// Rotation of a figure is just simply selecting different index
  /// in the array.
  static const std::array<std::array<Block, 3>, 2> _figure;

  Position _pos{};
  std::int32_t _idx{0};
  std::array<Block, 3> _blocks{_figure[0]};

  explicit Bar(Direction dir)
  {
    std::int32_t size{_figure.size()};

    _idx += dir;
    if (_idx >= size)
      _idx = 0;
    else if (_idx < 0)
      _idx = size - 1;

    _blocks = _figure[_idx];
  }
};
} // namespace Tetris

#endif //__TETRIS_FIGURE_IMPL_H__
