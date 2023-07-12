#include "processor.h"
#include "linux_parser.h"


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
float AJ = float(LinuxParser::ActiveJiffies());
float IJ = float(LinuxParser::IdleJiffies());
return AJ/(AJ+IJ);
}