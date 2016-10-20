/* 
 * File:    TcpClient.h
 * Author:  Mauricio Matamoros
 *
 * Created: October 19, 2016
 */

#include "TcpClient.h"

TcpClient::~TcpClient(){ this->stop();}

TcpClient::TcpClient() 
	: nccSemaphore(0), port(2000)
{
	this->running = false;
	this->acceptor = NULL;
	this->mainThread = NULL;
	this->service = NULL;
}

TcpClient::TcpClient(unsigned short port)
    : nccSemaphore(0), port(port)
{
	this->running = false;
	this->acceptor = NULL;
	this->mainThread = NULL;
	this->service = NULL;
}

unsigned short TcpClient::getPort()
{
	return this->port;
}

void TcpClient::setPort(unsigned short port)
{
	if(port != 0)
		this->port = port;
}

bool TcpClient::isRunning()
{
	return this->running;
}

void TcpClient::start(){
	if(this->running)
		return;

	running = true;
	emptyPacketsReceivedQ();
	this->mainThread = new boost::thread(boost::bind(&TcpClient::mainThreadTask, this));
	
}

void TcpClient::stop()
{
	if(!this->running)
		return;
	
	this->running = false;
	this->service->stop();
	delete this->acceptor;
	delete this->service;
	delete this->mainThread;
	
}

void TcpClient::mainThreadTask()
{
	this->service = new boost::asio::io_service();
	while(this->running){
		this->acceptor = NULL;
		try{
			this->acceptor = new tcp::acceptor(*(this->service), tcp::endpoint(tcp::v4(), port));
			beginAcceptConnection();
			break;
		}
		catch( ... ){
			if(this->acceptor)
				delete acceptor;
			continue;
		}
	}
	
	//this->service->run();
	while(this->running)
	{
		this->service->run();
	}
}

void TcpClient::beginAcceptConnection()
{
	Session* new_session = new Session(*service, packetsReceived);
	this->acceptor->async_accept(
		new_session->socket(),
		boost::bind(
			&TcpClient::handleAccept,
			this,
			new_session,
			boost::asio::placeholders::error
		)
	);
}

void TcpClient::emptyPacketsReceivedQ(){
	this->packetsReceived.clear();
}

void TcpClient::handleAccept(Session *new_session, const boost::system::error_code& error){
    if (!error)
    {
		new_session -> start();
		tcp::socket& sock = new_session->socket();
		tcp::socket* sockPtr = &sock;
		{
			scoped_lock(socketsMutex);
			sockets.push_back(sockPtr);
		}
		nccSemaphore.post();
		std::cout << "Client connected" << std::endl;
		beginAcceptConnection();
    }
    else
    {
      delete new_session;
    }
}

bool TcpClient::sendTo(tcp::socket& socket, const std::string& s) const
{
	if(!socket.is_open())
		return false;
	try{
		boost::asio::write(socket,
			boost::asio::buffer(s),
			boost::asio::transfer_all()
		);
	}
	// catch (std::exception& e)
	// {
	//	std::cerr << "Exception: " << e.what() << std::endl;
	// }
	catch(...){ return false; }
	return true;
}

size_t TcpClient::sendToAll(const std::string& s)
{
	size_t count = 0;
	tcp::socket *socket;
	scoped_lock(socketsMutex);

	for(size_t i = 0; i < sockets.size(); ++i)
	{
		socket = sockets[i];
		if(socket == NULL)
			continue;
		
		if(sendTo(*socket, s))
			++count;
	}
	return count;
}

ProducerConsumer<TcpPacket*>& TcpClient::getPacketsReceived()
{
	return this->packetsReceived;
}


void TcpClient::waitClientConnected(){
	if(sockets.size() > 0)
		return;
	nccSemaphore.wait();
}

bool TcpClient::waitClientConnected(const int& timeout){
	if(sockets.size() > 0)
		return true;
	if(timeout < 0){
		waitClientConnected();
		return true;
	}
	boost::system_time deadline = boost::get_system_time() + boost::posix_time::milliseconds(timeout);
	return nccSemaphore.timed_wait(deadline);
}