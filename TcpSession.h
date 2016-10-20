/* 
 * File:    TcpSession.h
 * Author:  Mauricio Matamoros
 *
 * Created: October 19, 2016
 */

#ifndef __TCP_SESSION_H__
#define	__TCP_SESSION_H__

#include <cstdlib>
#include <iostream>
#include <queue>
#include <boost/filesystem.hpp>
#include <boost/bind.hpp>
#include <boost/pending/queue.hpp>
#include <boost/asio.hpp>
#include "TcpPacket.h"
#include "ProducerConsumer.h"

using boost::asio::ip::tcp;

class Session {
public:
	Session(boost::asio::io_service& io_service, ProducerConsumer<TcpPacket*>& q);
	virtual ~Session();
	void handle_write(const boost::system::error_code& error);
	tcp::socket& socket();
	void start();
	void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
    void print(char *data ,int max_length);
private:
	tcp::socket sckt;
	static const int MAX_LENGTH = 4194304;
	char data[MAX_LENGTH];
	ProducerConsumer<TcpPacket*>& packetsReceived;
};

#endif	/* __TCP_SESSION_H__*/

