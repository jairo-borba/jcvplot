//
// Created by Jairo Borba on 12/10/21.
//
#include "MovingX.h"
namespace jcvplot {
    void MovingX::setup(
            const Series::SeriesPoint_t &iniX,
            const Series::SeriesPoint_t &maxX,
            const Series::SeriesPoint_t &stepX,
            bool bounceBack,
            bool vanish,
            bool stemMode){
            m_iniX = iniX;
            m_maxX = maxX;
            m_stepX = stepX;
            m_currentX = iniX;
            m_bounceBack = bounceBack;
            m_vanish = vanish;
            m_curDisplacement = 0.0;
            m_stemMode = stemMode;
    }
    int MovingX::step(){
        size_t idx = 0;
        auto mvx_it = m_movingX.begin();
        auto pmv_it = m_positiveMove.begin();
        auto replaceQty = 0;
        m_curDisplacement += m_stepX;
        for( idx = 0; idx < m_movingX.size(); idx++,++mvx_it,++pmv_it){
            auto &v = *mvx_it;
            auto &pmv = *pmv_it;
            if(pmv) {
                auto next = v + m_stepX;
                if (next >= m_maxX) {
                    if(m_bounceBack) {
                        auto gapBeforeMax = m_maxX - v;
                        v = m_maxX + gapBeforeMax - m_stepX;
                        pmv = false;
                    }
                    else {
                        v = m_vanish ? v + m_stepX : m_maxX;
                        ++replaceQty;
                    }
                } else {
                    v += m_stepX;
                }
            }
            else {
                auto next = v - m_stepX;
                auto min = this->tensor()->minVisibleXValue();
                if (next < min) {
                    if(m_bounceBack) {
                        auto gapBeforeMin = v - min;
                        v = min + m_stepX - gapBeforeMin;
                        pmv = true;
                    }
                    else {
                        v = m_vanish ? min - 1 : min;
                        --replaceQty;
                    }
                } else {
                    v -= m_stepX;
                }
            }
        }
        return replaceQty;
    }
    void MovingX::init(){
        size_t seriesSize = m_series->size();
        m_positiveMove.resize(seriesSize, true);
        m_movingX.clear();
        for( auto v : m_series->list()){
            auto x = -v.first;
            m_movingX.push_back(x+m_curDisplacement);
        }
    }
    bool MovingX::render(cv::Mat &figure) const{
        auto success = true;
        auto firstIteration = true;
        cv::Point2d previousPoint;
        if(m_series->size() != m_movingX.size())
            return false;
        auto mvx_it = m_movingX.begin();
        auto pmv_it = m_positiveMove.begin();
        for(auto vit = m_series->begin(); vit != m_series->end();){
            auto &mvx = *mvx_it;
            auto &pmv = *pmv_it;
            auto y = vit->second;
            if(this->tensor()->minVisibleXValue() > mvx) {
                ++vit;
                ++mvx_it;
                ++pmv_it;
                break;
            }
            cv::Point2d point;
            tensor()->transformToPixelBaseCoordinate(
                    point,
                    cv::Point3d(mvx,y, 0.0),
                    figure,
                    yawAngle(),
                    rollAngle(),
                    pitchAngle());
            if(mvx < m_maxX){
                cv::Scalar color = cv::Scalar(10,20,255);
                if(pmv){
                    color = cv::Scalar(255,25,10);
                }
                if(firstIteration){
                    firstIteration = false;
                }
                else {
                    cv::line(
                            figure,
                            previousPoint,
                            point,
                            scalarColor());
                }
                previousPoint = point;
                //cv::circle(figure,point,4,color);
                ++vit;
                ++mvx_it;
                ++pmv_it;
            }
            else {
                auto vit_del = vit++;
                auto mvx_it_del = mvx_it++;
                auto pmv_it_del = pmv_it++;
                m_series->erase(vit_del);
                m_movingX.erase(mvx_it_del);
                m_positiveMove.erase(pmv_it_del);
            }
        }
        return success;
    }
    MovingX &MovingX::setSeries(std::shared_ptr<Series> &series){
        m_series = series;
        return *this;
    }
}
