#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/pcd_io.h>
#include <pcl/range_image/range_image_planar.h>
#include <pcl/visualization/range_image_visualizer.h>
#include <boost/thread/thread.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

int main (int argc, char** argv) {
	Mat src = imread(argv[1], IMREAD_GRAYSCALE);
	float dataf[src.rows * src.cols];
	for (int i=0; i<src.rows * src.cols; i++) {
		int r = i / src.cols;
		int c = i % src.cols;
		dataf[i] = (float) src.at<unsigned char>(r, c);
	}

	float fx = 525.0, fy = 525.0; // default focal length
	float cx = 319.5, cy = 239.5; // default optical center
	pcl::RangeImagePlanar pclImage = pcl::RangeImagePlanar();
	pclImage.setDepthImage(dataf, src.cols, src.rows, cx, cy, fx, fy);

	/*
	pcl::visualization::PCLVisualizer viewer("Sample Viewer");
	viewer.addPointCloud(pclImage.makeShared(), "sample cloud");
	// viewer.showCloud(cloud.makeShared());
	while (!viewer.wasStopped ()) {
		viewer.spinOnce (100);
		boost::this_thread::sleep (boost::posix_time::microseconds (100000));
	}
	*/

	pcl::visualization::RangeImageVisualizer range_image("Range image");
	range_image.showRangeImage(pclImage);
	while (!range_image.wasStopped ()) {
		// viewer.spinOnce (100);
		boost::this_thread::sleep (boost::posix_time::microseconds (100000));
	}
	return 0;
}
