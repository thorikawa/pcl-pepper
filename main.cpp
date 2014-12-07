#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>

int main () {
  pcl::PointCloud<pcl::PointXYZ> cloud;
  cloud.width    = 10000;  
  cloud.height   = 1;  
  cloud.is_dense = false;  
  cloud.points.resize (cloud.width * cloud.height);  

  for (size_t i = 0; i < cloud.points.size (); ++i) {
    cloud.points[i].x = 1024 * rand () / (RAND_MAX + 1.0);
    cloud.points[i].y = 1024 * rand () / (RAND_MAX + 1.0);
    cloud.points[i].z = 1024 * rand () / (RAND_MAX + 1.0);
  }

  pcl::visualization::PCLVisualizer viewer("Sample Viewer");
  viewer.addPointCloud(cloud.makeShared(), "sample cloud");
  // viewer.showCloud(cloud.makeShared());
  while (!viewer.wasStopped ()) {
    viewer.spinOnce (100);
    boost::this_thread::sleep (boost::posix_time::microseconds (100000));
  }
  return 0;
}
