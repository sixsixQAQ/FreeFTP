set(NAME curl)
set(${NAME}_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(${NAME}_LIBRARY ${CMAKE_CURRENT_LIST_DIR}/lib/libcurl.lib)
set(${NAME}_FOUND TRUE)

if(${NAME}_INCLUDE_DIR AND ${NAME}_LIBRARY)
	set(${NAME}_FOUND TRUE)
endif()

if(${NAME}_FOUND)
	if(NOT ${NAME}_FIND_QUIETLY)
		message(STATUS "Found curl: ${${NAME}_LIBRARY}")
	endif()
else()
	if(${NAME}_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find ${NAME}")
	endif()
endif()

add_library(${NAME} SHARED IMPORTED)
set_target_properties(${NAME} PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${${NAME}_INCLUDE_DIR}"
	IMPORTED_IMPLIB "${${NAME}_LIBRARY}"
	IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/bin/libcurl.dll"
)


mark_as_advanced(${NAME}_INCLUDE_DIR ${NAME}_LIBRARY)