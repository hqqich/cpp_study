#include <assert.h>
#include <iostream>
#include <sstream>
#include "leveldb/db.h"
#include "jni.h"
#include "windows.h"
#include "iostream"
#include <tchar.h>
#include "jni.h"
#include <libloaderapi.h>
#include "util/leveldb/levelDB.h"
#include "util/jvm/java8JVM.h"


using namespace std;


void setWinConsleUTF8() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL, "");
}

//int _tmain(int argc, _TCHAR *argv[]) {
//
////    levelDB();
//
//    startJVM();
//    return 0;
//}

int main() {

//    levelDB();

    startJVM();
    return 0;
}
