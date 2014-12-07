OpenCV_DIR?=/usr/local/opencv-3.0.0-beta
CXX?=g++
CXXFLAGS=-I/usr/local/include/pcl-1.8/ -I/usr/local/include/eigen3 \
-I/usr/local/include/ni -I/usr/local/include -I/usr/local/Cellar/vtk5/5.10.1/include/vtk-5.10 \
-O3 -Wall
LDFLAGS=-L${OpenCV_DIR}/lib -L/usr/local/lib -L/usr/local/Cellar/vtk5/5.10.1/lib/vtk-5.10 \
-lpcl_common -lpcl_io -lpcl_visualization -lpcl_filters -lpcl_geometry -lpcl_surface -lpcl_tracking \
-lvtksys -lvtkfreetype -lvtkDICOMParser -lvtkproj4 -lmpistubs -lMapReduceMPI -lvtkverdict -lvtkNetCDF -lvtkNetCDF_cxx -lvtkmetaio \
-lvtksqlite -lvtkexoIIc -lLSDyna -lvtkalglib -lvtkftgl -lvtkCommonPythonD -lvtkCommon -lvtkFilteringPythonD -lvtkFiltering -lvtkImagingPythonD -lvtkImaging \
-lvtkGraphicsPythonD -lvtkGraphics -lvtkGenericFilteringPythonD -lvtkGenericFiltering -lvtkIOPythonD -lvtkIO -lvtkRenderingPythonD -lvtkRendering -lvtkVolumeRenderingPythonD \
-lvtkVolumeRendering -lvtkHybridPythonD -lvtkHybrid -lvtkWidgetsPythonD -lvtkWidgets -lvtkInfovisPythonD -lvtkInfovis -lvtkGeovisPythonD -lvtkGeovis -lvtkViewsPythonD -lvtkViews \
-lvtkChartsPythonD -lvtkCharts -lvtkPythonCore \
-lboost_thread-mt -lboost_system
BUILD_DIR=bin
SRCS=main.cpp
OBJS=${SRCS:%.cpp=${BUILD_DIR}/%.o}

main: $(OBJS)
	${CXX} ${LDFLAGS} ${OBJS} -o $@
${BUILD_DIR}/%.o : %.cpp
	@mkdir -p $(dir $@)
	${CXX} ${CXXFLAGS} -c $< -o $@

clean:
	rm -rf ${BUILD_DIR} main
