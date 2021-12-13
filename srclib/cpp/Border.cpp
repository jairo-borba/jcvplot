//
// Created by Jairo Borba on 11/18/21.
//

#include "../include/jcvplot/Border.h"
namespace jcvplot{
    Border::Border():m_thickness(1){

    }
    bool Border::render(cv::Mat &figure) const{
        cv::Point2d upLeft;
        auto ret = tensor()->transformToPixelBaseCoordinate(
                upLeft,
                cv::Point3d(tensor()->minVisibleXValue(),
                tensor()->maxVisibleYValue(figure, yawAngle()),
                0.0),
                figure,
                yawAngle(),
                rollAngle(),
                pitchAngle());
        cv::Point2d upRight;
        ret &= tensor()->transformToPixelBaseCoordinate(
                upRight,
                cv::Point3d(tensor()->maxVisibleXValue(figure, yawAngle()),
                            tensor()->maxVisibleYValue(figure, yawAngle()), 0.0),
                figure,
                yawAngle(),
                rollAngle(),
                pitchAngle());
        cv::Point2d downLeft;
        ret &= tensor()->transformToPixelBaseCoordinate(
                downLeft,
                cv::Point3d(
                        tensor()->minVisibleXValue(),
                        tensor()->minVisibleYValue(),0.0),
                figure,
                yawAngle(),
                rollAngle(),
                pitchAngle());
        cv::Point2d downRight;
        ret &= tensor()->transformToPixelBaseCoordinate(
                downRight,
                cv::Point3d(
                    tensor()->maxVisibleXValue(figure, yawAngle()),
                    tensor()->minVisibleYValue(),0.0),
                figure,
                yawAngle(),
                rollAngle(),
                pitchAngle());
        if(ret) {
            cv::line(figure, downLeft, downRight, scalarColor(), m_thickness);
            cv::line(figure, upLeft, upRight, scalarColor(), m_thickness);
            cv::line(figure, downLeft, upLeft, scalarColor(), m_thickness);
            cv::line(figure, downRight, upRight, scalarColor(), m_thickness);
        }
        return true;
    }
    Border& Border::setThickness(int thickness){
        m_thickness = thickness;
        return *this;
    }
}