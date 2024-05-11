#include "matchhandler.h"
extern void onError(QString message);

MatchHandler::MatchHandler(QString s1,QString s2,QString finger,JavaHandler *hnd)
{
    sourcedir1 = s1;
    sourcedir2 = s2;
    fingerindex=finger;
    jhandler = hnd;
    QDir dir1(sourcedir1);
    QString pattern = "*_"+fingerindex+".png";
    images1 = dir1.entryList(QStringList() << pattern ,QDir::Files);
    QDir dir2(sourcedir2);
    images2 = dir2.entryList(QStringList() << pattern,QDir::Files);
    if(images1.empty() || images2.empty())
        onError("Empty image list");
    for(const QString &x :images1 )
    {
        QStringList items = x.split("_");
        QString name = items[0];

        if(!users1.contains(name))
            users1<<name;
    }
    for(const QString &x :images2 )
    {
        QStringList items = x.split("_");
        QString name = items[0];
        if(!users2.contains(name))
            users2<<name;
    }

}

void    MatchHandler::runMatcher(QVector<MatchStruct> &matches)
{
    for(const QString &n1 : images1)
    {
    QString name1 = sourcedir1+n1;
    double bestMatch = -1e+100;
    QString bestMatchedName = "";
    for (const QString &x : images2)
    {
        QString name2 = sourcedir2+x;
        double value = jhandler->callAfis(name1,name2);
        if(value>bestMatch)
        {
            bestMatch = value;
            bestMatchedName = x;
        }
    }


    MatchStruct mt;
    mt.user1 =n1.split("_")[0];
    mt.user2 = bestMatchedName.split("_")[0];
    mt.match = bestMatch;
    matches<<mt;
    qDebug()<<"Best matched for  "<<mt.user1<<"..is "<<
              mt.user2<<" With value "<<bestMatch;
    }
}

MatchHandler::~MatchHandler()
{
    //nothing here
}
