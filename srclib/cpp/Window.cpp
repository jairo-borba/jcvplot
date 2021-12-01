//
// Created by Jairo Borba on 10/31/21.
//

#include "../include/jcvplot/Window.h"

namespace jcvplot {
    Window::Window(size_t numberOfForms):
        m_forms(numberOfForms){
    }
    bool Window::render(cv::Mat &figure) const{
        bool success = true;
        return success;
    }
}
