//  $Id$
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_SHIP_HXX
#define HEADER_SHIP_HXX

#include <ClanLib/Display/sprite.h>
#include "input/controller.hxx"
#include "vector2d.hxx"
#include "colors.hxx"
#include "game_obj.hxx"

/** */
class Ship : public GameObj
{
private:
  CL_Sprite ship;
  CL_Sprite ship_left;
  CL_Sprite ship_right;

  FloatVector2d pos;
  float velocity;
  float strafe_velocity;
  float orientation;

  // Controll states 
  float acceleration;
  float steering;
  float strafe_steering;
  bool  left_firing;
  bool  right_firing;
  
  Colors::Color left_slot;
  Colors::Color right_slot;


  Colors::Color* current_slot;

  static Ship* current_;
public:
  static Ship* current() { return current_; }
  Ship(const FloatVector2d& pos);

  void set_pos(const FloatVector2d& pos);
  FloatVector2d get_pos() { return pos; }

  void set_slot(Colors::Color color);

  void update(float delta);
  void update_controlls(const Controller& controller);
  void draw();
private:
  Ship (const Ship&);
  Ship& operator= (const Ship&);
};

#endif

/* EOF */
