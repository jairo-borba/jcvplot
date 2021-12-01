//
// Created by Jairo Borba on 11/18/21.
//

#include "Border.h"
namespace jcvplot{
    Border::Border():m_thickness(1){

    }
    bool Border::render(cv::Mat &figure) const{
        //cv::rectangle(figure,
        //              cv::Point2d(getTensor()->bound().upperLeft.x, getTensor()->bound().upperLeft.y),
        //              cv::Point2d(figure.cols- getTensor()->bound().lowerRight.x,
        //                        figure.rows- getTensor()->bound().lowerRight.y),
        //              this->scalarColor(),m_thickness,0,0);
        cv::Point2d upLeft = tensor()->transformToPixelBaseCoordinate(
                cv::Point2d(tensor()->minVisibleXValue(),
                            tensor()->maxVisibleYValue(figure,axisAngle())),
                figure,
                cv::Point2d(0.0,0.0),
                axisAngle());
        cv::Point2d upRight = tensor()->transformToPixelBaseCoordinate(
                cv::Point2d(tensor()->maxVisibleXValue(figure,axisAngle()),
                            tensor()->maxVisibleYValue(figure,axisAngle())),
                figure,
                cv::Point2d(0.0,0.0),
                axisAngle());
        cv::Point2d downLeft = tensor()->transformToPixelBaseCoordinate(
                cv::Point2d(
                        tensor()->minVisibleXValue(),
                        tensor()->minVisibleYValue()),
                figure,
                cv::Point2d(0.0,0.0),
                axisAngle());
        cv::Point2d downRight = tensor()->transformToPixelBaseCoordinate(
                cv::Point2d(
                        tensor()->maxVisibleXValue(figure,axisAngle()),
                        tensor()->minVisibleYValue()),
                figure,
                cv::Point2d(0.0,0.0),
                axisAngle());
        cv::line(figure,downLeft,downRight,scalarColor(),m_thickness);
        cv::line(figure,upLeft,upRight,scalarColor(),m_thickness);
        cv::line(figure,downLeft,upLeft,scalarColor(),m_thickness);
        cv::line(figure,downRight,upRight,scalarColor(),m_thickness);
        return true;
    }
    Border& Border::setThickness(int thickness){
        m_thickness = thickness;
        return *this;
    }
}