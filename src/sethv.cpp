#include "sethv.h"

int32_t handle;
uint32_t hv_data;
std::vector<int> enable_channel;
std::string config_file;

int monitor()
{
  CVBoardTypes vme_board = cvV1718;
  CVErrorCodes ret;

  ret = CAENVME_Init(vme_board, 0, 0, &handle);
  if (ret != cvSuccess)
    {
      printf("\n\n Error opening V1718! \n\n");
      CAENVME_End(handle);
      return 1;
    }

  bool ready = true;
  int num_not_ready = 0;
  bool off = true;
  for (int ch = 0; ch < 6; ch++)
    {
      std::string stat = status(ch,-1);
      ready = (!strcmp(stat.c_str(),"ON ") || !strcmp(stat.c_str(),"OFF"));
      if (!ready)
	{
	  num_not_ready++;
	  printf("\x1b[37;41m V6521N -- CH%i -- %6.1f V -- %6.3f uA -- %s\x1b[39;49m\n",ch,get_voltage_v6521n(ch),get_current_v6521n(ch),stat.c_str());
	}
      else
	{
	  printf("\x1b[32m V6521N -- CH%i -- %6.1f V -- %6.3f uA -- %s\x1b[39m\n",ch,get_voltage_v6521n(ch),get_current_v6521n(ch),stat.c_str());
	}    
    }  
  for (int ch = 0; ch < 6; ch++)
    {
      std::string stat = status(ch,1);
      ready = (!strcmp(stat.c_str(),"ON ") || !strcmp(stat.c_str(),"OFF"));
      if (!ready)
	{
          num_not_ready++;
	  printf("\x1b[37;41m V6521P -- CH%i -- %6.1f V -- %6.3f uA -- %s\x1b[39;49m\n",ch,get_voltage_v6521p(ch),get_current_v6521p(ch),stat.c_str());
        }
      else
	{
	  printf("\x1b[32m V6521P -- CH%i -- %6.1f V -- %6.3f uA -- %s\x1b[39m\n",ch,get_voltage_v6521p(ch),get_current_v6521p(ch),stat.c_str());
        }
    }
 
  if (!ready) return 1;
  if (off) return 2;
  return 0;
}

