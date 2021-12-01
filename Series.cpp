//
// Created by Jairo Borba on 11/1/21.
//

#include "Series.h"
namespace jcvplot {

    bool Series::setSeriesData(
            const std::vector<Series::SeriesPoint_t> &x_data,
            const std::vector<Series::SeriesPoint_t> &y_data){
        auto x_size = x_data.size();
        auto y_size = y_data.size();
        if( x_size != y_size ){
            return false;
        }
        if(x_size != m_series.size())
            m_series.resize(x_size);
        for (size_t i = 0; i < x_size; ++i){
            m_series[i] =
                    std::pair<SeriesPoint_t,SeriesPoint_t>(x_data[i],y_data[i]);
        }

        return true;
    }
    void Series::clear(){
        m_series.clear();
    }
    Series::Series_t Series::series() const{
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