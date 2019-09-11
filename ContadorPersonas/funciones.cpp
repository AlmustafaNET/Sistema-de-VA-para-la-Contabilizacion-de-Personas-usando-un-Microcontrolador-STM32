#include "funciones.h"

void mat2raw(Mat src, uint8_t * dest)
{
    int total = src.cols * src.rows;
    uint8_t * ptr = src.data;
    for (int i=0; i < total; i++) {
        dest[i] = *ptr++;
    }
}

Mat raw2mat(uint8_t *img)
{
    Mat res(ALTO, ANCHO, CV_8UC1, img);
    return res;
}


void diferencia(uint8_t* img1, uint8_t* img2, uint8_t umbral){
    uint8_t valor = 0;
    for (int i=0;i < TOTAL; i++) {
        valor = (uint8_t)abs(img1[i] - img2[i]);
        img2[i] = valor >= umbral ? valor : 0;
    }
}

void copy(uint8_t *src, uint8_t *dest)
{
    for (int i=0;i < TOTAL; i++) {
        dest[i] = src[i];
    }
}

int conteo(uint8_t *img)
{
    int res = 0;
    for (int i=0;i < TOTAL; i++) {
        res += ((int)img[i]) > 0 ? 1 : 0;
    }
    return res;
}

void binarizar(uint8_t *img, uint8_t umbral)
{
    for (int i=0;i < TOTAL; i++) {
        img[i] = ((int)img[i]) > umbral ? 255 : 0;
    }
}

void dilatacion(uint8_t *img)
{
    //Imagen temporal
    uint8_t* temp = (uint8_t*)malloc(TOTAL);

    copy(img, temp);

    // Evito el borde
    int x = 0;
    int y = 0;
    for (int j=1;j < (ALTO - 1); j++) {
        for (int i=1;i < (ANCHO - 1); i++) {
            //cout << (int)img[(j*W)+i] << ",";
            if((int)temp[(j*ANCHO)+i] > 127){
                x = i - 1; y = j - 1; img[(y*ANCHO)+x] = 255;
                x = i + 0; y = j - 1; img[(y*ANCHO)+x] = 255;
                x = i + 1; y = j - 1; img[(y*ANCHO)+x] = 255;

                x = i - 1; y = j; img[(y*ANCHO)+x] = 255;
                x = i + 0; y = j; img[(y*ANCHO)+x] = 255;
                x = i + 1; y = j; img[(y*ANCHO)+x] = 255;

                x = i - 1; y = j + 1; img[(y*ANCHO)+x] = 255;
                x = i + 0; y = j + 1; img[(y*ANCHO)+x] = 255;
                x = i + 1; y = j + 1; img[(y*ANCHO)+x] = 255;
            }
        }
    }

    //Libero recursos
    free(temp);
}

void erosion(uint8_t *img)
{
    //Imagen temporal
    uint8_t* temp = (uint8_t*)malloc(TOTAL);

    copy(img, temp);

    // Evito el borde
    int x = 0;
    int y = 0;
    for (int j=1;j < (ALTO - 1); j++) {
        for (int i=1;i < (ANCHO - 1); i++) {
            if((int)temp[(j*ANCHO)+i] < 127){
                x = i - 1; y = j - 1; img[(y*ANCHO) + x] = 0;
                x = i + 0; y = j - 1; img[(y*ANCHO) + x] = 0;
                x = i + 1; y = j - 1; img[(y*ANCHO) + x] = 0;

                x = i - 1; y = j; img[(y*ANCHO) + x] = 0;
                x = i + 1; y = j; img[(y*ANCHO) + x] = 0;

                x = i - 1; y = j + 1; img[(y*ANCHO) + x] = 0;
                x = i + 0; y = j + 1; img[(y*ANCHO) + x] = 0;
                x = i + 1; y = j + 1; img[(y*ANCHO) + x] = 0;
            }
        }
    }

    //Libero recursos
    free(temp);
}

void apertura(uint8_t *img)
{
    erosion(img);
    dilatacion(img);
}

void cierre(uint8_t *img)
{
    dilatacion(img);
    erosion(img);
}


void vecinos(uint8_t *img, uint8_t valor, int x, int y, int* area){
    img[(y*ANCHO)+x] = valor;

    for (int j=(y-1);j<=(y+1);j++) {
        for (int i=(x-1);i<=(x+1);i++) {
            if(j < 0 || i < 0 || y >= ALTO || x >= ANCHO) continue;

            // Encontrado Blanco y aun no esta usado
            if((int)img[(j*ANCHO)+i] == 255){
                (*area)++;
                vecinos(img, valor,i, j, area);
            }
        }
    }
}

void bound_rectangulo(uint8_t *img, uint8_t valor, uint16_t* rect){
    // x1,y1,x2,y2
    rect[0] = (uint16_t)ANCHO;
    rect[1] = (uint16_t)ALTO;
    rect[2] = 0;
    rect[3] = 0;

    for (int j=0;j < ALTO; j++) {
        for (int i=0;i < ANCHO; i++) {
            // Encontrado Valor
            if((int)img[(j*ANCHO)+i] == valor){
                if(i < rect[0]) rect[0] = (uint16_t)i;
                if(j < rect[1]) rect[1] = (uint16_t)j;
                if(i > rect[2]) rect[2] = (uint16_t)i;
                if(j > rect[3]) rect[3] = (uint16_t)j;
            }
        }
    }
}

void filtrar_x_area(uint8_t *img, int min_area, uint16_t* rectangulos)
{
    //Imagen temporal
    int area = 0;
    // Valor por cada region
    uint8_t valor = 1;
    int ind_rect = 0;
    rectangulos[0] = 0;

    // Evito el borde
    for (int j=1;j < (ALTO - 1); j++) {
        for (int i=1;i < (ANCHO - 1); i++) {
            // Encontrado Blanco
            if((int)img[(j*ANCHO)+i] == 255){
                area = 0;
                vecinos(img, valor, i, j, &area);
                if(area > min_area){
                    //Extraer rectangulo
                    bound_rectangulo(img,valor, &rectangulos[(5 * ind_rect) + 2]);
                    rectangulos[(5 * ind_rect) + 1] = (uint16_t)area;
                    ind_rect++;
                    rectangulos[0] = (uint16_t)ind_rect;
                }
                valor++;
                if(valor > 254) valor = 1;
            }
        }
    }

    // Regiones a 255
    for (int k=0;k < TOTAL;k++) {
        if((int)img[k] > 0){
            img[k] = 255;
        }
    }
}
