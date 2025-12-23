
if (NOT DEFINED AUTO_PID_DIR)
    set(AUTO_PID_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/AutoTunePID")
endif()
if (NOT DEFINED AUTO_PID_CONF_DIR)
    set(AUTO_PID_CONF_DIR "${CMAKE_CURRENT_LIST_DIR}/port/AutoTunePID")
endif()


file(GLOB_RECURSE SOURCES ${AUTO_PID_DIR}/src/*.cpp)
file(GLOB_RECURSE PORTS ${AUTO_PID_CONF_DIR}/*.cpp)


add_library(autopid STATIC)

target_sources(autopid PUBLIC
	${SOURCES}
	${PORTS}
	)


# Add include directory
target_include_directories(autopid PUBLIC 
   ${AUTO_PID_DIR}/src/
   ${AUTO_PID_CONF_DIR}/
)

# Add the standard library to the build
target_link_libraries(autopid PUBLIC 
	pico_stdlib
	)