int getconfig()
{
  CVBoardTypes vme_board = cvV1718;
  CVErrorCodes ret;

  ret = CAENVME_Init(vme_board, 0, 0, &handle);
  if (ret != cvSuccess)
    {
      printf("\n\n Error opening V1718! \n\n");
      CAENVME_End(handle);
      return 1;
    }
  
  std::string BOARD,CHNUM,VSET,ISET,
    PW,TRIP_TIME,SVMAX,RAMP_DOWN,
    RAMP_UP,PWDOWN,IMON_RANGE;
  
  std::string line;
  std::ifstream configfile (config_file.c_str(),std::ifstream::in);
  
  if (configfile.is_open())
    {
      while (getline(configfile,line))
        {
	  std::stringstream ss(line);
          ss >> BOARD;
          if (BOARD == "N")
            {
              ss >> CHNUM >> VSET >> ISET >> PW >> TRIP_TIME
                 >> SVMAX >> RAMP_DOWN >> RAMP_UP >> PWDOWN >> IMON_RANGE;

              if (stoi(PW))
		{
		  enable_channel.push_back((uint32_t)stoi(CHNUM)+10);
		}
            }
          else if (BOARD == "P")
            {
              ss >> CHNUM >> VSET >> ISET >> PW >> TRIP_TIME
                 >> SVMAX >> RAMP_DOWN >> RAMP_UP >> PWDOWN >> IMON_RANGE;

              if (stoi(PW))
                {
		  enable_channel.push_back((uint32_t)stoi(CHNUM)+20);
		}
	    }
	  else
	    {
	      continue;
	    }
	}
    }
  else
    {
      std::cout << "Config file not opened." << std::endl;
      return 1;
    }

  std::cout << std::right << std::setw(7) << "Board"
	    << std::setw(8) << "Channel"
	    << std::setw(5) << "VSet"
	    << std::setw(5) << "ISet"
	    << std::setw(6) << "Power"
	    << std::setw(5) << "Trip"
	    << std::setw(5) << "VMax"
	    << std::setw(7) << "RampDn"
	    << std::setw(7) << "RampUp"
	    << std::setw(6) << "PwrDn"
	    << std::setw(6) << "ImonR" << std::endl;
  for (int ch = 0; ch < 6; ch++)
    {
      int en = 0;
      if (find(enable_channel.begin(),enable_channel.end(),ch+10) != enable_channel.end())
	{
	  en = 1;
	}

      std::cout << std::right << std::setw(7) << "V6521N"
		<< std::setw(8) << ch
		<< std::setw(5) << get_config_voltage_v6521n(ch)
		<< std::setw(5) << get_config_current_v6521n(ch)
		<< std::setw(6) << en
		<< std::setw(5) << get_trip_time_v6521n(ch)
		<< std::setw(5) << get_svmax_v6521n(ch)
		<< std::setw(7) << get_ramp_down_v6521n(ch)
		<< std::setw(7) << get_ramp_up_v6521n(ch)
		<< std::setw(6) << get_pwdown_v6521n(ch)
		<< std::setw(6) << get_imon_range_v6521n(ch) << std::endl;
    }
  for (int ch = 0; ch < 6; ch++)
    {
      int en = 0;
      if (find(enable_channel.begin(),enable_channel.end(),ch+20) != enable_channel.end())
        {
          en = 1;
	}

      std::cout << std::right << std::setw(7) << "V6521P"
		<< std::setw(8) << ch
		<< std::setw(5) << get_config_voltage_v6521p(ch)
		<< std::setw(5) << get_config_current_v6521p(ch)
		<< std::setw(6) << en
		<< std::setw(5) << get_trip_time_v6521p(ch)
		<< std::setw(5) << get_svmax_v6521p(ch)
		<< std::setw(7) << get_ramp_down_v6521p(ch)
		<< std::setw(7) << get_ramp_up_v6521p(ch)
		<< std::setw(6) << get_pwdown_v6521p(ch)
                << std::setw(6) << get_imon_range_v6521p(ch) << std::endl;
    }
  CAENVME_End(handle);
  return 0;
}

std::string status(int ch, int board)
{
  std::string full_status;

  if (board == -1)
    {
      struct STATUS_REGISTER *stat = (struct STATUS_REGISTER *) get_channel_status_v6521n(ch);
      if (stat->ON) full_status+="ON ";
      if (stat->RAMPUP) full_status+="RAMPUP ";
      if (stat->RAMPDOWN) full_status+="RAMPDOWN ";
      if (stat->OVERCURRENT) full_status+="OVERCURRENT ";
      if (stat->OVERVOLTAGE) full_status+="OVERVOLTAGE ";
      if (stat->UNDERVOLTAGE) full_status+="UNDERVOLTAGE ";
      if (stat->MAXV) full_status+="MAXV ";
      if (stat->MAXI) full_status+="MAXI ";
      if (stat->TRIP) full_status+="TRIP ";
      if (stat->OVERPOWER) full_status+="OVERPOWER ";
      if (stat->OVERTEMPERATURE) full_status+="OVERTEMPERATURE ";
      if (stat->DISABLED) full_status+="DISABLED ";
      if (stat->INTERLOCK) full_status+="INTERLOCK ";
      if (stat->UNCALIBRATED) full_status+="UNCALIBRATED ";
      if (full_status.length()==0) full_status+="OFF";
    }
  else if (board == 1)
    {
      struct STATUS_REGISTER *stat = (struct STATUS_REGISTER *) get_channel_status_v6521p(ch);
      if (stat->ON) full_status+="ON ";
      if (stat->RAMPUP) full_status+="RAMPUP ";
      if (stat->RAMPDOWN) full_status+="RAMPDOWN ";
      if (stat->OVERCURRENT) full_status+="OVERCURRENT ";
      if (stat->OVERVOLTAGE) full_status+="OVERVOLTAGE ";
      if (stat->UNDERVOLTAGE) full_status+="UNDERVOLTAGE ";
      if (stat->MAXV) full_status+="MAXV ";
      if (stat->MAXI) full_status+="MAXI ";
      if (stat->TRIP) full_status+="TRIP ";
      if (stat->OVERPOWER) full_status+="OVERPOWER ";
      if (stat->OVERTEMPERATURE) full_status+="OVERTEMPERATURE ";
      if (stat->DISABLED) full_status+="DISABLED ";
      if (stat->INTERLOCK) full_status+="INTERLOCK ";
      if (stat->UNCALIBRATED) full_status+="UNCALIBRATED ";
      if (full_status.length()==0) full_status+="OFF";
    }
  
  return full_status;
}

