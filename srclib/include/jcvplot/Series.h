// Created by Jairo Borba on 11/1/21.
#ifndef JCVPLOT_SERIES_H
#define JCVPLOT_SERIES_H
#include <vector>
#include <list>
#include <functional>
namespace jcvplot {
    template<class T> class Series {
    public:
        using SeriesCoord_t = T;
        using SeriesPoint_t = std::pair<SeriesCoord_t,SeriesCoord_t>;
        using Series_t = std::list<SeriesPoint_t>;
    private:
        Series_t m_series;
        std::function<void(std::pair<T,T>&)> m_loadFunction;
    public:
        void setLoadFunction(const std::function<void(std::pair<T,T>&)> &loadFunction){
            m_loadFunction = std::move(loadFunction);
        }
        void load(size_t count){
            auto coord = std::make_pair(0.,0.);
            for(auto i = 0; i < count; ++i) {
                m_loadFunction(coord);
                m_series.push_back(coord);
            }
        }
        const Series_t &list() const{
            return m_series;
        }
        Series_t &list(){
            return m_series;
        }
    };
}
#endif //JCVPLOT_SERIES_H
