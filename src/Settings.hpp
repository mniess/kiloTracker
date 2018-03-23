#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <opencv2/features2d.hpp>

#include <string>
#include <iostream>

#define VIDEOLOC "VideoLocation"
#define WANTEDDOTS "wantedDots"

#define MINTHRESHOLD "minThreshold"
#define MAXTHRESHOLD "maxThreshold"

#define MINBLUEHUE "minBlueHue"
#define MAXBLUEHUE "maxBlueHue"
#define MINBLUESAT "minBlueSat"
#define MAXBLUESAT "maxBlueSat"
#define MINBLUEVAL "minBlueVal"
#define MAXBLUEVAL "maxBlueVal"

#define MINREDHUE "minRedHue"
#define MAXREDHUE "maxRedHue"
#define MINREDSAT "minRedSat"
#define MAXREDSAT "maxRedSat"
#define MINREDVAL "minRedVal"
#define MAXREDVAL "maxRedVal"

class Settings {
public:
  Settings();

  bool write(std::string filename) const;

  bool read(std::string filename);

  std::string videoLoc;
  int wantedDots;
  int minThreshold;
  int maxThreshold;
  int minBlueHue;
  int maxBlueHue;
  int minBlueSat;
  int maxBlueSat;
  int minBlueVal;
  int maxBlueVal;
  int minRedHue;
  int maxRedHue;
  int minRedSat;
  int maxRedSat;
  int minRedVal;
  int maxRedVal;
private:
};

#endif  // SETTINGS_HPP
