#include "externStatus.hpp"
#include "sig.hpp"

void handle_sig(int sig)
{
    (void)sig;
    std::cout << "\r";
    gstatus = 2; //2
}