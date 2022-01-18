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
        std::shared_ptr<Series<double>> m_series;
        mutable std::list<Series<double>::SeriesCoord_t> m_movingX;
        mutable std::list<bool> m_positiveMove;
        Series<double>::SeriesCoord_t m_iniX;
        Series<double>::SeriesCoord_t m_maxX;
        Series<double>::SeriesCoord_t m_stepX;
        Series<double>::SeriesCoord_t m_currentX;
        mutable Series<double>::SeriesCoord_t m_curDisplacement;
        bool m_bounceBack;
        bool m_vanish;
        bool m_stemMode;
    public:
        void setup(const Series<double>::SeriesCoord_t &iniX,
                const Series<double>::SeriesCoord_t &maxX,
                const Series<double>::SeriesCoord_t &stepXs,
                bool bounceBack = false,
                bool vanish = false,
                bool stemMode = false);
        int step();
        void init();
        bool render(cv::Mat &figure) const override;
        MovingX &setSeries(std::shared_ptr<Series<double>> &series);
    };
}

#endif //JCVPLOT_MOVINGX_H
