//  $Id: string_converter.hxx,v 1.3 2003/06/03 14:11:22 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_STRING_CONVERTER_HXX
#define HEADER_PINGUS_STRING_CONVERTER_HXX

#include <string>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <sstream>

template <class T>
std::string to_string (const T& any)
{
  std::ostringstream oss;
  oss << any ;
  return oss.str();
}

/** Convert the contents in string \a rep to type \a T, if conversion
    fails false is returned and the value of \a x is unchanged, if
    true is returned the conversation was successfull. */
template <class T>
bool from_string(const std::string& rep, T& x)
{
 // this is necessary so that if "x" is not modified if the conversion fails
  T temp;
  std::istringstream iss(rep);
  iss >> temp;

  /*if (iss.fail())
    throw std::invalid_argument
    ("Exception: 'failed to extract type T from rep' " __FILE__ ": " + rep);*/

  if (iss.fail())
    {
      return false;
    }
  else
    {
      x = temp;
      return true;
    }
}

std::string string_upcase (const std::string&);
std::string string_downcase (const std::string&);

#endif

/* EOF */
