//  $Id$
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
// 
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HEADER_INPUT_AXIS_HXX
#define HEADER_INPUT_AXIS_HXX

#include <vector>
#include <ClanLib/Signals/slot.h>
#include <ClanLib/Signals/signal_v1.h>

class InputAxis
{
protected:
  std::vector<CL_Slot> slots;
  CL_Signal_v1<float> move;  
public:
  InputAxis() {}
  virtual ~InputAxis() {}

  virtual void update(float delta) {}
  CL_Signal_v1<float>& on_move() { return move; }
};

#endif

/* EOF */
