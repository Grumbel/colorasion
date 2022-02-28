# Colorasion
# Copyright (C) 2015-2020 Ingo Ruhnke <grumbel@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.0)
project(colorasion VERSION 0.2.0)

set(TINYCMMC_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/external/cmake-modules/modules/")
find_package(tinycmmc CONFIG)
message(STATUS "tinycmmc module path: ${TINYCMMC_MODULE_PATH}")
list(APPEND CMAKE_MODULE_PATH ${TINYCMMC_MODULE_PATH})

include(GNUInstallDirs)
include(MaximumWarnings)
include(InstallWithWrapper)
include(ClangTidy)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GUILE REQUIRED guile-1.8 IMPORTED_TARGET)
pkg_search_module(CLANCORE REQUIRED clanCore-1.0 IMPORTED_TARGET)
pkg_search_module(CLANAPP REQUIRED clanApp-1.0 IMPORTED_TARGET)
pkg_search_module(CLANGL REQUIRED clanGL-1.0 IMPORTED_TARGET)
pkg_search_module(CLANDISPLAY REQUIRED clanDisplay-1.0 IMPORTED_TARGET)
pkg_search_module(CLANSOUND REQUIRED clanSound-1.0 IMPORTED_TARGET)

file(GLOB COLORASION_SOURCES src/*.cxx src/input/*.cxx)

add_executable(colorasion ${COLORASION_SOURCES})
target_include_directories(colorasion PRIVATE src/)
target_link_libraries(colorasion PUBLIC
  PkgConfig::CLANCORE
  PkgConfig::CLANAPP
  PkgConfig::CLANGL
  PkgConfig::CLANDISPLAY
  PkgConfig::CLANGL
  PkgConfig::GUILE
  Threads::Threads)

install_with_wrapper(TARGETS colorasion)
install(DIRECTORY data/ DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}
  PATTERN "*~" EXCLUDE)

# EOF #
