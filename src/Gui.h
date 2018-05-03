#ifndef GUI_H
#define GUI_H

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include "Settings.h"
#include "Detector.h"

/**
 * Graphical user interface, persisting of 4 Windows.
 * Threshold: to get the inital filtering right
 * Red/Blue: for detecting Red and blue Dots
 * Image: Source image with drawn markers and traces
 */
class Gui {
public:
  Gui(Settings *settings);
  void start();

  /*
   * Handle mouse clicks on "Image" Window
   */
  void mouseClick(int event, int x, int y);
private:
  Settings *settings;
  std::vector<std::vector<cv::Point>> traces;
  // With pause: no new frames are loaded; detection is enabled; tracing is disabled
  bool pause = true;

  int traceA = -1;
  int traceB = -1;

  /**
   * Key events: S for Start, P for Pause, ESC for Quit
   * @return quit
   */
  bool keyEvents();

  /**
   * Just call mouseClick(), to overcome static restrictions
   */
  static void mouseCallback(int event, int x, int y, int flags, void *userdata);

  /**
   * Turn BGR into BGR
   * @param hsvColor
   * @return bgrColor
   */
  cv::Scalar HSV2BGR(const cv::Scalar &hsvColor) const;

  int getClosestTrace(cv::Point lastMouseClick);
};

#endif  // GUI_H
