#include <jni.h>
#include <string>
#include <dlib/external/libjpeg/jpeglib.h>
#include "dlib/image_processing/frontal_face_detector.h"
#include "dlib/image_io.h"
#include <iostream>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <android/log.h>
#include <dlib/opencv/cv_image.h>

#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,"native-lib",__VA_ARGS__)
using namespace dlib;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_orange_opencv_MainActivity_stringFromJNI(JNIEnv *env, jobject) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_orange_opencv_MainActivity_loadJpeg(JNIEnv *env, jobject instance, jlong native_addr) {


    frontal_face_detector detector = get_frontal_face_detector();
    cv::Mat *src = &(*((cv::Mat *) native_addr));
    cv::Mat temp;
    cv::cvtColor(*src, temp, CV_BGR2GRAY);
    cv_image<unsigned char> cimg(temp);

    std::vector<rectangle> dets = detector(cimg, 0);
    for (unsigned long j = 0; j < dets.size(); ++j) {
        cv::Rect rect =  cv::Rect(dets[j].left(), dets[j].top(), dets[j].width(), dets[j].height());
        cv::rectangle(*src, rect, cv::Scalar(255, 255, 255));
    }
    LOGW(" dets size = %d", dets.size());
}