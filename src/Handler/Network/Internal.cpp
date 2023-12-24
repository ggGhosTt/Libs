#include <FlameIDE/../../src/Handler/Network/Internal.hpp>
#include <FlameIDE/../../src/Handler/Network/UdpServer.hpp>

#include <FlameIDE/Os/Constants.hpp>
#include <FlameIDE/Os/Threads/Utils.hpp>

namespace flame_ide
{namespace handler
{namespace network
{namespace udp
{
namespace // anonymous
{

struct ServerCommunicationData
{
	os::network::UdpServer::WithClient client;
	Server::Message *message;
	Server::ActualOutput *output;
};

struct ClientCommunicationData
{
	os::network::UdpClient *client;
	Server::Message *message;
	Server::ActualOutput *output;
};

} // namespace anonymous
}}}} // namespace flame_ide::os::network::udp

// private callbacks for UDP - difinition
namespace flame_ide
{namespace handler
{namespace network
{namespace udp
{namespace callbacks
{
namespace // anonymous
{

// client

// TODO
//Types::ssize_t clientBytesToRead(void *data) noexcept;

// TODO
//Types::ssize_t clientReceive(void *data, templates::Range<byte_t *>) noexcept;

// TODO
//Types::ssize_t clientSend(void *data, templates::Range<const byte_t *>) noexcept;

// server

Types::ssize_t serverBytesToRead(const udp::ServerCommunicationData *message) noexcept;

Types::ssize_t serverReceive(
		udp::ServerCommunicationData *message, templates::Range<byte_t *> range
) noexcept;

Types::ssize_t serverSend(
		udp::ServerCommunicationData *data, templates::Range<const byte_t *>
) noexcept;

} // namespace anonymous
}}}}} // namespace flame_ide::os::network::udp::callbacks

// private callbacks for TCP - difinition
namespace flame_ide
{namespace os
{namespace network
{namespace tcp
{namespace callbacks
{
namespace // anonymous
{

// client

// TODO
//Types::ssize_t clientBytesToRead(void *data) noexcept;

// TODO
//Types::ssize_t clientReceive(void *data, templates::Range<byte_t *>) noexcept;

// TODO
//Types::ssize_t clientSend(void *data, templates::Range<const byte_t *>) noexcept;

// server

// TODO
//Types::ssize_t serverBytesToRead(void *data) noexcept;

// TODO
//Types::ssize_t serverReceive(void *data, templates::Range<byte_t *>) noexcept;

// TODO
//Types::ssize_t serverSend(void *data, templates::Range<const byte_t *>) noexcept;

} // namespace anonymous
}}}}} // namespace flame_ide::os::network::udp::callbacks

