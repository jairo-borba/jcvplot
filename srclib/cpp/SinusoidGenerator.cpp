//
// Created by Jairo Borba on 12/23/21.
//

#include "SinusoidGenerator.h"
#include <cmath>
namespace jcvplot{
    const double SinusoidGenerator::defaultFrequencyHz = 1000.0;
    const double SinusoidGenerator::defaultSamplingFrequencyHz = 1000.0;
    double (*SinusoidGenerator::defaultFunction)(double) = sin;

    SinusoidGenerator::SinusoidGenerator(double initialPhase):
            m_currentPhase(initialPhase),
            m_samplingFrequency(defaultSamplingFrequencyHz),
            m_frequency(defaultFrequencyHz),
            m_func(defaultFunction),
            m_seriesPtr(std::make_shared<jcvplot::Series>())
    {
    }
    SinusoidGenerator::SinusoidGenerator(
            double frequency,
            double samplingFrequency,
            double initialPhase):
            m_currentPhase(initialPhase),
            m_samplingFrequency(samplingFrequency),
            m_frequency(frequency),
            m_func(defaultFunction),
            m_seriesPtr(std::make_shared<jcvplot::Series>())
    {
    }
    SinusoidGenerator::SinusoidGenerator(
            double frequency,
            double samplingFrequency,
            double (*func)(double),
            double initialPhase):
            m_currentPhase(initialPhase),
            m_samplingFrequency(samplingFrequency),
            m_frequency(frequency),
            m_func(func),
            m_seriesPtr(std::make_shared<jcvplot::Series>())
    {
    }
    SinusoidGenerator &SinusoidGenerator::setSamplingFrequency(double samplingFrequencyHz){
        m_samplingFrequency = samplingFrequencyHz > 1.0 ? samplingFrequencyHz : 1.0;
        return *this;
    }
    SinusoidGenerator &SinusoidGenerator::setFrequency(double frequencyHz){
        m_frequency = frequencyHz > 1.0 ? frequencyHz : 1.0;
        return *this;
    }
    SinusoidGenerator &SinusoidGenerator::setFunction(double (*func)(double)){
        m_func = func;
        return *this;
    }
    void SinusoidGenerator::generate(double startTime, double periodLength){
        static auto pi = acos(-1.0);
        static auto circleRad = 2.0*pi;
        auto startPhase = circleRad*startTime;
        m_currentPhase = startPhase;
        generate(*m_seriesPtr, periodLength);
    }
    void SinusoidGenerator::generate(double periodLength){
        generate(*m_seriesPtr, periodLength);
    }
    size_t SinusoidGenerator::secondsToSampleCount(double seconds){
        auto samplesCount = static_cast<size_t>(m_samplingFrequency*seconds) + 1.0;
        return samplesCount;
    }
    void SinusoidGenerator::generate(jcvplot::Series &series, double periodLength){
        auto samplesCount = secondsToSampleCount(periodLength);
        auto &list = series.list();
        static auto pi = acos(-1.0);
        static auto circleRad = 2.0*pi;
        auto deltaTime = 1.0 / m_samplingFrequency;
        auto periodRad = m_frequency*circleRad;
        for( size_t i = 0; i < samplesCount; ++i){
            auto y = m_func(m_currentPhase*periodRad);
            list.push_back({m_currentPhase,y});
            m_currentPhase += deltaTime;
        }
        std::cout << std::endl;
    }
    std::shared_ptr<jcvplot::Series> SinusoidGenerator::signalPtr(){
        return m_seriesPtr;
    }
    jcvplot::Series &SinusoidGenerator::operator()(){
        return *m_seriesPtr;
    }
    const jcvplot::Series &SinusoidGenerator::operator()() const{
        return *m_seriesPtr;
    }
    double SinusoidGenerator::samplingFrequency()const{
        return m_samplingFrequency;
    }
    double SinusoidGenerator::frequency()const{
        return m_frequency;
    }
}