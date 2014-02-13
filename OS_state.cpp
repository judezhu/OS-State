#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std; 
using namespace boost; 


/*------------------------------
  Read the processor_type
  ------------------------------*/

string processor_type()
{

  ifstream cpu_info;
  string pro_type,temp;
  size_t pos;

  cpu_info.open("/proc/cpuinfo");
  
  for(int i=1; i!=5; i++)
  {
    
    std::getline(cpu_info,temp); 
  
  }

  std::getline(cpu_info, pro_type); 
  pos = pro_type.find(":");
  pro_type = pro_type.substr(pos);

  cpu_info.close();
  return pro_type;
}

/*------------------------------
  Read the kernel_version
 ------------------------------*/ 
string kernel_version()
{

  ifstream os_release;
  string ker_version;
  
  os_release.open("/proc/sys/kernel/osrelease");
  std::getline(os_release,ker_version);
  os_release.close();
 
  return ker_version;
}

/*------------------------------
  Read the uptime of the system
 ------------------------------*/ 
float system_uptime()

{
  ifstream sys_ut;
  float uptime;
  
  sys_ut.open("/proc/uptime");
  sys_ut >> uptime;
  sys_ut.close();

  return uptime;

}

/*--------------------------------------------------
  Read the time of user mode, system mode, idle mode
 --------------------------------------------------*/ 

double* processor_time(double *t)
{
  ifstream pro_t;
  string temp1;
  int temp2;
  
  pro_t.open("/proc/stat");
  pro_t >> temp1;
  pro_t >> t[0];
  pro_t >> temp2 ;
  pro_t >> t[1];
  pro_t >> t[2];
  pro_t.close();

  return t;  
}

/*-----------------------------------------
  Read the disk read/write requests 
 ----------------------------------------*/
int* disk_request(int* r)
 {
   ifstream disk_r;
   disk_r.open("/proc/diskstats");
   string temp;
   string s1 ("sda");
 
   while(disk_r.good())
   {
     std::getline(disk_r,temp);
     if(temp.find(s1)==string::npos)
     {
       continue;
     }
     else
     {
       break;
     }
   }
 
   vector <string> fields;
   temp = temp.substr(temp.find("sda"));
   split(fields,temp,is_any_of(" "));
   r[0] = atoi(fields[1].c_str());
   r[1] = atoi(fields[5].c_str());
   return r;
 }


/*----------------------------------
  Read the number of context switches
  ----------------------------------*/
int context_switches()
{

  ifstream context_s;
  string temp;
  int con_s;

  context_s.open("/proc/stat");
  string s1 ("ctxt");
 
  while(context_s.good())
  {
    std::getline(context_s,temp);
    if(temp.find(s1)==string::npos)
    {
      continue;
    }
    else
    {
      break;
    }
  }

 
  vector <string> fields;
  split(fields,temp,is_any_of(" "));
  con_s = atoi(fields[1].c_str());
  context_s.close();
 
  return con_s;
}

 /*----------------------------------
  Read time of system booted last time
  ----------------------------------*/
int boot_time()
{

  ifstream boot_t;
  string temp;
  int b_t;

  boot_t.open("/proc/stat");
  string s1 ("btime");
 
  while(boot_t.good())
  {
    std::getline(boot_t,temp);
    if(temp.find(s1)==string::npos)
    {
      continue;
    }
    else
    {
      break;
    }
  }

  vector <string> fields;
  split(fields,temp,is_any_of(" "));
  b_t = atoi(fields[1].c_str());
  boot_t.close();
 
  return b_t;
}


 /*----------------------------------
  Read number of processes created
  ----------------------------------*/
int processes_number()
{

  ifstream pro_num;
  string temp;
  int p_n;

  pro_num.open("/proc/stat");
  string s1 ("processes");
 
  while(pro_num.good())
  {
    std::getline(pro_num,temp);
    if(temp.find(s1)==string::npos)
    {
      continue;
    }
    else
    {
      break;
    }
  }

 
  vector <string> fields;
  split(fields,temp,is_any_of(" "));
  p_n = atoi(fields[1].c_str());
  pro_num.close();
 
  return p_n;
}

 /*----------------------------------
  Read total memory of system
  ----------------------------------*/
int memory_total()
{

  ifstream mem_t;
  string temp;
  int m_t;

  mem_t.open("/proc/meminfo");
  string s1 ("MemTotal");

 
  while(mem_t.good())
  {
    std::getline(mem_t,temp);
    if(temp.find(s1)==string::npos)
    {
      continue;
    }
    else
    {
      break;
    }
  }

  vector <string> fields;
  split(fields,temp,is_any_of(" "));
  m_t = atoi(fields[fields.size()-2].c_str());
  mem_t.close();
 
  return m_t;
}

 /*----------------------------------
  Read free memory of system
  ----------------------------------*/
int memory_free()
{

  ifstream mem_f;
  string temp;
  int m_f;

  mem_f.open("/proc/meminfo");
  string s1 ("MemFree");

  //get to the line of free memory info; store that line in temp; 
  while(mem_f.good())
  {
    std::getline(mem_f,temp);
    if(temp.find(s1)==string::npos)
    {
      continue;
    }
    else
    {
      break;
    }
  }

  //split the string accrording to spaces;
  vector <string> fields;
  split(fields,temp,is_any_of(" "));
  m_f = atoi(fields[fields.size()-2].c_str());
  mem_f.close();
 
  return m_f;
}

