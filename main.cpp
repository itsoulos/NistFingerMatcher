#include <QCoreApplication>
#include <jni.h>
# include <QDebug>
# include <string.h>
# include "javahandler.h"
# include "paramhandler.h"
# include "matchhandler.h"
# include <QDir>

ParamHandler phandler;
JavaHandler *jhandler=NULL;
MatchHandler *mhandler;

void onFreeMemory()
{
    if(jhandler!=NULL)
        delete jhandler;
    if(mhandler!=NULL)
        delete mhandler;
}
void onError(QString message)
{
    qDebug().noquote()<<QString("Fatal Error: %1").arg(message,40);
    onFreeMemory();
    qApp->exit(EXIT_FAILURE);
    exit(EXIT_FAILURE);
}

void addParams(ParamHandler &phandler)
{
    phandler.addParam("jarfile","FingerAfis.jar","Name of the Source Afis jar file.");
    phandler.addParam("methodname","CompareAfis","Name of  method in jar file.");
    phandler.addParam("fingerindex","01","Finger index: 01-10");
    phandler.addParam("sourcedir1",".","The first source dir of png images");
    phandler.addParam("sourcedir2",".","The second source directory of images");
    phandler.addParam("matchLimit","40.0","The match limit for sourceafirs");
    phandler.addParam("threads","1","Number of OpenMp threads");
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    addParams(phandler);
    phandler.parseCmdLine(a.arguments());


    jhandler=new JavaHandler(phandler.getParamValue("jarfile"),
                                          phandler.getParamValue("methodname"));

    mhandler = new MatchHandler(
                phandler.getParamValue("sourcedir1"),
                phandler.getParamValue("sourcedir2"),
                phandler.getParamValue("fingerindex"),
                jhandler,phandler.getParamValue("threads").toInt()
                );
    QVector<MatchStruct> matches;
    mhandler->runMatcher(matches);
    double score = 0.0;
    const double matchLimit = phandler.getParamValue("matchLimit").toDouble();
    for(int i=0;i<matches.size();i++)
    {
        if(matches[i].user1==matches[i].user2
                && matches[i].match>=matchLimit)
            score = score+1.0;
    }
    score = score *100.0/matches.size();
    printf("SCORE : %.2lf%%\n",score);
    onFreeMemory();
    return 0;
}
