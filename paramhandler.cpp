#include "paramhandler.h"

ParamHandler::ParamHandler()
{

}

void ParamHandler::error(QString message)
{
    qDebug().noquote()<<QString("Fatal Error: %1").arg(message,40);
    qApp->exit(EXIT_FAILURE);
    exit(EXIT_FAILURE);
}

void ParamHandler::parseCmdLine(QStringList args)
{
    QString lastParam="";
    for(int i=1;i<args.size();i++)
    {
        if(args[i]=="--help") printHelp();
        QStringList sp=args[i].split("=");
        QString name = sp[0];
        name = name.mid(2);
        QString value = sp[1];
        if(value=="")
        {
            error(QString("Param %1 is empty.").arg(value));
        }
        setParamValue(name,value);
    }
}
void    ParamHandler::addParam(QString name,QString value,QString help)
{
    QJsonObject t;
    t["name"]=name;
    t["value"]=value;
    t["help"]=help;
    params<<t;
}

void    ParamHandler::setParamValue(QString name,QString value)
{
    int icount=0;
    for(const QJsonValue &x : params)
    {
        QJsonObject t = x.toObject();
        if(t["name"]==name)
        {
            t["value"]=value;
            params[icount]=t;
            return;
        }
        icount++;
    }
}

QString ParamHandler::getParamValue(QString name) const
{
    for(const QJsonValue &x : params)
    {
        QJsonObject t = x.toObject();
        if(t["name"]==name)
            return t["value"].toString();
    }
    return "";
}

QString ParamHandler::getParamHelp(QString name) const
{
    for(const QJsonValue &x : params)
    {
        QJsonObject t = x.toObject();
        if(t["name"]==name)
            return t["help"].toString();
    }
    return "";
}

void ParamHandler::printParam(QString name)
{
    QString description = getParamHelp(name);
    QString value  = getParamValue(name);
    QString s=QString("%1 %2 %3 %4").arg("--"+name,-27).
            arg(description,-38).arg("Default value:",-15).arg(value,-10);
    qDebug().noquote()<<s;
}

void ParamHandler::printHelp()
{
    QString description = "Parameter Description";
    QString value  = "Parameter Value";
    QString s=QString("%1 %2 %3 %4").arg("Parameter Name",-27).
            arg(description,-38).arg("",-15).arg(value,-10);
    qDebug().noquote()<<s;
    qDebug().noquote()<<"==================================================================================================";
    for(const QJsonValue &x : params)
    {
        QJsonObject t = x.toObject();
        printParam(t["name"].toString());
    }
    exit(EXIT_SUCCESS);
}
ParamHandler::~ParamHandler()
{

}
