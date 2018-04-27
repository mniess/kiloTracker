#ifndef SETTINGS_H
#define SETTINGS_H

#include <opencv2/features2d.hpp>

#include <string>
#include <iostream>

#define VIDEOLOC "VideoLocation"
#define WANTEDDOTS "wantedDots"
#define MAXTRACEDIST "maxTraceDist"

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


/**
 * Read and write all settings, no getters for values
 */
class Settings {
public:
  Settings();

  bool write(std::string filename) const;

  bool read(std::string filename);

  // Path to the videolocation
  std::string videoLoc;
  // how many dots should be in the image?
  int wantedDots;
  // look in the radius of maxTraceDist for the last point, zero to disable
  int maxTraceDist;

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

#endif  // SETTINGS_H
