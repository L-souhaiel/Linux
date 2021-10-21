#include "principalwindow.h"
#include"loginwindow.h"


PrincipalWindow::PrincipalWindow()
{


 QMenu *menuFichier = menuBar()->addMenu("&File");
  QAction *actionQuitter = new QAction("&Adresse", this);
  actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
  menuFichier->addAction(actionQuitter);
  setWindowTitle(" S/J Animal Shop GmbH");
  setFixedSize(800,400);

  QPixmap image("/home/louati/Documents/layout/pet.png");
  QLabel *imageLabel = new QLabel();
  imageLabel->setPixmap(image);

  setFixedSize(1280,740);
  int x = ((screenGeometry.width() - this->width()) / 2);
  int y = ((screenGeometry.height() - this->height()) / 2);
  move(x, y);


 layout = new QHBoxLayout;

 layout->addWidget(imageLabel);
 QWidget *parents_widgets = new QWidget;
 parents_widgets->setLayout(layout);

 setCentralWidget(parents_widgets);


QObject::connect(actionQuitter ,SIGNAL(triggered()) , this , SLOT(adress()));



}






void PrincipalWindow::adress()

{


    QMessageBox::information(this,"our Adress " , " Daneckerstrasse 26 Berlin 10247 ");

}










void PrincipalWindow::setwidgets(QWidget *window)

{

  layout->addWidget(window);

}


