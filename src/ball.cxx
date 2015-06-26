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

#include <math.h>
#include "resources.hxx"
#include "ball.hxx"

Ball::Ball(Colors::Color c, float size_, const FloatVector2d& p, const FloatVector2d& v)
  : color(c), pos(p), vel(v)
{
  base = CL_Sprite("ball_base", resources);
  effect = CL_Sprite("ball_effect", resources);
  highlight = CL_Sprite("ball_highlight", resources);
  
  base.set_alignment(origin_center);
  effect.set_alignment(origin_center);
  highlight.set_alignment(origin_center);

  highlight.set_blend_func(blend_src_alpha, blend_one);

  size = size_;

  color_rgb = Colors::to_rgb(color);
}

void
Ball::update(float delta)
{
  orientation += 600.0f * delta;
  
  FloatVector2d old_pos = pos;
  pos = pos + vel*delta;

  if (pos.x < 0 || pos.x > 800)
    {
      vel.x = -vel.x;
      if (size <= .25f)
        size *= 0.75;
      pos = old_pos;
    }

  if (pos.y < 0 || pos.y > 600)
    {
      vel.y = -vel.y;
      if (size <= .25f)
      size *= 0.75;
      pos = old_pos;
    }
}

void
Ball::draw()
{
  if (size > .1f)
    {
  base.set_color(color_rgb);
  base.set_scale(size, size);
  base.draw((int)pos.x, (int)pos.y);

  effect.set_angle(orientation);
  effect.set_scale(size, size);
  effect.draw((int)pos.x, (int)pos.y);

  highlight.set_scale(size, size);
  highlight.draw((int)pos.x, (int)pos.y);
    }
}

/* EOF */
