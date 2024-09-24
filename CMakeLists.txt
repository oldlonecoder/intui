cmake_minimum_required(VERSION 3.13..3.29 FATAL_ERROR)
project(intui VERSION 0.1.0 LANGUAGES CXX)
set(BaseTarget ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

message("Entering ${PROJECT_NAME} project configuration:")
include(GNUInstallDirs)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${BaseTarget} STATIC  #SHARED
            include/${BaseTarget}/exports
            include/${BaseTarget}/support/string.h cc/support/string.cc
            include/${BaseTarget}/support/colors.h cc/support/colors.cc
            include/${BaseTarget}/support/geometry.h cc/support/geometry.cc
            include/${BaseTarget}/support/cadres.h cc/support/cadres.cc
            include/${BaseTarget}/support/ansi_32.h cc/support/ansi_32.cc
            include/${BaseTarget}/support/glyphes.h cc/support/glyphes.cc
            include/${BaseTarget}/support/sscan.h cc/support/sscan.cc
            include/${BaseTarget}/support/signals.h
            include/${BaseTarget}/support/cmdargs.h cc/support/cmdargs.cc            
            include/${BaseTarget}/support/object.h cc/support/object.cc
            include/${BaseTarget}/book/book.h cc/book/book.cc
            include/${BaseTarget}/lexer/lexer_types.h cc/lexer/lexer_types.cc
            include/${BaseTarget}/lexer/token_data.h cc/lexer/token_data.cc
            include/${BaseTarget}/lexer/tokens_table.h cc/lexer/tokens_table.cc
            include/${BaseTarget}/lexer/lexer.h cc/lexer/lexer.cc
            include/${BaseTarget}/est/alu.h cc/est/alu.cc
            include/${BaseTarget}/est/node.h cc/est/node.cc
            include/${BaseTarget}/est/variable.h cc/est/variable.cc
            include/${BaseTarget}/est/bloc.h cc/est/bloc.cc
            include/${BaseTarget}/est/expression.h cc/est/expression.cc
            include/${BaseTarget}/globals.h cc/intui/globals.cc
            include/${BaseTarget}/io/linux/terminal.h cc/intui/io/linux/terminal.cc
            include/${BaseTarget}/elements/element.h  cc/intui/elements/element.cc
            include/${BaseTarget}/events.h             cc/intui/events.cc
            include/${BaseTarget}/application.h        cc/intui/application.cc
            
)

target_compile_definitions(${BaseTarget} PUBLIC "${BaseTarget}_DEBUG=$<CONFIG:Debug>")
include(GenerateExportHeader)
generate_export_header(${BaseTarget} EXPORT_FILE_NAME ${${BaseTarget}_export})

IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    )
ENDIF ()

target_include_directories(${BaseTarget} PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           $<INSTALL_INTERFACE:include>
)

target_link_libraries(${BaseTarget} ${CMAKE_DL_LIBS}) # and other system dependencies...








install(DIRECTORY
        include/
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
)


add_custom_target("uninstall" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall"
    POST_BUILD
    COMMENT "Uninstall files with install_manifest.txt"
    COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in
    install_manifest.txt to be uninstalled!
)
# Enable packaging
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_NAME ${BaseTarget})
set(CPACK_GENERATOR "TGZ")

# Include CPack
include(CPack)

include(exec_test.cmake)
