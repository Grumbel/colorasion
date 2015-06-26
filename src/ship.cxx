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

#include "resources.hxx"
#include "controller_def.hxx"
#include "ship.hxx"
#include "ball_manager.hxx"
#include "game_world.hxx"
#include "math.hxx"

Ship* Ship::current_ = 0;

Ship::Ship(const FloatVector2d& pos_)
  : pos(pos_)
{
  current_ = this;

  ship = CL_Sprite("ship_base", resources);
  ship_left  = CL_Sprite("ship_left", resources);
  ship_right = CL_Sprite("ship_right", resources);

  ship.set_alignment(origin_center);
  ship_left.set_alignment(origin_center);
  ship_right.set_alignment(origin_center);

  velocity = 0;
  strafe_velocity = 0;
  orientation = 0;

  // Controll states 
  acceleration = 0;
  steering = 0;
  strafe_steering = 0;
  left_firing  = false;
  right_firing = false;

  left_slot  = Colors::RED;
  right_slot = Colors::CYAN;
  current_slot = &left_slot;
}

void
Ship::update(float delta)
{
  velocity        += 4.0f * acceleration * delta;
  orientation     += 4.0f * steering * delta;
  strafe_velocity += 4.0f * strafe_steering * delta;
  
  Math::cut(velocity, -50, 50);
  Math::cut(strafe_velocity, -10, 10);

  Math::cut(pos.x, 0, 800);
  Math::cut(pos.y, 0, 600);

  // FIXME: No delta
  strafe_velocity /= 1.01f;
  velocity        /= 1.01f;

  FloatVector2d vel(velocity, 0.0);
  pos += vel.rotate(orientation - Math::pi_2);
  pos += FloatVector2d(0.0, strafe_velocity).rotate(orientation - Math::pi_2);  
}

void
Ship::draw()
{
  ship.set_angle(orientation*180/3.1415927f);
  ship_right.set_angle(orientation*180/3.1415927f);
  ship_left.set_angle(orientation*180/3.1415927f);

  ship_left.set_color(Colors::to_rgb(left_slot));
  ship_right.set_color(Colors::to_rgb(right_slot));

  ship_left.draw(static_cast<int>(pos.x),
                 static_cast<int>(pos.y));
  ship_right.draw(static_cast<int>(pos.x),
                 static_cast<int>(pos.y));

  ship.draw(static_cast<int>(pos.x),
            static_cast<int>(pos.y));
}

void
Ship::set_pos(const FloatVector2d& pos_)
{
  pos = pos_;
}

void
Ship::update_controlls(const Controller& controller)
{
  acceleration    = -controller.get_axis_state(ACCELERATE_AXIS);
  steering        = controller.get_axis_state(ORIENTATION_AXIS);
  strafe_steering = controller.get_axis_state(STRAFE_AXIS);
  left_firing     = controller.get_button_state(PRIMARY_FIRE_BUTTON);
  right_firing    = controller.get_button_state(SECONDARY_FIRE_BUTTON);

  InputEventLst events = controller.get_events();

  for(InputEventLst::iterator i = events.begin(); i != events.end(); ++i)
    {
      if (i->type == BUTTON_EVENT)
        {
          if (i->button.name == SECONDARY_FIRE_BUTTON
              && i->button.down == true)
            {
              BallManager::current()->add(left_slot, .2f,
                                          pos + FloatVector2d(19, -19).rotate(orientation - Math::pi_2), 
                                          FloatVector2d(350.0f, 0).rotate(orientation - Math::pi_2)); 
                current_slot = &left_slot;
            }
          else if (i->button.name == PRIMARY_FIRE_BUTTON
                   && i->button.down == true)
            {
              BallManager::current()->add(right_slot, .2f,
                                          pos + FloatVector2d(19, 19).rotate(orientation - Math::pi_2), 
                                          FloatVector2d(350.0f, 0).rotate(orientation - Math::pi_2));
              current_slot = &right_slot;
            }
        }
    }
}

void
Ship::set_slot(Colors::Color c)
{
  *current_slot = c;
}

/* EOF */
