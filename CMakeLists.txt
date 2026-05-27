cmake_minimum_required(VERSION 3.16)

project(IChingDiviner VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#flatpak
option(FLATPAK_BUILD "Build for Flathub/Flatpak" OFF)
if(FLATPAK_BUILD)
    add_compile_definitions(FLATPAK_BUILD)
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets Network Svg Multimedia)
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/decks DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(true)
    qt_add_executable(IChingDiviner
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        iching.h iching.cpp
        resources.qrc
        constants.cpp constants.h
        aimanager.cpp aimanager.h modelselectordialog.cpp modelselectordialog.h
        model.h
        donationdialog.cpp donationdialog.h helpmenudialog.cpp helpmenudialog.h
        journalcalendar.cpp journalcalendar.h journaldialog.cpp journaldialog.h journalmanager.cpp journalmanager.h socialshare.cpp socialshare.h socialsharedialog.cpp socialsharedialog.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET IChingDiviner APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(IChingDiviner SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(IChingDiviner
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(IChingDiviner PRIVATE Qt6::Widgets Qt6::Network Qt6::Svg Qt6::Multimedia)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(true)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.IChingDiviner)
endif()
set_target_properties(IChingDiviner PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS IChingDiviner
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(FLATPAK_BUILD)
    # Install desktop file
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/io.github.alamahant.IChingDiviner.desktop"
            DESTINATION "share/applications")

    # Install metainfo file
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/io.github.alamahant.IChingDiviner.metainfo.xml"
            DESTINATION "share/metainfo")

    # Install app icon from root directory
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/io.github.alamahant.IChingDiviner.png"
            DESTINATION "share/icons/hicolor/512x512/apps"
            RENAME "io.github.alamahant.IChingDiviner.png")

    # Install icons from favicon directory
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/files/android-chrome-192x192.png"
            DESTINATION "share/icons/hicolor/192x192/apps"
            RENAME "io.github.alamahant.IChingDiviner.png")

    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/files/favicon-16x16.png"
            DESTINATION "share/icons/hicolor/16x16/apps"
            RENAME "io.github.alamahant.IChingDiviner.png")

    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/files/favicon-32x32.png"
            DESTINATION "share/icons/hicolor/32x32/apps"
            RENAME "io.github.alamahant.IChingDiviner.png")

    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/files/apple-touch-icon.png"
            DESTINATION "share/icons/hicolor/180x180/apps"
            RENAME "io.github.alamahant.IChingDiviner.png")

        install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/fonts/Noto_Serif_TC/static/NotoSerifTC-Black.ttf"
                   DESTINATION "share/${PROJECT_NAME}/fonts"
                   RENAME "NotoSerifTC-Black.ttf")
else()
           add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
               COMMAND ${CMAKE_COMMAND} -E copy
                   "${CMAKE_CURRENT_SOURCE_DIR}/fonts/Noto_Serif_TC/static/NotoSerifTC-Black.ttf"
                   "$<TARGET_FILE_DIR:${PROJECT_NAME}>/NotoSerifTC-Black.ttf"
               COMMENT "Copying font to binary directory")

endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(IChingDiviner)
endif()