// Handler::Internal implementation
namespace flame_ide
{namespace handler
{namespace network
{

Handler::Internal::Internal() noexcept
{
//	for (auto &i : workers)
//	{
//		i.set(udp, tcp);
//	}
}

Handler::Internal::~Internal() = default;

Handler::ServerHandle Handler::Internal::push(os::network::UdpServer &&server) noexcept
{
	udp::Server *data = udp.push(flame_ide::move(server));
	if (!data)
		return ServerHandle{};

	ServerHandle handle;
	handle.data = data;
	handle.callbackGetCommunicationHandle = getUdpServerHandleCallback();
	return handle;
}

Handler::CommunicationHandle Handler::Internal::push(os::network::UdpClient &&client) noexcept
{
	udp::Client *data = udp.push(flame_ide::move(client));
	if (!data)
		return CommunicationHandle{};

	Handler::CommunicationHandle handle;
//	handle.data[0] = nullptr; // ?
//	handle.data[1] = nullptr; // ?
//	handle.callbackBytesToRead = udp::callbacks::clientBytesToRead;
//	handle.callbackReceive = udp::callbacks::clientReceive;
//	handle.callbackSend = udp::callbacks::clientSend;
	return handle;
}

Handler::ServerHandle Handler::Internal::push(os::network::TcpServer &&server) noexcept
{
	if (!tcp.servers)
		tcp.servers = decltype(tcp.servers){};

	tcp::Server *data = nullptr;
	for (auto &i : *tcp.servers)
	{
		if (i->server)
			continue;
		data = i.pointer();
		break;
	}
	if (!data)
		return {};
	data->server = flame_ide::move(server);

	Handler::ServerHandle handle;
	{
		static auto callbackGetCommunicationHandle = [](void *data)
				-> Handler::CommunicationHandle
		{
			if (!data)
				return {};

			Handler::CommunicationHandle handle;
//			handle.data[0] = nullptr; // ?
//			handle.data[1] = nullptr; // ?
//			handle.callbackBytesToRead = tcp::callbacks::serverBytesToRead;
//			handle.callbackReceive = tcp::callbacks::serverReceive;
//			handle.callbackSend = tcp::callbacks::serverSend;
			return handle;
		};
		handle.callbackGetCommunicationHandle = callbackGetCommunicationHandle;
	}
	return handle;
}

Handler::CommunicationHandle Handler::Internal::push(os::network::TcpClient &&/*client*/) noexcept
{
	if (!tcp.clients)
		tcp.clients = decltype(tcp.clients){};

//	tcp::Client *data = nullptr;
//	for (auto &i : tcp.clients)
//	{
//		if (i.client)
//			continue;
//		data = &i;
//		break;
//	}
//	if (!data)
//		return {};
//	data->client = flame_ide::move(client);

	Handler::CommunicationHandle handle;
//	handle.data[0] = nullptr; // ?
//	handle.data[1] = nullptr; // ?
//	handle.callbackBytesToRead = tcp::callbacks::clientBytesToRead;
//	handle.callbackReceive = tcp::callbacks::clientReceive;
//	handle.callbackSend = tcp::callbacks::clientSend;
	return handle;
}

// private

Handler::ServerHandle::CallbackGetCommunicationHandle
Handler::Internal::getUdpServerHandleCallback() const noexcept
{
	using CallbackGetUdpCommunicationHandle =
			Handler::CommunicationHandle (*)(udp::Server *);
	using CallbackGetCommunicationHandle =
			Handler::ServerHandle::CallbackGetCommunicationHandle;

	using CallbackBytesToRead = Handler::CommunicationHandle::CallbackBytesToRead;
	using CallbackReceive = Handler::CommunicationHandle::CallbackReceive;
	using CallbackSend = Handler::CommunicationHandle::CallbackSend;

	static auto callbackGetCommunicationHandle = [](udp::Server *data)
			-> Handler::CommunicationHandle
	{
		if (!data)
			return Handler::CommunicationHandle{};

		udp::Server::Message *inputMessage = nullptr;
		{
			auto &input = data->input;
			os::threads::Locker inputLocker{ input.spin };

			if (input.first == input.last)
				return Handler::CommunicationHandle{};

			{
				auto *message = input.first->pointer();
				os::threads::Locker messageLocker{ message->spin };
				// TODO: а точно ли сообщение готово?

				inputMessage = message;
				inputMessage->state = udp::MessageState::PROCESSING;
			}
			++input.first;
		}

		Handler::CommunicationHandle handle;
		handle.object = udp::ServerCommunicationData{
				inputMessage->client, inputMessage, &data->output
		};
		handle.callbackBytesToRead = reinterpret_cast<CallbackBytesToRead>(
				udp::callbacks::serverBytesToRead
		);
		handle.callbackReceive = reinterpret_cast<CallbackReceive>(
				udp::callbacks::serverReceive
		);
		handle.callbackSend = reinterpret_cast<CallbackSend>(
				udp::callbacks::serverSend
		);
		return handle;
	};

	CallbackGetUdpCommunicationHandle callback = callbackGetCommunicationHandle;
	return reinterpret_cast<CallbackGetCommunicationHandle>(callback);
}


}}} // namespace flame_ide::os::network

