
set( CMAKE_AUTOMOC OFF )
set( CMAKE_AUTOUIC OFF )
set( CMAKE_AUTORCC OFF )

# minigzip: mini gzip implementation
add_library( minigzip STATIC "minigzip/minigzip.c" )
target_link_libraries( minigzip ZLIB::ZLIB )

# Qwt 5 (ported to Qt 6) and QwtPlot3D are always built from the bundled
# sources: distribution packages of these libraries are built against Qt 5.

# Qwt5
set( QWT_SVG_ITEM ON CACHE BOOL "" FORCE )
add_subdirectory( qwt5 )

# QwtPlot3D
add_subdirectory( qwtplot3d )

# liborigin
if( ORIGIN_IMPORT )
  find_package( PkgConfig )
  if( PkgConfig_FOUND )
    pkg_search_module( LIBORIGIN liborigin>=3.0.0 IMPORTED_TARGET GLOBAL )
  endif()
  if( NOT PkgConfig_FOUND OR NOT LIBORIGIN_FOUND )
    message( STATUS "liborigin: using own code" )
    add_subdirectory( liborigin )
  endif()
else()
  message( STATUS "liborigin not enabled" )
endif()
