//
// Created by Jairo Borba on 11/6/21.
//

#ifndef JCVPLOT_AXIS_H
#define JCVPLOT_AXIS_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "Figure.h"
namespace jcvplot {
    class Axis : public Figure{
    public:
        Axis();
        bool render(cv::Mat &figure) const override;
        Axis& setLength(double length);
        double length()const;
        Axis& setThickness(int thickness);
    private:
        const int DEFAULT_THICKNESS = 1;
        const int DEFAULT_PX_STEP = 50.0;
        const uint8_t DEFAULT_MARK_LENGTH = 5;

        double m_length;
        int m_thickness;

        //How far each mark will be placed from each other along the axis
        int m_stepPixels;
        uint8_t m_markLength;
    };
}

#endif //JCVPLOT_AXIS_H
