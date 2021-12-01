//
// Created by Jairo Borba on 11/18/21.
//

#ifndef JCVPLOT_BORDER_H
#define JCVPLOT_BORDER_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "Figure.h"
namespace jcvplot {
    class Border : public Figure {
    public:
        Border();
        bool render(cv::Mat &figure) const override;
        Border& setThickness(int thickness);
    private:
        int m_thickness;
    };
}


#endif //JCVPLOT_BORDER_H
