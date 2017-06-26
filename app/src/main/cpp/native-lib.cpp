#include <jni.h>
#include <string>
#include "dlib/image_processing/frontal_face_detector.h"
#include "dlib/image_io.h"
#include <android/log.h>
#include <include/opencv2/core.hpp>

#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,"native-lib",__VA_ARGS__)
using namespace dlib;
using namespace cv;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_orange_opencv_MainActivity_stringFromJNI(JNIEnv *env, jobject) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_orange_opencv_MainActivity_loadJpeg(JNIEnv *env, jobject instance, jstring path_) {
    clock_t start, finish;
    start = clock();
    const char *path = env->GetStringUTFChars(path_, NULL);
    frontal_face_detector detector = get_frontal_face_detector();
    array2d<unsigned char> img;
    load_image(img, path);
    pyramid_up(img);

    std::vector<rectangle> dets = detector(img,0);
    finish = clock();
    LOGW(" spend = %d", ((finish - start)/ CLOCKS_PER_SEC));
    env->ReleaseStringUTFChars(path_, path);
    LOGW(" dets size = %d", dets.size());

}