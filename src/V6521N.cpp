#include "V6521N.h"
#include "sethv.h"

CVErrorCodes write_to_v6521n(uint32_t vme_addr, uint32_t data){
  CVDataWidth data_size = cvD16;
  CVAddressModifier addr_mode = cvA32_U_DATA;
  vme_addr = vme_addr + V6521N_BASE_ADDRESS;
  return CAENVME_WriteCycle(handle, vme_addr, &data, addr_mode, data_size);
}

CVErrorCodes read_from_v6521n(uint32_t vme_addr){
  CVDataWidth data_size = cvD16;
  CVAddressModifier addr_mode = cvA32_U_DATA;
  vme_addr = vme_addr + V6521N_BASE_ADDRESS;
  return CAENVME_ReadCycle(handle, vme_addr, &hv_data, addr_mode, data_size);
}

int get_powered_v6521n(uint32_t ch_num){
  uint32_t vme_addr;
  switch(ch_num)
    {
    case 0: vme_addr = V6521N_PW_CH0;
      break;
    case 1: vme_addr = V6521N_PW_CH1;
      break;
    case 2: vme_addr = V6521N_PW_CH2;
      break;
    case 3: vme_addr = V6521N_PW_CH3;
      break;
    case 4: vme_addr = V6521N_PW_CH4;
      break;
    case 5: vme_addr = V6521N_PW_CH5;
      break;
    default: printf("Bad choice of channel!");
      return -1;
    }
  read_from_v6521n(vme_addr);
  return (int)hv_data;
}
      

CVErrorCodes set_svmax_v6521n(uint32_t ch_num, uint32_t vmax){

  uint32_t vme_addr;
  vmax = (uint32_t) vmax/V6521N_VOLTAGE_RESOLUTION; /*e.g. 3 kV => 30000 in register*/
  switch(ch_num)
  {
    case 0:  vme_addr = V6521N_SVMAX_CH0;
             break;
    case 1:  vme_addr = V6521N_SVMAX_CH1;
             break;
    case 2:  vme_addr = V6521N_SVMAX_CH2;
             break;
    case 3:  vme_addr = V6521N_SVMAX_CH3;
             break;
    case 4:  vme_addr = V6521N_SVMAX_CH4;
             break;
    case 5:  vme_addr = V6521N_SVMAX_CH5;
             break;
    default: printf("Bad choice of channel!");
             return cvInvalidParam; 
  }
  return write_to_v6521n(vme_addr, vmax);
}

int get_svmax_v6521n(uint32_t ch_num){
  uint32_t vme_addr;
  switch(ch_num)
    {
    case 0:  vme_addr = V6521N_SVMAX_CH0;
      break;
    case 1:  vme_addr = V6521N_SVMAX_CH1;
      break;
    case 2:  vme_addr = V6521N_SVMAX_CH2;
      break;
    case 3:  vme_addr = V6521N_SVMAX_CH3;
      break;
    case 4:  vme_addr = V6521N_SVMAX_CH4;
      break;
    case 5:  vme_addr = V6521N_SVMAX_CH5;
      break;
    default: printf("Bad choice of channel!");
      return -1;
    }
  read_from_v6521n(vme_addr);
  return (int)(hv_data*V6521N_VOLTAGE_RESOLUTION);
}


CVErrorCodes set_current_v6521n(uint32_t ch_num, float current){
  uint32_t vme_addr;
  current = (uint32_t) (current/V6521N_CURRENT_RESOLUTION); /*e.g. 100microA => 
                                             20000 in register*/
  switch(ch_num)
  {
    case 0:  vme_addr = V6521N_ISET_CH0;
             break;
    case 1:  vme_addr = V6521N_ISET_CH1;
             break;
    case 2:  vme_addr = V6521N_ISET_CH2;
             break;
    case 3:  vme_addr = V6521N_ISET_CH3;
             break;
    case 4:  vme_addr = V6521N_ISET_CH4;
             break;
    case 5:  vme_addr = V6521N_ISET_CH5;
             break;
    default: printf("Bad choice of channel!");
             return cvInvalidParam; 
  }
  return write_to_v6521n(vme_addr, current);
}

