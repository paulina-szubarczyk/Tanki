#include "network.h"
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/interprocess/detail/atomic.hpp>

//-----------------------------------------------------------------------------

Hive::Hive() :
		m_work_ptr(new io_service::work(m_io_service)), shutdown_(0) {
}

Hive::~Hive() {
}

io_service & Hive::GetService() {
	return io_service_;
}

bool Hive::HasStopped() {
	return (boost::interprocess::detail::atomic_cas32(&m_shutdown, 1, 1) == 1);
}

void Hive::Poll() {
	m_io_service.poll();
}

void Hive::Run() {
	m_io_service.run();
}

void Hive::Stop() {
	if (boost::interprocess::detail::atomic_cas32(&m_shutdown, 1, 0) == 0) {
		m_work_ptr.reset();
		m_io_service.run();
		m_io_service.stop();
	}
}

void Hive::Reset() {
	if (boost::interprocess::detail::atomic_cas32(&m_shutdown, 0, 1) == 1) {
		m_io_service.reset();
		m_work_ptr.reset(new io_service::work(m_io_service));
	}
}

//-----------------------------------------------------------------------------

Acceptor::Acceptor(std::shared_ptr<Hive> hive) :
		m_hive(hive), acceptor_(hive->GetService()), io_strand_(
				hive->GetService()), timer_(hive->GetService()), timer_interval_(
				1000), error_state_(0) {
}

Acceptor::~Acceptor() {
}

void Acceptor::StartTimer() {
	m_last_time = boost::posix_time::microsec_clock::local_time();
	m_timer.expires_from_now(boost::posix_time::milliseconds(m_timer_interval));
	m_timer.async_wait(
			m_io_strand.wrap(
					boost::bind(&Acceptor::HandleTimer, shared_from_this(),
							_1)));
}

void Acceptor::StartError(const boost::system::error_code & error) {
	if (boost::interprocess::detail::atomic_cas32(&m_error_state, 1, 0) == 0) {
		boost::system::error_code ec;
		acceptor_.cancel(ec);
		acceptor_.close(ec);
		m_timer.cancel(ec);
		OnError(error);
	}
}

void Acceptor::DispatchAccept(std::shared_ptr<Connection> connection) {
	acceptor_.async_accept(connection->GetSocket(),
			connection->GetStrand().wrap(
					boost::bind(&Acceptor::HandleAccept, shared_from_this(), _1,
							connection)));
}

void Acceptor::HandleTimer(const boost::system::error_code & error) {
	if (error || HasError() || hive_->HasStopped()) {
		StartError(error);
	} else {
		OnTimer(boost::posix_time::microsec_clock::local_time() - last_time_);
		StartTimer();
	}
}

void Acceptor::HandleAccept(const boost::system::error_code & error,
		std::shared_ptr<Connection> connection) {

	if (error || HasError() || hive_->HasStopped()) {
		connection->StartError(error);
	} else {
		if (connection->GetSocket().is_open()) {
			connection->StartTimer();
			if (OnAccept(connection,
					connection->GetSocket().remote_endpoint().address().to_string(),
					connection->GetSocket().remote_endpoint().port())) {

				connection->OnAccept(
						acceptor_.local_endpoint().address().to_string(),
						acceptor_.local_endpoint().port());
			}
		} else {
			StartError(error);
		}
	}
}

void Acceptor::Stop() {
	m_io_strand.post(
			boost::bind(&Acceptor::HandleTimer, shared_from_this(),
					error::connection_reset));
}

void Acceptor::Accept(std::shared_ptr<Connection> connection) {
	m_io_strand.post(
			boost::bind(&Acceptor::DispatchAccept, shared_from_this(),
					connection));
}

void Acceptor::Listen(const std::string & host, const uint16_t & port) {
	ip::tcp::resolver resolver(m_hive->GetService());
	ip::tcp::resolver::query query(host,
			boost::lexical_cast<std::string>(port));
	ip::tcp::endpoint endpoint = *resolver.resolve(query);
	acceptor_.open(endpoint.protocol());
	acceptor_.set_option(ip::tcp::acceptor::reuse_address( false));
	acceptor_.bind(endpoint);
	acceptor_.listen(socket_base::max_connections);
	StartTimer();
}

std::shared_ptr<Hive> Acceptor::GetHive() {
	return hive_;
}

ip::tcp::acceptor & Acceptor::GetAcceptor() {
	return acceptor_;
}

int32_t Acceptor::GetTimerInterval() const {
	return timer_interval_;
}

void Acceptor::SetTimerInterval(int32_t timer_interval) {
	m_timer_interval = timer_interval;
}

bool Acceptor::HasError() {
	return (boost::interprocess::detail::atomic_cas32(&m_error_state, 1, 1) == 1);
}

//-----------------------------------------------------------------------------

Connection::Connection(std::shared_ptr<Hive> hive) :
		m_hive(hive), socket_(hive->GetService()), io_strand_(
				hive->GetService()), timer_(hive->GetService()), receive_size_(
				4096), timer_interval_(1000), error_state_(0) {
}

Connection::~Connection() {
}

void Connection::Bind(const std::string & ip, uint16_t port) {
	ip::tcp::endpoint endpoint(ip::address::from_string(ip), port);
	m_socket.open(endpoint.protocol());
	m_socket.set_option(ip::tcp::acceptor::reuse_address( false));
	m_socket.bind(endpoint);
}

