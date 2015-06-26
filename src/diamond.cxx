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

#include "ship.hxx"
#include "resources.hxx"
#include "diamond.hxx"

Diamond::Diamond(Colors::Color c, const FloatVector2d& pos_)
  : color(c), pos(pos_)
{
  sprite = CL_Sprite("diamond_base", resources);
}

void
Diamond::update(float delta)
{
  if ((Ship::current()->get_pos() - pos).get_length() < 48)
    {
      Ship::current()->set_slot(color);
    }
}

void
Diamond::draw()
{
  sprite.set_color(Colors::to_rgb(color));
  sprite.draw((int)pos.x, (int)pos.y);
}

/* EOF */
