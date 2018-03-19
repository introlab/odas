#Scan for headers and add them for installation
file(GLOB_RECURSE ODAS_ALL_INCLUDES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)

message(STATUS "HEADER FILES: ${ODAS_ALL_INCLUDES}")

add_custom_target(odas_headers SOURCES ${ODAS_ALL_INCLUDES})

install(FILES ${ODAS_ALL_INCLUDES} DESTINATION include)
