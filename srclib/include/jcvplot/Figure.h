//
// Created by Jairo Borba on 10/31/21.
//
#ifndef JCVPLOT_FIGURE_H
#define JCVPLOT_FIGURE_H
#include <opencv2/opencv.hpp>
#include "ID.h"
#include <memory>
#include <list>
#include <utility>
#include <map>
#include "Tensor.h"
#include "AxisAngle.h"
namespace jcvplot {
    class Figure {
    public:
        typedef cv::Point3_<uint8_t> Color_t;
        typedef cv::Point3_<int32_t> Offset_t;
        typedef std::multimap<int,std::shared_ptr<Figure>> FigureContainer_t;
        typedef std::pair<size_t,std::shared_ptr<Figure>> FigureContainerPair_t;
        static const int DEFAULT_INSERT_SEQ_NO = 1024;
    private:
        bool m_on;
        ID m_id;
        Color_t m_color;
        FigureContainer_t m_figures;
        FigureContainer_t m_dynamicFigures;
        float m_scale;
        Offset_t m_offset;
        AxisAngle m_axisAngle;
        std::shared_ptr<Tensor> m_tensor;
    public:
        const std::shared_ptr<Tensor> &getTensor() const;
        const std::shared_ptr<Tensor> &tensor() const;
        void setTensor(const std::shared_ptr<Tensor> &mTensor);
        const AxisAngle& axisAngle()const;
        Figure &setAxisAngle(const AxisAngle&axisAngle);
    protected:
        const FigureContainer_t& figures()const;
        FigureContainer_t& figures();
        const FigureContainer_t& dynamicFigures()const;
        FigureContainer_t& dynamicFigures();
    public:
        Figure();
        virtual bool render(cv::Mat &figure) const = 0;
        virtual ~Figure()=default;
        const Color_t &color() const;
        cv::Scalar scalarColor() const;
        Figure& setID(const ID &id);
        Figure& off();
        Figure& on();
        bool isOn()const;
        virtual Figure& addFigure(std::shared_ptr<Figure> fig, int seq_no = DEFAULT_INSERT_SEQ_NO);
        virtual Figure& addDynamicFigure(std::shared_ptr<Figure> fig, int seq_no = DEFAULT_INSERT_SEQ_NO);
        Figure& setColor(const Color_t &color);
        Figure& setScale(float scale);
        float scale() const;
        Figure& setOffset(const Offset_t &offset);
        const Offset_t &offset() const;
    };
}

#endif //JCVPLOT_FIGURE_H
