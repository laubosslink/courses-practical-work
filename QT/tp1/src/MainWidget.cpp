/**
 * @file   MainWidget.cpp
 * @author Sebastien Fourey
 *
 * @brief  MainWidget methods definitions.
 */
#include "MainWidget.h"
#include <QMouseEvent>
#include <QString>
#include <QMessageBox>

#include <QTimeEdit>
#include <QTimer>

using namespace std;

MainWidget::MainWidget()
{
  // b) Titre de la fenetre
  setWindowTitle(QString("b) Titre de la fenetre"));

  // d) agrandissement 40 pixels (non demande, mais plus propre)
  setGeometry(100,100,300,300+40);

  QLabel *label = new QLabel("Colors, signals, and slots",this);
  label->setGeometry(10,10,290,30);
  label->setFont(QFont("Arial",14,QFont::Bold));

  // d) ajout nouveau champ
  lineDisplay2 = new QLineEdit("",this);

  lineDisplay2->setReadOnly(true);

  lineDisplay2->setGeometry(50,70,200,30);
  lineDisplay2->setAlignment(Qt::AlignHCenter);

  lineDisplay = new QLineEdit("",this);

  // c) read-only
  lineDisplay->setReadOnly(true);

  // d) deplacement 40 pixels
  lineDisplay->setGeometry(50,70+40,200,30);
  lineDisplay->setAlignment(Qt::AlignHCenter);

  qt = new QTimeEdit(QTime::currentTime(), this);
  qt->setGeometry(100,160,80,30);

  ColorWidget *colorWidget = new ColorWidget(this);
  // d) deplacement 40 pixels
  colorWidget->setGeometry(100,160 + 40,80,30);

  QPushButton *pushButtonRandomColor = new QPushButton("Random color",this);
  // d) deplacement 40 pixels
  pushButtonRandomColor->setGeometry(60,200 + 40,160,30);

  QPushButton *pushButtonQuit = new QPushButton("Quit",this);
  // d) deplacement 40 pixels (non demande, mais plus propre)
  pushButtonQuit->setGeometry(100,250+40,80,30);

  // bonus
  timer = new QTimer();
  timer->start(1000);

  // bonus
  connect(timer, SIGNAL(timeout()), 
         this,SLOT(updateTime()));

  connect(pushButtonQuit,SIGNAL(clicked()),
          this,SLOT(quitPressed()));

  connect(pushButtonRandomColor,SIGNAL(clicked()),
          colorWidget,SLOT(changeColor()));

  connect(colorWidget,SIGNAL(colorChanged(int,int,int)),
          this,SLOT(colorChanged(int,int,int)));

}

// bonus
void MainWidget::updateTime()
{
  qt->setTime(QTime::currentTime());
}

void MainWidget::quitPressed()
{
  QMessageBox::StandardButton button;
  button = QMessageBox::question(this,
                                 "You want to quit...",
                                 "Are you sure that you want to quit"
                                 " this great application?",
                                 QMessageBox::Yes|QMessageBox::No,
                                 QMessageBox::No );
  if ( button == QMessageBox::Yes ) {
    close();
  }
}


void MainWidget::colorChanged(int r, int g, int b)
{
  QString text("Color: R(%1) G(%2) B(%3)");
  lineDisplay->setText(text.arg(r).arg(g).arg(b));
}


// e) ecoute de la souris (x,y)
void MainWidget::mouseMoveEvent(QMouseEvent * e)
{
  QString text("(%1,%2)");
  lineDisplay2->setText(text.arg(e->x()).arg(e->y()));

  if(e->buttons() == Qt::LeftButton)
    lineDisplay2->setAlignment(Qt::AlignLeft);
  else if(e->buttons() == Qt::RightButton)
    lineDisplay2->setAlignment(Qt::AlignRight);
  else if(e->buttons() == Qt::MiddleButton)
    lineDisplay2->setAlignment(Qt::AlignHCenter);
}
