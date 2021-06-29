#include "Window.h"

/**
 * @file Window.cpp
 * @authors Diabloget, Jjvv21
 */

/**
 * @class Window
 * @brief Permite instanciar la ventana.
 * @details Contiene todas las caracteristicas de la ventana del IDE para la ejecucion y escritura de codigo C!.
 */

/**
 * @brief Constructor de la ventana.
 * @param parent
 * @details Constructor de la interfaz grafica usando biblioteca QT.
 */
Window::Window(QWidget *parent) :
        QWidget(parent) {
    setFixedSize(1100, 650);
    this->setWindowTitle("Genetic Puzzle");
    QGridLayout *layout = new QGridLayout(this);
    this->setLayout(layout);

    //server
    this->client = Client();
    this->init = false;

    /***
     * @Widget
     * Estos son los botones que se utilizaran en el IDE
     */
    //BOTON PARA EJECUTAR EL CODIGO
    SelectButton = new QPushButton("○", this);
    SelectButton->setFixedSize(30, 30);
    connect(SelectButton, SIGNAL(clicked()), this, SLOT(OpenImage()));
    //BOTON PARA DETENER EL FLUJO DEL PROGRAMA
    NextButton = new QPushButton("▶", this);
    NextButton->setFixedSize(32, 32);
    connect(NextButton, SIGNAL(clicked()), this, SLOT(Next()));
    //BOTON PARA SALTAR LINEA
    BackButton = new QPushButton("◀", this);
    BackButton->setFixedSize(30, 30);
    connect(BackButton, SIGNAL(clicked()), this, SLOT(Back()));
    //BOTON PARA ASIGNAR DIVISION
    DivButton = new QPushButton("Asignar divisor", this);
    DivButton->setFixedSize(110, 30);
    connect(DivButton, SIGNAL(clicked()), this, SLOT(SetDiv()));
    Next25Button = new QPushButton("⥤", this);
    Next25Button->setFixedSize(32, 32);
    connect(Next25Button, SIGNAL(clicked()), this, SLOT(Next25()));
    //BOTON PARA SALTAR LINEA
    Back25Button = new QPushButton("⥢", this);
    Back25Button->setFixedSize(30, 30);
    connect(Back25Button, SIGNAL(clicked()), this, SLOT(Back25()));
    //BOTON PARA ASIGNAR DIVISION
    /***
     * @Layout
     * LayOut para los botones
     */
    layout->addWidget(BackButton, 0, 2);
    layout->addWidget(SelectButton, 0, 0);
    layout->addWidget(NextButton, 0, 3);
    layout->addWidget(Back25Button, 0, 1);
    layout->addWidget(Next25Button, 0, 4);

    this->H = new QLabel();
    this->H->setFixedSize(100,100);
    this->H->setScaledContents( true );
    this->H->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    layout->addWidget(this->H,1,0);


    /***
     * @Widget
     * Este es un grupo en el que se crea dentro una contenedora para el TextEdit
     */

    Code = new QTextEdit();
    Code->setFont(
            QFont ("Ubuntu Mono", 12)
    );
    Code->setFixedSize(60, 30);
    layout->addWidget(Code);
    layout->addWidget(DivButton);



    QTabWidget *TabWindow = new QTabWidget();
    Log1 = new QTextEdit(this);
    Log1->setFixedHeight(100);
    Log2 = new QTextEdit(this);
    Log2->setFixedHeight(100);
    TabWindow->addTab(Log1, tr("Stdout"));
    TabWindow->addTab(Log2, tr("Application Log"));
}

/**
 * @brief Inicia la escritura.
 * @details Instancia a Lexer, para escribir lo escrito en el IDE dentro de un archivo de texto y tokenizarlo.
 */
void Window::OpenImage(){
    QUrl path = QFileDialog::getOpenFileUrl(this,
                                            tr("Select Image"),
                                            tr(""),
                                            tr("Image (*.pgm);;All Files (*)"));
    QString qpath = path.path();
    std::string realpath = qpath.toStdString();

    QPixmap px(qpath);
    this->H->setPixmap(px);
    //std::cout << realpath;
    std::cout << realpath << " es el path\n";

    client.initSender(realpath);
    this->init = true;
}
void Window::Next() {
    this->imagePath = client.createSender("1");
    QPixmap px(QString::fromStdString(this->imagePath));
    this->H->setPixmap(px);
    this->H->show();

}

void Window::Next25() {
    this->imagePath = client.createSender("2");
    QPixmap px(QString::fromStdString(this->imagePath));
    this->H->setPixmap(px);
    this->H->show();
}

void Window::Back() {
    this->imagePath = client.createSender("0");
    QPixmap px(QString::fromStdString(this->imagePath));
    this->H->setPixmap(px);
    this->H->show();
}

void Window::Back25() {
    this->imagePath = client.createSender("3");
    QPixmap px(QString::fromStdString(this->imagePath));
    this->H->setPixmap(px);
    this->H->show();
}

void Window::SetDiv() {
    if(init){
        try {
            int div = Code->toPlainText().toInt();
            client.initSender(Code->toPlainText().toStdString());
        } catch (std::invalid_argument) {
            std::cout << "No se inserto divisor valido\n";
        }
    }
}
/**
 * @details Agrega al vector cada instruccion por la que avanza dentro del texto.
 * @brief Avanza una linea en el texto.
 */



