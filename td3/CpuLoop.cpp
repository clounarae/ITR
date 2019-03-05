#include "CpuLoop.h"



CpuLoop::CpuLoop(Calibrator & calibrator) : m_calibrator(calibrator)
{
    //Nuthin?
}

CpuLoop::~CpuLoop()
{
    //Nuthin!
}


void CpuLoop::runTime(double duration)
{
    runLoop(m_calibrator.nLoops(duration));
}
