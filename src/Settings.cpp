#include "Settings.hpp"

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>

#include <string>

using std::string;
using cv::FileStorage;
using cv::FileNode;

bool Settings::write(string filename) const {
  FileStorage fs(filename, FileStorage::WRITE);
  if (!fs.isOpened()) {
    return false;
  }
  fs << VIDEOLOC  << videoLoc;
  fs.release();
  return true;
}

bool Settings::read(string filename) {
  FileStorage fs(filename, FileStorage::READ);
  if (!fs.isOpened()) {
    return false;
  }

  fs[VIDEOLOC] >> videoLoc;
  fs.release();
  return true;
}

bool Settings::validate() {
  return true;
}
