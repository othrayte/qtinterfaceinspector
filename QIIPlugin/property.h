#pragma once

#include <QString>
#include <QVariant>

struct Property {
	Property(const QString& name, QVariant value)
		: name(name)
		, value(value) {}

	QString name;
	QVariant value;
};