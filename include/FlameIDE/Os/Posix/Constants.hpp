#ifndef FLAMEIDE_OS_POSIX_CONSTANTS_HPP
#define FLAMEIDE_OS_POSIX_CONSTANTS_HPP

#include <FlameIDE/Os/Posix/Types.hpp>

#if FLAMEIDE_OS_POSIX != FLAMEIDE_OS_NULL

namespace flame_ide
{namespace os
{namespace posix
{

constexpr OsFileDescriptor OS_INVALID_DESCRIPTOR = -1;

constexpr OsStatus OS_STATUS_SUCCESS = 0;
constexpr OsStatus OS_STATUS_FAILED = -1;

constexpr OsSocketAddressIn OS_SOCKET_ADDRESS_INITIALIZER = {};
constexpr OsSocketDescriptor OS_SOCKET_DESCRIPTOR_INITIALIZER = {};
constexpr OsSocket OS_SOCKET_INITIALIZER = {
		OS_SOCKET_ADDRESS_INITIALIZER, OS_SOCKET_DESCRIPTOR_INITIALIZER
};
constexpr Types::size_t OS_SOCKET_TCP_MAX_CLIENTS = SOMAXCONN;

constexpr OsSocket OS_SOCKET_INVALID = OsSocket{
		OS_SOCKET_ADDRESS_INITIALIZER, OS_INVALID_DESCRIPTOR
};

constexpr OsThreadContext OS_THREAD_CONTEXT_INITIALIZER = OsThreadContext{};

constexpr OsMutexContext OS_MUTEX_CONTEXT_INITIALIZER = {
	PTHREAD_MUTEX_INITIALIZER, {}
};

constexpr OsSemaphoreContext OS_SEMAPHORE_CONTEXT_INITIALIZER = OsSemaphoreContext{};

constexpr OsSemaphoreValue OS_SEMAPHORE_VALUE_DEFAULT = 1u;
constexpr OsSemaphoreValue OS_SEMAPHORE_VALUE_INVALID =
		NumberLimitTrait<OsSemaphoreValue>::MAX_VALUE;

#define OS_SPINLOCK_INITIALIZER OsSpinlockContext{}

constexpr char OS_PLATFORM_PREFIX[] = "/tmp/";

constexpr OsLibraryHandle OS_LIBRARY_HANDLE_INVALID = OsLibraryHandle{};

constexpr char OS_LIBRARY_PREFIX[] = "lib";
constexpr char OS_LIBRARY_SUFFIX_SHARED[] = ".so";

constexpr char OS_DIRECTORY_SLASH = '/';

}}}

#ifndef FLAMEIDE_OS_NAMESPACE
#	define FLAMEIDE_OS_NAMESPACE ::flame_ide::os::posix
#endif // FLAMEIDE_OS_NAMESPACE

#endif // FLAMEIDE_OS_POSIX != FLAMEIDE_OS_NULL

#endif // FLAMEIDE_OS_POSIX_CONSTANTS_HPP
