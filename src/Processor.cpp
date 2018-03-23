#include <opencv2/imgproc.hpp>
#include <cv.hpp>
#include "Processor.h"

using cv::Mat;
using std::cout;
using std::endl;

Processor::Processor(Settings *settings) {
  pSettings = settings;
}

Mat Processor::createThresholdImage(Mat img) {
  Mat grayIMG, thresImg;

  cv::cvtColor(img, grayIMG, cv::COLOR_BGR2GRAY);
  cv::threshold(grayIMG, grayIMG, pSettings->minThreshold, 255, cv::THRESH_BINARY);
  cv::cvtColor(grayIMG, thresImg, cv::COLOR_GRAY2BGR);

  cv::bitwise_and(thresImg,img,thresImg);
  return thresImg;
}

Mat Processor::findRedBlobs(Mat rawImg) {
  Mat hsvImg, redImg, redLowImg, redHighImg;
  cv::cvtColor(rawImg, hsvImg, cv::COLOR_BGR2HSV);
  cv::inRange(hsvImg,
              cv::Scalar(pSettings->minRedHue, pSettings->minRedSat, pSettings->minRedVal),
              cv::Scalar(180, pSettings->maxRedSat, pSettings->maxRedVal),
              redLowImg);
  cv::inRange(hsvImg,
              cv::Scalar(1, pSettings->minRedSat, pSettings->minRedVal),
              cv::Scalar(pSettings->maxRedHue, pSettings->maxRedSat, pSettings->maxRedVal),
              redHighImg);
  cv::bitwise_or(redLowImg, redHighImg, redImg);
  return whiteNoiseCanceling(redImg);
}

Mat Processor::findBlueBlobs(Mat rawImg) {
  Mat hsvImg, blueImg;
  cv::cvtColor(rawImg, hsvImg, cv::COLOR_BGR2HSV);
  cv::inRange(hsvImg,
              cv::Scalar(pSettings->minBlueHue, pSettings->minBlueSat, pSettings->minBlueVal),
              cv::Scalar(pSettings->maxBlueHue, pSettings->maxBlueSat, pSettings->maxBlueVal),
              blueImg);
  return whiteNoiseCanceling(blueImg);
}

Mat Processor::whiteNoiseCanceling(cv::Mat mat) {
  cv::Mat c;
  cv::erode(mat, c, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2, 2)));
  cv::dilate(c, c, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2, 2)));
  cv::dilate(c, c, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2, 2)));
  cv::erode(c, c, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2, 2)));
  return c;
}

std::vector<std::vector<cv::Point>> Processor::findDots(cv::Mat mat, cv::Mat drawImg, cv::Scalar_<double> color) {
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
      cout << "Matrices not same Size! Will not draw on given image" << endl;
    }
  }
  return contours;
}
