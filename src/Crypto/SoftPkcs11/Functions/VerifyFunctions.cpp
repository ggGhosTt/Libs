#include <FlameIDE/../../src/Crypto/SoftPkcs11/Functions/VerifyFunctions.hpp>

#include <FlameIDE/Common/Utils.hpp>
#include <FlameIDE/Crypto/Pkcs11/Types/Enums.hpp>

namespace flame_ide
{namespace soft_pkcs11
{namespace functions
{namespace verify
{

pkcs11::value_types::ReturnType init(
		pkcs11::value_types::SessionHandle session
		, pkcs11::structs::MechanismPtr mechanism
		, pkcs11::value_types::ObjectHandle key
)
{
	flame_ide::unused(session);
	flame_ide::unused(mechanism);
	flame_ide::unused(key);

	return pkcs11::enums::value(pkcs11::enums::ReturnType::OK);
}

pkcs11::value_types::ReturnType update(
		pkcs11::value_types::SessionHandle session
		, pkcs11::value_types::BytePtr dataPart
		, pkcs11::value_types::Ulong dataPartLength
)
{
	flame_ide::unused(session);
	flame_ide::unused(dataPart);
	flame_ide::unused(dataPartLength);

	return pkcs11::enums::value(pkcs11::enums::ReturnType::OK);
}

pkcs11::value_types::ReturnType final(
		pkcs11::value_types::SessionHandle session
		, pkcs11::value_types::BytePtr signature
		, pkcs11::value_types::Ulong signatureLength
)
{
	flame_ide::unused(session);
	flame_ide::unused(signature);
	flame_ide::unused(signatureLength);

	return pkcs11::enums::value(pkcs11::enums::ReturnType::OK);
}

pkcs11::value_types::ReturnType full(
		pkcs11::value_types::SessionHandle session
		, pkcs11::value_types::BytePtr data
		, pkcs11::value_types::Ulong dataLength
		, pkcs11::value_types::BytePtr signature
		, pkcs11::value_types::Ulong signatureLength
)
{
	flame_ide::unused(session);
	flame_ide::unused(data);
	flame_ide::unused(dataLength);
	flame_ide::unused(signature);
	flame_ide::unused(signatureLength);

	return pkcs11::enums::value(pkcs11::enums::ReturnType::OK);
}

namespace recover
{

pkcs11::value_types::ReturnType init(
		pkcs11::value_types::SessionHandle session
		, pkcs11::structs::MechanismPtr mechanism
		, pkcs11::value_types::ObjectHandle key
)
{
	flame_ide::unused(session);
	flame_ide::unused(mechanism);
	flame_ide::unused(key);

	return pkcs11::enums::value(pkcs11::enums::ReturnType::OK);
}

pkcs11::value_types::ReturnType full(
		pkcs11::value_types::SessionHandle session
		, pkcs11::value_types::BytePtr data
		, pkcs11::value_types::Ulong dataLength
		, pkcs11::value_types::BytePtr signature
		, pkcs11::value_types::UlongPtr signatureLength
)
{
	flame_ide::unused(session);
	flame_ide::unused(data);
	flame_ide::unused(dataLength);
	flame_ide::unused(signature);
	flame_ide::unused(signatureLength);

	return pkcs11::enums::value(pkcs11::enums::ReturnType::OK);
}

} // namespace recover

}}}} // flame_ide::soft_pkcs11::functions::control