void Connection::StartSend() {
	if (!m_pending_sends.empty()) {
		async_write(m_socket, buffer(m_pending_sends.front()),
				m_io_strand.wrap(
						boost::bind(&Connection::HandleSend, shared_from_this(),
								placeholders::error, pending_sends_.begin())));
	}
}

void Connection::StartRecv(int32_t total_bytes) {
	if (total_bytes > 0) {
		m_recv_buffer.resize(total_bytes);
		async_read(m_socket, buffer(m_recv_buffer),
				m_io_strand.wrap(
						boost::bind(&Connection::HandleRecv, shared_from_this(),
								_1, _2)));
	} else {
		m_recv_buffer.resize(m_receive_buffer_size);
		m_socket.async_read_some(buffer(m_recv_buffer),
				m_io_strand.wrap(
						boost::bind(&Connection::HandleRecv, shared_from_this(),
								_1, _2)));
	}
}

void Connection::StartTimer() {
	m_last_time = boost::posix_time::microsec_clock::local_time();
	m_timer.expires_from_now(boost::posix_time::milliseconds(m_timer_interval));
	m_timer.async_wait(
			m_io_strand.wrap(
					boost::bind(&Connection::DispatchTimer, shared_from_this(),
							_1)));
}

void Connection::StartError(const boost::system::error_code & error) {
	if (boost::interprocess::detail::atomic_cas32(&m_error_state, 1, 0) == 0) {
		boost::system::error_code ec;
		m_socket.shutdown(ip::tcp::socket::shutdown_both, ec);
		m_socket.close(ec);
		m_timer.cancel(ec);
		OnError(error);
	}
}

void Connection::HandleConnect(const boost::system::error_code & error) {
	if (error || HasError() || hive_->HasStopped()) {
		StartError(error);
	} else {
		if (m_socket.is_open()) {
			OnConnect(m_socket.remote_endpoint().address().to_string(),
					m_socket.remote_endpoint().port());
		} else {
			StartError(error);
		}
	}
}

void Connection::HandleSend(const boost::system::error_code & error,
		std::list<std::vector<uint8_t> >::iterator itr) {
	if (error || HasError() || hive_->HasStopped()) {
		StartError(error);
	} else {
		OnSend(*itr);
		m_pending_sends.erase(itr);
		StartSend();
	}
}

void Connection::HandleRecv(const boost::system::error_code & error,
		int32_t actual_bytes) {
	if (error || HasError() || hive_->HasStopped()) {
		StartError(error);
	} else {
		m_recv_buffer.resize(actual_bytes);
		OnRecv(m_recv_buffer);
		m_pending_recvs.pop_front();
		if (!m_pending_recvs.empty()) {
			StartRecv(m_pending_recvs.front());
		}
	}
}

void Connection::HandleTimer(const boost::system::error_code & error) {
	if (error || HasError() || hive_->HasStopped()) {
		StartError(error);
	} else {
		OnTimer(boost::posix_time::microsec_clock::local_time() - last_time_);
		StartTimer();
	}
}

void Connection::DispatchSend(std::vector<uint8_t> buffer) {
	bool should_start_send = pending_sends_.empty();
	m_pending_sends.push_back(buffer);
	if (should_start_send) {
		StartSend();
	}
}

void Connection::DispatchRecv(int32_t total_bytes) {
	bool should_start_receive = pending_recvs_.empty();
	m_pending_recvs.push_back(total_bytes);
	if (should_start_receive) {
		StartRecv(total_bytes);
	}
}

void Connection::DispatchTimer(const boost::system::error_code & error) {
	m_io_strand.post(
			boost::bind(&Connection::HandleTimer, shared_from_this(), error));
}

void Connection::Connect(const std::string & host, uint16_t port) {
	boost::system::error_code ec;
	ip::tcp::resolver resolver(m_hive->GetService());
	ip::tcp::resolver::query query(host,
			boost::lexical_cast<std::string>(port));
	ip::tcp::resolver::iterator iterator = resolver.resolve(query);
	m_socket.async_connect(*iterator,
			m_io_strand.wrap(
					boost::bind(&Connection::HandleConnect, shared_from_this(),
							_1)));
	StartTimer();
}

void Connection::Disconnect() {
	m_io_strand.post(
			boost::bind(&Connection::HandleTimer, shared_from_this(),
					error::connection_reset));
}

void Connection::Recv(int32_t total_bytes) {
	m_io_strand.post(
			boost::bind(&Connection::DispatchRecv, shared_from_this(),
					total_bytes));
}

void Connection::Send(const std::vector<uint8_t> & buffer) {
	m_io_strand.post(
			boost::bind(&Connection::DispatchSend, shared_from_this(), buffer));
}

ip::tcp::socket & Connection::GetSocket() {
	return socket_;
}

strand & Connection::GetStrand() {
	return io_strand_;
}

std::shared_ptr<Hive> Connection::GetHive() {
	return hive_;
}

void Connection::SetReceiveBufferSize(int32_t size) {
	m_receive_buffer_size = size;
}

int32_t Connection::GetReceiveBufferSize() const {
	return receive_size_;
}

int32_t Connection::GetTimerInterval() const {
	return timer_interval_;
}

void Connection::SetTimerInterval(int32_t timer_interval) {
	m_timer_interval = timer_interval;
}

bool Connection::HasError() {
	return (boost::interprocess::detail::atomic_cas32(&m_error_state, 1, 1) == 1);
}

//-----------------------------------------------------------------------------
