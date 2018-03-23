#include "Settings.hpp"

using std::string;
using cv::FileStorage;
using cv::FileNode;

Settings::Settings() {
}

bool Settings::write(string filename) const {
  FileStorage fs(filename, FileStorage::WRITE);
  if (!fs.isOpened()) {
    return false;
  }
  fs << VIDEOLOC << videoLoc;
  fs << WANTEDDOTS << wantedDots;
  fs << MINTHRESHOLD << minThreshold;
  fs << MAXTHRESHOLD << maxThreshold;
  fs << MINBLUEHUE << minBlueHue;
  fs << MAXBLUEHUE << maxBlueHue;
  fs << MINBLUESAT << minBlueSat;
  fs << MAXBLUESAT << maxBlueSat;
  fs << MINBLUEVAL << minBlueVal;
  fs << MAXBLUEVAL << maxBlueVal;
  fs << MINREDHUE << minRedHue;
  fs << MAXREDHUE << maxRedHue;
  fs << MINREDSAT << minRedSat;
  fs << MAXREDSAT << maxRedSat;
  fs << MINREDVAL << minRedVal;
  fs << MAXREDVAL << maxRedVal;
  fs.release();
  return true;
}

bool Settings::read(string filename) {
  FileStorage fs(filename, FileStorage::READ);
  if (!fs.isOpened()) {
    return false;
  }

  fs[VIDEOLOC] >> videoLoc;
  fs[WANTEDDOTS] >> wantedDots;
  fs[MINTHRESHOLD] >> minThreshold;
  fs[MAXTHRESHOLD] >> maxThreshold;
  fs[MINREDHUE] >> minRedHue;
  fs[MAXREDHUE] >> maxRedHue;
  fs[MINREDSAT] >> minRedSat;
  fs[MAXREDSAT] >> maxRedSat;
  fs[MINREDVAL] >> minRedVal;
  fs[MAXREDVAL] >> maxRedVal;
  fs[MINBLUEHUE] >> minBlueHue;
  fs[MAXBLUEHUE] >> maxBlueHue;
  fs[MINBLUESAT] >> minBlueSat;
  fs[MAXBLUESAT] >> maxBlueSat;
  fs[MINBLUEVAL] >> minBlueVal;
  fs[MAXBLUEVAL] >> maxBlueVal;
  fs.release();
  return true;
}