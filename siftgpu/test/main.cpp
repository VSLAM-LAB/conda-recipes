// Link check against SiftGPU::sift_gpu: creates the objects AllFeature-VSLAM uses, without running them (no GPU).
#include <SiftGPU.h>

#include <cstdio>

int main(int argc, char**)
{
    if (argc > 1)  // never taken in the test task; keeps the calls from being optimised away
    {
        SiftGPU* sift = CreateNewSiftGPU(1);
        SiftMatchGPU* matcher = CreateNewSiftMatchGPU(4096);
        std::printf("%p %p\n", static_cast<void*>(sift), static_cast<void*>(matcher));
        delete sift;
        delete matcher;
    }
    return 0;
}
