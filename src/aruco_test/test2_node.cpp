#include <ros/ros.h>
#include <ros/package.h>
#include <iostream>
#include <aruco/aruco.h>
#include <aruco/cvdrawingutils.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <aruco/markerdetector.h>

/*This node checks distance from camera*/

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
        InImage=cv::imread("/home/rizi/ros_stuff/aruco_ws/src/aruco_test/markerprecise/pic0.jpg");
    	//Ok, let's detect
        MDetector.detect(InImage,Markers);
        
        aruco::MarkerDetector MDetector2;
        vector<aruco::Marker> Markers2;
        //read the input image
        cv::Mat InImage2;
        InImage2=cv::imread("/home/rizi/ros_stuff/aruco_ws/src/aruco_test/markerprecise/pic6.jpg");
    	//Ok, let's detect
        MDetector2.detect(InImage2,Markers2);
        
        /*-------------------Distance Check-----------------------*/
        
        double focal_length, kDist, kWidth, dist, pWidth, pWidth2;
        
        //For Calibration
        pWidth = (double) Markers[0].getPerimeter();
        kDist = 40.0;
        kWidth = 9.5 * 4.0;
        focal_length = (pWidth * kDist)/kWidth;
        
        //For Camera & Distortion Matrix
        int imLength = (InImage.rows)/2;
        int imWidth = (InImage.cols)/2;
        float cameraMatrixPrams[9] = {focal_length,0,imLength, 0,focal_length,imWidth, 0,0,1}; 
        cv::Mat cameraMatrix = cv::Mat(3, 3, CV_32F, cameraMatrixPrams);
        float distMatrixPrams[5] = {0,0,0,0,0};
        cv::Mat distMatrix = cv::Mat(1, 5, CV_32F, distMatrixPrams);
        cv::Size imSize(InImage.rows, InImage.cols);
        aruco::CameraParameters camParameters(cameraMatrix, distMatrix, imSize);
        
        Markers[0].calculateExtrinsics(kWidth, camParameters);
        Markers2[0].calculateExtrinsics(kWidth, camParameters);
        
        //For Detection
        pWidth2 = (double) Markers2[0].getPerimeter();
        dist = (kWidth * focal_length)/pWidth2;
        
        //Printing
        std::cout << std::endl;
        std::cout << "Distance Img1 (Known): " << kDist << std::endl;
        std::cout << "Distance Img2 (Calculated): " << dist << std::endl;
        std::cout << "Focal Length: " << focal_length << std::endl;
        std::cout << "pWidth Img1: " << pWidth << std::endl;
        std::cout << "pWidth Img2: " << pWidth2 << std::endl;
        
        /*-------------Orientation Detection-------------------------*/
        double pos[3], ori[4];
        Markers[0].OgreGetPoseParameters(pos, ori);
        
        std::cout << "Orientation Img1: " << ori[0] << ", " << ori[1] << ", "<< ori[2] << ", " <<ori[3] << std::endl;
        //std::cout << "Riz: Position: " << pos[0] << ", " << pos[1] << ", "<< pos[2] << std::endl;
        
        double pos2[3], ori2[4];
        Markers2[0].OgreGetPoseParameters(pos2, ori2);
        
        std::cout << "Orientation Img2: " << ori2[0] << ", " << ori2[1] << ", "<< ori2[2] << ", " <<ori2[3] << std::endl;
        //std::cout << "Riz: Position: " << pos2[0] << ", " << pos2[1] << ", "<< pos2[2] << std::endl;
        
        /*--------------------------------------------------------*/
        
        cv::waitKey(0);//wait for key to be pressed
    } catch (std::exception &ex)
    {
        std::cout<<"Exception :"<<ex.what()<<std::endl;
    }
    
    
	ros::WallDuration short_delay(4.0);
	short_delay.sleep();

	ros::shutdown();
	return 0;

}