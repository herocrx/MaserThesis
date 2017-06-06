project(private)

SET(lib_src FindTextureVisitor.cpp keyboardController.cpp windshieldController.cpp windshieldImage.cpp)

add_library(Windshield ${lib_src})


#add_library(FindTextureVisitor   SHARED FindTextureVisitor.cpp)
#add_library(keyboardController   SHARED keyboardController.cpp)
#add_library(windshieldController SHARED windshieldController.cpp)
#add_library(windshieldImage      SHARED windshieldImage.cpp)


