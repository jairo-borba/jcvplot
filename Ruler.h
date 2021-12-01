//
// Created by Jairo Borba on 11/19/21.
//
#ifndef JCVPLOT_RULER_H
#define JCVPLOT_RULER_H
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "Figure.h"
namespace jcvplot {
    class Ruler : public Figure{
    public:
        Ruler();
        bool render(cv::Mat &figure) const override;
        bool renderLegacy(cv::Mat &figure) const;
        Ruler& enableUp(bool up = true);
        Ruler& enableBottom(bool bottom = true);
        Ruler& enableLeft(bool left = true);
        Ruler& enableRight(bool right = true);
        Ruler& enableVerticalGrid(bool vert = true);
        Ruler& enableHorizontalGrid(bool horiz = true);
    private:
        const double DEFAULT_PX_STEP = 50.0;
        bool m_leftOn;
        bool m_rightOn;
        bool m_upOn;
        bool m_bottomOn;
        bool m_horizontalGridOn;
        bool m_verticalGridOn;
    };
}

#endif //JCVPLOT_RULER_H
