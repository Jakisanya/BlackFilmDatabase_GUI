#ifndef BLACKFILMDATABASE_GUI_2_CUSTOMSORTFILTERPROXYMODEL_H
#define BLACKFILMDATABASE_GUI_2_CUSTOMSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class CustomSortFilterProxyModel : public QSortFilterProxyModel
{
Q_OBJECT

public:
    explicit CustomSortFilterProxyModel(QObject *parent = nullptr);

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};

#endif //BLACKFILMDATABASE_GUI_2_CUSTOMSORTFILTERPROXYMODEL_H
