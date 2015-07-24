#include "propertymodel.h"

PropertyModel::PropertyModel() {
	_refreshTimer.setInterval(100);
	QObject::connect(&_refreshTimer, &QTimer::timeout, this, &PropertyModel::refresh);
	_refreshTimer.start();
}

QModelIndex PropertyModel::index(int row, int column, const QModelIndex& parent) const {
	if (parent.isValid()) {
		return createIndex(row, column, parent.row());
	} else {
		return createIndex(row, column, -1);
	}
}

QModelIndex PropertyModel::parent(const QModelIndex& index) const {
	if (!index.isValid() || index.internalId() == -1) {
		return QModelIndex();
	} else {
		return createIndex(index.internalId(), 0, -1);
	}
}

int PropertyModel::rowCount(const QModelIndex& parent) const {
	if (parent.isValid()) {
		if (parent.internalId() == -1) {
			QString type = _types.at(parent.row());
			return _properties[type].size();
		} else {
			return 0;
		}
	} else {
		return _properties.size();
	}
}

int PropertyModel::columnCount(const QModelIndex& parent) const { return 2; }

QVariant PropertyModel::data(const QModelIndex& index, int role) const {
	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		if (index.isValid()) {
			if (index.internalId() == -1) {
				if (index.column() == 0) {
					return _types.at(index.row());
				}
			} else {
				QString type				 = _types.at(index.internalId());
				const PropertyToken& token = _properties[type].at(index.row());
				if (index.column() == 0) {
					return token.property.name;
				} else if (index.column() == 1) {
					return token.typeHandler->get(token.property);
				}
			}
		}
	}
	return QVariant();
}

QVariant PropertyModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
		switch (section) {
		case 0: return "Property";
		case 1: return "Value";
		}
	}
	return QVariant();
}

bool PropertyModel::setData(const QModelIndex& index, const QVariant& value, int role) {
	if (role == Qt::EditRole && index.isValid() && index.internalId() != -1 && index.column() == 1) {
		QString type				 = _types.at(index.internalId());
		const PropertyToken& token = _properties[type].at(index.row());
		if (token.typeHandler->set(token.property, value)) {
			// emit dataChanged(index, index, { role });
			return true;
		}
	}
	return false;
}

Qt::ItemFlags PropertyModel::flags(const QModelIndex& index) const {
	if (index.isValid() && index.internalId() != -1 && index.column() == 1) {
		QString type				 = _types.at(index.internalId());
		const PropertyToken& token = _properties[type].at(index.row());
		if (token.typeHandler->isSetable(token.property)) {
			return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
		}
	}
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void PropertyModel::addProperties(QString type, TypeHandler* typeHandler, std::list<Property> properties) {
	if (!_properties.contains(type)) {
		beginInsertRows(QModelIndex(), _types.size(), _types.size() + 1);
		_types.append(type);
		_properties[type];
		endInsertRows();
	}
	int typeRow = _types.indexOf(type);
	for (Property property : properties) {
		int propertyRow = _properties[type].size();
		beginInsertRows(createIndex(typeRow, 0, -1), propertyRow, propertyRow + 1);
		_properties[type].append({typeHandler, property});
		endInsertRows();
	}
}

void PropertyModel::refresh() {
	for (int i = 0; i < _types.size(); ++i) {
		emit dataChanged(createIndex(0, 1, i), createIndex(_properties[_types[i]].size(), 1, i), {Qt::DisplayRole});
	}
}
