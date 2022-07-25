#
# Setup tasking system build configuration
#

# Determine the best default option for tasking system backend
if(NOT DEFINED CUBBYFLOW_TASKING_SYSTEM)
	find_package(TBB QUIET)
	if(TBB_FOUND)
	    set(TASKING_DEFAULT TBB)
	else()
		find_package(OpenMP QUIET)
		if(OpenMP_FOUND)
		    set(TASKING_DEFAULT OpenMP)
		else()
			find_package(HPX QUIET)
			if(HPX_FOUND)
				set(TASKING_DEFAULT HPX)
			else()
			set(TASKING_DEFAULT CPP11Thread)
			endif()
		endif()
	endif()
else()
	set(TASKING_DEFAULT ${CUBBYFLOW_TASKING_SYSTEM})
endif()

set(CUBBYFLOW_TASKING_SYSTEM ${TASKING_DEFAULT} CACHE STRING
	"Per-node thread tasking system [CPP11Thread, TBB, OpenMP, HPX, Serial]")

set_property(CACHE CUBBYFLOW_TASKING_SYSTEM PROPERTY
	STRINGS CPP11Thread TBB OpenMP HPX Serial)

# Note - Make the CUBBYFLOW_TASKING_SYSTEM build option case-insensitive
string(TOUPPER ${CUBBYFLOW_TASKING_SYSTEM} CUBBYFLOW_TASKING_SYSTEM_ID)

set(CUBBYFLOW_TASKING_TBB			FALSE)
set(CUBBYFLOW_TASKING_OPENMP		FALSE)
set(CUBBYFLOW_TASKING_CPP11THREAD	FALSE)
set(CUBBYFLOW_TASKING_HPX			FALSE)
set(CUBBYFLOW_TASKING_SERIAL		FALSE)

if(${CUBBYFLOW_TASKING_SYSTEM_ID} STREQUAL "TBB")
	set(CUBBYFLOW_TASKING_TBB TRUE)
elseif(${CUBBYFLOW_TASKING_SYSTEM_ID} STREQUAL "OPENMP")
	set(CUBBYFLOW_TASKING_OPENMP TRUE)
elseif(${CUBBYFLOW_TASKING_SYSTEM_ID} STREQUAL "HPX")
	set(CUBBYFLOW_TASKING_HPX TRUE)
elseif(${CUBBYFLOW_TASKING_SYSTEM_ID} STREQUAL "CPP11THREAD")
	set(CUBBYFLOW_TASKING_CPP11THREAD TRUE)
else()
	set(CUBBYFLOW_TASKING_SERIAL TRUE)
endif()

unset(TASKING_SYSTEM_LIBS)
unset(TASKING_SYSTEM_LIBS_MIC)

if(CUBBYFLOW_TASKING_TBB)
	find_package(TBB REQUIRED)
	add_definitions(-DCUBBYFLOW_TASKING_TBB)
	include_directories(${TBB_INCLUDE_DIRS})
	set(TASKING_SYSTEM_LIBS ${TBB_LIBRARIES})
	set(TASKING_SYSTEM_LIBS_MIC ${TBB_LIBRARIES_MIC})
else()
	unset(TBB_INCLUDE_DIRS	           CACHE)
	unset(TBB_LIBRARY		           CACHE)
	unset(TBB_LIBRARY_DEBUG	           CACHE)
	unset(TBB_LIBRARY_MALLOC		   CACHE)
	unset(TBB_LIBRARY_MALLOC_DEBUG	   CACHE)
	unset(TBB_INCLUDE_DIR_MIC		   CACHE)
	unset(TBB_LIBRARY_MIC	           CACHE)
	unset(TBB_LIBRARY_MALLOC_MIC	   CACHE)
	if(CUBBYFLOW_TASKING_OPENMP)
		find_package(OpenMP)
		if(OPENMP_FOUND)
			include_directories(${OpenMP_C_INCLUDE_DIR})
			set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
			set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
			add_definitions(-DCUBBYFLOW_TASKING_OPENMP)
		endif()
	elseif(CUBBYFLOW_TASKING_HPX)
		find_package(HPX REQUIRED)
		add_definitions(-DCUBBYFLOW_TASKING_HPX)
		set(TASKING_SYSTEM_LIBS ${HPX_LIBRARIES})
		include_directories(${HPX_INCLUDE_DIRS})
	elseif(CUBBYFLOW_TASKING_CPP11THREAD)
		add_definitions(-DCUBBYFLOW_TASKING_CPP11THREAD)
	else()
		# Serial
		# Do nothing, will fall back to scalar code (useful for debugging)
	endif()
endif()
