cmake_minimum_required(VERSION 3.27)
project(BlackFilmDatabase_GUI_2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
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

set(SOURCES
        main.cpp
        MainGraphicsView.cpp
        SearchPage.cpp
        ResultsPage.cpp
        MovieTableModel.cpp
        MovieTableModel.h
        CustomSortFilterProxyModel.cpp
        CustomSortFilterProxyModel.h
        FilmHighlightPage.cpp
        FilmHighlightPage.h
)

set(HEADERS
        MainGraphicsView.h
        SearchPage.h
        ResultsPage.h
)

# This line processes the Q_OBJECT macro in the header files
qt6_wrap_cpp(MOC_SOURCES ${HEADERS})

add_executable(BlackFilmDatabase_GUI_2 ${SOURCES} ${MOC_SOURCES})

add_subdirectory(libpqxx-master)

target_link_libraries(BlackFilmDatabase_GUI_2
        Qt6::Core
        Qt6::Widgets
        Qt6::Multimedia
        Qt6::MultimediaWidgets
        Qt6::QuickControls2
        pqxx
)