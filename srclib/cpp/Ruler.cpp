//
// Created by Jairo Borba on 11/19/21.
//
#include "../include/jcvplot/Ruler.h"
namespace jcvplot{
    Ruler::Ruler():
        m_rightOn(false),
        m_leftOn(true),
        m_bottomOn(true),
        m_upOn(false),
        m_horizontalGridOn(false),
        m_verticalGridOn(false){
    }

    Ruler& Ruler::enableVerticalGrid(bool vert){
        m_verticalGridOn = vert;
        return *this;
    }
    Ruler& Ruler::enableHorizontalGrid(bool horiz){
        m_horizontalGridOn = horiz;
        return *this;
    }
    Ruler& Ruler::enableUp(bool up){
        m_upOn = up;
        return *this;
    }
    Ruler& Ruler::enableBottom(bool bottom){
        m_bottomOn = bottom;
        return *this;
    }
    Ruler& Ruler::enableLeft(bool left){
        m_leftOn = left;
        return *this;
    }
    Ruler& Ruler::enableRight(bool right){
        m_rightOn = right;
        return *this;
    }
    bool Ruler::render(cv::Mat &figure) const{
        auto success = true;
        cv::HersheyFonts font = cv::FONT_HERSHEY_PLAIN;
        double fontScale = 1.0;
        int textThickness = 1;
        std::list<double> listX;
        std::list<double> listY;
        tensor()->genEvenXValues(listX,figure);
        tensor()->genEvenYValues(listY,figure);
        for(auto x : listX){
            cv::Point2d startPoint =
                    tensor()->transformToPixelBaseCoordinate(
                            cv::Point3d(x, tensor()->minVisibleYValue(),0.0),
                            figure,
                            axisAngle());
            std::ostringstream number;
            number << x;
            int baseline = 0;
            cv::Size txtSize = cv::getTextSize(
                    number.str(), font, fontScale,
                    textThickness, &baseline);
            if(m_upOn) {
                cv::Point2d upPoint =
                        tensor()->transformToPixelBaseCoordinate(
                                cv::Point3d(x,
                                            tensor()->maxVisibleYValue(
                                                    figure,
                                                    axisAngle()),0.0),
                                figure,
                                axisAngle(),
                                cv::Point3d(
                                        -cos(axisAngle().x_rad())*txtSize.width/2,
                                        -txtSize.height,
                                        0.0)
                                );

                cv::putText(figure,
                            number.str(),
                            upPoint,
                            font,
                            fontScale,
                            this->scalarColor(),
                            textThickness);
            }
            if(m_bottomOn) {
                cv::Point2d downPoint =
                        cv::Point2d(
                                startPoint.x-cos(axisAngle().x_rad())*(txtSize.width/2),
                                startPoint.y + txtSize.height + 8);
                cv::putText(figure,
                            number.str(),
                            downPoint,
                            font,
                            fontScale,
                            this->scalarColor(),
                            textThickness);
            }
            if(m_verticalGridOn) {

                cv::Point2d endPoint =
                        tensor()->transformToPixelBaseCoordinate(
                                cv::Point3d(
                                        x,
                                        tensor()->maxVisibleYValue(figure,axisAngle()),
                                        0.0),
                                figure,
                                axisAngle());
                cv::line(figure,
                         startPoint,
                         endPoint,
                         this->scalarColor());
            }
        }
        for(auto y : listY){
            cv::Point2d startPoint =
                    tensor()->transformToPixelBaseCoordinate(
                            cv::Point3d(tensor()->minVisibleXValue(), y, 0.0),
                            figure,
                            axisAngle());
            std::ostringstream number;
            number << y;
            int baseline = 0;
            cv::Size txtSize = cv::getTextSize(
                    number.str(), font, fontScale,
                    textThickness, &baseline);
            if(m_leftOn) {
                cv::Point2d txtBackToLeft =
                        cv::Point2d(startPoint.x-txtSize.width,
                                  startPoint.y);
                cv::putText(figure,
                            number.str(),
                            txtBackToLeft,
                            font, fontScale,
                            this->scalarColor(),
                            textThickness);
            }
            if(m_rightOn) {
                cv::Point2d txtForwardToRight =
                        tensor()->transformToPixelBaseCoordinate(
                                cv::Point3d(
                                        tensor()->maxVisibleXValue(figure,axisAngle()),
                                                                   y,0.0),
                figure, axisAngle(), cv::Point3d(6.0, 0,0.0));
                cv::putText(figure,
                            number.str(),
                            txtForwardToRight,
                            font, fontScale,
                            this->scalarColor(),
                            textThickness);
            }
            if(m_horizontalGridOn) {
                cv::Point2d endPoint =
                        tensor()->transformToPixelBaseCoordinate(
                                cv::Point3d(
                                        tensor()->maxVisibleXValue(figure,axisAngle()),
                                        y,0.0),
                                figure,axisAngle(),cv::Point3d(0.0,0.0,0.0)
                                );
                cv::line(figure,
                         startPoint,
                         endPoint,
                         this->scalarColor());
            }
        }
        return success;
    }
}
