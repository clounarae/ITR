#ifndef __TD3_CPU_LOOP_H
#define __TD3_CPU_LOOP_H


#include "Calibrator.h"
#include "Looper.h"


class CpuLoop : public Looper
{
    public:
        CpuLoop(Calibrator & calibrator);
        ~CpuLoop();
        CpuLoop(const CpuLoop & e) = delete;
        CpuLoop & operator=(const CpuLoop & e) = delete;

        void runTime(double duration);

    private:
        Calibrator & m_calibrator;
};


#endif  //__TD3_CPU_LOOP_H
