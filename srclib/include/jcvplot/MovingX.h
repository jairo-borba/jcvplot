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
#include <list>
namespace jcvplot {
    class MovingX : public Figure{
    private:
        std::shared_ptr<Series> m_series;
        mutable std::list<Series::SeriesPoint_t> m_movingX;
        mutable std::list<bool> m_positiveMove;
        Series::SeriesPoint_t m_iniX;
        Series::SeriesPoint_t m_maxX;
        Series::SeriesPoint_t m_stepX;
        Series::SeriesPoint_t m_currentX;
        mutable Series::SeriesPoint_t m_curDisplacement;
        bool m_bounceBack;
        bool m_vanish;
        bool m_stemMode;
    public:
        void setup(const Series::SeriesPoint_t &iniX,
                const Series::SeriesPoint_t &maxX,
                const Series::SeriesPoint_t &stepXs,
                bool bounceBack = false,
                bool vanish = false,
                bool stemMode = false);
        int step();
        void init();
        bool render(cv::Mat &figure) const override;
        MovingX &setSeries(std::shared_ptr<Series> &series);
    };
}

#endif //JCVPLOT_MOVINGX_H
