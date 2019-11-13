
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
/// @brief Tetris In Memory Game
///
/// How to play:
///  * Global variable s_cmd is a user input
///  * Screen is at this memory address: &tetris._screen._lines
///    Format the memory view to see single bytes and 8 bytes per line.
///  * Progress the game in the debugger. Stop on a breakpoint and
///    put a new command in s_cmd variable. Continue stepping through
///    the program.


#include "TetrisGame.h"
#include <chrono>
#include <iostream>
#include <thread>

/// @brief Single command buffer for a player
///
/// Satisfies requirements:
///   [REQ_NoPendingCommands](https://github.com/grygorek/TetrisArch#REQ_NoPendingCommands)
///   [REQ_SinglePlayer](https://github.com/grygorek/TetrisArch#REQ_SinglePlayer)
volatile Tetris::Command s_cmd;

int main()
{
  Tetris::Game tetris;

  std::thread timer{[]() {
    while (1)
    {
      /// Satisfies requirements:
      ///   [REQ_OnTimerCommand](https://github.com/grygorek/TetrisArch#REQ_OnTimerCommand)
      std::this_thread::sleep_for(std::chrono::seconds(1));
      s_cmd = Tetris::Command::TranslateDown;
    }
  }};

  std::thread input{[]() {
    while (1)
    {
      /// Satisfies requirements:
      ///   [REQ_NoPendingCommands](https://github.com/grygorek/TetrisArch#REQ_NoPendingCommands)
      switch (std::getchar())
      {
      case 'a':
        s_cmd = Tetris::Command::TranslateLeft;
        break;
      case 'd':
        s_cmd = Tetris::Command::TranslateRigth;
        break;
      case ' ':
        s_cmd = Tetris::Command::RotateRight;
        break;
      case 's':
        s_cmd = Tetris::Command::TranslateDown;
        break;
      default:
        break;
      }
    }
  }};

  while (1)
  {
    if (s_cmd != Tetris::Command::Idle)
    {
      /// Single input, single player
      /// Satisfies requirements:
      ///   [REQ_SinglePlayer](https://github.com/grygorek/TetrisArch#REQ_SinglePlayer)
      tetris.Input(s_cmd);
      /// Satisfies requirements:
      ///   [REQ_NoPendingCommands](https://github.com/grygorek/TetrisArch#REQ_NoPendingCommands)
      s_cmd = Tetris::Command::Idle;
      tetris.Tick();
    }
  }
}