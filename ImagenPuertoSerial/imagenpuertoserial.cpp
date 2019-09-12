#include "imagenpuertoserial.h"
#include "ui_imagenpuertoserial.h"

ImagenPuertoSerial::ImagenPuertoSerial(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImagenPuertoSerial)
{
    ui->setupUi(this);

    connect(&m_servidor, SIGNAL(eError(QString)), this, SLOT(onError(QString)));
    connect(&m_servidor, SIGNAL(eRecibido(QByteArray)), this, SLOT(onRecibido(QByteArray)));
    connect(&m_servidor, SIGNAL(eConectado(QString)), this, SLOT(onConectado(QString)));

}

ImagenPuertoSerial::~ImagenPuertoSerial()
{
    delete ui;
}

void ImagenPuertoSerial::dibujar(QByteArray buff)
{
    qDebug() << "Dibujar: " << buff.length() << m_cols << m_rows;

    int len = m_rows * m_cols;
    if(m_isColor==1){
        len = m_rows * m_cols * 2;
    }

    if(buff.length() != len) return;

    QImage img(m_rows, m_cols, QImage::Format_RGB888);


    char* ptr = buff.data();


    for (int j=0; j < m_rows; j++) {
       for (int i=0; i < m_cols; i++) {           
           // Imagen a COLOR
           if(m_isColor==1){
                uint8_t b2 = static_cast<uint8_t>(*ptr);
                ptr++;
                uint8_t b1 = static_cast<uint8_t>(*ptr);
                ptr++;

                uint16_t nHex = static_cast<uint16_t>((b1 << 8) + b2);

                uint8_t r,g,b;
                // Formato RGB555
                b = nHex & 0x1f;
                g = (nHex >> 5) & 0x1f;
                r = (nHex >> 10) & 0x1f;

                r = r * 255 / 0x1F;
                g = g * 255 / 0x1F;
                b = b * 255 / 0x1F;
                img.setPixel(j, i, qRgb(r,g,b));
           }
           // Imagen GRIS
           else{
               uint8_t b = static_cast<uint8_t>(*ptr);
               ptr++;
               b = b * 255 / 0x1F;
               img.setPixel(j, i, qRgb(b,b,b));
           }

        }
    }


    ui->lblPic->setPixmap(QPixmap::fromImage(img));
}

void ImagenPuertoSerial::onError(QString msg)
{
    ui->statusBar->showMessage("Error: " + msg, 5000);
    QMessageBox::critical(this, "Error", msg);
    ui->btnCapturar->setEnabled(true);
}

void ImagenPuertoSerial::onConectado(QString msg)
{
    ui->statusBar->showMessage(msg);
}

void ImagenPuertoSerial::onRecibido(QByteArray buff)
{
    //Cabecera    

    if(buff.length() > 10 && buff.length() < 100){
        QString s_buff = QString::fromLatin1(buff);
        qDebug() << "FRAME: " << s_buff;
        int ind0 = -1;
        int ind1 = -1;
        ind0 = s_buff.indexOf("<FRAME:");
        if(ind0 >= 0){
            ind1 = s_buff.indexOf(">", ind0);
            s_buff = s_buff.mid(ind0, (ind1 - ind0));
            QStringList args = s_buff.split(":");
            m_rows = args.at(1).toInt();
            m_cols = args.at(2).toInt();
            m_isColor = args.at(3).toInt();
            qDebug() << "Tamaño: " << m_rows << m_cols << m_isColor << m_buff.length();

            m_cols_data = m_cols;
            if(m_isColor==1){
                m_cols_data = m_cols * 2;
            }

            m_buff = m_buff.remove(0, ind1 + 1);
            //qDebug() << m_buff;
        }
        m_buff.clear();
        qDebug() << "Cabecera " << ind0 << ind1;
    }
    // FIN
    else if(buff.length() == 5){
        QString s_buff = QString::fromLocal8Bit(buff);
        qDebug() << "FIN: " << s_buff;

        ui->btnCapturar->setEnabled(true);

        dibujar(m_buff);
    }
    else if(buff.length() == m_cols_data){
        //qDebug() << "BUFF: " << buff.length() << m_buff.length() << buff.mid(100, 20);
        m_buff.append(buff);
    }
    else{
       qDebug() << "REC: " << buff.length() << QString::fromLocal8Bit(buff);
    }
}

void ImagenPuertoSerial::on_btnCapturar_clicked()
{
    ui->btnCapturar->setEnabled(false);

    bool res = m_servidor.isConectado();

    if(!res){
        res = m_servidor.conectarToHost("192.168.0.163", 7777);
    }

    if(res) m_servidor.escribir("<FRAME>");
    else{
        qDebug() << "NO SE PUDO CONECTAR!";
        m_servidor.cerrarTodo();
    }
}

void ImagenPuertoSerial::on_btnCerrar_clicked()
{
    m_servidor.escribir("<CLOSE>");
    m_servidor.cerrarTodo();
    this->close();
}
