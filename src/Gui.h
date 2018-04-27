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

private:
  Settings *settings;

  // With pause, the current image is processed over and over again
  bool pause = true;

  /**
   * Key events: S for Start, P for Pause, ESC for Quit
   * @return quit
   */
  bool keyEvents();
   /**
    * Turn BGR into BGR
    * @param hsvColor
    * @return bgrColor
    */
  cv::Scalar HSV2BGR(const cv::Scalar &hsvColor) const;
};

#endif  // GUI_H