CVErrorCodes set_voltage_v6521n(uint32_t ch_num, uint32_t voltage){
  uint32_t vme_addr;
  voltage = (uint32_t) voltage/V6521N_VOLTAGE_RESOLUTION; 
                                          
  switch(ch_num)
  {
    case 0:  vme_addr = V6521N_VSET_CH0;
             break;
    case 1:  vme_addr = V6521N_VSET_CH1;
             break;
    case 2:  vme_addr = V6521N_VSET_CH2;
             break;
    case 3:  vme_addr = V6521N_VSET_CH3;
             break;
    case 4:  vme_addr = V6521N_VSET_CH4;
             break;
    case 5:  vme_addr = V6521N_VSET_CH5;
             break;
    default: printf("Bad choice of channel!");
             return cvInvalidParam; 
  }
  return write_to_v6521n(vme_addr, voltage);
}

float get_voltage_v6521n(uint32_t ch_num){
  uint32_t vme_addr;
  switch(ch_num)
  {
    case 0:  vme_addr = V6521N_VMON_CH0;
             break;
    case 1:  vme_addr = V6521N_VMON_CH1;
             break;
    case 2:  vme_addr = V6521N_VMON_CH2;
             break;
    case 3:  vme_addr = V6521N_VMON_CH3;
             break;
    case 4:  vme_addr = V6521N_VMON_CH4;
             break;
    case 5:  vme_addr = V6521N_VMON_CH5;
             break;
    default: printf("Bad choice of channel!");
             return -1; 
  }
  read_from_v6521n(vme_addr);
  return (float)(hv_data*V6521N_VOLTAGE_RESOLUTION);
}

float get_config_voltage_v6521n(uint32_t ch_num){
  uint32_t vme_addr;
  switch(ch_num)
    {
    case 0: vme_addr = V6521N_VSET_CH0;
      break;
    case 1:  vme_addr = V6521N_VSET_CH1;
      break;
    case 2:  vme_addr = V6521N_VSET_CH2;
      break;
    case 3:  vme_addr = V6521N_VSET_CH3;
      break;
    case 4:  vme_addr = V6521N_VSET_CH4;
      break;
    case 5:  vme_addr = V6521N_VSET_CH5;
      break;
    default: printf("Bad choice of channel!");
      return -1;
    }
  read_from_v6521n(vme_addr);
  return (float)(hv_data*V6521N_VOLTAGE_RESOLUTION);
}


float get_current_v6521n(uint32_t ch_num){
  uint32_t vme_addr;
  switch(ch_num)
  {
    case 0:  vme_addr = V6521N_IMONH_CH0;
             break;
    case 1:  vme_addr = V6521N_IMONH_CH1;
             break;
    case 2:  vme_addr = V6521N_IMONH_CH2;
             break;
    case 3:  vme_addr = V6521N_IMONH_CH3;
             break;
    case 4:  vme_addr = V6521N_IMONH_CH4;
             break;
    case 5:  vme_addr = V6521N_IMONH_CH5;
             break;
    default: printf("Bad choice of channel!");
             return -1; 
  }
  read_from_v6521n(vme_addr);
  return (float)(hv_data*V6521N_CURRENT_RESOLUTION);
}

float get_config_current_v6521n(uint32_t ch_num){
  uint32_t vme_addr;
  switch(ch_num)
    {
    case 0:  vme_addr = V6521N_ISET_CH0;
      break;
    case 1:  vme_addr = V6521N_ISET_CH1;
      break;
    case 2:  vme_addr = V6521N_ISET_CH2;
      break;
    case 3:  vme_addr = V6521N_ISET_CH3;
      break;
    case 4:  vme_addr = V6521N_ISET_CH4;
      break;
    case 5:  vme_addr = V6521N_ISET_CH5;
      break;
    default: printf("Bad choice of channel!");
      return -1;
    }
  read_from_v6521n(vme_addr);
  return (float)(hv_data*V6521N_CURRENT_RESOLUTION);
}


