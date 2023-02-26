#include "sig.hpp"
#include "externStatus.hpp"

void handle_sig(int sig)
{
    (void)sig;
    std::cout << "\r";
    status = shutdown;
}

void ctl_d(int sig)
{
    (void)sig;
    std::cout << "heyyyyyyy";
    // gstatus = 0;
}