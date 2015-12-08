/**
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */

/**
 * @author Parmentier Laurent <laurent.parmentier@ecole.ensicaen.fr>
 */

#include "editeurhtml.h"
#include "ui_editeurhtml.h"
#include "widgetDocument.h"
#include "widgetStat.h"

#include <QDebug>

#include <QByteArray>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>
#include <QCloseEvent>

EditeurHTML::EditeurHTML(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditeurHTML)
{
    ui->setupUi(this);

    /**
     * Pixmax
     */
    QIcon newDocumentIcon(":/pictures/document-new.png");
    QIcon opentDocumentIcon(":/pictures/document-open.png");
    QIcon saveDocumentIcon(":/pictures/document-save.png");
    QIcon saveAsDocumentIcon(":/pictures/document-save-as.png");
    QIcon copySelectionIcon(":/pictures/edit-copy.png");
    QIcon cutSelectionIcon(":/pictures/edit-cut.png");
    QIcon pasteSelectiontIcon(":/pictures/edit-paste.png");

    /**
     * Menu bar
     */
    QMenu *file = ui->menuBar->addMenu("&Fichier");
    QMenu *edition = ui->menuBar->addMenu("&Edition");
    QMenu *aide = ui->menuBar->addMenu("&Aide");

    /* Fichier */
    QAction *newFile = new QAction(newDocumentIcon, tr("&Nouveau"), this);
    QAction *openFile = new QAction(opentDocumentIcon, tr("&Ouvrir..."), this);
    EditeurHTML::saveFileAction = new QAction(saveDocumentIcon, tr("&Enregistrer"), this);
    EditeurHTML::saveAsFileAction = new QAction(saveAsDocumentIcon, tr("&Enregistrer sous..."), this);
    QAction *closeFile = new QAction(tr("&Fermer"), this);
    QAction *quitApplication = new QAction(tr("&Quitter"), this);

    file->addAction(newFile);
    file->addAction(openFile);
    file->addAction(saveFileAction);
    file->addAction(saveAsFileAction);
    file->addAction(closeFile);

    file->addSeparator();
    file->addAction(quitApplication);

    /* Edition */
    EditeurHTML::copySelectionAction = new QAction(copySelectionIcon, tr("&Copier"), this);
    EditeurHTML::cutSelectionAction = new QAction(cutSelectionIcon, tr("&Couper"), this);
    EditeurHTML::pasteSelectionAction = new QAction(pasteSelectiontIcon, tr("&Coller"), this);

    edition->addAction(copySelectionAction);
    edition->addAction(cutSelectionAction);
    edition->addAction(pasteSelectionAction);

    /**
     * Aide
     */
    QAction *aPropos = new QAction("&A propos...", this);

    aide->addAction(aPropos);

    /**
     * mainToolBar
     */
    ui->mainToolBar->addAction(newFile);
    ui->mainToolBar->addAction(openFile);
    ui->mainToolBar->addAction(saveFileAction);
    ui->mainToolBar->addAction(saveAsFileAction);

    /**
     * statusBar
     */
    ws = new WidgetStat(this);
    ui->statusBar->addPermanentWidget(ws);

    /**
     * Raccourcis
     */
    newFile->setShortcut(Qt::CTRL + Qt::Key_N);
    openFile->setShortcut(Qt::CTRL + Qt::Key_O);
    saveFileAction->setShortcut(Qt::CTRL + Qt::Key_S);
    copySelectionAction->setShortcut(Qt::CTRL + Qt::Key_C);
    pasteSelectionAction->setShortcut(Qt::CTRL + Qt::Key_V);
    cutSelectionAction->setShortcut(Qt::CTRL + Qt::Key_X);

    /**
     * Tabwidget
     */
    ui->tabWidget->setTabsClosable(true);

    /**
     * Connections BUS
     */
    connect(newFile, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(openFile, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(saveFileAction, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(saveAsFileAction, SIGNAL(triggered()), this, SLOT(saveFileAs()));
    connect(closeFile, SIGNAL(triggered()), this, SLOT(closeCurrentTab()));
    connect(copySelectionAction, SIGNAL(triggered()), this, SLOT(copySelection()));
    connect(pasteSelectionAction, SIGNAL(triggered()), this, SLOT(pasteSelection()));
    connect(cutSelectionAction, SIGNAL(triggered()), this, SLOT(cutSelection()));

    connect(aPropos, SIGNAL(triggered()), this, SLOT(aboutDialog()));

    connect(quitApplication, SIGNAL(triggered()), this, SLOT(close()));

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(setCurrentStat(int)));
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(ui->tabWidget, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(newFile()));

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(checkAvailableSave(int)));

    // Des fichiers à ouvrir peuvent être précsés sur la ligne de commande
    bool fileFinded = false;

    if(QApplication::arguments().length() != 0)
    {
        QStringList qsl = QApplication::arguments();

        for(int i=1; i<qsl.length(); i++)
        {
            QFileInfo f(qsl.at(i));

            if(f.exists() && f.isFile())
            {
                fileFinded = true;
                EditeurHTML::openFile(qsl.at(i));
            }
        }
    }

    // Si des fichiers sont précisés sur la ligne de commande, aucun document vide sans nim n'est ouvert
    if(!fileFinded)
    {
        // au lancement un document vide est ouvert
        EditeurHTML::newFile();
    }
}

void EditeurHTML::aboutDialog()
{
    QMessageBox::about(this, tr("EditeurHTML"), tr("Développé par PARMENTIER Laurent<br>et ELHIMDI Yasmine"));
}

void EditeurHTML::closeEvent(QCloseEvent *event)
{
    for(int i=ui->tabWidget->count(); i>0; i--)
    {
        ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(i));
        closeCurrentTab();
    }

    if(ui->tabWidget->count() != 0)
    {
        event->ignore();
    }
}

