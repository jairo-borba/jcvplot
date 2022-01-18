//
// Created by Jairo Borba on 11/21/21.
//

#ifndef JCVPLOT_STEM_H
#define JCVPLOT_STEM_H
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "Figure.h"
#include "Series.h"
#include <memory>
namespace jcvplot{
    class Stem : public Figure{
    private:
        std::shared_ptr<Series<double>> m_series;
    public:
        bool render(cv::Mat &figure) const override;
        Stem &setSeries(std::shared_ptr<Series<double>> &series);
    };
}

#endif //JCVPLOT_STEM_H
