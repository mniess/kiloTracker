#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>

#define VIDEOLOC "VideoLocation"

class Settings {
 public:
  bool write(std::string filename) const;
  bool read(std::string filename);
  bool validate();

  std::string videoLoc;
};

#endif  // SETTINGS_HPP
