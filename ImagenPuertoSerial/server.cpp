
#include "server.h"

Server::Server(QObject* parent): QObject(parent)
{
    m_sk = nullptr;

    m_conectado = false;

    connect(&m_server, SIGNAL(newConnection()),
            this, SLOT(aceptarConexion()));
}

Server::~Server()
{
    cerrarTodo();
}

int Server::puerto()
{
    return m_puerto;
}

QString Server::HostIp()
{
    return m_HostIp;
}

bool Server::isServer()
{
    return m_HostIp.isEmpty();
}

bool Server::isConectado()
{
    return m_conectado;
}

void Server::aceptarConexion()
{
    m_sk = m_server.nextPendingConnection();

    m_conectado = true;

    qDebug() << "Cliente aceptado!: " << m_sk->peerAddress().toString();

    connect(m_sk, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    connect(m_sk, SIGNAL(readyRead()), this, SLOT(leer()));

    emit eConectado("Cliente aceptado!: " + m_sk->peerAddress().toString());
}

void Server::leer()
{
    emit eRecibido(m_sk->readAll());
}


void Server::escribir(QString txt)
{
    if(m_sk != nullptr){
        if(m_sk->isOpen()){
            m_sk->write(txt.toLocal8Bit());
        }
    }
}

void Server::cerrarTodo()
{
    m_conectado = false;

    if(m_sk != nullptr){
        if(m_sk->isOpen()){
            m_sk->close();
        }
    }

    if(m_server.isListening()){
        m_server.close();
    }
}

void Server::escuchar(int puerto)
{
    qDebug() << "Socket SERVER, escuchando en: " << puerto;
    if(m_server.isListening()){
        m_server.close();
    }
    m_HostIp = "";
    m_puerto = puerto;

    m_server.listen(QHostAddress::Any, static_cast<quint16>(m_puerto));
}

bool Server::conectarToHost(QString ip_host, int puerto)
{
    if(m_sk == nullptr){
        m_sk = new QTcpSocket();
        connect(m_sk, SIGNAL(connected()), this, SLOT(conectado()));
        connect(m_sk, SIGNAL(readyRead()), this, SLOT(leer()));
        connect(m_sk, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    }

    m_HostIp = ip_host.trimmed();
    m_puerto = puerto;

    m_sk->connectToHost(m_HostIp, static_cast<quint16>(m_puerto));

    return m_sk->isOpen();
}

void Server::conectado()
{
    m_conectado = true;
    emit eConectado("CONECTADO al servidor: " + m_HostIp);
}

void Server::intentarConectar()
{
    conectarToHost(m_HostIp, m_puerto);
}

void Server::onError(QAbstractSocket::SocketError)
{
    qDebug() << "Socket Error: " << m_sk->errorString();
    m_sk->abort();
    m_sk->close();

    emit eError(m_sk->errorString());

    if(!isServer()){
        m_conectado = false;
    }
}
