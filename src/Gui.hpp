#ifndef GUI_HPP
#define GUI_HPP

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include "Settings.hpp"
#include "Processor.h"

class Gui {
public:
  Gui(Settings *settings);

  void start();

private:
  Processor processor = Processor(nullptr);
  Settings *settings;

  bool pause = true;
  cv::VideoCapture cap;
  cv::SimpleBlobDetector::Params params;

  bool keyEvents();
};

#endif  // GUI_HPP
