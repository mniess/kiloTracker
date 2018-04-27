#include "Gui.h"
#include "Tracer.h"

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#define RED cv::Scalar(0, 0, 255)
#define BLUE cv::Scalar(255, 0, 0)
#define YELLOW cv::Scalar(0, 255, 255)
#define GREEN cv::Scalar(0, 255, 0)

using std::string;
using cv::Mat;

Gui::Gui(Settings *set) {

  settings = set;

  cv::namedWindow("Image", CV_WINDOW_AUTOSIZE);
  cv::namedWindow("Threshold", CV_WINDOW_AUTOSIZE);
  cv::namedWindow("Blue", CV_WINDOW_AUTOSIZE);
  cv::namedWindow("Red", CV_WINDOW_AUTOSIZE);

  cv::createTrackbar("minThreshold", "Threshold", &(*settings).minThreshold, 255);

  cv::createTrackbar("minH", "Blue", &(*settings).minBlueHue, 180);
  cv::createTrackbar("maxH", "Blue", &(*settings).maxBlueHue, 180);
  cv::createTrackbar("minS", "Blue", &(*settings).minBlueSat, 255);
  cv::createTrackbar("maxS", "Blue", &(*settings).maxBlueSat, 255);
  cv::createTrackbar("minV", "Blue", &(*settings).minBlueVal, 255);
  cv::createTrackbar("maxV", "Blue", &(*settings).maxBlueVal, 255);

  cv::createTrackbar("minH", "Red", &(*settings).minRedHue, 180);
  cv::createTrackbar("maxH", "Red", &(*settings).maxRedHue, 180);
  cv::createTrackbar("minS", "Red", &(*settings).minRedSat, 255);
  cv::createTrackbar("maxS", "Red", &(*settings).maxRedSat, 255);
  cv::createTrackbar("minV", "Red", &(*settings).minRedVal, 255);
  cv::createTrackbar("maxV", "Red", &(*settings).maxRedVal, 255);
}

void Gui::start() {
  int currFrame;
  Mat rawImg, marksImg, thresImg, redImg, blueImg;
  std::vector<cv::KeyPoint> keypoints;
  std::vector<std::vector<cv::Point>> traces;
  cv::VideoCapture cap(settings->videoLoc);
  Tracer tracer(settings);
  Detector detector(settings);

  if (!(cap.isOpened() && cap.read(rawImg))) {
    std::cout << "Could not get Img from capture!" << std::endl;
    return;
  }

  while (true) {
    marksImg = rawImg.clone();

    //THRESHOLD
    thresImg = detector.createThresholdImage(rawImg);
    if (!thresImg.empty()) {
      cv::imshow("Threshold", thresImg);
    } else {
      std::cout << "ThresImg is Empty!" << std::endl;
    }

    //RED
    redImg = detector.findRedBlobs(thresImg);
    cv::imshow("Red", redImg);

    std::vector<std::vector<cv::Point> > redContours = detector.findDots(redImg, marksImg, GREEN);
    int redDots = redContours.size();

    //BLUE
    blueImg = detector.findBlueBlobs(thresImg);
    cv::imshow("Blue", blueImg);

    std::vector<std::vector<cv::Point> > blueContours = detector.findDots(blueImg, marksImg, YELLOW);
    int blueDots = blueContours.size();

    //Tracing
    if (!pause) {
      redContours.insert(redContours.end(), blueContours.begin(), blueContours.end());
      tracer.processNewContours(redContours, currFrame++);
      traces = tracer.getPointTraces();
    }

    for (int i = 0; i < traces.size(); ++i) {
      cv::polylines(marksImg, traces[i], false, HSV2BGR(cv::Scalar(i * 31 % 180, 255, 255)));
    }

    //Final Image
    cv::imshow("Image", marksImg);

    //Output
    int diff = blueDots + redDots - settings->wantedDots;
    std::cout << "Blue: " << blueDots << ", Red:" << redDots;
    if (diff != 0) {
      std::cout << "-> Diff: " << diff;
    }
    std::cout << std::endl;

    //Load next Image
    if (!pause) {
      if (!cap.read(rawImg)) {
        std::cout << "Video finished!" << std::endl;
        return;
      }
    }

    if (keyEvents()) {
      break;
    }
  }
}

cv::Scalar Gui::HSV2BGR(const cv::Scalar &hsvColor) const {
  Mat rgb, hsv(1, 1, CV_8UC3, hsvColor);
  cvtColor(hsv, rgb, CV_HSV2BGR);
  return cv::Scalar(rgb.data[0], rgb.data[1], rgb.data[2]);
}

bool Gui::keyEvents() {
  int key = cv::waitKey(30);
  if (key == 27) { // esc
    return true;
  }
  if (key == 'p') {
    pause = true;
  }
  if (key == 's') {
    pause = false;
  }
  return false;
}
