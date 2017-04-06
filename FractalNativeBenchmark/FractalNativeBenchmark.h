#pragma once
#include <jni.h>

#ifndef FRACTALNATIVEBENCHMARK_API
#define FRACTALNATIVEBENCHMARK_API

struct Point {
	INT x, y;
	BOOLEAN b;
};

jobject pointJavaWrap(JNIEnv *env, Point p);

#ifdef __cplusplus
extern "C" {
#endif
	JNIEXPORT void generate(Point* image, INT w, INT h);
#ifdef __cplusplus
}
#endif
#endif