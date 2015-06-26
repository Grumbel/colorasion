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

#include <iostream>
#include "ball_manager.hxx"

BallManager* BallManager::current_;

BallManager::BallManager()
{
  current_ = this;
}

BallManager::~BallManager()
{
  
}

void
BallManager::update(float delta)
{
  for(Balls::iterator i = add_balls.begin(); i != add_balls.end(); ++i)
    {
      balls.push_back(*i);
    }
  add_balls.clear();

  for(Balls::iterator i = balls.begin(); i != balls.end(); ++i)
    {
      Balls::iterator j = i;
      ++j;
      for(; j != balls.end(); ++j)
        {
          float dist = ((*i)->get_pos() - (*j)->get_pos()).get_length();
          if (dist
              <
              ((*i)->get_pixel_size()/2
               + (*j)->get_pixel_size()/2)
              )
            {
              //std::cout << "Ball collision" << std::endl;
              if ((*i)->get_size() <= .25f
                  || (*j)->get_size() <= .25f)
                {
              if ((*i)->get_size() > (*j)->get_size())
                (*i)->set_size((*i)->get_size() + .02f);
              else
                (*j)->set_size((*j)->get_size() + .02f);
                }
            }
        }
    }

  for(Balls::iterator i = balls.begin(); i != balls.end(); ++i)
    (*i)->update(delta);
}

void
BallManager::draw()
{
  for(Balls::iterator i = balls.begin(); i != balls.end(); ++i)
    {
      (*i)->draw();
    }
}

void
BallManager::add(Colors::Color color,
                 float size,
                 const FloatVector2d& pos,
                 const FloatVector2d& vel)
{
  add_balls.push_back(new Ball(color, size, pos, vel));
}

/* EOF */
