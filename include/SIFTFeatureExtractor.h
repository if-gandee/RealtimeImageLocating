#pragma once
#include <iostream>
#include "ImageWithFeature.h"


namespace imgregionloc {

	class SIFTFeatureExtractor
	{

	private:
		cv::Mat m_image;
		cv::Mat m_image_internal;
		float m_maxlen;
		float scale_factor;

		ImageWithFeaturePtr m_image_with_feature;
		cv::Ptr<cv::SIFT> m_extractor;
		SIFTExtractorParam m_init_param;
		

	public:
		SIFTFeatureExtractor() :m_image_with_feature(new ImageWithFeature) {
			init_with_params(m_init_param);
		}
		void set_image(const cv::Mat& img);
		void init_with_params(const SIFTExtractorParam& p);
		void process_keypoint();
		void process_feature();
		void process_keypoint_and_feature();
		void set_keypoints(const std::vector<cv::KeyPoint>& input_kps, const cv::Mat& input_desc);
		void get_image_with_feature(ImageWithFeaturePtr& image_with_feature) const;
		ImageWithFeaturePtr get_image_with_feature() const;


		float m_scale_factor;

		cv::Mat get_internal_image() const {
			return m_image_internal;
		}

	};

	using SIFTFeatureExtractorPtr = std::shared_ptr<SIFTFeatureExtractor>;
}

