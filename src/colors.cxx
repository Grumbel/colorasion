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

#include "colors.hxx"

namespace Colors {

CL_Color to_rgb(Color c)
{
  switch(c)
    {
    case RED:
      return CL_Color(255, 0, 0);
    case CYAN:
      return CL_Color(0, 255, 255);
    case BLUE:
      return CL_Color(0, 0, 255);
    case YELLOW:
      return CL_Color(255, 255, 0);
    case PURPLE:
      return CL_Color(255, 0, 255);
    case GREEN:
      return CL_Color(0, 255, 0);
    default:
      return CL_Color(255, 0, 0);
    }
}

Color random()
{
  return static_cast<Color>(rand()%6);
}

} // namespace Colors

/* EOF */
