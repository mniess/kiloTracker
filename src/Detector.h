#ifndef KILOTRACKER_PROCESSOR_H
#define KILOTRACKER_PROCESSOR_H

#include "Settings.h"

class Detector {

public:
  Detector(Settings *settings);
  cv::Mat createThresholdImage(cv::Mat img);
  cv::Mat findRedBlobs(cv::Mat rawImg);
  cv::Mat findBlueBlobs(cv::Mat mat);
  std::vector<std::vector<cv::Point>> findDots(cv::Mat anaMat,
                                               cv::Mat drawMat = cv::Mat(),
                                               cv::Scalar_<double> color = cv::Scalar(255, 0, 0));
private:
  Settings *settings;
  cv::Mat whiteNoiseCanceling(cv::Mat mat);
};

#endif //KILOTRACKER_PROCESSOR_H
