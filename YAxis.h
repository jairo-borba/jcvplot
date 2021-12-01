//
// Created by Jairo Borba on 10/31/21.
//

#ifndef JCVPLOT_YAXIS_H
#define JCVPLOT_YAXIS_H
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "Figure.h"
namespace jcvplot {
    class YAxis : public Figure{
    public:
        YAxis();
        bool render(cv::Mat &figure) const override;
        YAxis& setThickness(int thickness);
    private:
        const int DEFAULT_THICKNESS = 2;
        int m_thickness;
    };
}
#endif //JCVPLOT_YAXIS_H
