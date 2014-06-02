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

#include <stdexcept>

namespace py = boost::python;

namespace game {

const std::string PyGameConfig::shipConfigFunName_ = "shipConfig";
const std::string PyGameConfig::gameboardSizeFunName_ = "gameboardSize";

py::object shipConfigFun_;
py::object gameboardSizeFun_;

PyGameConfig::PyGameConfig(const std::string& filename) {

	try {
		Py_Initialize();

		//Get the main module
		py::object main_module = py::import("__main__");
		py::object main_namespace = main_module.attr("__dict__");

		LOG(INFO) << "Initializing from: " << filename;

		py::exec_file(filename.c_str(), main_module, main_namespace);

		shipConfigFun_ = main_namespace[shipConfigFunName_.c_str()];
		gameboardSizeFun_ = main_namespace[gameboardSizeFunName_.c_str()];
	} catch (std::exception& e) {

		std::runtime_error err("Couldn't initialize PyGameConfig");
		LOG(ERROR) << err.what();
		throw err;
	}
}

PyGameConfig::~PyGameConfig() {

	Py_Finalize();
}

int PyGameConfig::getGameboardSize() const {

	return py::extract<int>(gameboardSizeFun_())();
}

std::map<int, int> PyGameConfig::getShipConfig() const {

	std::map<int, int> configParamMap;
	py::list configParamList = py::extract<py::list>(shipConfigFun_())();

	for(int i = 0; i < py::len(configParamList);) {

		int key = py::extract<int>(configParamList[i++]);
		int value = py::extract<int>(configParamList[i++]);
		configParamMap[key] = value;
	}
	return configParamMap;
}

} /* namespace ships */

