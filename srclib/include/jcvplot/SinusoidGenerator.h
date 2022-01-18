//
// Created by Jairo Borba on 12/23/21.
//
#ifndef JCVPLOT_SINUSOIDGENERATOR_H
#define JCVPLOT_SINUSOIDGENERATOR_H
#include <functional>
#include <cmath>
namespace jcvplot {
    template<class T, class func_t = std::function<T(T)>> class SinusoidGenerator {
    public:
        double _initialPhase;
        double _currentPhase;
        double _samplingFrequency;
        double _frequency;
        func_t _fnc_calc;
        SinusoidGenerator()=default;
        SinusoidGenerator(const SinusoidGenerator&)=default;
        SinusoidGenerator(SinusoidGenerator&)=default;
        SinusoidGenerator(SinusoidGenerator&&)=default;
        SinusoidGenerator(
                double startPhase,
                double samplingFrequency,
                double frequency,
                func_t fnc_calc = [](T input)->T{return sin(input);}):
                _initialPhase(startPhase),
                _currentPhase(startPhase),
                _samplingFrequency(samplingFrequency),
                _frequency(frequency),
                _fnc_calc(fnc_calc){
        }
        void reset(){
            _currentPhase = _initialPhase;
        }
        void operator()(std::pair<T,T> &coordinate) {
            static auto pi = acos(-1.0);
            static auto circleRad = 2.0 * pi;
            auto deltaTime = 1.0 / _samplingFrequency;
            auto periodRad = _frequency * circleRad;
            auto y = _fnc_calc(_currentPhase * periodRad);
            _currentPhase += deltaTime;
            coordinate.first = _currentPhase;
            coordinate.second = y;
        }
    };
    double operator "" _msecs(long double mSeconds){
        auto samplesCount = static_cast<double>(mSeconds/1000.0);
        return samplesCount;
    };
}
#endif //JCVPLOT_SINUSOIDGENERATOR_H
