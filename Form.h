//
// Created by Jairo Borba on 10/31/21.
//
#ifndef JCVPLOT_FORM_H
#define JCVPLOT_FORM_H
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "Figure.h"
namespace jcvplot {
    class Form :public Figure{
    private:
        mutable cv::Mat m_image;
        mutable cv::Mat m_anime;
        int m_rows;
        int m_cols;
    public:
        void init(int rows, int cols);
        void close();
        bool render(cv::Mat &figure) const override;
        bool renderAll();
        bool renderDynamic();
        const cv::Mat image()const;
        const cv::Mat anime()const;
    };
}
#endif //JCVPLOT_FORM_H
