cmake_minimum_required(VERSION 3.16)
project(Roundabout VERSION 0.1.0)

# abilita il supporto per i test, tra cui l'opzione BUILD_TESTING usata sotto
include(CTest)
option(GRAPHIC "Enable the graphics" ON)

# richiedi l'uso di C++17, senza estensioni non-standard offerte dal compilatore usato 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# compila sempre con i warning abilitati
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

# abilita l'address sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address -fno-omit-frame-pointer")

# richiedi il componente graphics della libreria SFML, versione 2.5
#   le dipendenze vengono identificate automaticamente
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

# aggiungi l'eseguibile, da produrre a partire dai sorgenti indicati
#  notare l'assenza degli header file, che pero' possono essere indicati
if (GRAPHIC)
    add_executable(Roundabout.out main.cpp functionsclasses.cpp)
    target_link_libraries(Roundabout.out PRIVATE sfml-graphics)
else()
    add_executable(Roundaboutng.out mainng.cpp functionsclasses.cpp)
endif(GRAPHIC)
