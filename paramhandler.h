#ifndef PARAMHANDLER_H
#define PARAMHANDLER_H
# include <QString>
# include <QStringList>
# include <QDebug>
# include <QJsonArray>
# include <QJsonObject>
# include <QCoreApplication>
class ParamHandler
{
private:
    QJsonArray params;
public:
    ParamHandler();
    void addParam(QString name,QString value,QString help);
    void    setParamValue(QString name,QString value);
    QString getParamValue(QString name) const;
    QString getParamHelp(QString name)  const;
    void printParam(QString name);
    void error(QString message);
    void parseCmdLine(QStringList args);
    void printHelp();
    ~ParamHandler();
};

#endif // PARAMHANDLER_H
