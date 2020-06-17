#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QPluginLoader>
#include <QFileInfoList>
#include "opencv2/opencv.hpp"
#include "cvplugininterferce.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_inputImageBtn_pressed();

    void on_helpBtn_pressed();

    void on_filtersBtn_pressed();

private:
    void getPluginsList();
    Ui::Widget *ui;
};
#endif // WIDGET_H
