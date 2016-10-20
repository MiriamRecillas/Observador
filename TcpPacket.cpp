/* 
 * File:    TcpPacket.h
 * Author:  Mauricio Matamoros
 *
 * Created: October 19, 2016
 */

#include "TcpPacket.h"

TcpPacket::TcpPacket(const char* data, size_t length)
:dataStrings()
{
	std::string allData;

	this->data = new char[length];
	this->dataLength = length;
	for(size_t i = 0; i < length; ++i){
		allData+=data[i];
		this->data[i] = data[i];
	}
	boost::split(this->dataStrings, allData, boost::is_any_of("\0"));        
}

TcpPacket::~TcpPacket(){
	delete[] this->data;
	this->dataStrings.clear();
}


std::vector<char> TcpPacket::getData(){
	std::vector<char> data;
	for(size_t i = 0; i < dataLength; ++i)
		data.push_back(this->data[i]);
	return data;
}

size_t TcpPacket::getDataLenght(){
    return this->dataLength;
}

void TcpPacket::getData(char **buffer, size_t *bufferLength){
    *bufferLength = this->dataLength;
    if(this->dataLength <= 0){
		*buffer =NULL;
		return;
    }
    *buffer = new char[this->dataLength];
    for(size_t i = 0; i < dataLength; ++i)
		*buffer[i] = this->data[i];
}

std::string TcpPacket::getDataString(int index){
    return this->dataStrings[index];
}
std::vector<std::string>& TcpPacket::getDataStrings(){
 return this->dataStrings;
}


