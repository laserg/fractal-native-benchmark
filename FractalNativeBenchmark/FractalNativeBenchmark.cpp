// FractalNativeBenchmark.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "FractalNativeBenchmark.h"
#include "com_epam_it_week_fractal_jni_Fractal.h"

#define RANGE 80
#define MAX 50
#define INDEX 0.01
#define RE_C 1.07
#define IM_C 0.0001

JNIEXPORT jobjectArray JNICALL Java_com_epam_it_1week_fractal_jni_Fractal_generate
(JNIEnv *env, jclass cls, jint w, jint h) {
	if (w < 0 || h < 0) {
		env->ThrowNew(env->FindClass("java/lang/IllegalArgumentException"),
			"The width or height can not be less than zero");
		return NULL;
	}
	int size = w * h;
	jobjectArray javaImage = env->NewObjectArray(size, env->FindClass("com/epam/it_week/fractal/jni/Point"), 0);
	Point *image = (Point*)malloc(sizeof(Point) * size);
	generate(image, w, h);
	for (int i = 0; i < size; ++i) {
		env->SetObjectArrayElement(javaImage, i, pointJavaWrap(env, image[i]));
	}
	free(image);
	return javaImage;
}

jobject pointJavaWrap(JNIEnv *env, Point p) {
	jclass pointCls = env->FindClass("com/epam/it_week/fractal/jni/Point");
	jmethodID pointClsCtr = env->GetMethodID(pointCls, "<init>", "(IIZ)V");
	return env->NewObject(pointCls, pointClsCtr, p.x, p.y, p.b);
}

void generate(Point* image, INT w, INT h) {
	const std::complex<double> constant(RE_C, IM_C);
	std::complex<double> z;
	double re_z, im_z;
	int k = 0;
	for (int x = -w / 2; x < w / 2; x++) {
		for (int y = -h / 2; y < h / 2; y++) {
			z.real(x * INDEX);
			z.imag(y * INDEX);
			re_z = fabs(z.real());
			im_z = fabs(z.imag());
			for (int i = 0; (re_z < RANGE || im_z < RANGE || abs(z) < RANGE) && i < MAX; i++) {
				z = pow(z, 3) + constant;
				re_z = fabs(z.real());
				im_z = fabs(z.imag());
			}
			image[k] = { x + w / 2, y + h / 2, re_z < MAX || im_z < MAX * 50 ? false : true };
			k++;
		}
	}
}