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

#include "game_world.hxx"

GameWorld* GameWorld::current_ = 0;

GameWorld::GameWorld()
{
  current_ = this;
}

GameWorld::~GameWorld()
{
}

void
GameWorld::add(GameObj* obj)
{
  gameobjs.push_back(obj);
}

void
GameWorld::update(float delta)
{
  GameObjs tgameobjs = gameobjs;
  for(GameObjs::iterator i = tgameobjs.begin(); i != tgameobjs.end(); ++i)
    {
      (*i)->update(delta);
    }
}

void
GameWorld::draw()
{
  for(GameObjs::iterator i = gameobjs.begin(); i != gameobjs.end(); ++i)
    {
      (*i)->draw();
    }
}

/* EOF */
