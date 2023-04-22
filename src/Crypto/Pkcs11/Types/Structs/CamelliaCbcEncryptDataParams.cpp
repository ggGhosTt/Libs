#include <FlameIDE/Crypto/Pkcs11/Types/Structs/CamelliaCbcEncryptDataParams.hpp>
#include <FlameIDE/Common/Utils.hpp>

namespace flame_ide
{namespace pkcs11
{namespace structs
{

CamelliaCbcEncryptDataParams::CamelliaCbcEncryptDataParams() noexcept
{}

CamelliaCbcEncryptDataParams::CamelliaCbcEncryptDataParams(
		const CamelliaCbcEncryptDataParams &params
) noexcept
{
	operator=(params);
}

CamelliaCbcEncryptDataParams::CamelliaCbcEncryptDataParams(const Parent &params) noexcept
{
	operator=(params);
}

CamelliaCbcEncryptDataParams::CamelliaCbcEncryptDataParams(
		const decltype(Parent::iv) &iv
		, const decltype(Parent::pData) &data
		, const decltype(Parent::length) &dataLength
) noexcept
{
	copy(this->iv, iv);
	pData = data;
	length = dataLength;
}

CamelliaCbcEncryptDataParams &
CamelliaCbcEncryptDataParams::operator=(const CamelliaCbcEncryptDataParams &params) noexcept
{
	return operator=(static_cast<const Parent &>(params));
}

CamelliaCbcEncryptDataParams &
CamelliaCbcEncryptDataParams::operator=(const Parent &params) noexcept
{
	copy(iv, params.iv);
	pData = params.pData;
	length = params.length;

	return *this;
}

//using Parent::iv; // [16]
//using Parent::pData;
//using Parent::length;

}}} // flame_ide::pkcs11::structs
