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
        auto retX = true;
        for(auto x : listX){
            cv::Point2d startPoint;
            retX &= tensor()->transformToPixelBaseCoordinate(
                    startPoint,
                    cv::Point3d(x, tensor()->minVisibleYValue(),0.0),
                    figure,
                    yawAngle(),
                    rollAngle(),
                    pitchAngle());
            std::ostringstream number;
            number << x;
            int baseline = 0;
            cv::Size txtSize = cv::getTextSize(
                    number.str(), font, fontScale,
                    textThickness, &baseline);
            if(m_upOn && retX) {
                cv::Point2d upPoint;
                retX &= tensor()->transformToPixelBaseCoordinate(
                        upPoint,
                        cv::Point3d(x,
                                    tensor()->maxVisibleYValue(
                                            figure,
                                            yawAngle()), 0.0),
                        figure,
                        yawAngle(),
                        rollAngle(),
                        pitchAngle(),
                        cv::Point3d(
                            -cos(yawAngle().x_rad()) * txtSize.width / 2,
                            -txtSize.height,
                            0.0)
                    );
                if(retX) {
                    cv::putText(figure,
                                number.str(),
                                upPoint,
                                font,
                                fontScale,
                                this->scalarColor(),
                                textThickness);
                }
            }
            if(m_bottomOn && retX) {
                cv::Point2d downPoint =
                        cv::Point2d(
                                startPoint.x- cos(yawAngle().x_rad()) * (txtSize.width / 2),
                                startPoint.y + txtSize.height + 8);
                cv::putText(figure,
                            number.str(),
                            downPoint,
                            font,
                            fontScale,
                            this->scalarColor(),
                            textThickness);
            }
            if(m_verticalGridOn && retX) {
                cv::Point2d endPoint;
                retX &= tensor()->transformToPixelBaseCoordinate(
                        endPoint,
                        cv::Point3d(
                        x,
                        tensor()->maxVisibleYValue(figure, yawAngle()),
                        0.0),
                        figure,
                        yawAngle(),
                        rollAngle(),
                        pitchAngle());
                if(retX) {
                    cv::line(figure,
                         startPoint,
                         endPoint,
                         this->scalarColor());
                }
            }
        }
        auto retY = true;
        for(auto y : listY){
            cv::Point2d startPoint;
            retY &= tensor()->transformToPixelBaseCoordinate(
                    startPoint,
                    cv::Point3d(tensor()->minVisibleXValue(), y, 0.0),
                    figure,
                    yawAngle(),
                    rollAngle(),
                    pitchAngle());
            std::ostringstream number;
            number << y;
            int baseline = 0;
            cv::Size txtSize = cv::getTextSize(
                    number.str(), font, fontScale,
                    textThickness, &baseline);
            if(m_leftOn && retY) {
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
            if(m_rightOn && retY) {
                cv::Point2d txtForwardToRight;
                retY &= tensor()->transformToPixelBaseCoordinate(
                        txtForwardToRight,
                        cv::Point3d(tensor()->maxVisibleXValue(figure,yawAngle()),y,0.0),
                        figure,
                        yawAngle(),
                        rollAngle(),
                        pitchAngle(),
                        cv::Point3d(6.0, 0,0.0));
                if(retY) {
                    cv::putText(figure,
                                number.str(),
                                txtForwardToRight,
                                font, fontScale,
                                this->scalarColor(),
                                textThickness);
                }
            }
            if(m_horizontalGridOn && retY) {
                cv::Point2d endPoint;
                retY &= tensor()->transformToPixelBaseCoordinate(
                        endPoint,
                        cv::Point3d(
                                tensor()->maxVisibleXValue(figure, yawAngle()),
                                y,0.0),
                        figure, yawAngle(),
                        rollAngle(),
                        pitchAngle());
                if(retY) {
                    cv::line(
                            figure,
                            startPoint,
                            endPoint,
                            this->scalarColor());
                }
            }
        }
        return success;
    }
}
