//
// Created by Jairo Borba on 10/31/21.
//

#ifndef JCVPLOT_WINDOW_H
#define JCVPLOT_WINDOW_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "Form.h"
#include <vector>
#include "Figure.h"
namespace jcvplot {
    class Window : public Figure{
    private:
        std::vector<Form> m_forms;
    public:
        bool render(cv::Mat &figure) const override;
        Window(size_t numberOfForms = 1);
    };
}

#endif //JCVPLOT_WINDOW_H
