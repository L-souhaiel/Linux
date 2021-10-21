#ifndef PRINCIPALWINDOW_H
#define PRINCIPALWINDOW_H
#include<QtWidgets>


class PrincipalWindow : public QMainWindow
{

    Q_OBJECT

public:
         PrincipalWindow();
         void setwidgets(QWidget *window) ;

public slots:
         void adress();


private :
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
     QHBoxLayout *layout = new QHBoxLayout;
};

#endif // PRINCIPALWINDOW_H
