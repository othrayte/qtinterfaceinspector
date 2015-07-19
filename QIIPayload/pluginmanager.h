#pragma once

#include "typehandler.h"
#include "typehandlerprovider.h"

#include <QObject>
#include <QDir>
#include <QPluginLoader>

#include <map>

struct PluginData {
	QString name;
	QString version;
	QString author;
	bool enabled;
	QString fileName;
	QString filePath;
};

class PluginManager : public QObject, public TypeHandlerProvider {
	Q_OBJECT

public:
	PluginManager(QObject* parent = nullptr);
	~PluginManager();

	static QDir pluginDirectory();

	bool knows(QString fileName);
	void learn(QFileInfo file);

	virtual QList<TypeHandler*> handlers() const override;

signals:
	void pluginListUpdated();

public slots:
	void search();

	void enable(QString fileName);
	void disable(QString fileName);

private:
	mutable QMap<QString, QPluginLoader*> _loadedPlugins;
	QMap<QString, PluginData> _plugins; // plugins by filename
};