void EditeurHTML::setCurrentStat(int i)
{
    //ws->setWidgetDocument(static_cast<WidgetDocument*>(ui->tabWidget->currentWidget()));
}

void EditeurHTML::newFile()
{
    QWidget *w = new WidgetDocument(this, ws);
    ui->tabWidget->addTab(w, w->windowTitle()); // use windowTitle ??

    ui->tabWidget->setCurrentWidget(w);

    checkAvailableData();

    connect(w, SIGNAL(windowTitleChanged(QString)), this, SLOT(currentTabNameChanged(QString)));
}

void EditeurHTML::currentTabNameChanged(QString name)
{
    WidgetDocument *w = (WidgetDocument*) ui->tabWidget->currentWidget();

    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), name);

    if(w->isModified())
    {
        EditeurHTML::saveFileAction->setEnabled(true);
    } else
    {
        EditeurHTML::saveFileAction->setDisabled(true);
    }
}

void EditeurHTML::openFile(const QString & filename)
{
    WidgetDocument *w = new WidgetDocument(this, ws);

    if(w->loadFile(filename))
    {
        ui->tabWidget->addTab(w, filename);
        ui->tabWidget->setCurrentWidget(w);
        checkAvailableData();
        connect(w, SIGNAL(windowTitleChanged(QString)), this, SLOT(currentTabNameChanged(QString)));
    } else
    {
        delete w;
    }
}

void EditeurHTML::openFile()
{
    const QString filename = QFileDialog::getOpenFileName(this);
    openFile(filename);
}

void EditeurHTML::saveFile()
{
    WidgetDocument *w = (WidgetDocument*) ui->tabWidget->currentWidget();

    if(w->filenameExist())
    {
        w->saveFile();
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), w->getFilename());
    } else
    {
        saveFileAs();
    }
}

void EditeurHTML::saveFileAs()
{
    QString filename = QFileDialog::getSaveFileName(this);
    QFile f(filename);

    if(f.open(QIODevice::WriteOnly))
    {
        WidgetDocument *w = (WidgetDocument*) ui->tabWidget->currentWidget();
        w->setFilename(filename);
        w->saveFile();

        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), filename);
    }
}

void EditeurHTML::copySelection()
{
    if(ui->tabWidget->currentWidget() == 0)
    {
        QMessageBox::warning(this, "Editeur HTML", "Impossible de copier, aucun document ouvert");
        return;
    }

    ((WidgetDocument*) ui->tabWidget->currentWidget())->copy();
}

void EditeurHTML::pasteSelection()
{
    if(ui->tabWidget->currentWidget() == 0)
    {
        QMessageBox::warning(this, "Editeur HTML", "Impossible de coller, aucun document ouvert");
        return;
    }

    ((WidgetDocument*) ui->tabWidget->currentWidget())->paste();
}


void EditeurHTML::cutSelection()
{
    if(ui->tabWidget->currentWidget() == 0)
    {
        QMessageBox::warning(this, "Editeur HTML", "Impossible de couper, aucun document ouvert");
        return;
    }

    ((WidgetDocument*) ui->tabWidget->currentWidget())->cut();
}

void EditeurHTML::closeCurrentTab()
{
    return closeTab(ui->tabWidget->currentIndex());
}

void EditeurHTML::closeTab(int index)
{
    WidgetDocument *w = (WidgetDocument*) ui->tabWidget->widget(index);;

    if(w->isModified())
    {
        QMessageBox mb;
        mb.setInformativeText("Le document a été modifié.");
        mb.setText("Sauvegarder le fichier avant de quitter ?");

        QPushButton *yes = mb.addButton(tr("Oui"), QMessageBox::YesRole);
        mb.addButton(tr("Non"), QMessageBox::NoRole);
        QPushButton *ann = mb.addButton(tr("Annuler"), QMessageBox::RejectRole);

        mb.exec();

        if((QPushButton*)mb.clickedButton() == ann)
        {
          return;
        }

        if((QPushButton*)mb.clickedButton() == yes)
        {
            if(w->filenameExist())
                w->saveFile();
            else
                saveFileAs();
        }
    }

    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());

    checkAvailableData();
}

void EditeurHTML::checkAvailableData()
{
    // Action coller active qui si il y a un document ouvert
    if(ui->tabWidget->count() <= 0)
    {
        pasteSelectionAction->setDisabled(true);
        copySelectionAction->setDisabled(true);
        cutSelectionAction->setDisabled(true);
        saveAsFileAction->setDisabled(true);
        saveFileAction->setDisabled(true);
    } else
    {
        pasteSelectionAction->setDisabled(false);
        copySelectionAction->setDisabled(false);
        cutSelectionAction->setDisabled(false);
        saveAsFileAction->setDisabled(false);
    }
}

void EditeurHTML::checkAvailableSave(int widgetIndex)
{
    if(ui->tabWidget->count() == 0)
        return;

    WidgetDocument* w = (WidgetDocument*) ui->tabWidget->widget(widgetIndex);

    if(w->isModified())
    {
        saveFileAction->setDisabled(false);
    } else
    {
        saveFileAction->setDisabled(true);
    }
}

EditeurHTML::~EditeurHTML()
{
    delete ui;
}
