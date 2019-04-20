#pragma once

#include <memory>
#include "opencv2/core.hpp"

namespace eco 
{

class EcoTracker
{
public:
    virtual ~EcoTracker() { }
    
    static std::unique_ptr<EcoTracker> createInstance(float tlx, float tly, float height, float width, cv::Mat im, const char* cfgFolder);
    
    virtual cv::Rect track(cv::Mat img) = 0;
};

}
