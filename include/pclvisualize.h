#pragma once

#include <iostream>
#include <thread>

#include <pcl/common/common_headers.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>




struct PCLviewerPy {
    PCLviewerPy(const std::string &name) : name(name) { }
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }

    void updateViewer(py::array_t<double> input1)
    {

    }
    void startViewer(){

      while (!viewer.wasStopped ())
        {
          viewer.spinOnce (100);
          std::this_thread::sleep_for(100ms);
        }

    }


    // the internal variables
    std::string name;
    pcl::PointCloud<pcl::PointXYZ> P;
    pcl::PointCloud<pcl::PointXYZRGB> Prgb;
    pcl::visualization::PCLVisualizer viewer;

    bool accumulate;
    bool quitviewer;
};


pcl::visualization::PCLVisualizer::Ptr simpleVis (pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud);

void testviewer();