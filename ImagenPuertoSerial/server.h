#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>

#include <QDebug>


class Server: public QObject
{
    Q_OBJECT
public:
    Server(QObject * parent = nullptr);
    ~Server();

    int puerto();
    QString HostIp();

    bool isServer();
    bool isConectado();

signals:
    void eConectado(QString msg);
    void eRecibido(QByteArray buff);
    void eError(QString msg);
public slots:
    void escribir(QString txt);
    void cerrarTodo();
    void escuchar(int puerto);
    bool conectarToHost(QString ip_host, int puerto);
private slots:
    void conectado();
    void aceptarConexion();
    void leer();
    void intentarConectar();
    void onError(QAbstractSocket::SocketError);
private:
    QTcpServer m_server;
    QTcpSocket* m_sk;
    QString m_HostIp;
    int m_puerto;


    bool m_conectado;
};
#endif // SERVER_H
