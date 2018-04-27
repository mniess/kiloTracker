#include <iostream>
#include <vector>
#include <fstream>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"

#include "Settings.h"
#include "Gui.h"
#include "Cli.h"

using std::cout;
using std::endl;
using std::string;

int main(int argc, char **argv) {
  const std::string keys = "{help h usage ? || Show this message}"
                           "{@settingsFile| settings.jaml| Path to settings file}"
                           "{nogui||Run without gui}"
                           "{v video|| Path to video, overrides value in settings file}";
  cv::CommandLineParser parser(argc, reinterpret_cast<const char *const *>(argv), keys);
  parser.about("KiloTracker v1.0\nKeyboard control:\n\t'S' for Start\n\t'P' for Pause\n\t'ESC' to exit");
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

  if (!settingsLoaded) {
    cout << "writing new settings file to " << settingsPath << endl;
  }

  if (parser.has("video")) {
    string loc = parser.get<string>("video");
    settings.videoLoc = loc;
  }

  if (parser.has("nogui")) {
    Cli cli(&settings);
    cli.start();
  } else {
    Gui gui(&settings);
    gui.start();
    settings.write(settingsPath);
  }
  return 0;
}
