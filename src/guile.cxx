//  $Id: guile.cxx,v 1.18 2003/08/20 00:15:10 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
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

#include <assert.h>
#include <guile/gh.h>
#include <ClanLib/Core/System/cl_assert.h>

#include "guile.hxx"

namespace Guile {
std::string
scm2string (SCM data)
{
  std::string str;
  
  if (gh_string_p(data))
    {
      char* tmpstr = gh_scm2newstr(data, 0);
      str = tmpstr;
      free(tmpstr);
    } else {
      SCM scmstr = scm_make_string(SCM_MAKINUM(0), SCM_UNDEFINED);
      SCM port = scm_mkstrport(SCM_INUM0, scmstr,
                               SCM_OPN | SCM_WRTNG, "scm_mkstrport");
      scm_display(data, port);
      char* tmpstr = gh_scm2newstr(scmstr, 0);
      str = tmpstr;
      free(tmpstr);
    }
  return str;
}

SCM vector2scm (const FloatVector2d& vec)
{
  /** If this causes throuble on WIN32, replace it with gh_cons() */
  return SCM_BOOL_F; /*scm_listify (gh_symbol2scm ("pos"),
                       gh_double2scm(vec.x),
                       gh_double2scm(vec.y),
                       gh_double2scm(vec.z),
                       SCM_UNDEFINED);*/
}

SCM pos2scm (int x, int y)
{
  return SCM_BOOL_F;/*scm_listify (gh_symbol2scm ("pos"),
                      gh_int2scm (x),
                      gh_int2scm (y), 
                      SCM_UNDEFINED);*/
}

void pretty_print (std::ostream& stream, SCM obj)
{
  std::cout << "pretty_print" << std::endl;
  // FIXME: ...lalala..
  gh_write (obj);
  gh_newline ();

}

bool equal_p(SCM a, SCM b)
{
  return SCM_NFALSEP(scm_equal_p(a, b));
}

SCM symbol2scm(const char* str)
{
  return scm_str2symbol(str);
}

std::string keyword2string(SCM keyword)
{
  assert(SCM_KEYWORDP(keyword));
  //puts("keyword2string: ");
  //gh_display(keyword);
  //gh_newline();
  //gh_display(scm_keyword_dash_symbol(keyword));
  //gh_newline();

  char* str = gh_symbol2newstr(scm_keyword_dash_symbol(keyword), 0);
  std::string ret = str + 1; // skip the dash
  free(str);
  return ret;
}

AList keywords2alist(SCM lst)
{
  AList alist;
  while(gh_pair_p(lst) && !gh_null_p(gh_cdr(lst)))
    {
      SCM key  = gh_car(lst);
      SCM data = gh_cadr(lst);
    
      if (scm_keyword_p(key) == SCM_BOOL_F)
        {
          std::cout << "Skipping keyword: " << key << std::endl;
        }
      else
        {
          std::string keyword = Guile::keyword2string(key);
          if (gh_string_p(data))
            {
              alist.set_string(keyword,
                               Guile::scm2string(data));
            }
          else if (gh_exact_p(data))
            {
              alist.set_int(keyword,
                            gh_scm2int(data));
            }
          else if (gh_inexact_p(data))
            {
              alist.set_float(keyword,
                              gh_scm2double(data));
            }
          else if (gh_boolean_p(data))
            {
              alist.set_bool(keyword,
                             gh_scm2bool(data));
            }
          else if (gh_list_p(data) && gh_length(data) == 2
                   && gh_exact_p(gh_car(data)) 
                   && gh_exact_p(gh_cadr(data)))
            {
              IntVector2d vec;
              vec.x = gh_scm2int(gh_car(data));
              vec.y = gh_scm2int(gh_cadr(data));
              alist.set_int_vector2d(keyword,
                                     vec);
            }
          else if (gh_symbol_p(data))
            {
              alist.set_string(keyword,
                               Guile::symbol2string(data));
            }
          else
            {
              std::cout << "Guile: Error: Couldn't handle data" << std::endl;
              gh_display(data);
              gh_newline();
            }          
        }

      lst = gh_cddr(lst);
    }
  return alist;
}

AList scm2alist(SCM lst)
{
  AList alist;
  while(!gh_null_p(lst))
    {
      SCM key  = gh_caar(lst);
      SCM data = gh_cdar(lst);

      if (gh_pair_p(data) && gh_null_p(gh_cdr(data)))
        data = gh_car(data);

      if (!gh_symbol_p(key))
        {
          std::cout << "Guile: Error: key not a symbol" << std::endl;
          gh_display(key);
          gh_newline();
        }
      else
        {
          if (gh_string_p(data))
            {
              alist.set_string(Guile::symbol2string(key), 
                               Guile::scm2string(data));
            }
          else if (gh_exact_p(data))
            {
              alist.set_int(Guile::symbol2string(key), 
                            gh_scm2int(data));
            }
          else if (gh_inexact_p(data))
            {
              alist.set_float(Guile::symbol2string(key), 
                              gh_scm2double(data));
            }
          else if (gh_boolean_p(data))
            {
              alist.set_bool(Guile::symbol2string(key), 
                             gh_scm2bool(data));
            }
          else if (gh_list_p(data) && gh_length(data) == 2
                   && gh_exact_p(gh_car(data)) 
                   && gh_exact_p(gh_cadr(data)))
            {
              IntVector2d vec;
              vec.x = gh_scm2int(gh_car(data));
              vec.y = gh_scm2int(gh_cadr(data));
              alist.set_int_vector2d(Guile::symbol2string(key), 
                                     vec);
            }
          else if (gh_symbol_p(data))
            {
              alist.set_string(Guile::symbol2string(key),
                               Guile::symbol2string(data));
            }
          else
            {
              std::cout << "Guile: Error: Couldn't handle data" << std::endl;
              gh_display(data);
              gh_newline();
            }
        }

      lst = gh_cdr(lst);
    }
  return alist;
}

std::string symbol2string(SCM symbol)
{
  char* c_str = gh_symbol2newstr(symbol, 0);
  std::string str = c_str;
  free(c_str);
  return str;
}

void enter_repl()
{
  SCM func = gh_lookup("feuerkraft:repl");
  if (func != SCM_BOOL_F)
    {
      scm_call_0(func);
    }
  else
    {
      std::cout << "### Error: feuerkraft.scm must be loaded to use the repl!" << std::endl;
    }
}

void enable_debug()
{
#if 0 // OLD Guile
  SCM_DEVAL_P = 1;
  SCM_BACKTRACE_P = 1;
  SCM_RECORD_POSITIONS_P = 1;
  SCM_RESET_DEBUG_MODE;
#else
  gh_eval_str("(debug-enable 'debug)"
              "(debug-enable 'backtrace)"
              "(read-enable  'positions)");
#endif
}

/** Disable all debugging */
void disable_debug()
{
  gh_eval_str("(debug-disable 'debug)"
              "(debug-disable 'backtrace)"
              "(read-disable  'positions)");
}

void enable_readline()
{
#ifdef WITH_STATIC_READLINE
  std::cout << "Loading readline... " << std::endl;
  scm_init_readline();
#endif

  gh_eval_str("(use-modules (ice-9 readline))"
              "(activate-readline)");
}

} // namespace Guile

/* EOF */