int setconfig()
{
  CVBoardTypes vme_board = cvV1718;
  CVErrorCodes ret;

  ret = CAENVME_Init(vme_board, 0, 0, &handle);
  if (ret != cvSuccess)
    {
      printf("\n\n Error opening V1718! \n\n");
      CAENVME_End(handle);
      return 1;
    }

  std::string BOARD,CHNUM,VSET,ISET,
    PW,TRIP_TIME,SVMAX,RAMP_DOWN,
    RAMP_UP,PWDOWN,IMON_RANGE;

  std::string line;
  std::ifstream configfile (config_file.c_str(),std::ifstream::in);

  bool success = true;

  if (configfile.is_open())
    {
      while (getline(configfile,line))
	{
	  std::stringstream ss(line);
	  ss >> BOARD;
	  if (BOARD == "N")
	    {
	      ss >> CHNUM >> VSET >> ISET >> PW >> TRIP_TIME 
		 >> SVMAX >> RAMP_DOWN >> RAMP_UP >> PWDOWN >> IMON_RANGE;
	      
	      ret = set_voltage_v6521n((uint32_t)stoi(CHNUM),(uint32_t)stoi(VSET));
	      if (ret != cvSuccess)
		{
		  printf("\nBad voltage or bad channel\n");
		  success = false;
		}

	      ret = set_current_v6521n((uint32_t)stoi(CHNUM),stof(ISET));
	      if (ret != cvSuccess)
		{
		  printf("\nBad current or bad channel\n");
		  success = false;
		}

	      if (stoi(PW)) enable_channel.push_back((uint32_t)stoi(CHNUM)+10);

	      ret = set_trip_time_v6521n((uint32_t)stoi(CHNUM),(uint32_t)stoi(TRIP_TIME));
	      if (ret != cvSuccess)
		{
		  printf("\nBad trip time or bad channel\n");
		  success = false;
		}

	      ret = set_svmax_v6521n((uint32_t)stoi(CHNUM),(uint32_t)stoi(SVMAX));
	      if (ret != cvSuccess)
		{
		  printf("\nBad svmax or bad channel\n");
		  success = false;
		}

	      ret = set_ramp_down_v6521n((uint32_t)stoi(CHNUM),(uint32_t)stoi(RAMP_DOWN));
	      if (ret != cvSuccess)
		{
		  printf("\nBad ramp down or bad channel\n");
		  success = false;
		}

	      ret = set_ramp_up_v6521n((uint32_t)stoi(CHNUM),(uint32_t)stoi(RAMP_UP));
	      if (ret != cvSuccess)
		{
		  printf("\nBad ramp up or bad channel\n");
		  success = false;
		}

	      if (stoi(PWDOWN))
		{
		  ret = ramp_down_channel_v6521n((uint32_t)stoi(CHNUM));
		}
	      else 
		{
		  ret = kill_channel_v6521n((uint32_t)stoi(CHNUM));
		}
	      if (ret != cvSuccess)
		{
		  printf("\nBad power down or bad channel\n");
		  success = false;
		}

	      if (stoi(IMON_RANGE))
		{
		  ret = set_imon_low_v6521n((uint32_t)stoi(CHNUM));
		}
	      else
		{
		  ret = set_imon_high_v6521n((uint32_t)stoi(CHNUM));
		}
	      if (ret != cvSuccess)
		{
		  printf("\nBad imon range or bad channel\n");
		  success = false;
		}
	    }
	  else if (BOARD == "P")
	    {
	      ss >> CHNUM >> VSET >> ISET >> PW >> TRIP_TIME 
		 >> SVMAX >> RAMP_DOWN >> RAMP_UP >> PWDOWN >> IMON_RANGE;
	    
	      ret = set_voltage_v6521p((uint32_t)stoi(CHNUM),(uint32_t)stoi(VSET));
              if (ret != cvSuccess)
                {
                  printf("\nBad voltage or bad channel\n");
                  success = false;
                }

	      ret = set_current_v6521p((uint32_t)stoi(CHNUM),stof(ISET));
              if (ret != cvSuccess)
                {
                  printf("\nBad current or bad channel\n");
                  success = false;
                }

	      if (stoi(PW)) enable_channel.push_back((uint32_t)stoi(CHNUM)+20);

              ret = set_trip_time_v6521p((uint32_t)stoi(CHNUM),(uint32_t)stoi(TRIP_TIME));
              if (ret != cvSuccess)
                {
                  printf("\nBad trip time or bad channel\n");
                  success = false;
		}

              ret = set_svmax_v6521p((uint32_t)stoi(CHNUM),(uint32_t)stoi(SVMAX));
              if (ret != cvSuccess)
                {
                  printf("\nBad svmax or bad channel\n");
                  success = false;
                }

	      ret = set_ramp_down_v6521p((uint32_t)stoi(CHNUM),(uint32_t)stoi(RAMP_DOWN));
              if (ret != cvSuccess)
                {
                  printf("\nBad ramp down or bad channel\n");
                  success = false;
		}

	      ret = set_ramp_up_v6521p((uint32_t)stoi(CHNUM),(uint32_t)stoi(RAMP_UP));
              if (ret != cvSuccess)
		{
                  printf("\nBad ramp up or bad channel\n");
		  success = false;
                }

              if (stoi(PWDOWN))
                {
                  ret = ramp_down_channel_v6521p((uint32_t)stoi(CHNUM));
                }
              else
                {
                  ret = kill_channel_v6521p((uint32_t)stoi(CHNUM));
                }
              if (ret != cvSuccess)
                {
                  printf("\nBad power down or bad channel\n");
                  success = false;
                }

	      if (stoi(IMON_RANGE))
                {
                  ret = set_imon_low_v6521p((uint32_t)stoi(CHNUM));
		}
              else
                {
                  ret = set_imon_high_v6521p((uint32_t)stoi(CHNUM));
		}
	      if (ret != cvSuccess)
		{
                  printf("\nBad imon range or bad channel\n");
                  success = false;
		}

	    }
	  else
	    {
	      continue;
	    }

	}
    }
  else
    {
      std::cout << "Something is wrong with the config file." << std::endl;
      return 1;
    }

  CAENVME_End(handle);
  if (!success) return 1;
  return 0;
}

