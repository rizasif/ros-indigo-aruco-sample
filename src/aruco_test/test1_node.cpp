#include <ros/ros.h>
#include <ros/package.h>
#include <iostream>
#include <aruco/aruco.h>
#include <aruco/cvdrawingutils.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <aruco/markerdetector.h>

/*This node runs basic marker detection code*/

int main(int argc, char** argv)
{
	ros::init(argc, argv, "test1_node");
	ros::AsyncSpinner spinner(1);
	spinner.start();

	ros::NodeHandle node_handle;

    try
    {
        aruco::MarkerDetector MDetector;
        vector<aruco::Marker> Markers;
        //read the input image
        cv::Mat InImage;
        InImage=cv::imread("/home/rizi/ros_stuff/aruco_ws/src/aruco_test/images/aruco_marker_1.png");
    	//Ok, let's detect
        MDetector.detect(InImage,Markers);
        //for each marker, draw info and its boundaries in the image
        for (unsigned int i=0;i<Markers.size();i++) {
            std::cout<<Markers[i]<<std::endl;
            Markers[i].draw(InImage,cv::Scalar(0,0,255),2);
        }
        cv::imshow("in",InImage);
        cv::waitKey(0);//wait for key to be pressed
    } catch (std::exception &ex)
    {
        cout<<"Exception :"<<ex.what()<<endl;
    }
    
    
	ros::WallDuration short_delay(4.0);
	short_delay.sleep();

	ros::shutdown();
	return 0;

}