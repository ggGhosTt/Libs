set(FLAME_NAMESPACE Flame)

set(FLAME_FAKE_HEADER_MODULE_SUFFIX hpp)
set(FLAME_HEADER_MODULE_SUFFIX header)
set(FLAME_OBJECT_MODULE_SUFFIX o)
set(FLAME_STATIC_MODULE_SUFFIX static)
set(FLAME_SHARED_MODULE_SUFFIX shared)

set(FLAME_NAME_SEPARATOR ".")
set(FLAME_ALIAS_SEPARATOR "::")

if (FLAME_CREATE_STATIC)
	set(FLAME_STATIC CREATE_STATIC_LIBRARY)
endif()

if (FLAME_CREATE_SHARED)
	set(FLAME_SHARED CREATE_SHARED_LIBRARY)
endif()

if (FLAME_CMAKE_DEBUG)
	set(FLAME_DEBUG DEBUG)
endif()
