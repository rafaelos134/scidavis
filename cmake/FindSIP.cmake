# FindSIP
# -------

# Result Variables
# ^^^^^^^^^^^^^^^^

# This will define the following variables:

# ``SIP_FOUND``
#   True if the system has the SIP executable.
# ``SIP_EXECUTABLE``
#   SIP Executable.
# ``SIP_VERSION``
#   The version of the SIP executable.

# Cache Variables
# ^^^^^^^^^^^^^^^

# The following cache variables may also be set:

# ``SIP_DIR``
#   The directory containing SIP_EXECUTABLE.

if( SIP_DIR )
  find_program( SIP_EXECUTABLE
    NAMES sip-build
    PATHS ${SIP_DIR}
    )
else()
  # prefer the sip-build installed next to the selected Python (e.g. in a virtual environment)
  get_filename_component( _Python3_BIN_DIR "${Python3_EXECUTABLE}" DIRECTORY )
  find_program( SIP_EXECUTABLE
    NAMES sip-build
    HINTS ${_Python3_BIN_DIR}
    )
  get_filename_component( SIP_DIR ${SIP_EXECUTABLE} DIRECTORY CACHE )
endif()

execute_process(
  COMMAND ${SIP_EXECUTABLE} -V
  OUTPUT_VARIABLE SIP_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SIP
  FOUND_VAR SIP_FOUND
  REQUIRED_VARS SIP_EXECUTABLE
  VERSION_VAR SIP_VERSION
  )

mark_as_advanced( SIP_DIR )
