//
// Created by Jairo Borba on 11/21/21.
//
#include "../include/jcvplot/Stem.h"
namespace jcvplot{
    bool Stem::render(cv::Mat &figure) const{
        auto success = true;
        for( auto v : m_series->list()){
            cv::Point2d point;
            auto ret = tensor()->transformToPixelBaseCoordinate(
                    point,
                    cv::Point3d(v.first, v.second, 0.0),
                    figure,
                    yawAngle(),
                    rollAngle(),
                    pitchAngle());
            if(ret){
                cv::circle(
                        figure,
                        point,
                        4,
                        scalarColor());
            cv::Point2d pointZeroY;
                    tensor()->transformToPixelBaseCoordinate(
                            pointZeroY,
                            cv::Point3d(v.first, 0.0, 0.0),
                            figure,
                            yawAngle(),
                            rollAngle(),
                            pitchAngle());
            cv::line(
                    figure,
                    point,
                    pointZeroY,
                    scalarColor(),1);
            }
        }
        return success;
    }
    Stem &Stem::setSeries(std::shared_ptr<Series<double>> &series){
        m_series = series;
        return *this;
    }
}