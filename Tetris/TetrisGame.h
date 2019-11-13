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

#ifndef __TETRIS_GAME_H__
#define __TETRIS_GAME_H__

#include "Command.h"
#include "FigureImpl.h"
#include "ScreenDef.h"
#include <random>



/// Tetris game namespace
/// 
/// All types and functions used in the game are inside this namespace.
namespace Tetris
{
/// @brief Tetris game object
///
/// Entire game happens in computers memory. To observe the game
/// the debugger needs to be opened and _screen._lines memory 
/// location needs to be observed.
///
/// User's input should be passed to Input funtion.
/// Tick function must be called each time a new input has been inserted.
/// Tick is there to progress the game.
class Game
{
public:
  Game() { _figure->Draw(_screen, DrawMode::draw); }

  Game(const Game &) = delete;
  void operator=(const Game &) = delete;

  /// Dispatch new command to the game
  void Input(Command cmd) 
  {
    /// Satisfies requirements:
    ///   [REQ_NoPendingCommands](https://github.com/grygorek/TetrisArch#REQ_NoPendingCommands)
    _cmd = cmd;
  }

  /// Progress the game. React to commands.
  void Tick()
  {
    /// Satisfies requirements: [REQ_Cmd](https://github.com/grygorek/TetrisArch#REQ_Cmd)
    switch (_cmd)
    {
    case Command::Idle:
      break;
    case Command::RotateLeft:
      Rotate(Direction::left);
      break;
    case Command::RotateRight:
      Rotate(Direction::right);
      break;
    case Command::TranslateDown:
      Translate(Position{1, 0});
      break;
    case Command::TranslateLeft:
      Translate(Position{0, -1});
      break;
    case Command::TranslateRigth:
      Translate(Position{0, 1});
      break;
    }
    _cmd = Command::Idle;
  }

private:
  /// Command to execute
  Command _cmd{};
  /// Pointer to a current figure
  std::shared_ptr<Figure> _figure{RandomFigureGenerator()};
  /// Game screen
  TetrisScreen _screen{};
  
  /// Handle 'translate' command
  /// @param p - translation vector
  void Translate(Position p)
  {
    // must clear before checking colisions
    _figure->Draw(_screen, DrawMode::clear);
    auto result{_figure->Translate(_screen, p)};
    _figure->Draw(_screen, DrawMode::draw);

    if (result == false && _cmd == Command::TranslateDown)
    {
      /// Satisfies requirements:
      ///   [REQ_LineFull](https://github.com/grygorek/TetrisArch#REQ_LineFull)
      ///   [REQ_FigureLifeTime](https://github.com/grygorek/TetrisArch#REQ_FigureLifeTime)
      _screen.RemoveFullLines();
      _figure = RandomFigureGenerator();
      _figure->Draw(_screen, DrawMode::draw);
    }
  }

  /// Handle 'rotation' command
  /// @param d - rotation direction
  void Rotate(Direction d)
  {
    // must clear before checking colisions
    _figure->Draw(_screen, DrawMode::clear);
    auto result{_figure->Rotate(_screen, d)};
    _figure->Draw(_screen, DrawMode::draw);
  }

  /// @brief Generate a new figure
  ///
  /// New figure is generated randomly.
  ///
  /// @returns pointer to a new figure
  static std::shared_ptr<Figure> RandomFigureGenerator()
  {
    std::random_device dev;
    std::default_random_engine rndEng{dev()};
    std::uniform_int_distribution<int> selectFigure(0, 3);
    auto figureID{selectFigure(rndEng)};

    Position initPos{0, TetrisScreen::Dimention()._col / 2 - 1};

    // Instead of dynamically allocating an object I tried to have
    // static objects and just return a pointer to it. In that way
    // I would avoid dynamic allocation. Unfortunately, for some reason
    // MSVS2019 was getting crazy and not working properly. Making this
    // dynamic works.
    switch (figureID)
    {
    default:
    case 0:
      return std::make_shared<BigSquare>(initPos);
    case 1:
      return std::make_shared<Bar>(initPos);
    case 2:
      return std::make_shared<BarT>(initPos);
    case 3:
      return std::make_shared<Square>(initPos);
    }
  }

};

} // namespace Tetris

#endif
