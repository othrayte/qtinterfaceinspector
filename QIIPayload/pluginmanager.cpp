#include "pluginmanager.h"

#include "qiipayload.h"

#include <QDir>
#include <QPluginLoader>
#include <QFileInfo>
#include <QJsonArray>
#include <QDebug>

PluginManager::PluginManager(QObject* parent)
	: QObject(parent) {}

PluginManager::~PluginManager() {}

QDir PluginManager::pluginDirectory() {
	QDir directory(QiiPayload::instance()->location());
	return directory;
}

bool PluginManager::knows(QString fileName) { return _plugins.count(fileName) > 0; }

void PluginManager::learn(QFileInfo file) {
	qDebug() << file.absoluteFilePath();
	QPluginLoader loader(file.absoluteFilePath());

	QJsonObject metadata = loader.metaData()["MetaData"].toObject();
	if (metadata.isEmpty()) return;

	QString fileName = file.fileName();
	qDebug() << metadata;
	// Always read json data, encase it changed due to recompiling
	PluginData& data = _plugins[fileName];
	data.name		= metadata["name"].toString("<unnamed-plugin>");
	data.version	 = metadata["version"].toString("<unknown-version>");
	data.author	  = metadata["author"].toString("<unknown-author>");
	data.filePath	= file.canonicalFilePath();
	data.fileName	= fileName;
}

QList<TypeHandler*> PluginManager::handlers() const {
	QList<TypeHandler*> plugins;
	for (const auto& plugin : _plugins) {
		if (plugin.enabled) {
			if (!_loadedPlugins.contains(plugin.fileName)) {
				_loadedPlugins[plugin.fileName] = new QPluginLoader(plugin.filePath, const_cast<PluginManager*>(this));
			}
			if (QPluginLoader* loader = _loadedPlugins[plugin.fileName]) {
				if (auto instance = qobject_cast<TypeHandler*>(loader->instance())) {
					plugins.push_back(instance);
				}
			}
		}
	}
	return plugins;
}

void PluginManager::search() {
	qDebug() << "[PluginManager]"
			 << "Searching: " << pluginDirectory();
	for (const QFileInfo& file : pluginDirectory().entryInfoList(QDir::Files)) {
		learn(file);
	}
	emit pluginListUpdated();
}

void PluginManager::enable(QString fileName) {
	_loadedPlugins[fileName]->setFileName(fileName);
	_plugins[fileName].enabled = true;
}

void PluginManager::disable(QString fileName) {
	_plugins[fileName].enabled = false;
	_loadedPlugins.remove(fileName);
}
