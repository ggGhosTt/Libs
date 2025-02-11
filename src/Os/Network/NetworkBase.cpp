#include <FlameIDE/Os/Network/NetworkBase.hpp>

#include <FlameIDE/Os/Constants.hpp>

#include <FlameIDE/../../src/Os/Network/SocketFunctions.hpp>

namespace flame_ide
{namespace os
{namespace network
{
namespace // anonymous
{

NetworkBase::SocketType getSocketType(const Socket &socket) noexcept
{
	return static_cast<NetworkBase::SocketType>(socket::getType(socket));
};

} // namespace anonymous
}}} // namespace flame_ide::os::network

namespace flame_ide
{namespace os
{namespace network
{

// public

NetworkBase::~NetworkBase() noexcept
{
if (!operator bool())
		return;

	socket::destroy(socket);
}

NetworkBase::operator bool() const noexcept
{
	return (SOCKET_INVALID.descriptor != socket.descriptor) || (status >= 0);
}

Status NetworkBase::getStatus() const noexcept
{
	return status;
}

const Socket &NetworkBase::native() const
{
	return socket;
}

const NetworkBase::NativeCallbacks &NetworkBase::callbacks() noexcept
{
	static const NativeCallbacks socketControl = []()
	{
		NativeCallbacks callbacks;
		callbacks.destroy = socket::destroy;
		callbacks.receivingBytesNumber = socket::receivingBytesNumber;
		callbacks.getIpv4 = socket::getIpv4;
		callbacks.type = getSocketType;
		callbacks.error = socket::getError;
		callbacks.isListener = socket::isListener;
		callbacks.isServer = socket::isServer;
		return callbacks;
	} ();
	return socketControl;
}

// protected

NetworkBase::NetworkBase(Socket socket) noexcept : socket{ socket }
{
	if (operator bool())
		return;

	setStatus(STATUS_FAILED);
}

NetworkBase::NetworkBase(NetworkBase &&base) noexcept : NetworkBase(base.socket)
{
	operator=(move(base));
}

NetworkBase &NetworkBase::operator=(NetworkBase &&base) noexcept
{
	status = base.status;
	socket = base.socket;

	base.status = os::STATUS_SUCCESS;
	base.socket = os::SOCKET_INITIALIZER;

	return *this;
}

void NetworkBase::setStatus(Status statusInit) noexcept
{
	this->status = statusInit;
}

NetworkBase::SocketType NetworkBase::getType() const
{
	auto type = static_cast<NetworkBase::SocketType>(socket::getType(socket));
	switch (type) {
		case SocketType::STREAM:
		case SocketType::DATAGRAM:
			return type;

		case SocketType::UNKNOWN:
		default:
			return SocketType::UNKNOWN;
			break;
	}
}

os::Status NetworkBase::getError() const
{
	os::Status localStatus = socket::getError(socket);
	return localStatus;
}

bool NetworkBase::isServer() const
{
	return socket::isServer(socket);
}

bool NetworkBase::isListener() const
{
	return socket::isListener(socket);
}

// private

Types::int_t NetworkBase::checkStatus(Status status) noexcept
{
	if (status < 0)
	{
		return os::STATUS_FAILED;
	}
	return os::STATUS_SUCCESS;
}

}}} // namespace flame_ide::os::network
