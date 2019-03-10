#ifndef FLAMEIDE_STREAMS_NAMEDPIPEREADER
#define FLAMEIDE_STREAMS_NAMEDPIPEREADER

#include <FlameIDE/Streams/StreamUtils.hpp>
#include <FlameIDE/Streams/FileStreamReader.hpp>
#include <FlameIDE/Common/OsTypes.hpp>

namespace flame_ide
{namespace streams
{

///
/// @brief The NamedPipeReader class
///
class NamedPipeReader: public stream_utils::AbstractByteStreamReader
{
public:
	using Parent = stream_utils::AbstractByteStreamReader;

	NamedPipeReader() noexcept;
	NamedPipeReader(const NamedPipeReader &) = delete;
	NamedPipeReader(NamedPipeReader &&reader) noexcept;

	///
	/// @brief NamedPipeReader
	/// @param name
	/// @param deletePipe
	///
	NamedPipeReader(const char *name, bool deletePipe = true) noexcept;

	virtual ~NamedPipeReader() noexcept;

	NamedPipeReader &operator=(const NamedPipeReader &) = delete;
	NamedPipeReader &operator=(NamedPipeReader &&reader) noexcept;

	virtual SizeTraits::SsizeType read(OutputByteRange range) noexcept;
	virtual SizeTraits::SsizeType read(OutputCircularByteRange range) noexcept;

	///
	/// @brief getFileDescriptor
	/// @param continueOwning
	/// @return
	///
	os::FileDescriptor getFileDescriptor(bool continueOwning = false) noexcept;

	///
	/// @brief open
	/// @param name
	/// @param deletePipe
	/// @return
	///
	os::Status open(const char *name, bool deletePipe = true) noexcept;

private:
	FileStreamReader reader; ///<
	bool delPipe; ///<
};

}}

#endif // FLAMEIDE_STREAMS_NAMEDPIPEREADER
