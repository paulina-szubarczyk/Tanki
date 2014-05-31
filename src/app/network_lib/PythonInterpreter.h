/*
 * PythonInterpreter.h
 *
 *  Created on: May 31, 2014
 *      Author: Adam Kosiorek
 */

#ifndef PYTHONINTERPRETER_H_
#define PYTHONINTERPRETER_H_

//#include <boost/python.hpp>

#include <string>
#include <map>



namespace ships {

class ConfigureScript {
public:
	ConfigureScript(const std::string& filename, const std::string& funcName);
	virtual ~ConfigureScript();

	std::map<std::string, std::string> getConfiguration();

private:


};

} /* namespace ships */

#endif /* PYTHONINTERPRETER_H_ */
