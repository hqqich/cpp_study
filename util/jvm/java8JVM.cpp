//
// Created by admin on 2023/12/13.
//

#include "java8JVM.h"
#include <iostream>
#include <sstream>
#include "leveldb/db.h"
#include "jni.h"
#include "windows.h"
#include "iostream"
#include <tchar.h>
#include "jni.h"
#include <libloaderapi.h>




// ===================================
using namespace std;

typedef jint(JNICALL *JNICREATEPROC)(JavaVM **, void **, void *);

bool startJVM();


//启动java虚拟机
bool startJVM() {
    int pause;
    //获取jvm动态库的路径
//    TCHAR *jvmPath = _T("C:\\\"Program Files\"\\Java\\jdk1.8.0_333\\jre\\bin\\server\\jvm.dll");
    TCHAR *jvmPath = _T("C:\\Program Files\\Java\\jdk1.8.0_333\\jre\\bin\\server\\jvm.dll");

    cout << jvmPath << endl;

    //java虚拟机启动时接收的参数，每个参数单独一项
    int nOptionCount = 2;
    JavaVMOption vmOption[2];
    //设置JVM最大允许分配的堆内存，按需分配
    vmOption[0].optionString = "-Xmx100M";
    //设置classpath
    vmOption[1].optionString = "-Djava.class.path=./Test.jar";

    JavaVMInitArgs vmInitArgs;
    vmInitArgs.version = JNI_VERSION_1_8;
    vmInitArgs.options = vmOption;
    vmInitArgs.nOptions = nOptionCount;
    //忽略无法识别jvm的情况
    vmInitArgs.ignoreUnrecognized = JNI_TRUE;

    //设置启动类，注意分隔符为"/"
    const char startClass[] = "me/hqqich/App";
    //启动方法，一般是main函数，当然可以设置成其他函数
    const char startMethod[] = "main";

    //加载JVM,注意需要传入的字符串为LPCWSTR,指向一个常量Unicode字符串的32位指针，相当于const wchar_t*
    HINSTANCE jvmDLL = LoadLibrary(jvmPath);
    if (jvmDLL == NULL) {
        cout << "89:加载JVM动态库错误" << endl;
        return false;
    }

    //初始化jvm物理地址
    JNICREATEPROC jvmProcAddress = (JNICREATEPROC) GetProcAddress(jvmDLL, "JNI_CreateJavaVM");
    if (jvmDLL == NULL) {
        FreeLibrary(jvmDLL);
        cout << "加载JVM动态库错误" << endl;
        return false;
    }

    //创建JVM
    JNIEnv *env;
    JavaVM *jvm;
    jint jvmProc = (jvmProcAddress)(&jvm, (void **) &env, &vmInitArgs);
    if (jvmProc < 0 || jvm == NULL || env == NULL) {
        FreeLibrary(jvmDLL);
        cout << "创建JVM错误" << endl;
        return false;
    }

    //加载启动类
    jclass mainclass = env->FindClass(startClass);
    if (env->ExceptionCheck() == JNI_TRUE || mainclass == NULL) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        FreeLibrary(jvmDLL);
        cout << "加载启动类失败" << endl;
        return false;
    }

    //加载启动方法
    jmethodID methedID = env->GetStaticMethodID(mainclass, startMethod, "([Ljava/lang/String;)V");
    if (env->ExceptionCheck() == JNI_TRUE || methedID == NULL) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        FreeLibrary(jvmDLL);
        cout << "加载启动方法失败" << endl;
        cin >> pause;
        return false;
    }

    cout << "开始执行" << endl;
    env->CallStaticVoidMethod(mainclass, methedID, NULL);
    cout << "执行结束" << endl;

    //jvm释放
    jvm->DestroyJavaVM();
    return true;
}