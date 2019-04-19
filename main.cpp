#include <iostream>
#include <fstream>
#include <memory>
#include "opencv2/opencv.hpp"
#include "cnf.hpp"
#include "tracker.hpp"

#include <chrono>
#include <thread>
using namespace std;

using namespace cv;
using namespace Feature;
int main(int argv,char** argc)
{
    Mat im(imread("/mnt/data1/outputimages/gray_460.png",IMREAD_UNCHANGED));
    Track::Tracker a(257, 207, 74, 98, im);

    char name[100];
    for(int i = 461;i<1500;++i)
    {
        sprintf(name,"/mnt/data1/outputimages/gray_%d.png",i);
        im = imread(name,IMREAD_UNCHANGED);
        a.track(im);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    cout<<" total time:"<<a.time<<" fps:"<<119/a.time<<endl;
    return 0;
}