project(private)

SET(lib_src SHARED  FindTextureVisitor.cpp windshieldController.cpp windshieldImage.cpp keyboardController ) 

find_package(OpenSceneGraph)


add_library(Windshield ${lib_src})

target_link_libraries(Windshield osg osgGA osgViewer osgDB)


#add_library(windshieldController SHARED windshieldController.cpp)
#add_library(windshieldImage 	 SHARED windshieldImage.cpp)
#add_library(FindTextureVisitor   SHARED FindTextureVisitor.cpp)
#add_library(keyboardController   SHARED keyboardController.cpp)


