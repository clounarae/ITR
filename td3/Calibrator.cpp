#include "Calibrator.h"

#include <iostream>


Calibrator::Calibrator(double samplingPeriod, unsigned nSamples)
{
    m_nSamples = nSamples;

    m_sampling.reserve(nSamples + 1);
    m_sampling.push_back(0.);
    
    std::cout << "Calibration starting ...\n";
    start(samplingPeriod);
    m_looper.runLoop();
    
    m_a = 0.;
    for(unsigned i = 1 ; i < m_sampling.size() ; i++)
        m_a += (m_sampling[i] - m_sampling[i-1]) / samplingPeriod;
    m_a /= m_sampling.size() - 1;
    
    m_b = 0.;
    for(unsigned i = 1 ; i < m_sampling.size() ; i++)
        m_b += m_sampling[i] - (m_a * samplingPeriod * i);
    m_b /= m_sampling.size() - 1;
    /*
    std::cout << "Samples values : (" << samplingPeriod << ")\n";
    for(int i = 0 ; i < m_sampling.size() ; i++)
        std::cout << i << "\t: " << m_sampling[i] << "\n";
    */
    std::cout << "Calibration values : a = " << m_a << "; b = " << m_b << ".\n";
}

Calibrator::~Calibrator()
{
    //Nuthin
}


double Calibrator::nLoops(double duration)
{
    return m_a * duration + m_b;
}


void Calibrator::callback(void)
{
    double rslt = m_looper.getSample();
    
    m_sampling.push_back(rslt);
    
    if(m_sampling.size() >= m_nSamples + 1) // First value is 0.
    {
        m_looper.stopLoop();
        stop();
    }
}
