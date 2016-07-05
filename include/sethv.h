#ifndef SETHV_H
#define SETHV_H

#define V1718_USB_PORT 1

#include "V6521N.h"
#include "V6521P.h"

#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include "CAENVMElib.h"

extern uint32_t hv_data;
extern int32_t handle;
extern std::vector<int> enable_channel;
extern std::string config_file;

int init();
std::string status(int ch, int board);
int setconfig();
int powerdown();
int powerup();
int getconfig();
int monitor();
int rampspeed(int speed);

struct STATUS_REGISTER {
  unsigned ON:1;
  unsigned RAMPUP:1;
  unsigned RAMPDOWN:1;
  unsigned OVERCURRENT:1;
  unsigned OVERVOLTAGE:1;
  unsigned UNDERVOLTAGE:1;
  unsigned MAXV:1;
  unsigned MAXI:1;
  unsigned TRIP:1;
  unsigned OVERPOWER:1;
  unsigned OVERTEMPERATURE:1;
  unsigned DISABLED:1;
  unsigned INTERLOCK:1;
  unsigned UNCALIBRATED:1;
};


#endif
