cmake_minimum_required(VERSION 2.6)
project(demo)

INCLUDE(FindPkgConfig)

IF(CMAKE_COMPILER_IS_GNUCC)
SET(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -Wall -std=c++0x -DBUILD_SHARED_LIBS=OFF")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

# definicoes da remoteAPI para CPP
add_definitions(-DNON_MATLAB_PARSING) #informa que nao vai usar matlab
add_definitions(-DMAX_EXT_API_CONNECTIONS=255) #num_maximo de conexoes

set(SOURCES
    remoteApi/extApi.c
    #remoteApi/extApiCustom.c
    remoteApi/extApiPlatform.c
)

set(LIB 
    libarmc_simulator.so
)
 
set(HEADERS
    remoteApi/extApi.h
    #remoteApi/extApiCustom.h
    remoteApi/extApiInternal.h
    remoteApi/extApiPlatform.h
    remoteApi/v_repConst.h
    remoteApi/v_repLib.h
    remoteApi/armc_simulator.h
)

include_directories("include/")
include_directories("remoteApi/")

find_package (Threads) #acompanha bibliotecas padrão para c/c++

#Uma das maneiras de se encontrar uma biblioteca usando o cmake é da seguinte maneira:
find_library(ARMC
	NAMES ${LIB} PATHS ${CMAKE_HOME_DIRECTORY}/remoteApi/
)

add_executable(demo
               demo.c
               ${SOURCES}
	       ${HEADERS})
	       
#target_link_libraries(demo ${CMAKE_THREAD_LIBS_INIT} ${LIB} "-L${CMAKE_HOME_DIRECTORY}/remoteApi/")
target_link_libraries(demo ${CMAKE_THREAD_LIBS_INIT} ${ARMC})


install(TARGETS demo RUNTIME DESTINATION bin)
