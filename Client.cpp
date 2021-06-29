/**
 * @file Client.cpp
 * @authors Diabloget, Jjvv21
 */

#include "Client.h"

/**
 * @class Client
 * @brief Servidor
 * @details Servidor que maneja los Json entrantes y salientes a traves de sockets.
 */


/**
 * @brief Constructor del Client
 * @details Constructor que permite hacer uso de los metodos para enviar y recibir del servidor.
 */
Client::Client() {

}

/**
 * @brief Metodo para enviar.
 * @details Prepara el servidor para enviar un mensaje en formato Json.
 */
std::string Client::createSender(std::string direction) {
    char sctr[direction.length() + 1];
    strcpy(sctr, direction.c_str());

    printf("%s\n","Sender" );
    if ((sender = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(sender, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    addressSender.sin_family = AF_INET;
    addressSender.sin_addr.s_addr = INADDR_ANY;
    addressSender.sin_port = htons(8080);
    if (connect(sender, (struct sockaddr *)&addressSender, sizeof(addressSender)) < 0)
    {
        printf("\nConnection Failed \n");
        exit(EXIT_FAILURE);
    }
    //char *ok1 = "ok1";

    send(sender , sctr , strlen(sctr) , 0 );
    close(sender);
    return createReader();

}

/**
 * @brief Metodo que inicia el servidor.
 * @details Metodo que al recibir el mensaje init, prepara el servidor para la escucha.
 */
void Client::initSender(std::string path){
    char sctr[path.length() + 1];
    strcpy(sctr, path.c_str());

    printf("%s\n","Sender" );
    if ((sender = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(sender, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    addressSender.sin_family = AF_INET;
    addressSender.sin_addr.s_addr = INADDR_ANY;
    addressSender.sin_port = htons(8080);
    if (connect(sender, (struct sockaddr *)&addressSender, sizeof(addressSender)) < 0)
    {
        printf("\nConnection Failed \n");
        exit(EXIT_FAILURE);
    }
    //char *ok1 = "ok1";

    send(sender , sctr , strlen(sctr) , 0 );
    close(sender);
}

/**
 * @brief Escucha de instrucciones.
 * @details Metodo que prepara al servidor para recibir instrucciones en formato Json.
 */
std::string Client::createReader() {
    if ((reader = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(reader, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    addressReader.sin_family = AF_INET;
    addressReader.sin_addr.s_addr = INADDR_ANY;
    addressReader.sin_port = htons(8080);
    if (bind(reader, (struct sockaddr *)&addressReader, sizeof(addressReader))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(reader, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("%s\n","Waiting" );
    bool end = false;
    int clientConection;
    bzero(buffer,1024);
    do{
        if ((clientConection = accept(reader, (struct sockaddr *)&addressReader,(socklen_t*)&addrlen))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        int readLen = read(clientConection , buffer, 1024);
        if (readLen > 0){
            printf("%s\n",buffer);
            std::string msg(buffer);
            //JsonManager jmanager = JsonManager();
            //direction = mem->addValue(jmanager.JsonDecomposer(msg));

            end = true;
        }
        close(clientConection);
    } while(!end);
    close(reader);
    return buffer;
    //createSender();
}