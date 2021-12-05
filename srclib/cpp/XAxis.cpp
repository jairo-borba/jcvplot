//
// Created by Jairo Borba on 10/31/21.
//

#include "XAxis.h"

namespace jcvplot{
    XAxis::XAxis():m_thickness(DEFAULT_THICKNESS){
    }
    bool XAxis::render(cv::Mat &figure) const{
        auto success = true;
        cv::Point2d zero =
                getTensor()->transformToPixelBaseCoordinate(
                        cv::Point3d(0.0, 0.0, 0.0),
                        figure,
                        axisAngle());
        cv::Point2d tip =
                getTensor()->transformToPixelBaseCoordinate(
                        cv::Point3d(
                                0.9*getTensor()->maxVisibleXValue(figure,
                                        axisAngle()),0.0,0.0),
                        figure,
                        axisAngle());

        cv::line(figure,
                 zero,
                 tip,
                 this->scalarColor(),
                 m_thickness);

        return success;
    }
    XAxis& XAxis::setThickness(int thickness)
    {
        m_thickness = thickness;
        return *this;
    }
}
