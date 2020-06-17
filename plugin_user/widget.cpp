#include "widget.h"
#include "ui_widget.h"
#define FILTERS_SUBFLODER "/filter_plugins/"
#include <QDebug>
#define cout qDebug()
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    getPluginsList();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::getPluginsList()
{
    //获取插件文件夹的路径
    QDir filtersDir(qApp->applicationDirPath()+FILTERS_SUBFLODER);
    QFileInfoList filters = filtersDir.entryInfoList(QDir::NoDotAndDotDot|QDir::Files,
                                                     QDir::Name);
    foreach (QFileInfo filter, filters) {
        if(QLibrary::isLibrary(filter.absoluteFilePath()))
        {
            QPluginLoader pluginLoader(filter.absoluteFilePath(),this);
            if(dynamic_cast<CvPluginInterface*>(pluginLoader.instance()))
            {
                cout<<filter.fileName();
                ui->filtersList->addItem(filter.fileName());
                pluginLoader.unload();
            }
            else {
                QMessageBox::warning(this,
                                     tr("Warning"),
                                     QString("make sure %1 is correct").arg(filter.fileName()));
            }
        }
        else {
            QMessageBox::warning(this,
                                 tr("Warning"),
                                 QString("%1 is not a plugin").arg(filter.fileName()));
        }
    }

    if(ui->filtersList->count()<=0){
        QMessageBox::critical(this,tr("没有插件"),tr("该程序无插件无法运行"));
        this->setEnabled(false);
    }
}


void Widget::on_inputImageBtn_pressed()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("打开图像文件"),
                                                    QDir::currentPath(),
                                                    tr("images")+"(*.jpg *.png *.bmp)");
    if(QFile::exists(fileName))
    {
        ui->inputImageEdit->setText(fileName);
    }
}

void Widget::on_helpBtn_pressed()
{
    if(ui->filtersList->currentRow() >= 0)
    {
        QPluginLoader pluginLoader(qApp->applicationDirPath()+FILTERS_SUBFLODER+ui->filtersList->currentItem()->text());
        CvPluginInterface *plugin = dynamic_cast<CvPluginInterface*>(pluginLoader.instance());
        if(plugin)
        {
            QMessageBox::information(this,tr("关于插件"),plugin->description());
        }
        else {
            QMessageBox::warning(this,
                                 tr("警告"),
                                 QString("确保插件%1存在并且可用的").arg(ui->filtersList->currentItem()->text()));
        }
    }
    else {
        QMessageBox::warning(this,
                             tr("警告"),
                             tr("从列表中选择第一个滤波器插件"));
    }
}

void Widget::on_filtersBtn_pressed()
{
    if(ui->filtersList->currentRow() >= 0 && !ui->inputImageEdit->text().isEmpty())
    {
        QPluginLoader pluginLoader(qApp->applicationDirPath()+FILTERS_SUBFLODER+ui->filtersList->currentItem()->text());
        CvPluginInterface *plugin = dynamic_cast<CvPluginInterface*>(pluginLoader.instance());
        if(plugin)
        {
            if(QFile::exists(ui->inputImageEdit->text())){
                using namespace cv;
                Mat inputImage,outputImage;
                inputImage = imread(ui->inputImageEdit->text().toStdString(),0);
                plugin->processImage(inputImage,outputImage);
                imshow(tr("filters image").toStdString(),outputImage);
            }else {

                QMessageBox::warning(this,
                                     tr("关于插件"),
                                     tr("确保%1存在").arg(ui->inputImageEdit->text()));
            }
        }
        else {
            QMessageBox::warning(this,
                                 tr("警告"),
                                 QString("确保插件%1存在并且可用的").arg(ui->filtersList->currentItem()->text()));
        }
    }
    else {
        QMessageBox::warning(this,
                             tr("警告"),
                             tr("从列表中选择第一个滤波器插件"));
    }
}
