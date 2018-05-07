#include <opencv2/core/types.hpp>
#include "Tracer.h"

Tracer::Tracer(Settings *s) {
  settings = s;
}

void Tracer::processNewContours(std::vector<std::vector<cv::Point>> contours, int frame) {
  if (settings->maxTraceDist != 0) {
    std::vector<cv::Point> points = contoursToPoints(contours);
    if (traces.empty()) {
      initTraces(points, frame);
      return;
    }

    //find each trace its next point
    for (auto &trace: traces) {
      int i = findNearestPoint(trace.back(), points, settings->maxTraceDist);
      if (i != -1) {
        trace.emplace_back(points[i], frame);
        points.erase(points.begin() + i);
      } else {
        finishedTraces.push_back(trace);
      }
    }

    //Match leftover points to old traces
    for (auto &finTrace: finishedTraces) {
      int i = findNearestPoint(finTrace.back(), points, settings->maxTraceDist * 2);
      if (i != -1) {
        finTrace.emplace_back(points[i], frame);
        points.erase(points.begin() + i);
        traces.push_back(finTrace);
      }
    }

    //Create new Traces for left overs
    for (auto &point: points) {
      traces.emplace_back(1, TracePoint(point, frame));
    }

    cleanUpTraces(frame);
  }
}

std::vector<std::vector<TracePoint>> Tracer::getTraces() {
  std::vector<std::vector<TracePoint>> allTraces;
  allTraces.reserve(finishedTraces.size() + traces.size());
  allTraces.insert(allTraces.end(), traces.begin(), traces.end());
  allTraces.insert(allTraces.end(), finishedTraces.begin(), finishedTraces.end());
  return allTraces;
}

std::vector<std::vector<cv::Point>> Tracer::getPointTraces() {
  return convertTracePointsToPoints(getTraces());
}

std::vector<std::vector<cv::Point>> Tracer::getcurrPointTraces() {
  return convertTracePointsToPoints(traces);
}

std::vector<std::vector<cv::Point>> Tracer::convertTracePointsToPoints(std::vector<std::vector<TracePoint>> traces) {
  std::vector<std::vector<cv::Point>> pointTraces;
  for (auto &trace:traces) {
    std::vector<cv::Point> pointTrace;
    for (auto &tracePoint:trace) {
      pointTrace.push_back(tracePoint.p);
    }
    pointTraces.push_back(pointTrace);
  }
  return pointTraces;
}

void Tracer::initTraces(std::vector<cv::Point> points, int frame) {
  for (auto point:points) {
    traces.emplace_back(1, TracePoint(point, frame));
  }
}

std::vector<cv::Point> Tracer::contoursToPoints(std::vector<std::vector<cv::Point>> contours) {
  std::vector<cv::Point> points;
  for (auto const &contour: contours) {
    points.push_back(getCenter(contour));
  }
  return points;
}

cv::Point Tracer::getCenter(std::vector<cv::Point> contour) {
  cv::Point center;
  for (cv::Point const &vec: contour) {
    center += vec;
  }
  center.x /= contour.size();
  center.y /= contour.size();
  return center;
}
int Tracer::findNearestPoint(TracePoint &pivotPoint, std::vector<cv::Point> candidates, float maxTraceDist) {
  int nearestPoint = -1;
  float nearestSquareDist = maxTraceDist * maxTraceDist;
  for (int i = 0; i < candidates.size(); ++i) {
    cv::Point diff = pivotPoint.p - candidates[i];
    float sqareDist = diff.x * diff.x + diff.y * diff.y;

    if (sqareDist < nearestSquareDist) {
      nearestPoint = i;
      nearestSquareDist = sqareDist;
    }

  }
  return nearestPoint;
}

void Tracer::cleanUpTraces(int currFrame) {
  //Remove old traces from current traces (they where added to old traces before)
  traces.erase(
      std::remove_if(traces.begin(),
                     traces.end(),
                     [&](std::vector<TracePoint> x) {
                       return x.back().frame == (currFrame - 1);
                     }),
      traces.end());

  //Remove reactivated traces from old traces (they where added to current traces before)
  finishedTraces.erase(
      std::remove_if(finishedTraces.begin(),
                     finishedTraces.end(),
                     [&](std::vector<TracePoint> x) {
                       return x.back().frame == currFrame;
                     }),
      finishedTraces.end());
}