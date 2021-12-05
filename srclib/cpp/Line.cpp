//
// Created by Jairo Borba on 11/2/21.
//

#include "../include/jcvplot/Line.h"
namespace jcvplot{
    bool Line::render(cv::Mat &figure) const{
        auto success = true;
        auto firstIteration = true;
        cv::Point2d previousPoint;
        for( auto v : m_series->series()){
            if(firstIteration){
                firstIteration = false;
                previousPoint =
                        getTensor()->transformToPixelBaseCoordinate(
                                cv::Point3d(v.first, v.second, 0.0),
                                figure,
                                axisAngle());
                continue;
            }
            auto point =
                    getTensor()->transformToPixelBaseCoordinate(
                            cv::Point3d(
                                    v.first,
                                    v.second,
                                    0.0),
                            figure,
                            axisAngle());
            cv::line(
                        figure,
                        previousPoint,
                        point,
                        scalarColor());
                previousPoint = point;
        }
        return success;
    }
    Line &Line::setSeries(std::shared_ptr<Series> &series){
        m_series = series;
        return *this;
    }
}