#pragma once

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QWidget>

#include <vector>
#include <unordered_map>

class WidgetModel : public QAbstractItemModel {
	struct WidgetInfo {
		WidgetInfo(QWidget* parent)
			: parent(parent)
			, watchingChildren(false) {}

		QWidget* parent;
		bool watchingChildren;
		std::vector<QWidget*> children;
	};

public:
	WidgetModel();
	~WidgetModel();

	virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
	virtual QModelIndex parent(const QModelIndex& index) const override;

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	virtual bool canFetchMore(const QModelIndex& parent) const override;
	virtual void fetchMore(const QModelIndex& parent) override;

	virtual bool eventFilter(QObject* watched, QEvent* event) override;

	void addRootWidget(QWidget* widget);

	void addWidget(QWidget* parent, QWidget* widget);
	void removeWidget(QWidget* parent, QWidget* widget);

private:
	void watch(QWidget* widget) const;
	const std::vector<QWidget*>& getChildren(QWidget* widget) const;
	QModelIndex indexFor(QWidget* widget) const;

	mutable std::unordered_map<QWidget*, WidgetInfo> _shadowMap;
};
