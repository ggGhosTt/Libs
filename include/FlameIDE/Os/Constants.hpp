#ifndef FLAMEIDE_OS_CONSTANTS_HPP
#define FLAMEIDE_OS_CONSTANTS_HPP

#include <FlameIDE/Os/Types.hpp>

#include <FlameIDE/Os/Posix/Constants.hpp>
#include <FlameIDE/Os/Windows/Constants.hpp>

namespace flame_ide
{namespace os
{

/// @brief
constexpr FileDescriptor INVALID_DESCRIPTOR =
		FLAMEIDE_OS_NAMESPACE::OS_INVALID_DESCRIPTOR;

/// @brief
constexpr Status STATUS_SUCCESS =
		FLAMEIDE_OS_NAMESPACE::OS_STATUS_SUCCESS;

constexpr Socket SOCKET_INITIALIZER =
		FLAMEIDE_OS_NAMESPACE::OS_SOCKET_INITIALIZER;
constexpr Socket SOCKET_INVALID =
		FLAMEIDE_OS_NAMESPACE::OS_SOCKET_INVALID;

/// @brief
constexpr ThreadContext THREAD_CONTEXT_INITIALIZER =
		FLAMEIDE_OS_NAMESPACE::OS_THREAD_CONTEXT_INITIALIZER;

/// @brief
constexpr MutexContext MUTEX_CONTEXT_INITIALIZER =
		FLAMEIDE_OS_NAMESPACE::OS_MUTEX_CONTEXT_INITIALIZER;

/// @brief
constexpr SemaphoreContext SEMAPHORE_CONTEXT_INITIALIZER =
		FLAMEIDE_OS_NAMESPACE::OS_SEMAPHORE_CONTEXT_INITIALIZER;

/// @brief
constexpr SemaphoreValue SEMAPHORE_VALUE_DEFAULT =
		FLAMEIDE_OS_NAMESPACE::OS_SEMAPHORE_VALUE_DEFAULT;

/// @brief
constexpr SemaphoreValue SEMAPHORE_VALUE_INVALID =
		FLAMEIDE_OS_NAMESPACE::OS_SEMAPHORE_VALUE_INVALID;

/// @brief PLATFORM_PREFIX
constexpr auto PIPE_NAME_PREFIX = FLAMEIDE_OS_NAMESPACE::OS_PLATFORM_PREFIX;

constexpr auto LIBRARY_HANDLE_INVALID = FLAMEIDE_OS_NAMESPACE::OS_LIBRARY_HANDLE_INVALID;

constexpr auto LIBRARY_PREFIX = FLAMEIDE_OS_NAMESPACE::OS_LIBRARY_PREFIX;
constexpr auto LIBRARY_SUFFIX_SHARED = FLAMEIDE_OS_NAMESPACE::OS_LIBRARY_SUFFIX_SHARED;

constexpr auto DIRECTORY_SLASH = FLAMEIDE_OS_NAMESPACE::OS_DIRECTORY_SLASH;

}}

#undef FLAMEIDE_OS_NAMESPACE

#endif // FLAMEIDE_OS_CONSTANTS_HPP
