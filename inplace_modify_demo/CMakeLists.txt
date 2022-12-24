include(FetchContent)

FetchContent_Declare(
  cli11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11
  GIT_TAG        v2.2.0
)

FetchContent_MakeAvailable(cli11)

set(INPLACE_MODIFY_DEMO_SRCFILES 
"main.cpp"
"cmdlineoptions.h" 
"cmdlineoptions.cpp" 
"utilities.cpp"
"utilities.h"
)

add_executable(inplace_modify_demo ${INPLACE_MODIFY_DEMO_SRCFILES}  )

set_target_properties(inplace_modify_demo PROPERTIES CXX_STANDARD 17)
target_compile_definitions(inplace_modify_demo PRIVATE _LIBCZISTATICLIB)

target_link_libraries(inplace_modify_demo PRIVATE libCZIStatic CLI11::CLI11)

message("LIBCZI -> ${LIBCZI_INCLUDE_DIR}")

target_include_directories(inplace_modify_demo PRIVATE ${IPP_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR} ${LIBCZI_INCLUDE_DIR})

IF(UNIX)
  # seems to be problem with glibc I'd reckon -> https://stackoverflow.com/questions/51584960/stdcall-once-throws-stdsystem-error-unknown-error-1
  target_link_libraries(inplace_modify_demo  PUBLIC pthread)
ENDIF(UNIX)

IF(WIN32)
	set(Inplace_Modify_Demo_UNIX_ENVIRONMENT 0)
	set(Inplace_Modify_Demo_WIN32_ENVIRONMENT 1)
ENDIF()
IF(UNIX)
  set(Inplace_Modify_Demo_UNIX_ENVIRONMENT 1)
	set(Inplace_Modify_Demo_WIN32_ENVIRONMENT 0)
ENDIF()


configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/InplaceModifyDemo_Config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/InplaceModifyDemo_Config.h"
  )

target_include_directories(inplace_modify_demo PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# checking platform -> https://gitlab.kitware.com/cmake/community/wikis/doc/cmake/Checking-Platform
#                   -> https://stackoverflow.com/questions/9160335/os-specific-instructions-in-cmake-how-to

install(TARGETS inplace_modify_demo RUNTIME  DESTINATION bin)