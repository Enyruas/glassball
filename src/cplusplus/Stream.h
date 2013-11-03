#ifndef GLASSBALL_STREAM_H_
#define GLASSBALL_STREAM_H_

#include <iostream>
#include <string>

#define ERRSTREAM ErrorStream()
#define SCREENSTREAM ScreenStream()

class ErrorStream {
  public:
	ErrorStream operator<<(std::string log) {
		std::cout<<"Error log"<<log<<std::endl;
		return *this;
	}
	ErrorStream operator<<(const char *log) {
		std::cout<<"Error log"<<log<<std::endl;
		return *this;
	}
};

class ScreenStream {
  public:
	ScreenStream operator<<(std::string log) {
		std::cout<<log;
		return *this;
	}
	ScreenStream operator<<(const char *log) {
		std::cout<<log;
		return *this;
	}
};

#endif
