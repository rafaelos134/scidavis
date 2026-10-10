cmake_minimum_required( VERSION 3.16.3 )

# Qwt 5.2.3 as used by SciDAVis, ported to Qt 6.
# Vendored from https://github.com/SciDAVis/qwt5-qt5 (commit 511b07e); only the
# library sources are kept (no docs, examples or Designer plugin).
project( qwt5
  VERSION 5.2.3
  DESCRIPTION "Qt Widgets for Technical Applications (Qwt 5), ported to Qt 6"
  LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED TRUE )
set( CMAKE_CXX_EXTENSIONS OFF )

set( CMAKE_AUTOUIC OFF )
set( CMAKE_AUTORCC OFF )
set( CMAKE_AUTOMOC ON )

if( MSVC )
  # /wd4456 Silent "declaration of %1 hides %2 ..."
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /W4 /permissive- /wd4456" )
  if( CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-nonportable-include-path" )
  else()
    add_compile_options( "/MP" )
  endif()
else()
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -Wall -Wextra -pedantic" )
endif()

find_package( Qt6 6.8 COMPONENTS Core Gui Widgets PrintSupport REQUIRED )

option( QWT_PLOT "Enable all classes, that are needed to use the QwtPlot widget" ON )

option( QWT_WIDGETS "Enable all classes, that are needed to use the all other widgets \
  (sliders, dials, ...)" ON )

option( QWT_SVG_ITEM "Display SVG images on the plot canvas" ON )
if( QWT_SVG_ITEM )
  find_package( Qt6 COMPONENTS Svg REQUIRED )
endif()

add_subdirectory( src )
