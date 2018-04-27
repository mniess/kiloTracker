
#include <opencv2/videoio.hpp>
#include <fstream>
#include "Cli.h"
#include "Detector.h"

Cli::Cli(Settings *settings) {
  this->settings = settings;
}

void Cli::start() {
  Detector detector(settings);
  Tracer tracer(settings);
  cv::VideoCapture cap(settings->videoLoc);
  cv::Mat m, thres;

  std::ofstream counts;
  counts.open(getFilepath("counts.csv"));
  counts << "Blue, Red\n";

  int i;
  while (cap.read(m)) {
    //Detect
    thres = detector.createThresholdImage(m);
    std::vector<std::vector<cv::Point>> contours = detector.findDots(detector.findBlueBlobs(thres));
    std::vector<std::vector<cv::Point>> redContours = detector.findDots(detector.findRedBlobs(thres));

    //Counts
    unsigned long blueDots = contours.size();
    unsigned long redDots = redContours.size();
    counts << blueDots << ", " << redDots << "\n";

    //Trace
    contours.insert(contours.end(), redContours.begin(), redContours.end());
    tracer.processNewContours(contours, i);

    //Status
    if (i % 100 == 0) {
      std::cout << i << " Frames processed" << std::endl;
    }
    i++;
  }
  writeTraces(tracer);
  counts.close();
  std::cout << "Finished. Last Frame was " << i << std::endl;
}

void Cli::writeTraces(Tracer tracer) {
  std::ofstream traceLog;
  traceLog.open(getFilepath("trace.csv"));

  for(auto &trace:tracer.getTraces()) {
    for(auto tracepoint:trace) {
      traceLog << tracepoint.p.x << "," << tracepoint.p.y << "," << tracepoint.frame << "; ";
    }
    traceLog << std::endl;
  }

  traceLog.close();
}

std::string Cli::getFilepath(std::string filename) const {
  std::string filePath = settings->videoLoc;
  int last = filePath.find_last_of("/");
  if (last < 0) { //No absolute path
    filePath = filename;
  } else {
    filePath.replace(last, filePath.length() - last, "/" + filename);
  }
  std::cout << filePath << std::endl;
  return filePath;
}