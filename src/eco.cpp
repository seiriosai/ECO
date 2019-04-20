#include "tracker.hpp"
#include "eco.h"

std::unique_ptr<EcoTracker> EcoTracker::createInstance(float tlx, float tly, float height, float width, cv::Mat im, const char* cfgFolder)
{
    return std::unique_ptr<EcoTracker>(new Track::Tracker(tlx, tly, height, width, im, cfgFolder));
}
