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

#ifndef HEADER_COLORASION_MAIN_HXX
#define HEADER_COLORASION_MAIN_HXX

#include <ClanLib/application.h>

class CL_DisplayWindow;

/** */
class ColorasionMain : public CL_ClanApplication
{
private:
  CL_DisplayWindow* window;
public:
  ColorasionMain();
  ~ColorasionMain();

  void init();
  void deinit();
  void parse_args(int argc, char** argv);

  int main(int argc, char** argv);
private:
  ColorasionMain (const ColorasionMain&);
  ColorasionMain& operator= (const ColorasionMain&);
} app;

#endif

/* EOF */
