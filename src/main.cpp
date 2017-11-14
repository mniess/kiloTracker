#include <iostream>
#include <string>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include "Settings.hpp"

using namespace cv;

using std::cout;
using std::endl;
using std::string;

void help(char** argv) {
  cout << "no help. TODO";
}

int main(int argc, char** argv) {
  cv::CommandLineParser parser(argc, argv, "{@input||}{help h ||}");
  if (parser.has("help")) {
    help(argv);
    return 0;
  }
  string filename = parser.get<string>("@input");

  Settings settings;

  if (!filename.empty()) {
    if (!settings.read(filename)) {
      help(argv);
      return 1;
    }
    cout << settings.videoLoc << endl;
  }
  VideoCapture cap(settings.videoLoc);

  Mat imgTmp;
  cap.read(imgTmp);

  imshow("Test", imgTmp);
  waitKey(0);
  return 0;
}
