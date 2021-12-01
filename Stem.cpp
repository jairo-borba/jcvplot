//
// Created by Jairo Borba on 11/21/21.
//
#include "Stem.h"
namespace jcvplot{
    bool Stem::render(cv::Mat &figure) const{
        auto success = true;
        for( auto v : m_series->series()){
            cv::Point2d point =
                    getTensor()->transformToPixelBaseCoordinate(
                            cv::Point2d(v.first, v.second),
                            figure,
                            cv::Point2d(0.0,0.0),
                            axisAngle());
            cv::circle(
                        figure,
                        point,
                        4,
                        scalarColor());
            auto pointZeroY =
                    getTensor()->transformToPixelBaseCoordinate(
                            cv::Point2d(v.first, 0.0), figure,
                            cv::Point2d(0.0,0.0),
                            axisAngle());
            cv::line(
                    figure,
                    point,
                    pointZeroY,
                    scalarColor(),1);
        }
        return success;
    }
    Stem &Stem::setSeries(std::shared_ptr<Series> &series){
        m_series = series;
        return *this;
    }
}