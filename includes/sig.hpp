#pragma once

#include <signal.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include "Server.hpp"
#include "status.hpp"

void handle_sig(int sig);
void ctl_d(int sig);