//
// Created by Jairo Borba on 12/10/21.
//

#include "MovingX.h"

namespace jcvplot {
    void MovingX::setup(
            const Series::SeriesPoint_t &iniX,
            const Series::SeriesPoint_t &maxX,
            const Series::SeriesPoint_t &stepX){
            m_iniX = iniX;
            m_maxX = maxX;
            m_stepX = stepX;
            m_currentX = iniX;
    }
    void MovingX::step(){
        size_t idx = 0;
        for( auto &v : m_movingX){
            if(m_positiveMove[idx]) {
                auto next = v + m_stepX;
                if (next > m_maxX) {
                    auto gapBeforeMax = m_maxX - v;
                    v = m_maxX + gapBeforeMax - m_stepX;
                    m_positiveMove[idx] = false;
                } else {
                    v += m_stepX;
                }
            }
            else {
                auto next = v - m_stepX;
                auto min = this->tensor()->minVisibleXValue();
                if (next < min) {
                    auto gapBeforeMin = v - min;
                    v = min + m_stepX - gapBeforeMin;
                    m_positiveMove[idx] = true;
                } else {
                    v -= m_stepX;
                }
            }
            idx++;
        }
    }
    void MovingX::init(){
        m_movingX.reserve(m_series->series().size());
        m_positiveMove.resize(m_series->series().size(),true);
        for( auto v : m_series->series()){
            m_movingX.push_back(-v.first);
        }
    }
    bool MovingX::render(cv::Mat &figure) const{
        auto success = true;
        size_t idx = 0;
        for( auto v : m_series->series()){
            if(this->tensor()->minVisibleXValue() > m_movingX[idx]) {
                idx++;
                continue;
            }
            cv::Point2d point;
            auto ret = getTensor()->transformToPixelBaseCoordinate(
                    point,
                    cv::Point3d(
                            m_movingX[idx],
                            v.second, 0.0),
                    figure,
                    yawAngle(),
                    rollAngle(),
                    pitchAngle());
            if(ret){
                cv::Scalar color = cv::Scalar(10,20,255);
                if(m_positiveMove[idx] ){
                    color = cv::Scalar(255,25,10);
                }
                cv::circle(
                        figure,
                        point,
                        4,
                        color);
            }
            idx++;
        }
        return success;
    }
    MovingX &MovingX::setSeries(std::shared_ptr<Series> &series){
        m_series = series;
        return *this;
    }
}