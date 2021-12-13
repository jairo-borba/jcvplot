//
// Created by Jairo Borba on 12/10/21.
//

#ifndef JCVPLOT_MOVINGX_H
#define JCVPLOT_MOVINGX_H


#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "Figure.h"
#include "Series.h"
#include <memory>
namespace jcvplot {
    class MovingX : public Figure{
    private:
        std::shared_ptr<Series> m_series;
        std::vector<Series::SeriesPoint_t> m_movingX;
        std::vector<bool> m_positiveMove;
        Series::SeriesPoint_t m_iniX;
        Series::SeriesPoint_t m_maxX;
        Series::SeriesPoint_t m_stepX;
        Series::SeriesPoint_t m_currentX;
    public:
        void setup(const Series::SeriesPoint_t &iniX,
                const Series::SeriesPoint_t &maxX,
                const Series::SeriesPoint_t &stepXs);
        void step();
        void init();
        bool render(cv::Mat &figure) const override;
        MovingX &setSeries(std::shared_ptr<Series> &series);
    };
}

#endif //JCVPLOT_MOVINGX_H
