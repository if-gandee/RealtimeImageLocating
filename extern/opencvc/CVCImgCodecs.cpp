//
//  CVCImgCodecs.cpp
//  OpenCV-C
//
//  Created by Gerrit Goossen on 5/24/21.
//  Copyright (c) 2021 Gamma Ray Digital, Inc. All rights reserved.
//

#include <opencv2/opencv.hpp>
#include "OpenCVC.h"
#include "CVCPrivate.h"

CVCMat CVCimread(const char* filename, int flags)
{
	try {
		cv::Mat image = cv::imread(filename, flags);
		if (image.data != NULL) {
			cv::Mat *returnImage = new cv::Mat(image);
			return (CVCMat)returnImage;
		}
	} catch (...) { }

	return NULL;
}
/*
bool CVCimreadmulti(const char* filename, CV_OUT std::vector<Mat>& mats, int flags)
{
}
*/
bool CVCimwrite(const char* filename, CVCMat img, const int* params, int paramCount)
{
	// convert the parameters
	std::vector<int> cvParams;
	for (int c = 0; c < paramCount; c++) {
		cvParams.push_back(params[c]);
	}

	return cv::imwrite(filename, CVCMatRef(img), cvParams);
}

void CVCimdecodeMat(char* buf, int n_byte, int flags, CVCMat dst){
	auto& _dst = *(cv::Mat*)dst;

	cv::imdecode(cv::Mat(1,n_byte, CV_8UC1, buf), flags, &_dst);
}

CVC_EXPORT void CVCimencodeMat(const char* ext, CVCMat src, CVCMat dst, int* params, int n_param)
{
	auto& _src = *(cv::Mat*)src;
	auto& _dst = *(cv::Mat*)dst;
	std::vector<int> cvParams;
	if(params && n_param>0)
		cvParams = std::vector<int>(params, params+n_param);
	std::vector<uchar> _out;
	cv::imencode(ext, _src, _out, cvParams);
	cv::Mat(1, _out.size(), CV_8UC1, _out.data()).copyTo(_dst);
}
/*
bool CVCimwritemulti(const char *filename, InputArrayOfArrays img, const std::vector<int>& params = std::vector<int>())
{
}
*/
CVCMat CVCimdecode(CVCUCharVector buf, int flags)
{
	CVCMat mat = CVCMatCreate();
	CVCMatRef(mat) = cv::imdecode(CVCUCharVectorRef(buf), flags);
	return mat;
}

/*
CVCMat CVCimdecode(CVCMat buf, int flags, CVCMat dst);
{
}
 */

bool CVCimencode(const char* ext, CVCMat img, CVCUCharVector buf, CVCIntVector params)
{
	return cv::imencode(ext, CVCMatRef(img), CVCUCharVectorRef(buf), CVCIntVectorRef(params));
}

bool CVChaveImageReader(const char* filename)
{
	return cv::haveImageReader(filename);
}

bool CVChaveImageWriter(const char* filename)
{
	return cv::haveImageWriter(filename);
}
