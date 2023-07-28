cmake_minimum_required(VERSION 3.25)
project(NodeEngine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/Qt/Qt/6.4.3/mingw_64/bin")
set(assimp_DIR D:/VSCode_codes/lib/assimp/lib/cmake/assimp-5.2)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)

set(EXE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(DLL_OUTPUT_PATH "${CMAKE_BINARY_DIR}/plugins")

set(RESOURCE_FILES
        resource/icons/icons.qrc
        resource/images/images.qrc
        resource/styles/styles.qrc
        )
qt_add_resources(QT_RESOURCES ${RESOURCE_FILES})

set(PROJECT_SOURCES
        src/main.cpp
        src/NE_Editor.cpp
        src/NE_Editor.h
        src/pch.h
        src/config.cpp
        src/config.h
        src/NE_Title.cpp
        src/NE_Title.h
        src/NE_View.cpp
        src/NE_View.h
        src/NE_Scene.cpp
        src/NE_Scene.h
        src/NE_Node_Basic.cpp
        src/NE_Node_Basic.h
        src/NE_Port_Basic.cpp
        src/NE_Port_Basic.h
        src/NE_Line_Basic.cpp
        src/NE_Line_Basic.h
        src/nodes/LogicLibrary.cpp
        src/nodes/LogicLibrary.h
        src/nodes/BasicMathLibrary.cpp
        src/nodes/BasicMathLibrary.h
        src/nodes/interfaces/NodeLibraryPluginInterface.h
        src/nodes/interfaces/NodeLibraryPlugin.cpp
        src/nodes/interfaces/NodeLibraryPlugin.h src/NE_Widgets.cpp src/NE_Widgets.h)

set(PRECOMPILED_HEADER pch.h)
add_library(nativelib SHARED ${PROJECT_SOURCES})
set_target_properties(nativelib PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${DLL_OUTPUT_PATH}"
        RUNTIME_OUTPUT_DIRECTORY "${DLL_OUTPUT_PATH}"
        ARCHIVE_OUTPUT_DIRECTORY ""
        PREFIX "")
target_link_libraries(nativelib
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

add_executable(NodeEngine ${PROJECT_SOURCES} ${QT_RESOURCES})
set_target_properties(NodeEngine PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${EXE_OUTPUT_PATH}"
        RUNTIME_OUTPUT_DIRECTORY "${EXE_OUTPUT_PATH}"
        ARCHIVE_OUTPUT_DIRECTORY ""
        PREFIX "")

target_link_libraries(NodeEngine
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
