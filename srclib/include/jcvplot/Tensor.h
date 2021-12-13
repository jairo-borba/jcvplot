//
// Created by Jairo Borba on 11/23/21.
//
#ifndef JCVPLOT_TENSOR_H
#define JCVPLOT_TENSOR_H
#include <opencv2/opencv.hpp>
#include <list>
#include "AxisAngle.h"
namespace jcvplot {
    class Tensor {
    public:
        Tensor() = default;
        class Boundaries_t{
        public:
            Boundaries_t():
                upperLeft(cv::Point2d (0.0,0.0)),
                lowerRight(cv::Point2d(0.0,0.0)){
            }
            Boundaries_t(const cv::Point2d &a_upperLeft,
                         const cv::Point2d &a_lowerRight):
                    upperLeft(a_upperLeft),
                    lowerRight(a_lowerRight){}
            cv::Point2d upperLeft;
            cv::Point2d lowerRight;
        };
        class PixelsPerUnit_t{
        public:
            PixelsPerUnit_t(
                    double a_xPixels = 1.0,
                    double a_yPixels = 1.0,
                    double a_zPixels = 1.0):
                    xPixels(a_xPixels),
                    yPixels(a_yPixels),
                    zPixels(a_zPixels){}
            double xPixels;
            double yPixels;
            double zPixels;
        };
        class StartValue_t{
        public:
            StartValue_t(
                    double a_xStartValue = 0.0,
                    double a_yStartValue = 0.0,
                    double a_zStartValue = 0.0):
                    xStartValue(a_xStartValue),
                    yStartValue(a_yStartValue),
                    zStartValue(a_zStartValue){}
            double xStartValue;
            double yStartValue;
            double zStartValue;
        };
        class StepValue_t{
        public:
            StepValue_t(
                    double a_xStepValue = 0.0,
                    double a_yStepValue = 0.0,
                    double a_zStepValue = 0.0):
                    xStepValue(a_xStepValue),
                    yStepValue(a_yStepValue),
                    zStepValue(a_zStepValue){}
            double xStepValue;
            double yStepValue;
            double zStepValue;
        };
        class CvMatShape{
            int m_rows;
            int m_cols;
        public:
            CvMatShape():m_rows(0),m_cols(0) { } ;
            CvMatShape(const cv::Mat &mat){
                m_cols = mat.cols;
                m_rows = mat.rows;
            }
            const CvMatShape &operator()(const cv::Mat &mat){
                m_cols = mat.cols;
                m_rows = mat.rows;
                return *this;
            }
            const CvMatShape &operator()() const{
                return *this;
            }
            int rows() const{
                return m_rows;
            }
            int cols() const{
                return m_cols;
            }
        };
        Tensor& setData(const PixelsPerUnit_t &pixelsPerUnit,
                        const StartValue_t &startValue,
                        const StepValue_t &stepValue,
                        const Boundaries_t &bound);
        bool transformToPixelBaseCoordinate(
                cv::Point2d &outPoint,
                const cv::Point3d &point,
                const CvMatShape &shape,
                const AxisAngle &yawAngleRad,
                const AxisAngle &rollAngleRad,
                const AxisAngle &pitchAngleRad,
                const cv::Point3d &offset = cv::Point3d(0.0, 0.0, 0.0)
                ) const;
        bool transformToPixelBaseCoordinateProjection(
                cv::Point2d &outPoint,
                const cv::Point3d &point,
                const CvMatShape &shape,
                const AxisAngle &yawAngleRad = AxisAngle(),
                const cv::Point3d &offset = cv::Point3d(0.0, 0.0, 0.0)
        ) const;
        void genEvenYValues(std::list<double> &points, const CvMatShape &shape)const;
        void genEvenXValues(std::list<double> &points, const CvMatShape &shape)const;
        double minVisibleXValue() const;
        double minVisibleYValue() const;
        double maxVisibleXValue(const CvMatShape &shape, const AxisAngle &angleRad) const;
        double maxVisibleYValue(const CvMatShape &shape, const AxisAngle &angleRad) const;
        double minVisibleX() const;
        double minVisibleY() const;
        double maxVisibleX(const CvMatShape &shape) const;
        double maxVisibleY(const CvMatShape &shape) const;
        const Boundaries_t &bound() const;
        Boundaries_t &bound();
        const PixelsPerUnit_t &pixelsPerUnit() const;
        PixelsPerUnit_t &pixelsPerUnit();
        const StartValue_t &startValue() const;
        StartValue_t &startValue();
        const StepValue_t &stepValue() const;
        StepValue_t &stepValue();
    private:
        PixelsPerUnit_t m_pixelsPerUnit;
        StartValue_t m_startValue;
        StepValue_t m_stepValue;
        Boundaries_t m_bound;
    };
}

#endif //JCVPLOT_TENSOR_H
