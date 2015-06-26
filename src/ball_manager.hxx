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

#ifndef HEADER_BALL_MANAGER_HXX
#define HEADER_BALL_MANAGER_HXX

#include <vector>
#include "ball.hxx"

/** */
class BallManager : public GameObj
{
private:
  typedef std::vector<Ball*> Balls;
  Balls balls;
  Balls add_balls;
  
  static BallManager* current_;
public:
  static BallManager* current() { return current_; };

  BallManager();
  ~BallManager();

  void update(float delta);
  void draw();
  
  void add(Colors::Color color,
           float size,
           const FloatVector2d& pos,
           const FloatVector2d& vel);
};

#endif

/* EOF */
