
#include <opencv2/videoio.hpp>
#include <fstream>
#include "Cli.h"
#include "Settings.h"
#include "Detector.h"
#include "Tracer.h"

Cli::Cli(Settings *settings) {
  this->settings = settings;
}

void Cli::start() {
  Detector detector = Detector(settings);
  cv::VideoCapture cap = cv::VideoCapture(settings->videoLoc);
  cv::Mat m, thres;

  std::ofstream logger;
  logger.open(getFilepath("counts.csv"));
  logger << "Blue, Red\n";

  int i = 0;
  while (cap.read(m)) {
    thres = detector.createThresholdImage(m);
    cv::Mat b = detector.findBlueBlobs(thres);
    unsigned long blueDots = detector.findDots(b).size();
    unsigned long redDots = detector.findDots(detector.findRedBlobs(thres)).size();
    logger << blueDots << ", " << redDots << "\n";
    ++i;
    if (i % 100 == 0) {
      std::cout << i << " Frames processed" << std::endl;
    }
  }
  logger.close();
}

std::string Cli::getFilepath(std::string filename) const {
  std::string filePath = settings->videoLoc;
  int last = filePath.find_last_of("/");
  if (last < 0) { //No absolute path
    filePath = filename;
  } else {
    filePath.replace(last, filePath.length() - last, "/"+filename);
  }
  std::cout << filePath << std::endl;
  return filePath;
}