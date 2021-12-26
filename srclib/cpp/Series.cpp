//
// Created by Jairo Borba on 11/1/21.
//

#include "../include/jcvplot/Series.h"
namespace jcvplot {

    size_t Series::size() const{
        return m_series.size();
    }

    bool Series::setSeriesData(
            const std::vector<Series::SeriesPoint_t> &x_data,
            const std::vector<Series::SeriesPoint_t> &y_data){
        auto x_size = x_data.size();
        auto y_size = y_data.size();
        if( x_size != y_size ){
            return false;
        }
        for (size_t i = 0; i < x_size; ++i){
            m_series.push_back({x_data[i],y_data[i]});
        }

        return true;
    }
    bool Series::setSeriesData(
            const std::vector<SeriesPoint_t> &y_data,
            SeriesPoint_t x_step,
            SeriesPoint_t x_start){
        auto x = x_start;
        for(auto y : y_data){
            m_series.push_back({x, y});
            x += x_step;
        }
        return true;
    }
    void Series::erase(Series_t::iterator &it){
        m_series.erase(it);
    }
    void Series::clear(){
        m_series.clear();
    }
    const Series::Series_t &Series::list() const{
        return m_series;
    }
    Series::Series_t &Series::list(){
        return m_series;
    }
    series_const_it Series::begin() const{
        return m_series.begin();
    }
    series_const_it Series::end() const{
        return m_series.end();
    }
    series_it Series::begin(){
        return m_series.begin();
    }
    series_it Series::end(){
        return m_series.end();
    }
}