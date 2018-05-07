#include "Settings.h"

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
  fs << MAXTRACEDIST << maxTraceDist;

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
  fs[MAXTRACEDIST] >> maxTraceDist;

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

  if(maxTraceDist == 0) {
    std::cout << "Warning: Tracing disabled! maxTraceDist==0" << std::endl;
  }
  return true;
}