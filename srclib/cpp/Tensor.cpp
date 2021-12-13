//
// Created by Jairo Borba on 11/23/21.
//
#include "../include/jcvplot/Tensor.h"
#include "../include/jcvplot/Transform3D.h"
namespace jcvplot{
    Tensor& Tensor::setData(
            const Tensor::PixelsPerUnit_t &pixelsPerUnit,
            const Tensor::StartValue_t &startValue,
            const Tensor::StepValue_t &stepValue,
            const Tensor::Boundaries_t &bound){
        m_startValue = startValue;
        m_pixelsPerUnit.xPixels = pixelsPerUnit.xPixels < 1.0 ? 1.0 : pixelsPerUnit.xPixels;
        m_pixelsPerUnit.yPixels = pixelsPerUnit.yPixels < 1.0 ? 1.0 : pixelsPerUnit.yPixels;
        m_stepValue.xStepValue = stepValue.xStepValue <= 0 ? 1.0 : stepValue.xStepValue;
        m_stepValue.yStepValue = stepValue.yStepValue <= 0 ? 1.0 : stepValue.yStepValue;
        m_bound = bound;
        return *this;
    }
    bool Tensor::transformToPixelBaseCoordinate(
            cv::Point2d &outPoint,
            const cv::Point3d &point,
            const CvMatShape &shape,
            const AxisAngle &yawAngleRad,
            const AxisAngle &rollAngleRad,
            const AxisAngle &pitchAngleRad,
            const cv::Point3d &offset
            ) const {
        //Transform the screen top Y origin
        // to bottom Y origin
        double yFlipMtx[3][3]{
            1.0, 0.0, 0.0,
            0.0,-1.0, 0.0,
            0.0, 0.0, 1.0
        };
        //Transform the representation basis
        //to pixel basis according to the
        //desired zoom on the graph(scaling)
        double scaleMtx[3][3]{
                m_pixelsPerUnit.xPixels, 0.0, 0.0,
                0.0, m_pixelsPerUnit.yPixels, 0.0,
                0.0, 0.0, m_pixelsPerUnit.zPixels
        };
        double rotatedMtx0[3][3]
                {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
        Transform3D::yaw(
                rotatedMtx0,
                scaleMtx,
                yawAngleRad.x_rad(),
                yawAngleRad.y_rad());
        double rotatedMtx1[3][3]
                {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
        Transform3D::roll(
                rotatedMtx1,
                rotatedMtx0,
                -rollAngleRad.x_rad(),
                -rollAngleRad.y_rad());
        double rotatedMtx[3][3]
                {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
        Transform3D::pitch(
                rotatedMtx,
                rotatedMtx1,
                pitchAngleRad.x_rad(),
                pitchAngleRad.y_rad());
        double transformMtx[3][3]
        {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
        Transform3D::matrixMultiplication(
                transformMtx,
                yFlipMtx,
                rotatedMtx);
        //Like a camera aiming a region of the graph
        double preOffsetVector[3]{//Offset on the representation basis
                -m_startValue.xStartValue,
                -m_startValue.yStartValue
                -m_startValue.zStartValue
        };
        auto regionHeight{
            shape.rows() -
            m_bound.upperLeft.y -
            m_bound.lowerRight.y};
        //Put the graph on inside the region desired
        double postOffsetVector[3]{//Offset on the pixel basis
                offset.x + m_bound.upperLeft.x,
                offset.y + regionHeight + m_bound.upperLeft.y,
                offset.z
        };
        //Values in the representation basis
        double inputVector[3]{
                point.x,
                point.y,
                point.z
        };
        //Values converted from
        //representation basis
        // to pixel basis
        double outputVector[3]{
                0.0, 0.0, 0.0
        };
        //Transform from representation basis to pixel basis
        Transform3D::transform(transformMtx,
            preOffsetVector,
            postOffsetVector,
            inputVector,
            outputVector);

        outPoint.x = outputVector[0];
        outPoint.y = outputVector[1];
        return true;
    }
    bool Tensor::transformToPixelBaseCoordinateProjection(
            cv::Point2d &outPoint,
            const cv::Point3d &point,
            const CvMatShape &shape,
            const AxisAngle &yawAngleRad,
            const cv::Point3d &offset
    ) const {
        //Transform the screen top Y origin
        // to bottom Y origin
        double yFlipMtx[3][3]{
                1.0, 0.0, 0.0,
                0.0,-1.0, 0.0,
                0.0, 0.0, 1.0
        };
        //Transform the representation basis
        //to pixel basis according to the
        //desired zoom on the graph(scaling)
        double scaleMtx[3][3]{
                m_pixelsPerUnit.xPixels, 0.0, 0.0,
                0.0, m_pixelsPerUnit.yPixels, 0.0,
                0.0, 0.0, m_pixelsPerUnit.zPixels
        };
        double rotatedMtx0[3][3]
                {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
        Transform3D::bypass(
                rotatedMtx0,
                scaleMtx,
                yawAngleRad.x_rad(),
                yawAngleRad.y_rad());
        double rotatedMtx1[3][3]
                {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
        Transform3D::bypass(
                rotatedMtx1,
                rotatedMtx0,
                -yawAngleRad.x_rad(),
                -yawAngleRad.y_rad());
        double rotatedMtx[3][3]
                {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
        Transform3D::bypass(
                rotatedMtx,
                rotatedMtx1, yawAngleRad.x_rad(),
                yawAngleRad.y_rad());
        double transformMtx[3][3]
                {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
        Transform3D::matrixMultiplication(
                transformMtx,
                yFlipMtx,
                rotatedMtx);
        //Like a camera aiming a region of the graph
        double preOffsetVector[3]{//Offset on the representation basis
                -m_startValue.xStartValue,
                -m_startValue.yStartValue
                -m_startValue.zStartValue
        };
        auto regionHeight{
                shape.rows() -
                m_bound.upperLeft.y -
                m_bound.lowerRight.y};
        //Put the graph on inside the region desired
        double postOffsetVector[3]{//Offset on the pixel basis
                offset.x + m_bound.upperLeft.x,
                offset.y + regionHeight + m_bound.upperLeft.y,
                offset.z
        };
        //Values in the representation basis
        double inputVector[3]{
                point.x,
                point.y,
                point.z+400.0
        };
        //Values converted from
        //representation basis
        // to pixel basis
        double outputVector[3]{
                0.0, 0.0, 0.0
        };
        //Transform from representation basis to pixel basis
        Transform3D::transform(transformMtx,
                               preOffsetVector,
                               postOffsetVector,
                               inputVector,
                               outputVector);

        outPoint.x = 0.0;
        outPoint.y = 0.0;
        auto w_coordinate = outputVector[2];
        if(w_coordinate < 1 && w_coordinate > -1){
            return false;
        }
        double focalPoint = 100.0;
        double z_projection = 1.0;//focalPoint / w_coordinate;
        outPoint.x = (outputVector[0]*z_projection);
        outPoint.y = (outputVector[1]*z_projection);
        return true;
    }
    double Tensor::minVisibleX() const{
        auto min = this->bound().upperLeft.x;
        return min;
    }
    double Tensor::minVisibleY() const{
        auto min = this->bound().upperLeft.y;
        return min;
    }
    double Tensor::maxVisibleX(const CvMatShape &shape) const{
        auto max = shape.cols() - bound().lowerRight.x;
        return max;
    }
    double Tensor::maxVisibleY(const CvMatShape &shape) const{
        auto max = shape.rows() - bound().lowerRight.y;
        return max;
    }
    double Tensor::minVisibleXValue() const{
        auto min = this->m_startValue.xStartValue;
        return min;
    }
    double Tensor::minVisibleYValue() const{
        auto min = this->m_startValue.yStartValue;
        return min;
    }
    double Tensor::maxVisibleXValue(const CvMatShape &shape,const AxisAngle &angleRad) const{
        auto width = shape.cols() - bound().lowerRight.x - bound().upperLeft.x;
        // sec = 1 / cos(angleRad.x_rad());
        auto max = (m_startValue.xStartValue + (width / m_pixelsPerUnit.xPixels));// * sec
        return max;
    }
    double Tensor::maxVisibleYValue(const CvMatShape &shape,const AxisAngle &angleRad) const{
        auto height = shape.rows() - bound().lowerRight.y - bound().upperLeft.y;
        auto sec = 1 / cos(angleRad.y_rad());
        auto max = //sec *
                (m_startValue.yStartValue +
                (static_cast<double>(height) / m_pixelsPerUnit.yPixels));
        return max;
    }
    void Tensor::genEvenXValues(
            std::list<double> &points,
            const CvMatShape &shape) const{
        auto horizontalUnits =
                (static_cast<double>(shape.cols()) -
                bound().upperLeft.x - bound().lowerRight.x) /
                        m_pixelsPerUnit.xPixels;
        auto horizontalPointsCount =
                (horizontalUnits / stepValue().xStepValue) - 1.0;
        auto point = m_startValue.xStartValue + m_stepValue.xStepValue;
        for(
                auto i = 0.0;
                i < horizontalPointsCount;
                ++i, point += m_stepValue.xStepValue){
            points.push_back(point);
        }
    }
    void Tensor::genEvenYValues(
            std::list<double> &points,
            const CvMatShape &shape) const{
        auto verticalUnits =
                (static_cast<double>(shape.rows()) -
                bound().upperLeft.y - bound().lowerRight.y) /
                m_pixelsPerUnit.yPixels;
        auto verticalPointsCount =
                (verticalUnits / stepValue().yStepValue) - 1;
        auto point = m_startValue.yStartValue + m_stepValue.yStepValue;
        for(auto i = 0;
                i < verticalPointsCount;
                ++i, point += m_stepValue.yStepValue){
            points.push_back(point);
        }
    }
    const Tensor::Boundaries_t &Tensor::bound() const{
        return m_bound;
    }
    Tensor::Boundaries_t &Tensor::bound(){
        return m_bound;
    }
    const Tensor::PixelsPerUnit_t &Tensor::pixelsPerUnit() const{
        return m_pixelsPerUnit;
    }
    Tensor::PixelsPerUnit_t &Tensor::pixelsPerUnit(){
        return m_pixelsPerUnit;
    }
    const Tensor::StartValue_t &Tensor::startValue() const{
        return m_startValue;
    }
    Tensor::StartValue_t &Tensor::startValue(){
        return m_startValue;
    }
    const Tensor::StepValue_t &Tensor::stepValue() const{
        return m_stepValue;
    }
    Tensor::StepValue_t &Tensor::stepValue(){
        return m_stepValue;
    }
}