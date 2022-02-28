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

#ifndef HEADER_BALL_HXX
#define HEADER_BALL_HXX

#include <ClanLib/Display/sprite.h>
#include "vector2d.hxx"
#include "colors.hxx"
#include "game_obj.hxx"

/** */
class Ball
{
private:
  CL_Sprite effect;
  CL_Sprite highlight;
  CL_Sprite base;

  float size;
  float orientation;

  Colors::Color color;
  CL_Color color_rgb;

  FloatVector2d pos;
  FloatVector2d vel;
public:
  Ball(Colors::Color c, float size_, const FloatVector2d& p, const FloatVector2d& v);

  void set_size(float s) { size = s; }
  float get_size() { return size; }

  float get_pixel_size() { return 64 * size; }
  FloatVector2d get_pos() { return pos; }

  void update(float delta);
  void draw();
};

#endif

/* EOF */