int main (int argc, char *argv[])
  {

    if (argc == 1)
    {
      cout<< "\n      -------------------------------------------------------------\n";
      cout<< "         --------------------OS State Part A --------------------\n";
      cout<< "      -------------------------------------------------------------\n\n";
  
      //display processor type, and kernel version
      cout<< "Processor Type: "<<processor_type()<<"\n";
      cout<< "Kernel Version: "<<kernel_version()<<"\n";
    
      //display uptime and change uptime into hour, min, sec
      cout<< "The amount of time since it was last booted: "<<int(system_uptime())<<"sec";
      int hour, min, sec;
      sec = system_uptime();
      hour = sec/3600; 
      min = (sec%3600)/60;
      sec = (sec%3600)%60;   
      cout << " ("<< hour << "hour "<<  min  << "min " <<  sec  << "sec" << ")\n" ;
      
      //display amount of time the processor has spent
      double time[3];
      processor_time(time);
      cout<< "The amount of time the processor has spent in user mode: " << int(time[0]/100.0)<<"sec\n";
      cout<< "The amount of time the processor has spent in system mode: " << int(time[1]/100.0)<<"sec\n";
      cout<< "The amount of time the processor has spent in idle  mode: " << int(time[2]/100.0)<<"sec\n";
  
      //display the read/write request
      int request[2];
      disk_request(request);
      cout<< "The number of disk read requests made on the system: " << request[0] << "\n";
      cout<< "The number of disk write requests made on the system:" << request[1] << "\n";

      //display the number of context switches
      cout<< "The number of context switches the kernel has performed: "<< context_switches()<<"\n";
     
      //display the time when the system last booted 
      time_t rawtime = boot_time();
      cout<< "The time the system was last booted: " << ctime(&rawtime) <<"";

      //display the number of created process number, memory amount, free memory
      cout<< "The number of processes that have been created since the last boot: "<<processes_number() << "\n";
      cout<< "The amount of memory configured for this computer: "<< memory_total()<<"kB\n";
      cout<< "The amount of memory currently available: "<<memory_free()<< "kB\n";
    }

    else if (argc == 3)
    {
      int s,p,n ; // total time, period time and number of periods;
      p = atoi(argv[1]);
      s = atoi(argv[2]);
      n = s/p;
      cout<< "\n      -------------------------------------------------------------\n";
      cout<< "         --------------------OS State Part B--------------------\n";
      cout<< "      -------------------------------------------------------------\n\n";
      cout<< "Sampling start: \n";
     
      // raw data
      double user[2];
      double system[2];
      double idle[2];
      double read[2]; //read begin, read end
      double write[2]; //write begin, write end
      double cs[2]; //context switch begin and end
      double pn[2]; // process number begin and end
      
      //average data
      double avr_user, avr_system, avr_idle;
      double avr_read, avr_write, avr_cs, avr_pn, avr_mf;
      
      //read user, system, idle mode time at the beginning
      double time[3];
      processor_time(time);
      user[0] = time[0];
      system[0] = time[1];
      idle[0] = time[2];
  
     // read disk read, write, context switch, process number and free memory at the beginning
      cout<<"Data is taking at 0sec ......\n";
      int request[2];
      disk_request(request);
      read[0] =  request[0]; 
      write[0] =  request[1];
      
      cs[0] = context_switches();
      pn[0] = processes_number();
      
      avr_mf = memory_free(); 
    
      sleep(p);

      for(int i=1; i<=n; i++)
      { 
        cout <<"Data is taking at " << i*p << "sec ......\n";
        avr_mf = avr_mf + memory_free();
        
        sleep(p);
        
      }
      cout << "Sampling is done.\n\n";
 
      processor_time(time);
      user[1] = time[0];
      system[1] = time[1];
      idle[1] = time[2];
     
     // read disk read, write, context switch and process number at the end
      disk_request(request);
      read[1] =  request[0]; 
      write[1] =  request[1];
      
      cs[1] = context_switches();
      pn[1] = processes_number();
     
     // calculate the average of  read disk read, write, context switch and process number
      avr_user = (user[1]-user[0])/100.0/double(n);
      avr_system = (system[1]-system[0])/100.0/double(n);
      avr_idle = (idle[1]-idle[0])/100.0/double(n);

      avr_read = (read[1]-read[0])/double(n);
      avr_write = (write[1]-write[0])/double(n);
      avr_cs = (cs[1]-cs[0])/double(n);
      avr_pn = (pn[1]-pn[0])/double(n);
      avr_mf = avr_mf/double(n);
      
      cout<<setiosflags(ios::fixed);      
      cout << "The average amount of time the processor has spent in user mode: "<< setprecision(2) << avr_user << "sec/period\n";
      cout << "The average amount of time the processor has spent in system mode: " << setprecision(2) << avr_system << "sec/period\n";
      cout << "The average amount of time the processor has spent in idle mode: " << setprecision(2) << avr_idle << "sec/period\n";
      cout << "The average number of disk read request made on the system: " << setprecision(2) << avr_read << "/period\n"; 
      cout << "The average number of disk write request made on the system: " << setprecision(2) << avr_write <<"/period\n";
      cout << "The avrage number of context switches the kernel has performed: " << setprecision(2) << avr_cs <<"/period\n";
      cout << "The avreage number of system processes created: " << setprecision(2) << avr_pn <<"/period\n"; 
      cout << "The average amount of memory currently available: " << setprecision(2) << avr_mf <<"kB\n";
    }
    else
    {
      cout << "Please give the correct sampling arguments to the program!\n";
      exit(-1) ;
    }
    return 0;
}
