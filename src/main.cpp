// #include "FreeFTP.h"
// #include <QtWidgets/QApplication>
//
// int main(int argc, char *argv[])
//{
//     QApplication a(argc, argv);
//     FreeFTP w;
//     w.show();
//     return a.exec();
// }

#include "StringListModel.h"
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QFileIconProvider>
#include <QHeaderView>
#include <QLabel>
int
main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QFileIconProvider iconProvider;
    QIcon folderIcon = iconProvider.icon(QFileIconProvider::IconType::Folder);
    QIcon fileIcon = iconProvider.icon(QFileIconProvider::IconType::File);
    QTableView tableView;
    QStandardItemModel model;

    tableView.setModel(&model);

    auto item0 = new QStandardItem;
    item0->setText("item0");
    item0->setIcon(folderIcon);
    model.appendRow(item0);

    auto item1 = new QStandardItem;
    item1->setText("item1");
    item1->setIcon(folderIcon);
    model.appendRow(item1);

    auto item2 = new QStandardItem;
    item2->setText("item2");
    item2->setIcon(fileIcon);
    model.appendRow(item2);


    tableView.show();
    tableView.setShowGrid(false);
    tableView.setFocusPolicy(Qt::NoFocus);
    tableView.verticalHeader()->setVisible(false);
    tableView.horizontalHeader()->setHighlightSections(false);
    tableView.setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    tableView.setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    tableView.setEditTriggers(QAbstractItemView::EditTrigger::EditKeyPressed);
    auto nameItem = new QStandardItem("名称");
    auto modifyDateItem = new QStandardItem("修改日期");
    auto typeItem = new QStandardItem("类型");
    auto sizeItem = new QStandardItem("大小");
    nameItem->setTextAlignment(Qt::AlignLeft);
    modifyDateItem->setTextAlignment(Qt::AlignLeft);
    typeItem->setTextAlignment(Qt::AlignLeft);
    sizeItem->setTextAlignment(Qt::AlignLeft);

    model.setHorizontalHeaderItem(0, nameItem);
    model.setHorizontalHeaderItem(1, modifyDateItem);
    model.setHorizontalHeaderItem(2, typeItem);
    model.setHorizontalHeaderItem(3, sizeItem);

    tableView.setStyleSheet(R"(
QTableView{
    border:none;
}

QTableView QHeaderView::section{
    color:#4C607A;
}
)");
    return app.exec();
}
