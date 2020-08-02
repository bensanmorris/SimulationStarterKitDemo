cmake_minimum_required(VERSION 3.8)

set (FIREFLY_GL_MAJOR_VERSION 3 CACHE STRING "The OpenGL major version")
set (FIREFLY_GL_MINOR_VERSION 3 CACHE STRING "The OpenGL minor version")
add_definitions (-DFIREFLY_GL_MAJOR_VERSION=${FIREFLY_GL_MAJOR_VERSION} -DFIREFLY_GL_MINOR_VERSION=${FIREFLY_GL_MINOR_VERSION})

if(APPLE)
    find_package(firefly CONFIG REQUIRED PATHS "C:/Program Files/FireflyTech/FireflySceneComposer/bin/../CMake" NO_DEFAULT_PATH)
    set(CMAKE_MODULE_PATH ${firefly_DIR}/Modules;${CMAKE_MODULE_PATH})
    set(THIRDPARTY_ROOT ${firefly_DIR}/../ThirdParty)
    set(IMGUI_SRC_ROOT ${THIRDPARTY_ROOT}/include/imgui)
    set(SDK_ROOT ${firefly_DIR}/..)
    set(RESOURCES_ROOT ${firefly_DIR}/../../Frameworks)
    set(LIBS_DIR ${firefly_DIR}/../../Frameworks)
    set(SHADERS_DIR ${firefly_DIR}/../../Frameworks/Shaders)
    option(BUILD_WITH_CODESIGNING "Build with code signing" ON)
    if(BUILD_WITH_CODESIGNING)
        set(CMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM   "None" CACHE STRING "")
        set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Sign to run locally" CACHE STRING "")
        set(CMAKE_XCODE_ATTRIBUTE_OTHER_CODE_SIGNING_FLAGS "--deep" CACHE STRING "")
    endif()
    if(IOS)
        set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer" CACHE STRING "")
        message(STATUS "Building for iOS")
    else()
        set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Mac Developer" CACHE STRING "")
        set(CMAKE_OSX_SYSROOT                        "macosx10.15"   CACHE STRING "SDK version to build against")
        set(CMAKE_OSX_DEPLOYMENT_TARGET              "10.15"         CACHE STRING "Minimum version of target machine")
        set(CMAKE_OSX_ARCHITECTURES                  "x86_64"        CACHE STRING "Supported target architecture")
        set(CPACK_BUNDLE_NAME ${EDITOR_NAME})
        set(CPACK_BUNDLE_APPLE_CERT_APP              "Developer ID Application: None" CACHE STRING "")
    endif()
elseif(WIN32)
    find_package(firefly CONFIG REQUIRED PATHS "C:/Program Files/FireflyTech/FireflySceneComposer/bin/../lib/CMake" NO_DEFAULT_PATH)
    set(CMAKE_MODULE_PATH "C:/Program Files/FireflyTech/FireflySceneComposer/bin/../lib/CMake/Modules";${CMAKE_MODULE_PATH})
    set(THIRDPARTY_ROOT ${firefly_DIR}/../../ThirdParty)
    set(IMGUI_SRC_ROOT ${THIRDPARTY_ROOT}/include/imgui)
    set(SDK_ROOT ${firefly_DIR}/../..)
    set(RESOURCES_ROOT ${firefly_DIR}/../../bin)
    set(LIBS_DIR ${firefly_DIR}/../../bin)
    set(SHADERS_DIR ${firefly_DIR}/../../bin/Shaders)
else()
    find_package(firefly CONFIG REQUIRED PATHS "${CMAKE_SOURCE_DIR}/lib/CMake" NO_DEFAULT_PATH)
    set(THIRDPARTY_ROOT ${CMAKE_SOURCE_DIR}/ThirdParty)
    set(IMGUI_SRC_ROOT  ${THIRDPARTY_ROOT}/include/imgui)
    set(SDK_ROOT        ${CMAKE_SOURCE_DIR})
    set(RESOURCES_ROOT  ${CMAKE_SOURCE_DIR}/lib)
    set(LIBS_DIR        ${CMAKE_SOURCE_DIR}/bin)
    set(SHADERS_DIR 	${CMAKE_SOURCE_DIR}/bin/shaders)
    list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/lib/CMake)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/lib/CMake/Modules)
endif()
include(FireflyCommon)
FIND_PACKAGE(OpenGL REQUIRED)
find_package(SDL2)
set(CMAKE_CXX_STANDARD 11)

include_directories(${SDK_ROOT}/include/core/include
                    ${SDK_ROOT}/include/renderers
					${SDK_ROOT}/include/renderers/opengl/glad/include
                    ${SDK_ROOT}/include/plugins
                    ${SDK_ROOT}/include/plugins/Navigation
                    ${SDK_ROOT}/include/loaders
                    ${SDK_ROOT}/ThirdParty/include/
                    ${SDK_ROOT}/ThirdParty/include/imgui
                    ${SDK_ROOT}/ThirdParty/include/imgui/examples
                    ${OPENGL_INCLUDE_DIRS}
                    ${SDL2_INCLUDE_DIR})

set(PROJECT_NAME Game1)

SET(MAIN_SOURCES
    prototype.cpp
    ${SDK_ROOT}/include/renderers/opengl/glad/src/glad.c
)

SET(MAIN_HEADERS
    GLWindow.h
    scene.h
)

SOURCE_GROUP(Main FILES ${MAIN_SOURCES} ${MAIN_HEADERS})

SET(GAME_SOURCES
    GLWindow.cpp
    SDLHelper.cpp
    gamescene.cpp
    savedgames.cpp
)

