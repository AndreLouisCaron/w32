# Library configuration file used by dependent projects
# via find_package() built-in directive in "config" mode.

if(NOT DEFINED w32_FOUND)

  # Locate library headers.
  find_path(w32_include_dir
    NAMES w32.hpp
    PATHS ${w32_DIR}/code
  )

  # Export library targets.
  set(${PROJECT_NAME}_libraries
    w32
    CACHE INTERNAL "w32 library" FORCE
  )

  # Usual "required" et. al. directive logic.
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(
    w32 DEFAULT_MSG
    w32_include_dir
    ${PROJECT_NAME}_libraries
  )

  # Register library targets when found as part of a dependent project.
  # Since this project uses a find_package() directive to include this
  # file, don't recurse back into the CMakeLists file.
  if(NOT ${PROJECT_NAME} STREQUAL w32++)
    add_subdirectory(
      ${w32_DIR}
      ${CMAKE_CURRENT_BINARY_DIR}/w32
    )
  endif()
endif()
