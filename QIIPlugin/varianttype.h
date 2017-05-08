#pragma once

#include <QVariant>

class VariantType {
public:
	VariantType(const QVariant& variant) : _type(variant.userType()) {}

	QVariant::Type type() const { return _type >= QMetaType::User ? QVariant::UserType : static_cast<QVariant::Type>(_type); }
	const char* typeName() const { return QMetaType::typeName(_type); }
	int userType() const { return _type; }

	inline bool operator<(const VariantType& rhs) const { return _type < rhs._type; }

private:
	const int _type;
};