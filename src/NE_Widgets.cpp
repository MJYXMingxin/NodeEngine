//
// Created by 12603 on 2023/7/26.
//

#include "NE_Widgets.h"

NE_NodeListWidget::NE_NodeListWidget(QMap<QString, QStringList> data, QWidget *parent)
    : QTreeWidget(parent),
    _data(std::move(data))
{
    resize(200,300);
    setColumnCount(1);
    setHeaderHidden(true);
    construct_tree();
}

void NE_NodeListWidget::construct_tree() {
    clear();
    QVector<QTreeWidgetItem*> items;
    foreach(auto name, _data.keys()) {
        QStringList names(name);
        auto item = new QTreeWidgetItem(names);
        foreach(auto title, _data.value(name)) {
            auto node_item = new QTreeWidgetItem(QStringList(title));
            node_item->setData(0, Qt::UserRole,
                               QVariant::fromValue(QMap<QString, QString>({{name, title}})));
            item->addChild(node_item);
        }
        items.push_back(item);
    }
    insertTopLevelItems(0, items);
    connect(this, &QTreeWidget::itemClicked, [=](QTreeWidgetItem* item, int column) {
        item->isExpanded() ? item->setExpanded(false) : item->setExpanded(true);
    });
}

NE_NodeList::NE_NodeList(QMap<QString, QStringList> data, QWidget *parent)
    :QWidget(parent),
     _brush_highlight(QBrush(QColor(200,200,0))),
    searchbox(new QLineEdit(this)),
    tree(new NE_NodeListWidget(std::move(data), this))
{
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(searchbox);
    layout->addWidget(tree);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);
    loadStyleSheet("NodeList");
    QTreeWidgetItemIterator iterator(tree);
    QTreeWidgetItem *child = *iterator;
    _brush_origin = child->foreground(0);

    connect(searchbox, &QLineEdit::textChanged, [this](const QString &text){
        QString wildcard;
        wildcard.clear();
        wildcard.push_back("*");
        for(auto word: text){
            wildcard.push_back(word);
            wildcard.push_back("*");
        }
        for (int i = 0; i < tree->topLevelItemCount(); i++) {
            QTreeWidgetItem* item = tree->topLevelItem(i);
            resetTree(item);
            searchTree(item, wildcard);
        }
    });
}

void NE_NodeList::searchTree(QTreeWidgetItem *cItem, const QString &txt) const
{
    if (txt != "*") {
        QList<QTreeWidgetItem *> match = tree->findItems(txt, Qt::MatchWildcard | Qt::MatchRecursive);
        if (!match.empty()) {
            if (match.contains(cItem)) {
                cItem->setForeground(0, _brush_highlight);
                cItem->setForeground(1, _brush_origin);
                cItem->setExpanded(true);
                cItem->setHidden(false);
                bool have = false;
                for(int i = 0; i < cItem->childCount(); ++i) {
                    if (match.contains(cItem->child(i))){
                        have = true;
                        cItem->child(i)->setForeground(0, _brush_highlight);
                    }
                }
                if (have) {
                    for(int i = 0; i < cItem->childCount(); ++i) {
                        if (!match.contains(cItem->child(i))) {
                            cItem->child(i)->setHidden(true);
                        }
                    }
                }
            } else {
                bool have = false;
                for (int i = 0; i < cItem->childCount(); ++i) {
                    if (match.contains(cItem->child(i))){
                        have = true;
                        cItem->child(i)->setForeground(0, _brush_highlight);
                        cItem->setExpanded(true);
                    }
                }
                if (!have) {
                    cItem->setForeground(0,_brush_origin);
                    cItem->setExpanded(false);
                    cItem->setHidden(true);
                } else {
                    for (int i = 0; i < cItem->childCount(); ++i) {
                        if (!match.contains(cItem->child(i))){
                            cItem->child(i)->setForeground(0, _brush_origin);
                            cItem->child(i)->setHidden(true);
                        }
                    }
                }
            }
        } else {
            cItem->setForeground(0,_brush_origin);
            cItem->setExpanded(false);
            cItem->setHidden(true);
        }
    }
    else { resetTree(cItem); }
}

void NE_NodeList::resetTree(QTreeWidgetItem *cItem) const
{
    cItem->setForeground(0,_brush_origin);
    cItem->setHidden(false);
    cItem->setExpanded(false);
    for (int i = 0; i < cItem->childCount(); ++i) {
        cItem->child(i)->setForeground(0, _brush_origin);
        cItem->child(i)->setHidden(false);
    }
}

[[maybe_unused]] void NE_NodeList::clearSearchBar() const {
    searchbox->clear();
}

void NE_NodeList::loadStyleSheet(const QString &sheetName)
{
    QFile file(":/resource/styles/" + sheetName + ".qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        setStyleSheet(styleSheet);
    }
}