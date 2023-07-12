#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
string line;
string key;
string value;
long memtotal{0};
long memfree{0};

std::ifstream filestream(kProcDirectory+kMeminfoFilename);
  
if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          
          memtotal =stol(value);
          
                  }
        else if(key == "MemFree:"){
                 
          memfree=stol(value);
        }
      }
    }
  }
  
   return ((float(memtotal)-float(memfree))/float(memtotal));

}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
string line;
  string value;
  long uptime{0};
std::ifstream filestream(kProcDirectory+kUptimeFilename);
if(filestream.is_open()){
std::getline(filestream,line);
std::istringstream linestream(line);
linestream>>value;
}
uptime = std::stol(value);
  return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
long jiffie_nr{0};
jiffie_nr = LinuxParser::UpTime()*sysconf(_SC_CLK_TCK);
return jiffie_nr;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
string line;
string key;
string value;
  long activejiffies{0};
  int counter{0};
  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatFilename);
  if(filestream.is_open()){
   while(std::getline (filestream,line)){
    std::istringstream linestream(line);
    
    linestream>>value;
      if( counter==13 || counter==14  || counter==15 || counter==16){
        activejiffies +=stol(value);
      }
     counter++;
    }
    }
    
    
  
  return activejiffies;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
string line;
  string key;
  string value;
  long activejiffies{0};
 std::ifstream filestream(kProcDirectory+kStatFilename);
  if(filestream.is_open()){
    std::getline(filestream,line);
    std::istringstream linestream(line);
    while(linestream>>value){
      if(value!="cpu"){
        
        activejiffies += stol(value);
      }
      
    }
    
    
  }
return activejiffies;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { string line;
  string key;
  string value;
  long idlejiffies{0};
 std::ifstream filestream(kProcDirectory+kStatFilename);
  if(filestream.is_open()){
    std::getline(filestream,line);
    std::istringstream linestream(line);
    int i=0;
    while(linestream>>value){
      if(i==3 || i==4){
        
        idlejiffies += stol(value);
      }
      i++;
    }
    
    
  }
return idlejiffies; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
string line;
string value;
vector<string> jiffies{};
  
  std::ifstream filestream (kProcDirectory+kStatFilename);
  if(filestream.is_open()){
  std::getline (filestream,line);
  std::istringstream linestream(line);  
    while(linestream >> value){
    if (value != "cpu"){
    jiffies.emplace_back(value);
    }
    }
  
  }
return jiffies;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
string line;
  string value;
  string key;
  int totalprocesses;
std::ifstream filestream(kProcDirectory + kStatFilename);
if(filestream.is_open()){
while(getline(filestream,line)){
std::istringstream linestream(line);
linestream>>key>>value;
  if(key=="processes") {totalprocesses = stoi(value);}
}
}
return totalprocesses;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
string line;
  string value;
  string key;
  int runningprocesses;
std::ifstream filestream(kProcDirectory+kStatFilename);
if(filestream.is_open()){
while(getline(filestream,line)){
std::istringstream linestream(line);
linestream>>key>>value;
  if(key=="procs_running") {runningprocesses = stoi(value);}
}
}
return runningprocesses;

}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
string line;
  string value;
  std::ifstream filestream(kProcDirectory+to_string(pid)+kCmdlineFilename);
  if(filestream.is_open()){
    std::getline(filestream,line);
    
  }
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
string line;
  string value;
  string key;
  string ram{};
  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatusFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line)){
      std::istringstream linestream(line);
      linestream>>key>>value;
      if(key=="VmSize:"){
        
        ram = to_string(stol(value)/1000);
      }
    }
    
  }
  
return ram;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
string line;
  string key;
  string uid;
  string value{};
 std::ifstream filestream(kProcDirectory+to_string(pid)+kStatusFilename);
if(filestream.is_open()){
while(getline(filestream,line)){
std::istringstream linestream(line);
linestream>>key>>uid;
  if(key=="Uid:") {value=uid;}
  
}
 
}
 return value;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
string line;
  string value;
  string user;
  string password;
  string user_;
  std::ifstream filestream(kPasswordPath);
if(filestream.is_open()){
while(std::getline(filestream,line)){
    std::replace(line.begin(), line.end(), ':', ' ');
std::istringstream linestream(line);
linestream>>user>>password>>value;
  if(value==LinuxParser::Uid(pid)) { user_=user;}
  
}
}
  return user_;


}




// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line;
  string value;
  string starttime{};
    std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatFilename);
  int count=0;
  if(filestream.is_open()){
  while(std::getline(filestream,line) ){
    std::istringstream linestream(line);
    while(linestream>>value){
      if(count==21)   {starttime=value;}      
      count++;}
  }
  
   
  
  }
return LinuxParser::UpTime()-(stol(starttime)/sysconf(_SC_CLK_TCK));;
}