uint32_t* get_channel_status_v6521n(uint32_t ch_num){
  uint32_t vme_addr;
  switch(ch_num)
    {
    case 0: vme_addr = V6521N_CHSTATUS_CH0;
      break;
    case 1: vme_addr = V6521N_CHSTATUS_CH1;
      break;
    case 2: vme_addr = V6521N_CHSTATUS_CH2;
      break;
    case 3: vme_addr = V6521N_CHSTATUS_CH3;
      break;
    case 4: vme_addr = V6521N_CHSTATUS_CH4;
      break;
    case 5: vme_addr = V6521N_CHSTATUS_CH5;
      break;
    default: printf("Bad choice of channel!\n");
      //return cvInvalidParam;
      return &hv_data;
    }
  read_from_v6521n(vme_addr);
  return &hv_data;
}

CVErrorCodes set_ramp_down_v6521n(uint32_t ch_num, uint32_t volts_per_sec){
  uint32_t vme_addr;
  switch(ch_num)
  {
    case 0:  vme_addr = V6521N_RAMP_DOWN_CH0;
             break;
    case 1:  vme_addr = V6521N_RAMP_DOWN_CH1;
             break;
    case 2:  vme_addr = V6521N_RAMP_DOWN_CH2;
             break;
    case 3:  vme_addr = V6521N_RAMP_DOWN_CH3;
             break;
    case 4:  vme_addr = V6521N_RAMP_DOWN_CH4;
             break;
    case 5:  vme_addr = V6521N_RAMP_DOWN_CH5;
             break;
    default: printf("Bad choice of channel!");
             return cvInvalidParam; 
  }
  return write_to_v6521n(vme_addr, volts_per_sec);
}

int get_ramp_down_v6521n(uint32_t ch_num){
  uint32_t vme_addr;
  switch(ch_num)
    {
    case 0:  vme_addr = V6521N_RAMP_DOWN_CH0;
      break;
    case 1:  vme_addr = V6521N_RAMP_DOWN_CH1;
      break;
    case 2:  vme_addr = V6521N_RAMP_DOWN_CH2;
      break;
    case 3:  vme_addr = V6521N_RAMP_DOWN_CH3;
      break;
    case 4:  vme_addr = V6521N_RAMP_DOWN_CH4;
      break;
    case 5:  vme_addr = V6521N_RAMP_DOWN_CH5;
      break;
    default: printf("Bad choice of channel!");
      return -1;
    }
  read_from_v6521n(vme_addr);
  return (int)hv_data;
}

int get_ramp_up_v6521n(uint32_t ch_num){
  uint32_t vme_addr;
  switch(ch_num)
    {
    case 0:  vme_addr = V6521N_RAMP_UP_CH0;
      break;
    case 1:  vme_addr = V6521N_RAMP_UP_CH1;
      break;
    case 2:  vme_addr = V6521N_RAMP_UP_CH2;
      break;
    case 3:  vme_addr = V6521N_RAMP_UP_CH3;
      break;
    case 4:  vme_addr = V6521N_RAMP_UP_CH4;
      break;
    case 5:  vme_addr = V6521N_RAMP_UP_CH5;
      break;
    default: printf("Bad choice of channel!");
      return -1;
    }
  read_from_v6521n(vme_addr);
  return (int)hv_data;
}


CVErrorCodes set_ramp_up_v6521n(uint32_t ch_num, uint32_t volts_per_sec){
  uint32_t vme_addr;
  switch(ch_num)
  {
    case 0:  vme_addr = V6521N_RAMP_UP_CH0;
             break;
    case 1:  vme_addr = V6521N_RAMP_UP_CH1;
             break;
    case 2:  vme_addr = V6521N_RAMP_UP_CH2;
             break;
    case 3:  vme_addr = V6521N_RAMP_UP_CH3;
             break;
    case 4:  vme_addr = V6521N_RAMP_UP_CH4;
             break;
    case 5:  vme_addr = V6521N_RAMP_UP_CH5;
             break;
    default: printf("Bad choice of channel!");
             return cvInvalidParam; 
  }
  return write_to_v6521n(vme_addr, volts_per_sec);
}

