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
void setupAxis(
        jcvplot::Form &form,
        std::shared_ptr<jcvplot::Figure> axis,
        const jcvplot::AxisAngle &axisAngle){
    axis->setColor(jcvplot::Figure::Color_t(128,0,0));
    axis->setOffset(jcvplot::Figure::Offset_t(400,250,0));
    axis->setYawAngle(axisAngle);
    //form.addDynamicFigure(axis);
}

void setTensor2(std::shared_ptr<jcvplot::Tensor> tensor){
    jcvplot::Tensor::Boundaries_t bound{
            cv::Point2d(100,50),
            cv::Point2d(100,50)};
    jcvplot::Tensor::PixelsPerUnit_t pixelsPerUnit{5000.0,50.0};
    jcvplot::Tensor::StartValue_t startValue{0.0,-2.0};
    jcvplot::Tensor::StepValue_t stepValue{2,2};
    tensor->setData(pixelsPerUnit,startValue,stepValue,bound);
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

    jcvplot::SinusoidGenerator signal(100,4000);
    std::shared_ptr<jcvplot::Series> series = signal.signalPtr();
    signal.generate(40.0);
    setTensor2(tensor);
    x_axis->setTensor(tensor);
    y_axis->setTensor(tensor);
    ruler->setTensor(tensor);
    border->setTensor(tensor);
    stem->setTensor(tensor);
    line->setTensor(tensor);
    mov->setTensor(tensor);

    ruler->enableUp().enableLeft().enableRight().enableBottom();

    std::vector<double> xv;
    std::vector<double> yv;
    double x_phase = 1.2;

    series->setSeriesData(xv,yv);
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
    //form.addDynamicFigure(line);
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
    mov->setup(-2*acos(-1),8.0,0.1,false,true);
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
    for(int a = 0; running; a++)
    {
        auto x_axisAngle = 0.0*2.0*0.5*acos(-1) * static_cast<double>(a)/static_cast<double>(max);
        auto y_axisAngle = 0.0*2.0*0.5*acos(-1) * static_cast<double>(a)/static_cast<double>(max);
        //x_axisAngle = 0.5*acos(-1);
        //y_axisAngle = 0.5*acos(-1);
        auto z_axisAngle = y_axisAngle;
        //goSeries(xv,yv,0.0,0.5,2*acos(-1), x_phase, sin);
        x_phase += 0.0;//0.3;
        mov->step();
        if(series->size() < signal.secondsToSampleCount(3.0)){
            signal.generate(4.0);
            mov->init();
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
                signal.setSamplingFrequency(signal.samplingFrequency()+1.0);
                break;
            case 'a':
                signal.setSamplingFrequency(signal.samplingFrequency()-1.0);
                break;
            case 'f':
                signal.setFrequency(signal.frequency()+1.0);
                break;
            case 'd':
                signal.setFrequency(signal.frequency()-1.0);
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
