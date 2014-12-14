#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/pcd_io.h>
#include <boost/thread/thread.hpp>

int main (int argc, char** argv) {
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  if (pcl::io::loadPCDFile<pcl::PointXYZ> (argv[1], *cloud) == -1) //* load the file
  {
    PCL_ERROR ("Couldn't read file \n");
    return (-1);
  }

  pcl::visualization::PCLVisualizer viewer("Sample Viewer");
  viewer.addPointCloud(cloud, "sample cloud");
  while (!viewer.wasStopped ()) {
    viewer.spinOnce (100);
    boost::this_thread::sleep (boost::posix_time::microseconds (100000));
  }
  return 0;
}
