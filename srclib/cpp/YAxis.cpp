//
// Created by Jairo Borba on 11/2/21.
//
#include "YAxis.h"
namespace jcvplot{
    YAxis::YAxis():m_thickness(DEFAULT_THICKNESS){
    }
    bool YAxis::render(cv::Mat &figure) const{
        auto success = true;
        //auto ninetyDegrees = acos(-1) * 0.1;
        AxisAngle angle(
                axisAngle().x_rad(),
                axisAngle().y_rad(),
                axisAngle().z_rad());
        cv::Point2d zero =
                getTensor()->transformToPixelBaseCoordinate(
                        cv::Point3d(0.0, 0.0, 0.0),
                        figure,
                        angle);
        cv::Point2d tip =
                getTensor()->transformToPixelBaseCoordinate(
                        cv::Point3d(
                                0.0,5.0,0.0),
                        figure,
                        angle);

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
