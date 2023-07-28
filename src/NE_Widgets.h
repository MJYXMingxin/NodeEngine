//
// Created by 12603 on 2023/7/26.
//

#ifndef NODEENGINE_NE_WIDGETS_H
#define NODEENGINE_NE_WIDGETS_H

#include "pch.h"

class NE_NodeListWidget : public QTreeWidget{
    Q_OBJECT
public:
    explicit NE_NodeListWidget(QMap<QString, QStringList> data = {},
                               QWidget *parent = nullptr);
    void construct_tree();
private:
    QMap<QString, QStringList> _data;
};

class NE_NodeList : public QWidget{
    Q_OBJECT
public:
    explicit NE_NodeList(QMap<QString, QStringList> data = {},
                         QWidget *parent = nullptr);
    void searchTree(QTreeWidgetItem *cItem, const QString &txt) const;
    void resetTree(QTreeWidgetItem *cItem) const;

    [[maybe_unused]] void clearSearchBar() const;

    void loadStyleSheet(const QString &sheetName);

public:
    QLineEdit *searchbox;
    NE_NodeListWidget *tree;
    QBrush _brush_highlight;
    QBrush _brush_origin;
};

#endif //NODEENGINE_NE_WIDGETS_H
