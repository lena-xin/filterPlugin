#include "median_plugin.h"

Median_plugin::Median_plugin()
{
}

Median_plugin::~Median_plugin()
{

}

QString Median_plugin::description()
{
    return "this is plugin";
}

void Median_plugin::processImage(const cv::Mat &inputImage, cv::Mat &outputImage)
{
    cv::medianBlur(inputImage,outputImage,5);
}
