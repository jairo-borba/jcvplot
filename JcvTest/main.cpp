
// DISCLAIMER:[START]
// THIS FILE IS A SANDBOX, I USE IT FOR TESTS AND EXPERIMENTS
// DONE DURING SPARE TIME, BUT STILL WITH LOVE :D
// WE ARE GOING TO CREATE FACTORIES AND UTILITIES ONCE WE DEFINE THE LAYOUTS
// DISCLAIMER:[END]

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
#include "jcvplot/MovingX.h"
#include "jcvplot/SinusoidGenerator.h"
#include <math.h>
void setupAxis(
        jcvplot::Form &form,
        std::shared_ptr<jcvplot::Figure> axis,
        const jcvplot::AxisAngle &axisAngle){
    axis->setColor(jcvplot::Figure::Color_t(128,0,0));
    axis->setOffset(jcvplot::Figure::Offset_t(400,250,0));
    axis->setYawAngle(axisAngle);
}
void setTensor2(std::shared_ptr<jcvplot::Tensor> tensor){
    jcvplot::Tensor::Boundaries_t bound{
            cv::Point2d(100,50),
            cv::Point2d(100,50)};
    jcvplot::Tensor::PixelsPerUnit_t pixelsPerUnit{50.0,50.0};
    jcvplot::Tensor::StartValue_t startValue{0.,-2.0};
    jcvplot::Tensor::StepValue_t stepValue{2,2};
    tensor->setData(pixelsPerUnit,startValue,stepValue,bound);
}
double f(double){
    return 0.;
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
    std::shared_ptr<jcvplot::MovingX> mov = std::make_shared<jcvplot::MovingX>();
    std::shared_ptr<jcvplot::Tensor> tensor = std::make_shared<jcvplot::Tensor>();
    //jcvplot::SinusoidGenerator signal(1,50,
    //                                  [](double phase){ return sin(phase);});
    //std::shared_ptr<jcvplot::Series> series = signal.signalPtr();
    jcvplot::SinusoidGenerator<double> signal(
            0.,
            50.,
            1.,
            [](double input){return sin(input);});

    std::shared_ptr<jcvplot::Series<double>> series =
            std::make_shared<jcvplot::Series<double>>();
    setTensor2(tensor);
    x_axis->setTensor(tensor);
    y_axis->setTensor(tensor);
    ruler->setTensor(tensor);
    border->setTensor(tensor);
    stem->setTensor(tensor);
    line->setTensor(tensor);
    mov->setTensor(tensor);
    ruler->enableUp().enableLeft().enableRight().enableBottom();
    stem->setSeries(series);
    line->setSeries(series);
    mov->setSeries(series);
    ruler->setColor(
            jcvplot::Figure::Color_t(
                    120,
                    20,
                    20));
    ruler->enableHorizontalGrid().enableVerticalGrid();
    auto x_axisAngle = acos(-1)*0.0;
    auto y_axisAngle = -acos(-1)*0.0;
    ruler->setYawAngle(
            jcvplot::AxisAngle(x_axisAngle,y_axisAngle,0.0)
            );
    border->setYawAngle(
            jcvplot::AxisAngle(x_axisAngle,y_axisAngle,0.0)
    );
    stem->setYawAngle(jcvplot::AxisAngle(x_axisAngle,y_axisAngle,0.0));
    line->setYawAngle(jcvplot::AxisAngle(x_axisAngle,y_axisAngle,0.0));
    border->setThickness(1);
    border->setColor(jcvplot::Figure::Color_t(50,50,50));
    form.addDynamicFigure(ruler);
    form.addDynamicFigure(border);
    form.addDynamicFigure(line);
    //form.addDynamicFigure(stem);
    form.addDynamicFigure(mov);
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
    mov->setup(0.0,20.,.1,true,true);
    const std::function<void(std::pair<double,double>&)> &fn = signal;
    //series->setLoadFunction(signal);
    auto myX = 0;
    std::array<double,11> arr{0,.1,.2,.3,.4,.5,.6,.7,.8,.9,1};
    series->setLoadFunction(jcvplot::SinusoidGenerator<double>(0.,
                            50.,
                            1.,
                            [](double input)->double {return cos(input);}));
    //series->setLoadFunction([myX, &arr](std::pair<double,double>& v) mutable noexcept(true)
    //                        {v.second = arr[myX%arr.size()];v.first = myX++;});
    //series->setLoadFunction([](std::pair<double,double>& in){static auto x = 0.0; in.first = x+=0.1;in.second=sin(x);});
    series->load(240);
    series->load(240);
    mov->init();
    form.setColor(jcvplot::Figure::Color_t(200,200,200));
    form.init(700,1400);
    form.renderAll();
    form.renderDynamic();
    cv::imshow("JCVPlot", form.anime());
    cv::waitKey(0);
    auto max = 200;
    auto freq = 0.8;
    auto x_ini = 0.0;
    auto running = true;
    auto prevSz = series->list().size();
    for(int a = 0; running; a++)
    {
        auto x_axisAngle = 0.0*2.0*0.5*acos(-1) * static_cast<double>(a)/static_cast<double>(max);
        auto y_axisAngle = 0.0*2.0*0.5*acos(-1) * static_cast<double>(a)/static_cast<double>(max);
        auto z_axisAngle = y_axisAngle;
        mov->step();
        if(prevSz != series->list().size()) {
            prevSz = series->list().size();
            if (prevSz < 250) {
                series->load(50);
                mov->init();
            }
        }
        ruler->setYawAngle(
                jcvplot::AxisAngle(
                        x_axisAngle,
                        y_axisAngle,
                        z_axisAngle)
        );
        border->setYawAngle(
                jcvplot::AxisAngle(
                        x_axisAngle,
                        y_axisAngle,
                        z_axisAngle)
        );
        stem->setYawAngle(jcvplot::AxisAngle(x_axisAngle,y_axisAngle,z_axisAngle));
        line->setYawAngle(jcvplot::AxisAngle(x_axisAngle,y_axisAngle,z_axisAngle));
        x_axis->setYawAngle(jcvplot::AxisAngle(x_axisAngle,y_axisAngle,z_axisAngle));
        y_axis->setYawAngle(jcvplot::AxisAngle(x_axisAngle,y_axisAngle,z_axisAngle));
        form.renderDynamic();
        cv::imshow("JCVPlot", form.anime());

        char key = cv::waitKey(20.0);
        switch(key)
        {
            case 's':
                //signal.setSamplingFrequency(signal.samplingFrequency()+1.0);
                break;
            case 'a':
                //signal.setSamplingFrequency(signal.samplingFrequency()-1.0);
                break;
            case 'f':
                //signal.setFrequency(signal.frequency()+1.0);
                break;
            case 'd':
                //signal.setFrequency(signal.frequency()-1.0);
                break;
            case 'w':
                for(;;){
                    if(cv::waitKey(50.0) == 'c')
                        break;
                }
                break;
            case 'q':
                running = false;
                break;
        }
    }
    cv::waitKey(20.0);
    return 0;
}
