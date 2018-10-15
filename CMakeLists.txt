# aquí hay una config más complicada y completa para compilar con Qt
# https://github.com/nholthaus/cmake-qt-project/blob/master/CMakeLists.txt
# otra muy buena y larga es la de Clementine

cmake_minimum_required(VERSION 3.4)

project(libroskop)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# para que genere una compilation database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#set (CMAKE_CXX_FLAGS "-DQT_WIDGETS_LIB -fno-plt -O2")

find_package(Qt4 REQUIRED QtSql)

include_directories(objs)

# Metemos en una variable los nombres de los ficheros 
set(fuentes
    mainwindow.ui
    mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/objs/proxynombres.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/dlggestionlibros.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/dlggestionlibros.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/dlgseleccionargeneral.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/dlgseleccionargeneral.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/nuevacategoria.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/nuevacategoria.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/nuevoautor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/nuevoautor.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/nuevolibroentrada.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/nuevolibroentrada.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/objs/variados.h
)

# aquí se puede poner:
add_executable(${PROJECT_NAME} "main.cpp" ${fuentes} icons.qrc)

# En el caso de programa de consola usamos esto: 
target_link_libraries(${PROJECT_NAME} Qt4::QtGui Qt4::QtSql)
