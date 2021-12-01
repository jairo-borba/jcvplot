//
// Created by Jairo Borba on 11/19/21.
//
#include "Ruler.h"
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
                            cv::Point2d(x, tensor()->minVisibleYValue()),
                            figure,
                            cv::Point2d(0.0,0.0),
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
                                cv::Point2d(x,
                                            tensor()->maxVisibleYValue(
                                                    figure,
                                                    axisAngle())),
                                figure,
                                cv::Point2d(-cos(axisAngle().x_rad())*txtSize.width/2, -txtSize.height),
                                axisAngle());

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
                                cv::Point2d(
                                        x,
                                        tensor()->maxVisibleYValue(figure,axisAngle())),
                                figure,
                                cv::Point2d(0.0,0.0),
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
                            cv::Point2d(tensor()->minVisibleXValue(), y),
                            figure,
                            cv::Point2d(0.0,0.0),
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
                                cv::Point2d(tensor()->maxVisibleXValue(figure,axisAngle()), y),
                                figure, cv::Point2d(6.0, 0),axisAngle());
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
                                cv::Point2d(tensor()->maxVisibleXValue(figure,axisAngle()), y),
                                figure,
                                cv::Point2d(0.0,0.0),
                                axisAngle());
                cv::line(figure,
                         startPoint,
                         endPoint,
                         this->scalarColor());
            }
        }
        return success;
    }
    bool Ruler::renderLegacy(cv::Mat &figure) const{
        auto success = true;
        auto rowUpperLeftLimit = static_cast<double>(getTensor()->bound().upperLeft.y);
        auto colUpperLeftLimit = static_cast<double>(getTensor()->bound().upperLeft.x);
        auto rowLowerRightLimit = static_cast<double>(getTensor()->bound().lowerRight.y);
        auto colLowerRightLimit = static_cast<double>(getTensor()->bound().lowerRight.x);
        auto pixelRows = static_cast<double>(figure.rows) - (rowLowerRightLimit + rowUpperLeftLimit);
        auto pixelCols = static_cast<double>(figure.cols) - (colLowerRightLimit + colUpperLeftLimit);
        auto stepYPixels = tensor()->pixelsPerUnit().yPixels * tensor()->stepValue().yStepValue;
        auto stepXPixels = tensor()->pixelsPerUnit().xPixels * tensor()->stepValue().xStepValue;
        auto pivotY = static_cast<double>(figure.rows) - rowLowerRightLimit;
        auto pivotX = colUpperLeftLimit;
        auto numberOfYPoints = static_cast<size_t>(pixelCols / stepYPixels) + 1;
        auto yPointValue = tensor()->startValue().yStartValue;
        auto row = pivotY;
        auto numberOfXPoints = static_cast<size_t>(pixelRows / stepXPixels) + 1;
        auto xPointValue = tensor()->startValue().xStartValue;
        auto col = pivotX;

        for( auto idx = 0; idx < numberOfYPoints; idx++ ){
            std::ostringstream number;
            number << yPointValue;
            int back = 4 + (number.str().length() * 11);
            if(m_leftOn) {
                cv::putText(figure,
                            number.str(),
                            cv::Point2d(colUpperLeftLimit - back, row + 5),
                            1, 1,
                            this->scalarColor(),
                            1);
            }
            if(m_rightOn) {
                cv::putText(figure,
                            number.str(),
                            cv::Point2d(
                                    figure.cols - colLowerRightLimit + 6,
                                    row + 5),
                            1,
                            1,
                            this->scalarColor(),
                            1);
            }
            if(m_verticalGridOn) {
                cv::line(figure,
                         cv::Point2d(colUpperLeftLimit, row),
                         cv::Point2d(figure.cols - colLowerRightLimit, row),
                         this->scalarColor());
            }
            row -= stepYPixels;
            yPointValue += tensor()->stepValue().yStepValue;
        }

        for( auto idx = 0; idx < numberOfXPoints; idx++ ){
            std::ostringstream number;
            number << xPointValue;
            int back = number.str().length() * 6;
            if(m_bottomOn){
                cv::putText(figure,
                            number.str(),
                            cv::Point2d (
                                    col-back,
                                    figure.rows - rowLowerRightLimit + 20),
                            1, 1,
                            scalarColor(),
                            1);
            }
            if(m_upOn) {
                cv::putText(figure,
                            number.str(),
                            cv::Point2d(
                                    col - back,
                                    rowUpperLeftLimit - 10),
                            1, 1, this->scalarColor(), 1);
            }
            if(m_horizontalGridOn) {
                cv::line(figure,
                         cv::Point2d(col, rowUpperLeftLimit),
                         cv::Point2d(col, figure.rows - rowLowerRightLimit),
                         this->scalarColor());
            }
            col += stepXPixels;
            xPointValue += tensor()->stepValue().xStepValue;
        }

        return success;
    }
}
