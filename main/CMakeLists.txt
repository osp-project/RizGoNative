file(GLOB MAIN_SRCS "./*.cpp" "./*.c")
message(NOTICE "${MAIN_SRCS}")
idf_component_register(SRCS ${MAIN_SRCS} INCLUDE_DIRS ".")