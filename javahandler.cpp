#include "javahandler.h"


JavaHandler::JavaHandler(QString nameOfJar,QString nameOfMethod)
{
    QString  pwd_path=QCoreApplication::applicationDirPath() ;
    jar_name = nameOfJar;
    method_name = nameOfMethod;
    options = new JavaVMOption[1];
    char option_string[1024];
    sprintf(option_string,"-Djava.class.path=%s/%s",
            pwd_path.toStdString().c_str(),
            jar_name.toStdString().c_str());
    options[0].optionString=option_string;
    vm_args.version = JNI_VERSION_1_6;
    vm_args.nOptions = 1;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = false;
    rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    if (rc != JNI_OK) {
             qDebug()<<"Error "<<rc;
            exit(EXIT_FAILURE);
      }
     cls2 = env->FindClass("org/example/Main");  // try to find the class
       if (cls2 == nullptr) {
           qDebug() << "ERROR: class not found !";
           jvm->DestroyJavaVM();
           exit(EXIT_FAILURE);
    }
   mid2 = env->GetStaticMethodID(cls2, method_name.toStdString().c_str(),
                                 "(Ljava/lang/String;Ljava/lang/String;)D");
   if (mid2 == nullptr) {
            qDebug() << "ERROR: method  not found !" ;
            jvm->DestroyJavaVM();
            exit(EXIT_FAILURE);
   }
}

double JavaHandler::callAfis(QString path1,QString path2)
{
   jstring jstr1 = env->NewStringUTF(path1.toStdString().c_str());
   jstring jstr2 = env->NewStringUTF(path2.toStdString().c_str());
   jdouble value=env->CallStaticDoubleMethod(cls2,mid2,jstr1,jstr2);
   return value;
}
void JavaHandler::attachThread()
{
    jvm->AttachCurrentThread((void **)&env,&vm_args);
}
JavaHandler::~JavaHandler()
{
  jvm->DestroyJavaVM();
}
