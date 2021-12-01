//
// Created by Jairo Borba on 11/2/21.
//

#ifndef JCVPLOT_LINE_H
#define JCVPLOT_LINE_H
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "Figure.h"
#include "Series.h"
#include <memory>
namespace jcvplot{
    class Line : public Figure{
    private:
        std::shared_ptr<Series> m_series;
        double m_pixelXValue;
        double m_pixelYValue;
    public:
        double getPixelYValue() const;
        void setPixelYValue(double pixelYValue);
        double getPixelXValue() const;
        void setPixelXValue(double pixelXValue);
        bool render(cv::Mat &figure) const override;
        Line &setSeries(std::shared_ptr<Series> &series);

    };
}

#endif //JCVPLOT_LINE_H
