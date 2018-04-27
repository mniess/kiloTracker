#include <opencv2/imgproc.hpp>
#include <cv.hpp>
#include "Detector.h"

using cv::Mat;

Detector::Detector(Settings *settings) {
  this->settings = settings;
}

Mat Detector::createThresholdImage(Mat img) {
  Mat grayIMG, thresImg;

  cv::cvtColor(img, grayIMG, cv::COLOR_BGR2GRAY);
  cv::threshold(grayIMG, grayIMG, settings->minThreshold, 255, cv::THRESH_BINARY);
  cv::cvtColor(grayIMG, thresImg, cv::COLOR_GRAY2BGR);

  cv::bitwise_and(thresImg, img, thresImg);
  return thresImg;
}

Mat Detector::findRedBlobs(Mat rawImg) {
  Mat hsvImg, redImg, redLowImg, redHighImg;
  cv::cvtColor(rawImg, hsvImg, cv::COLOR_BGR2HSV);
  cv::inRange(hsvImg,
              cv::Scalar(settings->minRedHue, settings->minRedSat, settings->minRedVal),
              cv::Scalar(180, settings->maxRedSat, settings->maxRedVal),
              redLowImg);
  cv::inRange(hsvImg,
              cv::Scalar(1, settings->minRedSat, settings->minRedVal),
              cv::Scalar(settings->maxRedHue, settings->maxRedSat, settings->maxRedVal),
              redHighImg);
  cv::bitwise_or(redLowImg, redHighImg, redImg);
  return whiteNoiseCanceling(redImg);
}

Mat Detector::findBlueBlobs(Mat rawImg) {
  Mat hsvImg, blueImg;
  cv::cvtColor(rawImg, hsvImg, cv::COLOR_BGR2HSV);
  cv::inRange(hsvImg,
              cv::Scalar(settings->minBlueHue, settings->minBlueSat, settings->minBlueVal),
              cv::Scalar(settings->maxBlueHue, settings->maxBlueSat, settings->maxBlueVal),
              blueImg);
  return whiteNoiseCanceling(blueImg);
}

Mat Detector::whiteNoiseCanceling(Mat mat) {
  Mat c;
  cv::erode(mat, c, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2, 2)));
  cv::dilate(c, c, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2, 2)));
  cv::dilate(c, c, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2, 2)));
  cv::erode(c, c, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2, 2)));
  return c;
}

std::vector<std::vector<cv::Point>> Detector::findDots(Mat mat, Mat drawImg, cv::Scalar_<double> color) {
  std::vector<std::vector<cv::Point> > contours;
  std::vector<cv::Vec4i> hierarchy;
  //Find
  cv::findContours(mat, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
  //Draw
  if (!drawImg.empty()) {
    if (drawImg.size == mat.size) {
      for (int i = 0; i < contours.size(); i++) {
        drawContours(drawImg, contours, i, color, 1, cv::LINE_AA, hierarchy);
      }

    } else {
      std::cout << "Matrices not same Size! Will not draw on given image" << std::endl;
    }
  }
  return contours;
}