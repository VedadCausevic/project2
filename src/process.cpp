#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"


using std::string;
using std::to_string;
using std::vector;



// Constructor

Process::Process (int pid_) {this->pid = pid_; }
// TODO: Return this process's ID
int Process::Pid() { return this->pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { 
  string line;
  string value;
  int counter = 0;
  float totaltime{0};
  float seconds{0};
  vector<float> times{};
std::ifstream filestream(LinuxParser::kProcDirectory+to_string(this->pid)+LinuxParser::kStatFilename);
  if(filestream.is_open()){
    std::getline (filestream,line);
    std::istringstream linestream(line);
    while(linestream>>value && counter<23){
      if( counter==13 || counter==14 || counter==15|| counter==16 || counter==21){
        times.emplace_back(stof(value));
      }
      counter++;
    }
    
    }
  totaltime=times[0]+times[1];
    totaltime+=times[2]+times[3];
    seconds = UpTime() - (times[4]/sysconf(_SC_CLK_TCK));
    return totaltime/seconds/sysconf(_SC_CLK_TCK);
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(this->pid); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(this->pid); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(this->pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() const { return  LinuxParser::UpTime(this->pid); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const &a) const {
    return Process::CpuUtilization() < a.CpuUtilization();
}