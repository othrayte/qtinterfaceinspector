#pragma once

#include <QString>
#include <QVariant>

struct Property {
	Property(const QString& name, QVariant id)
		: name(name)
		, id(id) {}

	QString name;
	QVariant id;
};