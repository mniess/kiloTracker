# kiloTracker

Was made for tracking and tracing kilobots on a video from overhead camera, but can be used for general tracking/tracing red and blue dots.

Only tested with linux

## Dependencies

 1. opencv

## Compile

Use provided cmake file to compile.

Suggested workflow on linux:
  1. `cd [git source]`
  1. `mkdir build`
  1. `cd build`
  1. `cmake ..`
  1. `make`
  1. Execute with `./kiloTracker`

## Usage

See `kiloTracker --help`

### GUI
Press 's' for start
Press 'p' for pause
Press 'esc' to quit and safe current parameters to settings file
