#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "auto_thread::auto_thread" for configuration "MinSizeRel"
set_property(TARGET auto_thread::auto_thread APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(auto_thread::auto_thread PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/auto_thread.lib"
  )

list(APPEND _cmake_import_check_targets auto_thread::auto_thread )
list(APPEND _cmake_import_check_files_for_auto_thread::auto_thread "${_IMPORT_PREFIX}/lib/auto_thread.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
