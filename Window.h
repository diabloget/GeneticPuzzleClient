#ifndef WINDOW_H
#define WINDOW_H

#include <QKeyEvent>
#include <QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtCore/QCoreApplication>
#include <QtGui/QTextBlock>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QListView>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPixmap>
#include <QGroupBox>
#include <QTableWidget>
#include <QFileDialog>
#include <iostream>
#include "vector"
#include "Client.h"

using namespace std;
/**
 * @brief The Window class : Clase que corresponde a la ventana principal
 */
class Window : public QWidget {
Q_OBJECT
public:

    explicit Window(QWidget *parent = 0);

    //QString getEditorReading();

    //void RefreshRAMBox();

    Client client;

    bool init;

    std::string imagePath;

private slots:

    void OpenImage();

    void Next();
    void Next25();
    void Back();
    void Back25();

    void SetDiv();


private:
    QPushButton *DivButton;

    QPushButton *BackButton;

    QPushButton *SelectButton;

    QPushButton *NextButton;

    QPushButton *Back25Button;

    QPushButton *Next25Button;

    QLabel *H;

    QTableWidget *Table;

    QTextEdit *Log1;

    QTextEdit *Log2;

    QTableWidgetItem *Header1, *Header2, *Header3, *Header4;

    QTextEdit *Code;

};

#endif // WINDOW_H