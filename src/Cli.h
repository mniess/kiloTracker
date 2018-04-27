
#ifndef KILOTRACKER_CLI_H
#define KILOTRACKER_CLI_H

#include "Settings.h"
#include "Tracer.h"

/**
 * Command-line interface; processes the whole video and logs results to same folder as the video
 */
class Cli {
public:
  Cli(Settings *settings);
  void start();

private:
  Settings *settings;

  /**
   * Get path+filename of video location to put output there
   * @param filename the name of the new file
   * @return path+filename or only filename, if video is in current folder
   */
  std::string getFilepath(std::string filename) const;
};

#endif //KILOTRACKER_CLI_H
