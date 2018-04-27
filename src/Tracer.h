#ifndef KILOTRACKER_TRACER_H
#define KILOTRACKER_TRACER_H

#include "Settings.h"

/**
 * TracePoint safes the point and the frame it was captured
 */
struct TracePoint {
  cv::Point p;
  int frame;
  TracePoint(cv::Point p, int frame) : p(p), frame(frame) {};
};

/**
 * Trace points in video and save them
 */
class Tracer {
public:
  Tracer(Settings *s);
  /**
   * Add the new found contours to a trace
   * @param contours found contours
   * @param frame number of current frame
   */
  void processNewContours(std::vector<std::vector<cv::Point>> contours, int frame);
  /**
   * @return all traces as vectors of TracePoint
   */
  std::vector<std::vector<TracePoint>> getTraces();
  /**
   * @return all traces as vectors of cv::Point
   */
  std::vector<std::vector<cv::Point>> getPointTraces();
  /**
   * @return only traces that where matched in the last processing step as vectors of cv::Point
   */
  std::vector<std::vector<cv::Point>> getcurrPointTraces();

private:
  Settings *settings;

  /**
   * all current traces; these are matched first
   */
  std::vector<std::vector<TracePoint>> traces;

  /**
   * Lost, old, maybe finished traces.
   */
  std::vector<std::vector<TracePoint>> finishedTraces;

  /**
   * Use simple average to calculate center of the contour
   * @param contour
   * @return center of contour
   */
  cv::Point getCenter(std::vector<cv::Point> contour);

  /**
   * Add the first points as new traces
   * @param vector the first points
   * @param frame first frame, usually 0 or 1
   */
  void initTraces(std::vector<cv::Point> vector, int frame);

  /**
   * Apply getCenter to a vector
   * @param contours
   * @return vector of each contours center
   */
  std::vector<cv::Point> contoursToPoints(std::vector<std::vector<cv::Point>> contours);

  /**
   * Get nearest point of the candidate points to the pivotPoint but not greater than maxTraceDist away
   * @param pivotPoint
   * @param candidates
   * @param maxTraceDist
   * @return index in candidates, that is nearest to pivot point, -1 if none found (because of maxTraceDist)
   */
  int findNearestPoint(TracePoint &pivotPoint, std::vector<cv::Point> candidates, float maxTraceDist);
  /**
   * Remove old traces from traces. Remove reactivated traces from finishedTraces.
   */
  void cleanUpTraces(int currFrame);

  std::vector<std::vector<cv::Point>> convertTracePointsToPoints(std::vector<std::vector<TracePoint>> traces);

};

#endif //KILOTRACKER_TRACER_H
