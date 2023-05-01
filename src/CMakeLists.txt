set(SOURCE_FILES rpn.cpp rpn.h visualization.cpp visualization.h)
add_executable(rpn ${SOURCE_FILES})

add_library(rpn_lib SHARED ${SOURCE_FILES})

target_compile_options(rpn PRIVATE -Wall -Werror)
