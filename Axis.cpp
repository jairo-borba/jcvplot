//
// Created by Jairo Borba on 11/6/21.
//

#include "Axis.h"
#include <cmath>
namespace jcvplot{
    Axis::Axis():
        m_length(1),
        m_thickness(DEFAULT_THICKNESS),
        m_stepPixels(DEFAULT_PX_STEP),
        m_markLength(DEFAULT_MARK_LENGTH){
    }
    Axis& Axis::setThickness(int thickness)
    {
        m_thickness = thickness;
        return *this;
    }
    bool Axis::render(cv::Mat &image) const{
        auto success = true;
        cv::Point2d zero =
                getTensor()->transformToPixelBaseCoordinate(
                        cv::Point2d(0.0, 0.0),
                        image,
                        cv::Point2d(0.0,0.0),
                        axisAngle());
        cv::Point2d tip =
                getTensor()->transformToPixelBaseCoordinate(
                        cv::Point2d(
                                0.9*getTensor()->maxVisibleYValue(
                                        image,
                                        axisAngle()),
                                        0.0),
                        image,
                        cv::Point2d(0.0,0.0),
                        axisAngle());

        cv::line(image,
                 zero,
                 tip,
                 this->scalarColor(),
                 m_thickness);

        return success;
    }
    Axis& Axis::setLength(double length){
        m_length = length;
        return *this;
    }
    double Axis::length()const{
        return m_length;
    }
}
