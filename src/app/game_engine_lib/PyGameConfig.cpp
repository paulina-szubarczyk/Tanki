/*
 * PyGameConfig.cpp
 *
 *  Created on: Jun 2, 2014
 *      Author: Adam Kosiorek
 */

#include "PyGameConfig.h"

#include "glog/logging.h"
#include <Python.h>
#include <boost/python.hpp>

namespace py = boost::python;
py::object configureFunction_;

namespace game {

PyGameConfig::PyGameConfig(const std::string& filename, const std::string& funcName) {

	Py_Initialize();

	//Get the main module
	py::object main_module = py::import("__main__");
	py::object main_namespace = main_module.attr("__dict__");
	py::exec_file(filename.c_str(), main_module, main_namespace);

	configureFunction_ = main_namespace[funcName.c_str()];
}

PyGameConfig::~PyGameConfig() {

	Py_Finalize();
}

std::map<std::string, std::string> PyGameConfig::getConfiguration() const {

	std::map<std::string, std::string> configParamMap;
	py::list configParamList = py::extract<py::list>(configureFunction_())();

	for(int i = 0; i < py::len(configParamList);) {

		std::string key = py::extract<std::string>(configParamList[i++]);
		std::string value = py::extract<std::string>(configParamList[i++]);
		configParamMap[key] = value;
	}
	return configParamMap;
}

} /* namespace ships */

