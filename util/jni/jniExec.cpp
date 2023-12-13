//
// Created by admin on 2023/12/13.
//

#include "jniExec.h"

#include <iostream>
#include "jni.h"
#include "windows.h"
#include <tchar.h>
#include <libloaderapi.h>


using namespace std;

typedef jint(JNICALL *JNICREATEPROC)(JavaVM **, void **, void *);


// 获取JNI相关的变量
void GetJNIEnvAndJavaVM(JNIEnv **pEnv, JavaVM **pVm) {
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

    //加载JVM,注意需要传入的字符串为LPCWSTR,指向一个常量Unicode字符串的32位指针，相当于const wchar_t*
    HINSTANCE jvmDLL = LoadLibrary(jvmPath);
    if (jvmDLL == NULL) {
        cout << "加载JVM动态库错误" << endl;
        return ;
    }

    //初始化jvm物理地址
    JNICREATEPROC jvmProcAddress = (JNICREATEPROC) GetProcAddress(jvmDLL, "JNI_CreateJavaVM");

    jint jvmProc = (jvmProcAddress)(pVm, (void **) pEnv, &vmInitArgs);
    if (jvmProc < 0 || *pVm == NULL || *pEnv == NULL) {
        FreeLibrary(jvmDLL);
        cout << "创建JVM错误" << endl;
    }
}


void test01() {

    JNIEnv *env;
    JavaVM *jvm;

    // 获取JNIEnv和JavaVM
    GetJNIEnvAndJavaVM(&env, &jvm);


    // ==== 下面获取File类
    // File类
    jclass fileClass = env->FindClass("java/io/File");
    // 构造函数
    jmethodID fileConstructor = env->GetMethodID(fileClass, "<init>", "(Ljava/lang/String;)V");
    if (fileConstructor == nullptr) {
        return;
    }

    // ==== 下面：String filePath = "./file.txt";
    jstring filePath = env->NewStringUTF("./file.txt");

    // ==== 下面：File fileObject = new File(filePath);
    jobject fileObject = env->NewObject(fileClass, fileConstructor, filePath);

    // // ==== 下面：boolean created = fileObject.createNewFile();
    jmethodID createNewFileMethod = env->GetMethodID(fileClass, "createNewFile", "()Z");
    if (createNewFileMethod == nullptr) {
        return;
    }
    jboolean created = env->CallBooleanMethod(fileObject, createNewFileMethod);
    if (created) {
        cout << "成功" << endl;
    } else {
        cout << "失败" << endl;
    }

    // 关闭 JVM
    jvm->DestroyJavaVM();
}