CVErrorCodes set_trip_time_v6521n(uint32_t ch_num, uint32_t trip_time){
  uint32_t vme_addr;
  trip_time = (uint32_t) trip_time/V6521N_TIME_RESOLUTION;

  switch(ch_num) {
    case 0:  vme_addr = V6521N_TRIP_TIME_CH0;
             break;
    case 1:  vme_addr = V6521N_TRIP_TIME_CH1;
             break;
    case 2:  vme_addr = V6521N_TRIP_TIME_CH2;
             break;
    case 3:  vme_addr = V6521N_TRIP_TIME_CH3;
             break;
    case 4:  vme_addr = V6521N_TRIP_TIME_CH4;
             break;
    case 5:  vme_addr = V6521N_TRIP_TIME_CH5;
             break;
    default: printf("Bad choice of channel!");
             return cvInvalidParam; 
  }
  return write_to_v6521n(vme_addr, trip_time);
}

int get_trip_time_v6521n(uint32_t ch_num){
  uint32_t vme_addr;

  switch(ch_num) {
  case 0:  vme_addr = V6521N_TRIP_TIME_CH0;
    break;
  case 1:  vme_addr = V6521N_TRIP_TIME_CH1;
    break;
  case 2:  vme_addr = V6521N_TRIP_TIME_CH2;
    break;
  case 3:  vme_addr = V6521N_TRIP_TIME_CH3;
    break;
  case 4:  vme_addr = V6521N_TRIP_TIME_CH4;
    break;
  case 5:  vme_addr = V6521N_TRIP_TIME_CH5;
    break;
  default: printf("Bad choice of channel!");
    return -1;
  }
  read_from_v6521n(vme_addr);
  return (int)(hv_data*V6521N_TIME_RESOLUTION);
}


CVErrorCodes enable_channel_v6521n(uint32_t ch_num){
  uint32_t vme_addr;

  switch(ch_num) {
    case 0:  vme_addr = V6521N_PW_CH0;
             break;
    case 1:  vme_addr = V6521N_PW_CH1;
             break;
    case 2:  vme_addr = V6521N_PW_CH2;
             break;
    case 3:  vme_addr = V6521N_PW_CH3;
             break;
    case 4:  vme_addr = V6521N_PW_CH4;
             break;
    case 5:  vme_addr = V6521N_PW_CH5;
             break;
    default: printf("Bad choice of channel!");
             return cvInvalidParam; 
  }
  return write_to_v6521n(vme_addr, 1);
}

CVErrorCodes disable_channel_v6521n(uint32_t ch_num){
  uint32_t vme_addr;

  switch(ch_num) {
    case 0:  vme_addr = V6521N_PW_CH0;
             break;
    case 1:  vme_addr = V6521N_PW_CH1;
             break;
    case 2:  vme_addr = V6521N_PW_CH2;
             break;
    case 3:  vme_addr = V6521N_PW_CH3;
             break;
    case 4:  vme_addr = V6521N_PW_CH4;
             break;
    case 5:  vme_addr = V6521N_PW_CH5;
             break;
    default: printf("Bad choice of channel!");
             return cvInvalidParam; 
  }
  return write_to_v6521n(vme_addr, 0);
}

CVErrorCodes ramp_down_channel_v6521n(uint32_t ch_num){
  uint32_t vme_addr;

  switch(ch_num) {
    case 0:  vme_addr = V6521N_PWDOWN_CH0;
             break;
    case 1:  vme_addr = V6521N_PWDOWN_CH1;
             break;
    case 2:  vme_addr = V6521N_PWDOWN_CH2;
             break;
    case 3:  vme_addr = V6521N_PWDOWN_CH3;
             break;
    case 4:  vme_addr = V6521N_PWDOWN_CH4;
             break;
    case 5:  vme_addr = V6521N_PWDOWN_CH5;
             break;
    default: printf("Bad choice of channel!");
             return cvInvalidParam; 
  }
  return write_to_v6521n(vme_addr, 1);
}