// private callbacks for UDP - implementation
namespace flame_ide
{namespace handler
{namespace network
{namespace udp
{namespace callbacks
{
namespace // anonymous
{

// client

// TODO
//Types::ssize_t clientBytesToRead(void */*data*/) noexcept
//{
//	return os::STATUS_FAILED;
//}

// TODO
//Types::ssize_t clientReceive(void */*data*/, templates::Range<byte_t *>) noexcept
//{
//	return os::STATUS_FAILED;
//}

// TODO
//Types::ssize_t clientSend(void */*data*/, templates::Range<const byte_t *>) noexcept
//{
//	return os::STATUS_FAILED;
//}

// server

Types::ssize_t serverBytesToRead(const udp::ServerCommunicationData *data) noexcept
{
	if (!data || !data->message)
		return os::STATUS_FAILED;

	os::threads::Locker{ data->message->spin };

	return data->message->size;
}

Types::ssize_t
serverReceive(
		udp::ServerCommunicationData *data, templates::Range<byte_t *> range
) noexcept
{
	if (!data || !data->message)
		return os::STATUS_FAILED;

	Types::ssize_t numberToRead = 0;
	auto &message = *data->message;
	{
		os::threads::Locker{ message.spin };

		const Types::ssize_t rangeSize = range.end() - range.begin();
		const Types::ssize_t messageSize = message.size;
		const Types::ssize_t toRead = (rangeSize < messageSize)
				? rangeSize
				: messageSize;

		auto begin = range.begin();
		for (Types::ssize_t i = 0; i < toRead; ++i, ++begin)
		{
			*begin = message.bytes[i];
		}
		message.size = 0;
		message.client = decltype(message.client){};
		message.state = MessageState::EMPTY;

		numberToRead = toRead;
	}
	return numberToRead;
}

Types::ssize_t
serverSend(
		udp::ServerCommunicationData *data, templates::Range<const byte_t *> range
) noexcept
{
	if (!data || !data->output)
		return os::STATUS_FAILED;

	auto &output = *data->output;
	Server::Message *message = nullptr;
	{
		os::threads::Locker locker{ output.spin };
		message = output.last->pointer();
		{
			os::threads::Locker locker{ message->spin };
			message->state = MessageState::PROCESSING;
		}
		++output.last;
	}

	const Types::ssize_t rangeSize = range.end() - range.begin();
	{
		os::threads::Locker locker{ message->spin };
		message->size = rangeSize;
		message->client = data->client;

		auto begin = range.begin();
		for (Types::ssize_t i = 0; i < rangeSize; ++i, ++begin)
		{
			message->bytes[i] = *begin;
		}

		message->state = MessageState::READY;
	}
	return rangeSize;
}

} // namespace anonymous
}}}}} // namespace flame_ide::os::network::udp::callbacks

// private callbacks for TCP - implementation
namespace flame_ide
{namespace os
{namespace network
{namespace tcp
{namespace callbacks
{
namespace // anonymous
{

// client

// TODO
//Types::ssize_t clientBytesToRead(void */*data*/) noexcept
//{
//	return os::STATUS_FAILED;
//}

// TODO
//Types::ssize_t clientReceive(void */*data*/, templates::Range<byte_t *>) noexcept
//{
//	return os::STATUS_FAILED;
//}

// TODO
//Types::ssize_t clientSend(void */*data*/, templates::Range<const byte_t *>) noexcept
//{
//	return os::STATUS_FAILED;
//}

// server

// TODO
//Types::ssize_t serverBytesToRead(void */*data*/) noexcept
//{
//	return os::STATUS_FAILED;
//}

// TODO
//Types::ssize_t serverReceive(void */*data*/, templates::Range<byte_t *>) noexcept
//{
//	return os::STATUS_FAILED;
//}

// TODO
//Types::ssize_t serverSend(void */*data*/, templates::Range<const byte_t *>) noexcept
//{
//	return os::STATUS_FAILED;
//}

} // namespace anonymous
}}}}} // namespace flame_ide::os::network::udp::callbacks
