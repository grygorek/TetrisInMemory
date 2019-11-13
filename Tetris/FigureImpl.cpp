
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

#include "FigureImpl.h"

namespace Tetris
{
/// @brief Same figure rotated
///
/// For 'Bar' there are only two different positons
const std::array<std::array<Block, 3>, 2> Bar::_figure{
    std::array<Block, 3>{Block{{0, 1}}, Block{{1, 1}}, Block{{2, 1}}},
    std::array<Block, 3>{Block{{1, 0}}, Block{{1, 1}}, Block{{1, 2}}}};

/// @brief Same figure rotated
///
/// For 'BarT' there are four different positons
const std::array<std::array<Block, 4>, 4> BarT::_figure{
    // clang-format off
    std::array<Block,4> {Block{{0,0}}, Block{{0,1}}, Block{{0,2}}, Block{{1,1}}},
    std::array<Block,4> {Block{{0,1}}, Block{{1,0}}, Block{{1,1}}, Block{{2,1}}},
    std::array<Block,4> {Block{{0,1}}, Block{{1,0}}, Block{{1,1}}, Block{{1,2}}},
    std::array<Block,4> {Block{{0,0}}, Block{{1,0}}, Block{{1,1}}, Block{{2,0}}}
    // clang-format on
};
} // namespace Tetris
