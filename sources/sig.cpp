#include "sig.hpp"


void handle_sig(int sig)
{
    (void)sig;
    std::cout << "\r";
    gstatus = 0;
}

void ctl_d(int sig)
{
    (void)sig;
    std::cout << "heyyyyyyy";
    // gstatus = 0;
}