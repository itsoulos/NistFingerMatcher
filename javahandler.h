#ifndef JAVAHANDLER_H
#define JAVAHANDLER_H

#include <jni.h>
# include <QString>
# include <QCoreApplication>
# include <QDebug>
class JavaHandler
{
private:
    JavaVM *jvm;
    JNIEnv *env;
    JavaVMInitArgs vm_args;
    JavaVMOption* options;
    jint rc;
    jclass cls2;
     jmethodID mid2;
     QString jar_name;
     QString method_name;
public:
    JavaHandler(QString nameOfJar,QString nameOfMethod);
    double callAfis(QString path1,QString path2);
    ~JavaHandler();
};

#endif // JAVAHANDLER_H