SET(GAME_HEADERS
    gamescene.h
    savedgames.h
)
SOURCE_GROUP(Game FILES ${GAME_SOURCES} ${GAME_HEADERS})

SET(GUI_SOURCES
    guiscene.cpp
)
SET(GUI_HEADERS
    guiscene.h
)
SOURCE_GROUP(Gui FILES ${GUI_SOURCES} ${GUI_HEADERS})

SET(IMGUI_SOURCES
    ${IMGUI_SRC_ROOT}/imgui.cpp
    ${IMGUI_SRC_ROOT}/imgui.h
    ${IMGUI_SRC_ROOT}/imgui_demo.cpp
    ${IMGUI_SRC_ROOT}/imgui_draw.cpp
    ${IMGUI_SRC_ROOT}/imgui_widgets.cpp
    ${IMGUI_SRC_ROOT}/imgui_internal.h
    ${IMGUI_SRC_ROOT}/imconfig.h
    ${IMGUI_SRC_ROOT}/imstb_rectpack.h
    ${IMGUI_SRC_ROOT}/imstb_textedit.h
    ${IMGUI_SRC_ROOT}/imstb_truetype.h
    ${IMGUI_SRC_ROOT}/examples/imgui_impl_sdl.cpp
    ${IMGUI_SRC_ROOT}/examples/imgui_impl_sdl.h
    ${IMGUI_SRC_ROOT}/examples/imgui_impl_opengl3.cpp
    ${IMGUI_SRC_ROOT}/examples/imgui_impl_opengl3.h
)
SOURCE_GROUP(3rdParty\\imgui FILES ${IMGUI_SOURCES})

set(SOURCES
   ${MAIN_SOURCES}
   ${MAIN_HEADERS}
   ${GAME_SOURCES}
   ${GAME_HEADERS}
   ${GUI_SOURCES}
   ${GUI_HEADERS}
   ${IMGUI_SOURCES}
)
   
if(APPLE)
    add_executable(${PROJECT_NAME}
                   MACOSX_BUNDLE
                   ${SOURCES})
else()
    add_executable(${PROJECT_NAME}
                   ${SOURCES})
endif()

set_target_properties (${PROJECT_NAME}
                       PROPERTIES
                       VERSION ${FIREFLY_VERSION}
                       SOVERSION ${FIREFLY_SOVERSION})

add_definitions (-DNOMINMAX -DIMGUI_IMPL_OPENGL_LOADER_GLAD)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} firefly::firefly firefly::ext_Navigation firefly::ext_Physics)
IF(WIN32)
	target_link_libraries(${PROJECT_NAME} winmm.lib version.lib imm32.lib)
ENDIF()
setup_linker_flags(CMAKE_EXE_LINKER_FLAGS)
IF(APPLE)    
    set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "@executable_path")
ENDIF()

# shaders
if(APPLE)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${SHADERS_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>/../Frameworks/Shaders)
else()
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${SHADERS_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders)
endif()

# resources
if(APPLE)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${RESOURCES_ROOT}/fonts/Default.TTF $<TARGET_FILE_DIR:${PROJECT_NAME}>/../Frameworks/fonts/Default.TTF)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${RESOURCES_ROOT}/light.png $<TARGET_FILE_DIR:${PROJECT_NAME}>/../Frameworks/light.png)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${RESOURCES_ROOT}/default_texture.png $<TARGET_FILE_DIR:${PROJECT_NAME}>/../Frameworks/default_texture.png)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/MyScene.msf $<TARGET_FILE_DIR:${PROJECT_NAME}>/../Frameworks/MyScene.msf)
else()
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${RESOURCES_ROOT}/fonts/Default.TTF $<TARGET_FILE_DIR:${PROJECT_NAME}>/fonts/Default.TTF)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${RESOURCES_ROOT}/light.png $<TARGET_FILE_DIR:${PROJECT_NAME}>/light.png)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${RESOURCES_ROOT}/default_texture.png $<TARGET_FILE_DIR:${PROJECT_NAME}>/default_texture.png)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/MyScene.msf $<TARGET_FILE_DIR:${PROJECT_NAME}>/MyScene.msf)
endif()

# dynamic libs
get_property(FIREFLY_PLUGINS_SET GLOBAL PROPERTY FIREFLY_PLUGINS SET)
if(${FIREFLY_PLUGINS_SET})
    get_property(FIREFLY_PLUGINS GLOBAL PROPERTY FIREFLY_PLUGINS)
    add_dependencies(${PROJECT_NAME} ${FIREFLY_PLUGINS})
endif()
if(APPLE)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LIBS_DIR}/libext_*.dylib $<TARGET_FILE_DIR:${PROJECT_NAME}>/../Frameworks)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LIBS_DIR}/libfirefly*.dylib $<TARGET_FILE_DIR:${PROJECT_NAME}>/../Frameworks)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND rm -f $<TARGET_FILE_DIR:${PROJECT_NAME}>/../Frameworks/libfireflyeditorplugin_*.dylib)
elseif(WIN32)	
    file(GLOB ENGINE_SUPPORT ${LIBS_DIR}/ext_*.dll ${LIBS_DIR}/firefly*.dll)
    if(ENGINE_SUPPORT)
        message("ENGINE_SUPPORT = ${ENGINE_SUPPORT}")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${ENGINE_SUPPORT} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    endif()	
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LIBS_DIR}/SDL2.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LIBS_DIR}/entityx.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LIBS_DIR}/lua.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

# rpath
if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "@executable_path/../Frameworks/")
endif()

