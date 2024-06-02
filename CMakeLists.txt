cmake_minimum_required(VERSION 3.27)
project(BlackFilmDatabase_GUI_2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)
set(CMAKE_AUTOUIC OFF)

set(Qt6_DIR "C:/Qt/6.6.2/mingw_64/lib/cmake/Qt6")
set(CMAKE_TOOLCHAIN_FILE "C:/Qt/6.6.2/mingw_64/lib/cmake/Qt6/qt.toolchain.cmake")
set(CMAKE_PREFIX_PATH "C:/Qt/6.6.2/mingw_64/lib/cmake/Qt6")
set(Qt6GuiTools_DIR "C:/Qt/6.6.2/mingw_64/lib/cmake/Qt6GuiTools")

find_package(Qt6 REQUIRED COMPONENTS
        Core
        Widgets
        Multimedia
        MultimediaWidgets
        QuickControls2
)

# Add your source files
set(SOURCES
        main.cpp
        SearchPage.cpp
        ResultsPage.cpp
        MainGraphicsView.cpp
)

# Tell CMake to generate the MOC files for your source files directly
qt6_wrap_cpp(MOC_SOURCES ${SOURCES})

add_executable(BlackFilmDatabase_GUI_2 ${SOURCES} SearchPage.h ResultsPage.h MainGraphicsView.h)

add_subdirectory(libpqxx-master)

target_link_libraries(BlackFilmDatabase_GUI_2
        Qt6::Core
        Qt6::Widgets
        Qt6::Multimedia
        Qt6::MultimediaWidgets
        Qt6::QuickControls2
        pqxx
)