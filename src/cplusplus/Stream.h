#ifndef GLASSBALL_STREAM_H_
#define GLASSBALL_STREAM_H_

#include <iostream>
#include <string>

#define ERRSTREAM ErrorStream()
#define SCREENSTREAM ScreenStream()

class ErrorStream {
  public:
	void operator<<(std::string log) {
		std::cout<<"Error log"<<log<<std::endl;
	}
};

class ScreenStream {
  public:
	void operator<<(std::string log) {
		std::cout<<"Screen log"<<log<<std::endl;
	}
};

#endif
