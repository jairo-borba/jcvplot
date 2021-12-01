// Created by Jairo Borba on 11/1/21.
#ifndef JCVPLOT_SERIES_H
#define JCVPLOT_SERIES_H
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
namespace jcvplot {
    class Series {
    public:
        typedef double SeriesPoint_t;
        typedef std::vector<std::pair<SeriesPoint_t,SeriesPoint_t>> Series_t;
    private:
        Series_t m_series;
    public:
        bool setSeriesData(
                const std::vector<SeriesPoint_t> &x_data,
                const std::vector<SeriesPoint_t> &y_data);
        void clear();
        Series_t::const_iterator begin() const;
        Series_t::const_iterator end() const;
        Series_t::iterator begin();
        Series_t::iterator end();
        Series_t series() const;
    };

    typedef Series::Series_t::const_iterator series_const_it;
    typedef Series::Series_t::iterator series_it;
}
#endif //JCVPLOT_SERIES_H
