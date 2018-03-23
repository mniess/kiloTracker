#include <iostream>
#include <vector>
#include <fstream>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"

#include "Settings.hpp"
#include "Gui.hpp"

using std::cout;
using std::endl;
using std::string;

int main(int argc, char **argv) {
  const std::string keys = "{help h usage ? || Show this message}"
      "{@settingsFile| settings.jaml| Path to settings file}"
      "{nogui||Run without gui}"
      "{v video|| Path to video, overrides value in settings file}";
  cv::CommandLineParser parser(argc, reinterpret_cast<const char *const *>(argv), keys);
  parser.about("KiloTracker v1.0");
  if (parser.has("help")) {
    parser.printMessage();
    return 0;
  }

  Settings settings;
  string settingsPath = parser.get<string>("@settingsFile");
  bool settingsLoaded = settings.read(settingsPath);
  if (!(settingsLoaded || parser.has("video"))) {
    cout << "Please provide a settings file with VideoLocation or give a video path" << endl;
    parser.printMessage();
    return 0;
  }

  if(!settingsLoaded) {
    cout << "writing new settings file to " << settingsPath << endl;
  }

  if (parser.has("video")) {
    string loc = parser.get<string>("video");
    settings.videoLoc = loc;
  }

  if (parser.has("nogui")) {
    Processor p = Processor(&settings);
    cv::VideoCapture cap = cv::VideoCapture(settings.videoLoc);
    cv::Mat m, thres;

    std::string filename = settings.videoLoc;
    int last = filename.find_last_of("/");
    filename.replace(last, filename.length() - last, "/counts.csv");
    std::cout << filename << std::endl;
    std::ofstream logger;
    logger.open(filename);
    logger << "Blue, Red\n";

    int i = 0;
    while (cap.read(m)) {
      thres = p.createThresholdImage(m);
      cv::Mat b = p.findBlueBlobs(thres);
      unsigned long blueDots = p.findDots(b).size();
      unsigned long redDots = p.findDots(p.findRedBlobs(thres)).size();
      logger << blueDots << ", " << redDots << "\n";
      ++i;
      if (i % 100 == 0) {
        std::cout << i << " Frames processed" << std::endl;
        logger.flush();
      }
    }
    logger.close();
  } else {
    Gui gui(&settings);
    gui.start();
    settings.write(settingsPath);
  }
  return 0;
}
