#include <iostream>
#include <fstream>
#include <memory>
#include "Eigen/Core"
#include "opencv2/opencv.hpp"
#include "opencv2/core/eigen.hpp"
#include "cnf.hpp"
#include "tracker.hpp"
#include "sample_space.hpp"
#include "scale_filter.hpp"
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    string video_path = "../";
    string groundtruth_path = "../";
    string video_name = "test2.avi";
    string gth_name = "test2.txt";
	VideoCapture vidCap;
	Mat frame;
    vidCap.open(video_path+video_name);
    if (!vidCap.isOpened())  
    {
        printf("Can't open file\n");
        return 0;
    }
    vidCap >> frame;

	int x, y, width, height;
	char c;
    std::ifstream cin(groundtruth_path+gth_name);
    if(!cin.is_open())
    {
        cout<<" there is no groundtruth file "<<endl;
        return 0;
    }
    cin >> x >> c >> y >> c >> width >> c >> height;
    cin.close();

    cout<<" get x  " << x << " y" << y << "w " << width << "h " << height << endl;
    Track::Tracker tracker(x, y, height, width, frame, nullptr);
    cout<<" initialed "<<endl;
    int num_track =0;
//    using namespace std::chrono_literals;
	while(true)
    {
		vidCap >> frame;
		if (frame.empty()) 
            break;
        cv::Rect rc = tracker.track(frame);
        
        // Visualizing
        rectangle(frame, rc, Scalar(0,255,0), 2);
        cv::imshow("result", frame);
        
        cv::waitKey(10);
        num_track++;
    }
    cout<<" total time:"<<tracker.time<<" fps:"<<(num_track-2)/tracker.time<<endl;
    return 0;
}
