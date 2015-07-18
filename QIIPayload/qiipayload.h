#pragma once

#include <QObject>

using namespace std;

class QiiPayload : public QObject {
	Q_OBJECT
public:
	QiiPayload(QString location);
	~QiiPayload();

	static QiiPayload* instance() { return _instance; }

	const QString& location() { return _location; }

public slots:
	void start();
	void stop();

private:
	QString _location;
	static QiiPayload* _instance;
};
