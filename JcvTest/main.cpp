#include <iostream>
#include "jcvplot/Form.h"
#include "jcvplot/XAxis.h"
#include "jcvplot/YAxis.h"
#include "jcvplot/Border.h"
#include "jcvplot/Ruler.h"
#include "jcvplot/Stem.h"
#include "jcvplot/Line.h"
#include "jcvplot/Tensor.h"
#include "jcvplot/AxisAngle.h"
void setupAxis(
        jcvplot::Form &form,
        std::shared_ptr<jcvplot::Figure> axis,
        const jcvplot::AxisAngle &axisAngle){
    axis->setColor(jcvplot::Figure::Color_t(128,0,0));
    axis->setOffset(jcvplot::Figure::Offset_t(400,250,0));
    axis->setAxisAngle(axisAngle);
    form.addDynamicFigure(axis);
}

void setTensor2(std::shared_ptr<jcvplot::Tensor> tensor){
    jcvplot::Tensor::Boundaries_t bound{
            cv::Point2d(200,100),
            cv::Point2d(200,300)};
    jcvplot::Tensor::PixelsPerUnit_t pixelsPerUnit{50.0,50.0};
    jcvplot::Tensor::StartValue_t startValue{0.0,-2.0};
    jcvplot::Tensor::StepValue_t stepValue{2,0.5};
    tensor->setData(pixelsPerUnit,startValue,stepValue,bound);
}
void setTensor3(std::shared_ptr<jcvplot::Tensor> tensor, double pxPerUnit){
    jcvplot::Tensor::Boundaries_t bound{
            cv::Point2d(80,80),
            cv::Point2d(80,80)};
    jcvplot::Tensor::PixelsPerUnit_t pixelsPerUnit{pxPerUnit,pxPerUnit};
    jcvplot::Tensor::StartValue_t startValue{0.0,-2.0};
    jcvplot::Tensor::StepValue_t stepValue{2,0.5};
    tensor->setData(pixelsPerUnit,startValue,stepValue,bound);
}
void goSeries(
        std::vector<double> &xv,
        std::vector<double> &yv,
        double x_ini,
        double x_step,
        double x_max,
        double x_phase,
        double (*func)(double)){

    int count = static_cast<int>((x_max - x_ini) / x_step) + 1;
    xv.resize(count);
    yv.resize(count);
    size_t idx = 0;
    for( auto x  = x_ini; x <= x_max; x += x_step ){
        xv[idx] = x;
        yv[idx] = func(x+x_phase);
        idx++;
    }
}

int main() {
    std::cout << "Hello, World - Jcvplot test !" << std::endl;
    jcvplot::Form form;
    std::shared_ptr<jcvplot::XAxis> x_axis = std::make_shared<jcvplot::XAxis>();
    std::shared_ptr<jcvplot::YAxis> y_axis = std::make_shared<jcvplot::YAxis>();
    std::shared_ptr<jcvplot::Ruler> ruler = std::make_shared<jcvplot::Ruler>();
    std::shared_ptr<jcvplot::Border> border = std::make_shared<jcvplot::Border>();
    std::shared_ptr<jcvplot::Stem> stem = std::make_shared<jcvplot::Stem>();
    std::shared_ptr<jcvplot::Line> line = std::make_shared<jcvplot::Line>();
    std::shared_ptr<jcvplot::Series> series = std::make_shared<jcvplot::Series>();
    std::shared_ptr<jcvplot::Tensor> tensor = std::make_shared<jcvplot::Tensor>();
    setTensor2(tensor);
    x_axis->setTensor(tensor);
    y_axis->setTensor(tensor);
    ruler->setTensor(tensor);
    border->setTensor(tensor);
    stem->setTensor(tensor);
    line->setTensor(tensor);

    ruler->enableUp().enableLeft().enableRight().enableBottom();

    std::vector<double> xv;
    std::vector<double> yv;
    double x_phase = 0.0;

    series->setSeriesData(xv,yv);
    stem->setSeries(series);
    line->setSeries(series);
    ruler->setColor(
            jcvplot::Figure::Color_t(
                    120,
                    20,
                    20));
    ruler->enableHorizontalGrid().enableVerticalGrid();
    auto x_axisAngle = acos(-1)*0.0;
    auto y_axisAngle = -acos(-1)*0.0;
    ruler->setAxisAngle(
            jcvplot::AxisAngle(x_axisAngle,y_axisAngle,0.0)
            );
    border->setAxisAngle(
            jcvplot::AxisAngle(x_axisAngle,y_axisAngle,0.0)
    );
    stem->setAxisAngle(jcvplot::AxisAngle(x_axisAngle,y_axisAngle,0.0));
    line->setAxisAngle(jcvplot::AxisAngle(x_axisAngle,y_axisAngle,0.0));
    border->setThickness(1);
    border->setColor(jcvplot::Figure::Color_t(50,50,50));
    form.addDynamicFigure(ruler);
    form.addDynamicFigure(border);
    form.addDynamicFigure(line);
    setupAxis(form,
              x_axis,
              jcvplot::AxisAngle(
                      0.0,
                      0.0,
                      0.0));
    setupAxis(form,
              y_axis,
              jcvplot::AxisAngle(
                      0.0,
                      0.0,
                      0.0));
    form.setColor(jcvplot::Figure::Color_t(200,200,200));
    form.init(700,1400);
    form.renderAll();
    form.renderDynamic();
    cv::imshow("JCVPlot", form.anime());
    cv::waitKey(0);
    auto max = 200;
    for(int a = 0; a <= max; a++) {
        auto x_axisAngle = 2.0*acos(-1) * static_cast<double>(a)/static_cast<double>(max);
        auto y_axisAngle = 2.0*acos(-1) * static_cast<double>(a)/static_cast<double>(max);
        auto z_axisAngle = y_axisAngle;
        goSeries(xv,yv,0.0,0.01,
                 2*acos(-1), x_phase, sin);
        x_phase += 0.5;
        series->clear();
        series->setSeriesData(xv,yv);
        ruler->setAxisAngle(
                jcvplot::AxisAngle(
                        x_axisAngle,
                        y_axisAngle,
                        z_axisAngle)
        );
        border->setAxisAngle(
                jcvplot::AxisAngle(
                        x_axisAngle,
                        y_axisAngle,
                        z_axisAngle)
        );
        stem->setAxisAngle(jcvplot::AxisAngle(x_axisAngle,y_axisAngle,z_axisAngle));
        line->setAxisAngle(jcvplot::AxisAngle(x_axisAngle,y_axisAngle,z_axisAngle));
        x_axis->setAxisAngle(jcvplot::AxisAngle(x_axisAngle,y_axisAngle,z_axisAngle));
        y_axis->setAxisAngle(jcvplot::AxisAngle(x_axisAngle,y_axisAngle,z_axisAngle));
        //setTensor3(tensor,30.0+static_cast<double>(a)/2.0);
        form.renderDynamic();
        cv::imshow("JCVPlot", form.anime());
        if( cv::waitKey(50.0) == 'q')
            break;
    }
    cv::waitKey(0);
    return 0;
}
