#ifndef MATCHHANDLER_H
#define MATCHHANDLER_H
# include <QString>
# include <QStringList>
# include <QVector>
# include <QDir>
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

public:
    MatchHandler(QString s1,QString s2,QString finger,JavaHandler *hnd);
    void runMatcher(QVector<MatchStruct> &matches);
    ~MatchHandler();
};

#endif // MATCHHANDLER_H