int powerdown()
{
  CVBoardTypes vme_board = cvV1718;
  CVErrorCodes ret;

  ret = CAENVME_Init(vme_board, 0, 0, &handle);
  if (ret != cvSuccess)
    {
      printf("\n\n Error opening V1718! \n\n");
      CAENVME_End(handle);
      return 1;
    }

  bool success = true;
  for (int ch = 0; ch < 6; ch++)
    {
      ret = disable_channel_v6521n(ch);
      if (ret != cvSuccess)
	{
	  printf("Error %d when ramping down V6521N!!\n",ret);
	  success = false;
	}
    }
  for (int ch = 0; ch < 6; ch++)
    {
      ret = disable_channel_v6521p(ch);
      if (ret != cvSuccess)
	{
	  printf("Error %d when ramping down V6521P!!\n",ret);
	  success = false;
	}
    }
  CAENVME_End(handle);
  if (!success) return 1;
  return 0;
}

int powerup()
{
  CVBoardTypes vme_board = cvV1718;
  CVErrorCodes ret;

  ret = CAENVME_Init(vme_board, 0, 0, &handle);
  if (ret != cvSuccess)
    {
      printf("\n\n Error opening V1718! \n\n");
      CAENVME_End(handle);
      return 1;
    }

  std::string BOARD,CHNUM,VSET,ISET,
    PW,TRIP_TIME,SVMAX,RAMP_DOWN,
    RAMP_UP,PWDOWN,IMON_RANGE;

  std::string line;
  std::ifstream configfile (config_file.c_str(),std::ifstream::in);

  bool success = true;

  if (configfile.is_open())
    {
      while (getline(configfile,line))
	{
	  std::stringstream ss(line);
          ss >> BOARD;
          if (BOARD == "N")
            {
              ss >> CHNUM >> VSET >> ISET >> PW >> TRIP_TIME
                 >> SVMAX >> RAMP_DOWN >> RAMP_UP >> PWDOWN >> IMON_RANGE;

	      if (stoi(PW)) 
		{
		  ret = enable_channel_v6521n((uint32_t)stoi(CHNUM));
		  if (ret != cvSuccess)
		    {
		      printf("Error enabling V6521N channel %i\n",stoi(CHNUM));
		      success = false;
		    }
		}
	    }
	  else if (BOARD == "P")
	    {
	      ss >> CHNUM >> VSET >> ISET >> PW >> TRIP_TIME
                 >> SVMAX >> RAMP_DOWN >> RAMP_UP >> PWDOWN >> IMON_RANGE;

              if (stoi(PW))
		{
                  ret = enable_channel_v6521p((uint32_t)stoi(CHNUM));
                  if (ret != cvSuccess)
                    {
                      printf("Error enabling V6521P channel %i\n",stoi(CHNUM));
                      success = false;
                    }
		}

	    }
	  else
	    {
	      continue;
	    }
	}
    }
  else
    {
      std::cout << "config_file not set" << std::endl;
      return 1;
    }

  CAENVME_End(handle);
  if (!success) return 1;
  return 0;
}

