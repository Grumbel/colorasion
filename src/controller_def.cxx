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

#include <iostream>
#include "controller_def.hxx"

int
ControllerDef::get_button_count()
{
  return 3;
}

int
ControllerDef::get_axis_count()
{
  return 3;
}

std::string
ControllerDef::button_id2name(int id)
{
  switch (id)
    {
    case PRIMARY_FIRE_BUTTON:
      return "primary-button";
    case SECONDARY_FIRE_BUTTON:
      return "secondary-button";
    case START_BUTTON:
      return "start-button";
    default:
      std::cout << "Error: Unknown button-id: " << id << std::endl;
      return "unknown";
    }
}

int
ControllerDef::button_name2id(const std::string& name)
{
  if      (name == "primary-button")
    return PRIMARY_FIRE_BUTTON;
  else if (name == "secondary-button")
    return SECONDARY_FIRE_BUTTON;
  else if (name == "start-button")
    return START_BUTTON;
  else
    return -1;
}

std::string
ControllerDef::axis_id2name(int id)
{
  switch (id)
    {
    case ORIENTATION_AXIS:
      return "orientation-axis";
    case ACCELERATE_AXIS:
      return "accelerate-axis";
    case STRAFE_AXIS:
      return "strafe-axis";
    default:
      return "unknown";
    }
}

int 
ControllerDef::axis_name2id(const std::string& name)
{
  if (name == "orientation-axis")
    return ORIENTATION_AXIS;
  else if (name == "accelerate-axis")
    return ACCELERATE_AXIS;
  else if (name == "strafe-axis")
    return STRAFE_AXIS;
  else
    return -1;
}

/* EOF */
