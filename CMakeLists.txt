cmake_minimum_required(VERSION 2.8)

PROJECT (VideoSonde)

find_package(glog QUIET OPTIONAL_COMPONENTS)
find_package(ceres QUIET OPTIONAL_COMPONENTS)
find_package(eigen QUIET OPTIONAL_COMPONENTS)
find_package(OpenCV  REQUIRED)
find_package(VTK  OPTIONAL_COMPONENTS)

file(GLOB VideoSonde_SRCS
    "*.h"
    "*.cpp")
ADD_EXECUTABLE (VideoSonde ${VideoSonde_SRCS})



if (OpenCV_FOUND)
	include_directories( ${OpenCV_INCLUDE_DIRS} ${CERES_INCLUDE_DIR} ${EIGEN_INCLUDE_DIR}  )
	target_link_libraries( VideoSonde ${OpenCV_LIBS} ${CERES_LIBRARIES}   ${GLOG_LIBRARIES} ${GFLAGS_LIBRARIES}
)
        if (Vtk_FOUND)
        	include_directories( ${Vtk_INCLUDE_DIRS} )
	        target_link_libraries( VideoSonde ${Vtk_LIBS} )
         endif (Vtk_FOUND)
else (OpenCV_FOUND)
message("PB->OPENCV = ${OpenCV_INCLUDE_DIRS}")
endif (OpenCV_FOUND)
