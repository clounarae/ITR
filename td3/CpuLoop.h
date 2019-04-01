#ifndef td3_CpuLoop_h_INCLUDED
#define td3_CpuLoop_h_INCLUDED


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


#endif
