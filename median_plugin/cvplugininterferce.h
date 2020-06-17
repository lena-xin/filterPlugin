#ifndef CVPLUGININTERFERCE_H
#define CVPLUGININTERFERCE_H
#include <QObject>
#include <QString>
#include "opencv2/opencv.hpp"

class CvPluginInterface{
public:
    virtual ~CvPluginInterface(){}
    virtual QString description()=0;
    virtual void processImage(const cv::Mat &inputImage, cv::Mat &outputImage)=0;
};

#define CVPLUGININTERFACE_IID "com.admin.cvplugininterface"
//Q_DECLARE_INTERFACE( ClassName, Identifier)
Q_DECLARE_INTERFACE (CvPluginInterface, CVPLUGININTERFACE_IID)

#endif // CVPLUGININTERFERCE_H
