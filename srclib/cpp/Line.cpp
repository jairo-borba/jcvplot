//
// Created by Jairo Borba on 11/2/21.
//

#include "../include/jcvplot/Line.h"
namespace jcvplot{
    bool Line::render(cv::Mat &figure) const{
        auto success = true;
        auto firstIteration = true;
        auto prevRet = false;
        cv::Point2d previousPoint;
        for( auto v : m_series->series()){
            if(firstIteration){
                firstIteration = false;
                prevRet = getTensor()->transformToPixelBaseCoordinate(
                        previousPoint,
                        cv::Point3d(v.first, v.second,0.0),
                        figure,
                        yawAngle(),
                        rollAngle(),
                        pitchAngle());
                continue;
            }
            cv::Point2d point;
            auto retPoint = getTensor()->transformToPixelBaseCoordinate(
                    point,
                    cv::Point3d(
                                    v.first,
                                    v.second,
                                    0.0),
                    figure,
                    yawAngle(),
                    rollAngle(),
                    pitchAngle());
            if(retPoint && prevRet) {
                cv::line(
                        figure,
                        previousPoint,
                        point,
                        scalarColor());
                previousPoint = point;
            }
        }
        return success;
    }
    Line &Line::setSeries(std::shared_ptr<Series> &series){
        m_series = series;
        return *this;
    }
}