# kiloTracker

Was made for tracking kilobots on a video from overhead camera, but can be used for a general tracking red and blue dots.

Only tested with linux

## Dependencies

 1. opencv

## Compile

Use cmake and make to compile. Suggested workflow on linux:
  1. `cd [git source]`
  1. `mkdir build`
  1. `cd build`
  1. `cmake ..`
  1. `make`
  1. Execute with `./kiloTracker`

## Usage

See `kiloTracker --help`

### GUI

Use key 's' for start and 'p' for pause. 'esc' closes all windows and safes current parameters to settings file
