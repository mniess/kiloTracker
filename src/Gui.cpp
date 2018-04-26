#include "Gui.hpp"
#include "Tracer.h"

#include <opencv2/highgui.hpp>  // GUI
#include <opencv2/imgproc.hpp>

#define RED cv::Scalar(0, 0, 255)
#define BLUE cv::Scalar(255, 0, 0)
#define YELLOW cv::Scalar(0, 255, 255)
#define GREEN cv::Scalar(0, 255, 0)

using std::string;
using std::cout;
using std::endl;
using cv::Mat;

struct Center {
  cv::Point2d location;
  double radius;
  double confidence;
};

Gui::Gui(Settings *set) {

  settings = set;
  cap = cv::VideoCapture(settings->videoLoc);

  cv::namedWindow("Image", CV_WINDOW_AUTOSIZE);
  cv::namedWindow("Red", CV_WINDOW_AUTOSIZE);
  cv::namedWindow("Blue", CV_WINDOW_AUTOSIZE);
  cv::namedWindow("Threshold", CV_WINDOW_AUTOSIZE);

  cv::createTrackbar("minH", "Red", &(*settings).minRedHue, 180);
  cv::createTrackbar("maxH", "Red", &(*settings).maxRedHue, 180);
  cv::createTrackbar("minS", "Red", &(*settings).minRedSat, 255);
  cv::createTrackbar("maxS", "Red", &(*settings).maxRedSat, 255);
  cv::createTrackbar("minV", "Red", &(*settings).minRedVal, 255);
  cv::createTrackbar("maxV", "Red", &(*settings).maxRedVal, 255);
  cv::createTrackbar("minH", "Blue", &(*settings).minBlueHue, 180);
  cv::createTrackbar("maxH", "Blue", &(*settings).maxBlueHue, 180);
  cv::createTrackbar("minS", "Blue", &(*settings).minBlueSat, 255);
  cv::createTrackbar("maxS", "Blue", &(*settings).maxBlueSat, 255);
  cv::createTrackbar("minV", "Blue", &(*settings).minBlueVal, 255);
  cv::createTrackbar("maxV", "Blue", &(*settings).maxBlueVal, 255);

  cv::createTrackbar("minThreshold", "Threshold", &(*settings).minThreshold, 255);

  params.filterByArea = true;
  params.filterByCircularity = true;

  processor = Processor(settings);
}

void Gui::start() {
  int currFrame;
  Mat rawImg;
  Mat marksImg;
  Mat thresImg;
  std::vector<cv::KeyPoint> keypoints;

  Tracer tracer(settings);

  if (!(cap.isOpened() && cap.read(rawImg))) {
    std::cout << "Could not get Img from capture!" << std::endl;
    return;
  }

  while (true) {
    marksImg = rawImg.clone();

    //THRESHOLD
    thresImg = processor.createThresholdImage(rawImg);
    if (!thresImg.empty()) {
      cv::imshow("Threshold", thresImg);
    } else {
      std::cout << "ThresImg is Empty!" << std::endl;
    }

    //RED
    Mat redImg = processor.findRedBlobs(thresImg);
    cv::imshow("Red", redImg);

    std::vector<std::vector<cv::Point> > redContours = processor.findDots(redImg, marksImg, GREEN);
    int redDots = redContours.size();

    //BLUE
    Mat blueImg = processor.findBlueBlobs(thresImg);
    cv::imshow("Blue", blueImg);

    std::vector<std::vector<cv::Point> > blueContours = processor.findDots(blueImg, marksImg, YELLOW);
    int blueDots = blueContours.size();

    //Tracing
    redContours.insert(redContours.end(), blueContours.begin(), blueContours.end());
    tracer.processNewContours(redContours, currFrame++);
    std::vector<std::vector<cv::Point>> traces = tracer.getcurrPointTraces();
    std::cout << traces.size() << std::endl;
    for (int i = 0; i <traces.size(); ++i) {
      Mat rgb;
      Mat hsv(1,1, CV_8UC3, cv::Scalar(i*31 %180,255,255));
      cvtColor(hsv, rgb, CV_HSV2BGR);
      cv::polylines(marksImg,traces[i],false,cv::Scalar(rgb.data[0], rgb.data[1], rgb.data[2]));
    }
    //Final Image
    cv::imshow("Image", marksImg);

    //Output
    std::ostringstream text;
    text << "Blue: " << blueDots << ", Red:" << redDots;
    int diff = blueDots + redDots - settings->wantedDots;
    if (diff != 0) {
      text << " DIFF: " << diff;
    }
    cout << text.str() << endl;

    //Load next Image
    if (!pause) {
      if (!cap.read(rawImg)) {
        std::cout << "Could not get Img from capture!" << std::endl;
        return;
      }
    }

    if (keyEvents())
      break;
  }
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
