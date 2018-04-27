#ifndef KILOTRACKER_TRACER_H
#define KILOTRACKER_TRACER_H

#include "Settings.hpp"

struct TracePoint {
  cv::Point p;
  int frame;
  TracePoint(cv::Point p, int frame) : p(p), frame(frame) {};
};

class Tracer {
public:
  Tracer(Settings *s);
  void processNewContours(std::vector<std::vector<cv::Point>> contours, int frame);
  std::vector<std::vector<TracePoint>> getTraces();
  std::vector<std::vector<cv::Point>> getPointTraces();
  std::vector<std::vector<cv::Point>> getcurrPointTraces();

private:
  Settings *settings;
  std::vector<std::vector<TracePoint>> traces;
  std::vector<std::vector<TracePoint>> finishedTraces;

  cv::Point getCenter(std::vector<cv::Point> contour);
  void initTraces(std::vector<cv::Point> vector, int i);
  std::vector<cv::Point> contoursToPoints(std::vector<std::vector<cv::Point>> vector);
  int findNearestPoint(TracePoint &pivotPoint, std::vector<cv::Point> candidates, float maxTraceDist);
  void cleanUpTraces(int currFrame);
  bool isOld(std::vector<TracePoint>, int lastFrame);

  std::vector<std::vector<cv::Point>> convertTracePointsToPoints(std::vector<std::vector<TracePoint>> traces);

};

#endif //KILOTRACKER_TRACER_H
