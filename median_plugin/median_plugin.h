#ifndef MEDIAN_PLUGIN_H
#define MEDIAN_PLUGIN_H

#include "median_plugin_global.h"
//1 包含接口文件
#include "cvplugininterferce.h"

//2 继承QObject和CvPluginInterface
class MEDIAN_PLUGIN_EXPORT Median_plugin:public QObject,
        public CvPluginInterface
{
    Q_OBJECT
//  添加插件的元数据
    Q_PLUGIN_METADATA(IID"com.admin.cvplugininterface")
    //声明插件中要实现的接口
    Q_INTERFACES(CvPluginInterface)
public:
    Median_plugin();
    ~Median_plugin();
    QString description();
    void processImage(const cv::Mat &inputImage, cv::Mat &outputImage);
};

#endif // MEDIAN_PLUGIN_H
