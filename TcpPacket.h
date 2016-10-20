/* 
 * File:    TcpPacket.h
 * Author:  Mauricio Matamoros
 *
 * Created: October 19, 2016
 */

#ifndef __TCP_PACKET_H__
#define	__TCP_PACKET_H__

#include <cstdlib>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/algorithm/string.hpp>

class TcpPacket {
public:
    TcpPacket(const char* data, size_t length);    
    ~TcpPacket();
	
	
	/**
	 * Gets a copy of the data received
     * @return a vector of chars containing the data received
     */
	std::vector<char> getData();
	/**
	 * Gets a copy of the data received
     * @param A pointer to a buffer where copy the data to
     * @param When this method returns contains the size of the buffer
     */
	void getData(char **buffer, size_t *bufferLength);
	/**
	 * Gets the length of the data received
     * @return the length of the data received
     */
	size_t getDataLenght();
	/**
	 * 
     * @param index
     * @return 
     */
	std::string getDataString(int index);
	/**
	 * 
     * @return 
     */
	std::vector<std::string>& getDataStrings();
	
private:
	char *data;
	size_t dataLength;
	std::vector<std::string> dataStrings;

};

#endif	/* __TCP_PACKET_H__ */
