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

#include <ClanLib/display.h>
#include <ClanLib/core.h>
#include <ClanLib/gl.h>

#include "game_config.hxx"
#include "resources.hxx"
#include "input/input_manager.hxx"
#include "guile.hxx"
#include "background.hxx"
#include "ship.hxx"
#include "game_world.hxx"
#include "colors.hxx"
#include "vector2d.hxx"
#include "ball_manager.hxx"
#include "diamond.hxx"
#include "colorasion_main.hxx"

ColorasionMain::ColorasionMain()
{

}

ColorasionMain::~ColorasionMain()
{
}

void 
ColorasionMain::init()
{
  CL_SetupCore::init();
  CL_SetupDisplay::init();
  CL_SetupGL::init();
}

void
ColorasionMain::deinit()
{
  InputManager::deinit();
  delete resources;

  CL_SetupGL::deinit();
  CL_SetupDisplay::deinit();
  CL_SetupCore::deinit();
}

void 
ColorasionMain::parse_args(int argc, char** argv)
{
  CL_CommandLine argp;

  const int debug_flag = 256;
    
  argp.set_help_indent(22);
  argp.add_doc   ("Colorasion, a colorfull shoot'em up.");

  argp.add_group("Display Options:");
  argp.add_option('g', "geometry",   "WxH", "Change window size to WIDTH and HEIGHT");
  argp.add_option('f', "fullscreen", "", "Launch the game in fullscreen");

  argp.add_group("Controlls Options:");
  argp.add_option('c', "controller", "FILE", "Use controller as defined in FILE");

  argp.add_group("Misc Options:");
  argp.add_option(debug_flag, "debug", "FILE", "Use controller as defined in FILE");
  argp.add_option('h', "help", "", "Print this help text");

  argp.parse_args(argc, argv);

  while (argp.next())
    {
      switch (argp.get_key())
        {
        case debug_flag:
          gamecfg->debug = 1;
          break;
		  
        case 'f':
          gamecfg->fullscreen = true;
          break;

        case 'g':
          if (sscanf(argp.get_argument().c_str(), "%dx%d",
                     &gamecfg->screen_width, &gamecfg->screen_height) == 2)
            {
              std::cout << "Geometry: " 
                        << gamecfg->screen_width << "x" << gamecfg->screen_height
                        << std::endl;
            }
          break;

        case 'c':
          gamecfg->controller_file = argp.get_argument();
          break;

        case 'h':
          argp.print_help();
          exit(EXIT_SUCCESS);
          break;

        case CL_CommandLine::REST_ARG:
          throw CL_Error("Rest arguments not supported");
          break;
        }
   }
}

int
ColorasionMain::main(int argc, char** argv)
{
  std::cout << "Starting Colorasion" << std::endl;

  try
    {
      gamecfg = new GameConfig();
  
      parse_args(argc, argv);
      
      // Init Guile
      scm_init_guile ();
      Guile::enable_debug();
      Guile::enable_readline();

      // Init all subsystems
      init();     

      // Create the main window
      window = new CL_DisplayWindow("Colorasion",
                                    gamecfg->screen_width, gamecfg->screen_height, 
                                    gamecfg->fullscreen);
      CL_Display::set_current_window (window);
      CL_Display::clear();

      resources = new CL_ResourceManager("../data/colorasion.xml");
      InputManager::init(gamecfg->controller_file);

      GameWorld world;
      BallManager balls;
      Background background;
      Ship ship(FloatVector2d(400, 300));
      
      world.add(&balls);
      world.add(&ship);

      srand(time(NULL));

      // Start Game
      unsigned int last_time = CL_System::get_time();

      for (int i = 0; i < 1; ++i)
        {
          balls.add(Colors::random(), 1.0f,
                    FloatVector2d(rand()% 800,
                                  rand()% 600),
                    FloatVector2d(50, 30));
          balls.add(Colors::random(), .7f,
                    FloatVector2d(rand()% 800,
                                  rand()% 600),
                    FloatVector2d(-20, 20));
        }

      for (int i = 0; i < 4; ++i)
        world.add(new Diamond(Colors::random(),
                              FloatVector2d(rand()% 800,
                                            rand()% 600)));

      while(!CL_Keyboard::get_keycode(CL_KEY_ESCAPE))
        {
          float delta = (CL_System::get_time() - last_time)/1000.0f;
          last_time = CL_System::get_time();
          
          // std::cout << "Delta: " << delta << std::endl;

          background.draw();
          world.draw();

          InputManager::update(delta);
          ship.update_controlls(InputManager::get_controller());
          world.update(delta);
         
          InputManager::clear();
 
          CL_Display::flip();
          CL_System::sleep(10);
          CL_System::keep_alive();
        }
      // End Game


      // Shutdown everything
      deinit();
    }
  catch (CL_Error& err)
    {
      std::cout << "CL_Error: " << err.message.c_str() << std::endl;
    }
  /*  catch (FeuerkraftError& err)
      {
      std::cout << "FeuerkraftError: " << err.what() << std::endl;
      }*/
  catch (std::exception& err)
    {
      std::cout << "Error: " << err.what() << std::endl;
    }
  catch (...)
    {
      std::cout << "Bug: Unknown exception catched, don't know what to do" << std::endl;
    }

  std::cout << "End" << std::endl;
}

/* EOF */
