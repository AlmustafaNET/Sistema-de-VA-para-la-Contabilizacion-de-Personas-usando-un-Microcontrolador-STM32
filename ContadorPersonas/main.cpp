#include "global.h"

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "funciones.h"

using namespace cv;
using namespace std;

int main(int, char**)
{
    VideoCapture cap("../videos/personas002.mp4");

    // Definición de Parametros
    int linea1 = (int)((ANCHO / 2.0) * 1.2);
    int linea2 = (int)((ANCHO / 2.0) * 0.8);
    const int cteMovimiento = (int)(TOTAL * 0.01); // 1%
    const int cteTamBlob = (int)(TOTAL * 0.05); // 5%;
    //////



    //0 : ninguna , 0x01: lineaUP, 0x02: lineaDW
    uint8_t estado = 0;
    uint8_t estado_ant = 0;
    uint8_t estados[20];
    for(uint8_t i=0; i < 20; i++) estados[i]=0;
    uint8_t ind_estado = 0;
    uint8_t direccion = 0;
    int personas = 0;

    // Reserva de memoria para imagenes
    uint8_t* img = (uint8_t*)malloc(TOTAL);
    uint8_t* img2 = (uint8_t*)malloc(TOTAL);

    uint16_t* rectangulos = (uint16_t*) malloc(26); // cantidad + 5 rectangulos. Cada rectangulo con x1,y1,x2,y2,area


    String texto = "";
    uint8_t primero = 1;

    // Check if camera opened successfully
      if(!cap.isOpened()){
        cout << "Error opening video stream or file" << endl;
        return -1;
      }

      while(1){
        Mat frame;
        // Capture frame-by-frame
        cap >> frame;
        // If the frame is empty, break immediately
        if (frame.empty())
          break;

        Mat gray;
        cvtColor(frame,gray, COLOR_RGB2GRAY);
        mat2raw(gray, img);

        //imshow("Gris", gray);

        //Primera Imagen
        if(primero){
            primero = 0;
            copy(img, img2);
        }

        //////////////

        diferencia(img, img2, 10);

        Mat temp = raw2mat(img2);
        imshow("Diferencia", temp);


        int cont_blancos = conteo(img2);
        if(cont_blancos > cteMovimiento){
            texto = "CON MOVIMIENTO";
            binarizar(img2, 1);

            dilatacion(img2);
            dilatacion(img2);
            dilatacion(img2);
            dilatacion(img2);
            dilatacion(img2);

            // Si hay mucho movmiento ( > 50% de la imagen), descartar la imagen
            cont_blancos = conteo(img2);
            if(cont_blancos < (TOTAL/2)){
                //rellenar(img2, w,h);
                filtrar_x_area(img2, cteTamBlob, rectangulos);

                uint16_t c_rects = rectangulos[0];
                uint8_t ind_rect=0;

                //Rectangulos reconocidos
                // Tomar el rectangulo mayor
                int area_mayor = 0;

                for (int i=0; i < c_rects; i++) {
                    int area = rectangulos[((i * 5) + 1)];

                    //cout << "Area: " << area << endl;

                    if(area > area_mayor){
                        area_mayor = area;
                        ind_rect = (uint8_t)((i * 5) + 2);
                    }
                }

                estado = 0;
                direccion = 0;

                if(area_mayor > 0){
                    // Dibujar rectangulos contenedores de objetos
                    uint16_t x1,y1,x2,y2;
                    x1 = rectangulos[ind_rect];
                    y1 = rectangulos[ind_rect + 1];
                    x2 = rectangulos[ind_rect + 2];
                    y2 = rectangulos[ind_rect + 3];
                    rectangle(frame, cvPoint(x1, y1), cvPoint(x2,y2), cvScalar(0, 255, 255), 2);


                    if((x1 < linea1) && (x2 > linea1)){
                        estado |= (1 << 0);
                        //cout << "LINEA UP: " << (int)estado << " - " << (int)estado_ant << endl;
                    }

                    if((x1 < linea2) && (x2 > linea2)){
                        estado |= (1 << 1);
                        //cout << "LINEA DW: " << (int)estado << " - " << (int)estado_ant << endl;
                    }
                }

                if(estado != estado_ant){
                    estados[ind_estado] = estado;

                    cout << "Estado " << (int)estado << endl;

                    if(estado == 0 && ind_estado > 0){
                        cout << "Procesar: " << (int)estado << "|";
                        for(uint8_t i=0; i < 20; i++) cout << (int)estados[i];
                        cout << endl;

                        for(uint8_t i=1; i < 20; i++){
                            if(estados[i-1]==2 && estados[i]==0){
                                if(estados[0]==1 || estados[0]==3)
                                    direccion = 1;
                            }
                            else if(estados[i-1]==1 && estados[i]==0){
                                if(estados[0]==2 || estados[0]==3)
                                    direccion = 2;
                            }
                            else if(estados[i-1]==3 && estados[i]==0){
                                if(estados[0]==1)
                                    direccion = 1;
                                else if(estados[0]==2)
                                    direccion = 2;
                            }
                        }

                        if(direccion == 1){
                            cout << "ENTRANDO!" << endl;
                            personas++;
                        }
                        else if(direccion == 2){
                            cout << "SALIENDO!" << endl;
                            personas--;
                            if(personas < 0) personas = 0;
                        }


                        for(uint8_t i=0; i < 20; i++) estados[i]=0;
                        ind_estado = 0;
                    }
                    else{
                        ind_estado++;
                    }

                    estado_ant = estado;
                }
            }
        }
        else{
            texto = "---";
        }


        //////////////

        // Ver resultados
        Mat resultado = raw2mat(img2);
        imshow( "Resultado", resultado);

        line(frame, cvPoint(linea1,0), cvPoint(linea1, ALTO), cvScalar(255, 0, 0), 2);
        line(frame, cvPoint(linea2,0), cvPoint(linea2, ALTO), cvScalar(0, 0, 255), 2);

        //putText(frame, texto, cvPoint(15,15), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(255,200,200), 1, CV_AA);
        //putText(frame, format("%05d", personas), cvPoint(15,234), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(255,200,200), 1, CV_AA);
        imshow( "Frame", frame );

        // Copiar imagen actual a anterior
        copy(img, img2);

        // Press  ESC on keyboard to exit
        char c=(char)waitKey(25);

        // Cuadro a cuandro
        while(c!=32){ // Barra de espacio
             c=(char)waitKey(25);
        }
        //

        if(c==27 || c==113)
          break;
      }

      destroyAllWindows();

      // When everything done, release the video capture object

      // Libero memoria
      free(img);
      free(img2);
      free(rectangulos);


      // Closes all the frames
      //cap.release();

      cout << "FIN!!!" << endl;

    return 0;
}
