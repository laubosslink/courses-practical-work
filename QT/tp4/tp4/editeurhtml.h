#ifndef EDITEURHTML_H
#define EDITEURHTML_H

#include <QMainWindow>

#include "widgetStat.h"

namespace Ui {
class EditeurHTML;
}

class EditeurHTML : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditeurHTML(QWidget *parent = 0);
    ~EditeurHTML();
private slots:
    void newFile();
    void openFile();
    void openFile(const QString &);
    void saveFile();
    void saveFileAs();
    void closeCurrentTab();
    void copySelection();
    void pasteSelection();
    void cutSelection();
    void setCurrentStat(int);
    void closeTab(int);
    void checkAvailableSave(int);
    void closeEvent(QCloseEvent *);
private slots:
    void currentTabNameChanged(QString);
    void aboutDialog();
private:
    Ui::EditeurHTML *ui;
    WidgetStat *ws;

    QAction* saveFileAction;
    QAction* saveAsFileAction;

    QAction* pasteSelectionAction;
    QAction* cutSelectionAction;
    QAction* copySelectionAction;

    void checkAvailableData();
};

#endif // EDITEURHTML_H
