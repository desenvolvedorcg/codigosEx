#include <string.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include <utility>

#include <stdint.h>
#include <stdlib.h>

using namespace std;


typedef struct keys_t {
    uint8_t *public_key;
    size_t pub_size;
} keys_t;


void print_byte_array_ocall( void *mem, int len )
{
  
    int i, count=0;
    uint8_t *array = ( uint8_t * ) mem;
    for ( i=0; i<len; i++ )
    {
        if ( count == 0 ) printf( "\n" );
        count = ( count + 1 ) % 8;
        printf( "0x%x", array[i] );
        if ( i+1 < len ) printf( ", " );
    }
    printf( "\n" );

}


int main()
{

  //Escrita em arquivo
  FILE *arq;
  arq = fopen("salvarArq2.txt", "r+");


   //Tentar recuperar aqui
    keys_t keyLida;
    keyLida.public_key = (uint8_t *) malloc(7);
    

    int tamanhoLido = 0;
    tamanhoLido = fread(&keyLida.pub_size, sizeof(size_t), 1, arq);
    tamanhoLido = fread(keyLida.public_key, 1, 7, arq);
    cout << "Será que leu memso "<< keyLida.pub_size << endl;
    print_byte_array_ocall(keyLida.public_key, 7);

   //Fim de tentar recuperar


}
