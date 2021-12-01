//
// Created by Jairo Borba on 10/31/21.
//
#include "Form.h"
namespace jcvplot{
    void Form::init(int rows, int cols){
        m_rows = rows;
        m_cols = cols;
        m_image = cv::Mat(
                cv::Size(m_cols,m_rows),
                CV_8UC3,
                this->scalarColor());
    }
    void Form::close(){

    }
    const cv::Mat Form::image()const{
        return m_image;
    }
    const cv::Mat Form::anime()const{
        return m_anime;
    }
    bool Form::renderAll() {
        this->render(m_image);
        for(auto &fig : this->figures()){
            if(fig.second->isOn()) {
                fig.second->render(m_image);
            }
        }

        m_image.copyTo(m_anime);
        for(auto &fig : this->dynamicFigures()){
            if(fig.second->isOn()) {
                fig.second->render(m_anime);
            }
        }
        return true;
    }
    bool Form::renderDynamic() {
        m_image.copyTo(m_anime);
        for(auto &fig : this->dynamicFigures()){
            if(fig.second->isOn()) {
                fig.second->render(m_anime);
            }
        }
        return true;
    }
    bool Form::render(cv::Mat &figure) const{
        bool success = true;
        typedef cv::Point3_<uint8_t> Pixel;
        const Color_t  &formColor = color();
        figure.forEach<Pixel>([formColor](Pixel &p, const int * position) -> void {
            p.x = formColor.x;
            p.y = formColor.y;
            p.z = formColor.z;
        });

        return success;
    }
}
