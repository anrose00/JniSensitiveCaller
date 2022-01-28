cmake_minimum_required(VERSION 3.10)

# set the project name
project(JniTest)

#define the list of source modules C
set(SOURCES_C 
   src/ResourceBundleJNI.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES_C})
if (MSVC)
   target_link_options(${PROJECT_NAME}  PRIVATE "/SUBSYSTEM:CONSOLE")
   
   if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
      target_compile_definitions(${PROJECT_NAME} PRIVATE _DEBUG)
      target_compile_options(${PROJECT_NAME} PRIVATE /MTd)   # Multi threaded debug
   else()
      STRING (REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}") # remove basic RT checks
      target_compile_options(${PROJECT_NAME} PRIVATE /MT)    # Multi threaded
      target_compile_options(${PROJECT_NAME} PRIVATE /GS-)   # disable buffer security checks
      # next two lines generate debug info for a release build
      # target_compile_options(${PROJECT_NAME} PRIVATE /Zi)    # generate debug info
      # target_link_options(${PROJECT_NAME} PRIVATE "/DEBUG")
   endif ()
endif ()
target_link_libraries(${PROJECT_NAME} PRIVATE vcruntime.lib kernel32 jvm.lib)
target_link_directories(${PROJECT_NAME} PRIVATE "D:/Java/jdk17/lib")
target_include_directories(${PROJECT_NAME} PRIVATE "D:/Java/jdk17/include")
target_include_directories(${PROJECT_NAME} PRIVATE "D:/Java/jdk17/include/win32")