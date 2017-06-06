cmake_minimum_required (VERSION 2.6)

#About the proeject
project(MasterThesis)

SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "0")
SET(VERSION_PATCH "0")

SET(VERSION "$.VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)")

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

find_package(OpenSceneGraph)
find_package(osg)
find_package(osgDB)
find_package(osgUtil)
find_package(osgViewer)

# add the binary tree to the searc pat for include files
include_directories(public/inc OpenSceneGraph/include private)

add_subdirectory(private)

add_executable(masterThesisRun main.cpp)

target_link_libraries(masterThesisRun Windshield osg osgGA osgViewer osgDB)


message("-- Creating folder resources")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/resources)
message("-- Moving axes.osgt to /bin/resources")
configure_file(resources/OpenSceneGraph-Data-3.0.0/axes.osgt ${CMAKE_CURRENT_BINARY_DIR}/bin/resources  COPYONLY)
message("-- Moving Windshield.osg to /bin/resources")
configure_file(resources/OpenSceneGraph-Data-3.0.0/Windshield.osg ${CMAKE_CURRENT_BINARY_DIR}/bin/resources  COPYONLY)
message("-- Moving glider.osg to /bin/resources")
configure_file(resources/OpenSceneGraph-Data-3.0.0/glider.osg ${CMAKE_CURRENT_BINARY_DIR}/bin/resources  COPYONLY)
message("-- Moving Script_To_Compile.sh to /bin/")
configure_file(scripts/Script_To_Compile.sh ${CMAKE_CURRENT_BINARY_DIR}/bin  COPYONLY)


