//
// Created by Jairo Borba on 11/2/21.
//
#include "YAxis.h"
namespace jcvplot{
    YAxis::YAxis():m_thickness(DEFAULT_THICKNESS){
    }
    bool YAxis::render(cv::Mat &figure) const{
        auto success = true;
        cv::Point2d zero =
                getTensor()->transformToPixelBaseCoordinate(
                        cv::Point2d(0.0, 0.0),
                        figure,
                        cv::Point2d(0.0,0.0),
                        axisAngle());
        cv::Point2d tip =
                getTensor()->transformToPixelBaseCoordinate(
                        cv::Point2d(
                                0.0,
                                0.9*getTensor()->maxVisibleYValue(
                                        figure,
                                        axisAngle())),
                        figure,
                        cv::Point2d(0.0,0.0),
                        axisAngle());

        cv::line(figure,
                 zero,
                 tip,
                 this->scalarColor(),
                 m_thickness);

        return success;
    }
    YAxis& YAxis::setThickness(int thickness)
    {
        m_thickness = thickness;
        return *this;
    }
}
