#ifndef IMAGENPUERTOSERIAL_H
#define IMAGENPUERTOSERIAL_H

#include <QMainWindow>
#include <QDebug>
#include "server.h"
#include <QMessageBox>

namespace Ui {
class ImagenPuertoSerial;
}

class ImagenPuertoSerial : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImagenPuertoSerial(QWidget *parent = nullptr);
    ~ImagenPuertoSerial();

private:
    void dibujar(QByteArray buff);
private slots:
    void onError(QString msg);
    void onConectado(QString msg);
    void onRecibido(QByteArray buff);
    void on_btnCapturar_clicked();

    void on_btnCerrar_clicked();

private:
    Ui::ImagenPuertoSerial *ui;
    Server m_servidor;
    QByteArray m_buff;
    int m_rows;
    int m_cols;
    int m_cols_data;
    int m_isColor;
};

#endif // IMAGENPUERTOSERIAL_H
