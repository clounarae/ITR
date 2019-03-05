#ifndef __TD3_CALIBRATOR_H
#define __TD3_CALIBRATOR_H

#include <vector>

#include "PeriodicTimer.h"
#include "Looper.h"


class Calibrator : public PeriodicTimer
{
    public:
        Calibrator(double samplingPeriod, unsigned nSamples);
        ~Calibrator();
        Calibrator(const Calibrator & e) = delete;
        Calibrator & operator=(const Calibrator & e) = delete;

        double nLoops(double duration);

        virtual void callback(void);

    private:
        double m_a;
        double m_b;
        unsigned m_nSamples;
        std::vector<double> m_sampling;
        Looper m_looper;
};


#endif  //__TD3_CALIBRATOR_H
