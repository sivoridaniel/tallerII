/*
 * Interest.cpp
 *
 *  Created on: Apr 8, 2016
 *      Author: agustin
 */

#include "Interest.h"

Interest::Interest(std::string category, std::string value)
{
	this->category = category;
	this->value = value;

}

Interest::~Interest()
{
}

std::string Interest::toJson()
{
	Json::Value root;
	Json::FastWriter writer;
	root["interest"]["category"] = this->category;
	root["interest"]["value"] = this->value;
	std::string json = writer.write(root);
	return json;
}
