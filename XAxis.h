//
// Created by Jairo Borba on 10/31/21.
//

#ifndef JCVPLOT_XAXIS_H
#define JCVPLOT_XAXIS_H
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "Figure.h"
namespace jcvplot {
    class XAxis : public Figure{
    public:
        XAxis();
        bool render(cv::Mat &figure) const override;
        XAxis& setThickness(int thickness);
    private:
        const int DEFAULT_THICKNESS = 2;
        int m_thickness;
    };
}
#endif //JCVPLOT_XAXIS_H
