#ifndef MATCHHANDLER_H
#define MATCHHANDLER_H
# include <QString>
# include <QStringList>
# include <QVector>
# include <QDir>
# include <omp.h>
# include "javahandler.h"

struct MatchStruct
{
    QString user1;
    QString user2;
    double  match;
};

class MatchHandler
{
private:
    QString sourcedir1,sourcedir2,fingerindex;
    JavaHandler *jhandler;
    QStringList images1,images2;
    QStringList users1,users2;
    int threads;
public:
    MatchHandler(QString s1,QString s2,QString finger,
                 JavaHandler *hnd,int t);
    void runMatcher(QVector<MatchStruct> &matches);
    ~MatchHandler();
};

#endif // MATCHHANDLER_H
