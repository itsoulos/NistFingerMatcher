#include <QCoreApplication>
#include <jni.h>
# include <QDebug>
# include <string.h>
# include "javahandler.h"
# include "paramhandler.h"
# include <QDir>
void addParams(ParamHandler &phandler)
{
    phandler.addParam("jarfile","FingerAfis.jar","Name of the Source Afis jar file.");
    phandler.addParam("methodname","CompareAfis","Name of  method in jar file.");
    phandler.addParam("fingerindex","01","Finger index: 01-10");
    phandler.addParam("sourcedir1",".","The first source dir of png images");
    phandler.addParam("sourcedir2",".","The second source directory of images");
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ParamHandler phandler;
    addParams(phandler);
    phandler.parseCmdLine(a.arguments());

    QDir dir1(phandler.getParamValue("sourcedir1"));
    QStringList images1 = dir1.entryList(QStringList() << "*.png" << "*.PNG",QDir::Files);
    qDebug()<<images1;
   /* JavaHandler *jhandler=new JavaHandler(phandler.getParamValue("jarfile"),
                                          phandler.getParamValue("methodname"));
    QString a1 = argv[1];
    QString a2 = argv[2];
    double testValue = jhandler->callAfis(a1,a2);
    qDebug()<<"TestValue: "<<testValue;
    delete jhandler;*/
    exit(EXIT_SUCCESS);
}