int main(int argc, char *argv[]) 
{
  int i = 1;
  int status = 1;

  if (!strcmp(argv[i], "--setconfig"))
    {
      if (i+1 == argc)
	{
	  printf("Feed me a config file!\n");
	  status = 1;
	}
      else
	{
	  config_file = (std::string)argv[i+1];
	  std::ifstream src(config_file,std::ios::binary);
	  std::ofstream dst("current.conf",std::ios::binary);
	  dst << src.rdbuf();
	}
      status = setconfig();
    }
  else if (!strcmp(argv[i], "--powerdown"))
    {
      status = powerdown();
    }
  else if (!strcmp(argv[i], "--powerup"))
    {
      if (i+1 == argc)
	{
	  config_file = "current.conf";
	}
      else
	{
	  config_file = (std::string)argv[i+1];
	}
      status = setconfig();
      if (!status) status = powerup();
    }
  else if (!strcmp(argv[i], "--getconfig"))
    {
      if (i+1 == argc)
	{
	  config_file = "current.conf";
	}
      else
	{
	  config_file = (std::string)argv[i+1];
	}
      status = setconfig();
      if (!status) status = getconfig(); 
    }
  else if (!strcmp(argv[i], "--monitor"))
    {
      status = monitor();
    }
  else if (!strcmp(argv[i], "--kill"))
    {
      status = powerdown();
    }
  else
    {
      printf("Usage: sethv [command] [optional parameters]\n");
      printf("  Commands:\n");
      printf("    --setconfig   Requires parameter pointing to the location of the\n");
      printf("                  configuration file.\n");
      printf("    --powerdown   Ramp down voltages and turn channels off.\n");
      printf("    --powerup     Turn channels on and ramp up voltages.\n");
      printf("    --getconfig   Read the pre-set parameters from VME.\n");
      printf("    --monitor     Read the instantaneous parameters from VME\n");
      printf("                  (e.g. voltage, current, etc.).\n");
      printf("    --kill        Ramp down voltages immediately.\n");
      status = 1;
    }
      
  return status;
}

