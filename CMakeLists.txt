project(libfdvcpp)
cmake_minimum_required(VERSION 2.8)
enable_language(CXX)

add_definitions(-std=c++14 -Wall -Wextra -Wconversion)

include_directories(.)

set(LIB_NAME fdvcpp)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(SRC_LIST

	Core/Object.abstract.cpp
	Core/Object-MemManager.class.cpp
	Core/AMain.abstract.cpp
	Core/Time.class.cpp
#	Core/Exception.class.cpp

	IO/Logger.class.cpp
#	IO/Term.class.cpp
	IO/Color.class.cpp
	IO/OutputStream.class.cpp

	Misc/BmpImg.class.cpp
)

set(INC_LIST

	Core/macro.hpp

	Core/Object.abstract.hpp
	Core/Object-MemManager.class.hpp
	Core/AMain.abstract.hpp
	Core/Time.class.hpp
	Core/make_array.template.hpp
#	Core/Exception.class.hpp

	IO/Logger.class.hpp
#	IO/Term.class.hpp
	IO/Color.class.hpp
	IO/OutputStream.class.hpp

	Misc/BmpImg.class.hpp

)

aux_source_directory(. SRC_LIST)
add_library(${LIB_NAME} ${SRC_LIST} ${INC_LIST})
