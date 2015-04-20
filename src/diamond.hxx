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

#ifndef HEADER_DIAMOND_HXX
#define HEADER_DIAMOND_HXX

#include <ClanLib/Display/sprite.h>
#include "game_obj.hxx"
#include "colors.hxx"
#include "vector2d.hxx"

/** */
class Diamond : public GameObj
{
private:
  CL_Sprite sprite;
  Colors::Color color;
  FloatVector2d pos;
public:
  Diamond(Colors::Color c, const FloatVector2d& pos);

  void update(float delta);
  void draw();
private:
  Diamond (const Diamond&);
  Diamond& operator= (const Diamond&);
};

#endif

/* EOF */
