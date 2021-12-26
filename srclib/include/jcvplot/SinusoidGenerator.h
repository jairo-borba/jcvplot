//
// Created by Jairo Borba on 12/23/21.
//

#ifndef JCVPLOT_SINUSOIDGENERATOR_H
#define JCVPLOT_SINUSOIDGENERATOR_H
#include "Series.h"
namespace jcvplot {
    class SinusoidGenerator {
    private:
        double m_currentPhase;
        double m_samplingFrequency;
        double m_frequency;
        double (*m_func)(double);
        std::shared_ptr<jcvplot::Series> m_seriesPtr;
    public:
        static const double defaultFrequencyHz;
        static const double defaultSamplingFrequencyHz;
        static double (*defaultFunction)(double);
        SinusoidGenerator(double initialPhase = 0.0);
        SinusoidGenerator(
                double frequency,
                double samplingFrequency,
                double initialPhase = 0.0);
        SinusoidGenerator(
                double frequency,
                double samplingFrequency,
                double (*func)(double),
                double initialPhase = 0.0);
        SinusoidGenerator &setSamplingFrequency(double samplingFrequencyHz);
        SinusoidGenerator &setFrequency(double frequencyHz);
        SinusoidGenerator &setFunction(double (*func)(double));
        double samplingFrequency()const;
        double frequency()const;
        size_t secondsToSampleCount(double seconds);
        void generate(double startTime, double periodLength);
        void generate(double periodLength);
        void generate(jcvplot::Series &series, double periodLength);
        std::shared_ptr<jcvplot::Series> signalPtr();
        jcvplot::Series &operator()();
        const jcvplot::Series &operator()() const;
    };
}

#endif //JCVPLOT_SINUSOIDGENERATOR_H