CVErrorCodes kill_channel_v6521n(uint32_t ch_num){
  uint32_t vme_addr;

  switch(ch_num) {
    case 0:  vme_addr = V6521N_PWDOWN_CH0;
             break;
    case 1:  vme_addr = V6521N_PWDOWN_CH1;
             break;
    case 2:  vme_addr = V6521N_PWDOWN_CH2;
             break;
    case 3:  vme_addr = V6521N_PWDOWN_CH3;
             break;
    case 4:  vme_addr = V6521N_PWDOWN_CH4;
             break;
    case 5:  vme_addr = V6521N_PWDOWN_CH5;
             break;
    default: printf("Bad choice of channel!");
             return cvInvalidParam; 
  }
  return write_to_v6521n(vme_addr, 0);
}

CVErrorCodes set_imon_high_v6521n(uint32_t ch_num){
  uint32_t vme_addr;
  
  switch(ch_num) {
  case 0: vme_addr = V6521N_IMON_RANGE_CH0;
    break;
  case 1: vme_addr = V6521N_IMON_RANGE_CH1;
    break;
  case 2: vme_addr = V6521N_IMON_RANGE_CH2;
    break;
  case 3: vme_addr = V6521N_IMON_RANGE_CH3;
    break;
  case 4: vme_addr = V6521N_IMON_RANGE_CH4;
    break;
  case 5: vme_addr = V6521N_IMON_RANGE_CH5;
    break;
  default: printf("Bad choice of channel!");
    return cvInvalidParam;
  }
  return write_to_v6521n(vme_addr, 0);
}

CVErrorCodes set_imon_low_v6521n(uint32_t ch_num){
  uint32_t vme_addr;

  switch(ch_num) {
  case 0: vme_addr = V6521N_IMON_RANGE_CH0;
    break;
  case 1: vme_addr = V6521N_IMON_RANGE_CH1;
    break;
  case 2: vme_addr = V6521N_IMON_RANGE_CH2;
    break;
  case 3: vme_addr = V6521N_IMON_RANGE_CH3;
    break;
  case 4: vme_addr = V6521N_IMON_RANGE_CH4;
    break;
  case 5: vme_addr = V6521N_IMON_RANGE_CH5;
    break;
  default: printf("Bad choice of channel!");
    return cvInvalidParam;
  }
  return write_to_v6521n(vme_addr, 1);
}

int get_pwdown_v6521n(uint32_t ch_num){
  uint32_t vme_addr;

  switch(ch_num) {
  case 0: vme_addr = V6521N_PWDOWN_CH0;
    break;
  case 1: vme_addr = V6521N_PWDOWN_CH1;
    break;
  case 2: vme_addr = V6521N_PWDOWN_CH2;
    break;
  case 3: vme_addr = V6521N_PWDOWN_CH3;
    break;
  case 4: vme_addr = V6521N_PWDOWN_CH4;
    break;
  case 5: vme_addr = V6521N_PWDOWN_CH5;
    break;
  default: printf("Bad choice of channel!");
    return -1;
  }
  read_from_v6521n(vme_addr);
  return (int)hv_data;
}

int get_imon_range_v6521n(uint32_t ch_num){
  uint32_t vme_addr;

  switch(ch_num) {
  case 0: vme_addr = V6521N_IMON_RANGE_CH0;
    break;
  case 1: vme_addr = V6521N_IMON_RANGE_CH1;
    break;
  case 2: vme_addr = V6521N_IMON_RANGE_CH2;
    break;
  case 3: vme_addr = V6521N_IMON_RANGE_CH3;
    break;
  case 4: vme_addr = V6521N_IMON_RANGE_CH4;
    break;
  case 5: vme_addr = V6521N_IMON_RANGE_CH5;
    break;
  default: printf("Bad choice of channel!");
    return -1;
  }
  read_from_v6521n(vme_addr);
  return (int)hv_data;
}
