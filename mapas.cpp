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
  arq = fopen("salvarArq2.txt", "w+");

  int tamGravado;



   map<int, string> Employees;
   //ap< uint64_t, keys_t > keys;


   keys_t keys;
   keys.pub_size = 7;
   keys.public_key = (uint8_t *) malloc (7);
   char privKey[7] = {0x11, 0x6e, 0x10, 0x3c, 0x10, 0x3c, 0x18};
   memcpy(keys.public_key, privKey, 7);

   keys_t keys1;
   keys1.pub_size = 4;
   keys1.public_key = (uint8_t *) malloc (keys.pub_size);
   char nvPubKey[4] = {0x33, 0x6e, 0x10, 0x89};
   memcpy(keys1.public_key, nvPubKey, 4);

    map< uint64_t, keys_t > keysMap;

    size_t data_size;

    data_size = sizeof(size_t) + sizeof(size_t) + keys.pub_size + sizeof(size_t) + keys1.pub_size;
    printf("The size of integer is %zu\n", data_size);
    uint8_t * dataTobeSaved = (uint8_t *) calloc(data_size, 1);

    memcpy( dataTobeSaved, &data_size, sizeof( size_t ) );
    dataTobeSaved += sizeof(size_t);
    
    memcpy(dataTobeSaved, &keys.pub_size, sizeof(size_t));
    dataTobeSaved += sizeof(size_t);
    memcpy(dataTobeSaved, keys.public_key, keys.pub_size);
    dataTobeSaved += keys.pub_size;
    

    //Criar uma estrutura agora
    keysMap.insert( pair< int, keys_t > ( 22, keys ) );
    keysMap.insert( pair< int, keys_t > ( 25, keys1 ) );

    print_byte_array_ocall(keysMap[25].public_key, 5);

    //Fazendo um for no meu mapa
    cout << "tentar imprimir usando um for" << endl;
    for( map<uint64_t, keys_t>::iterator ii=keysMap.begin(); ii!=keysMap.end(); ++ii){
      print_byte_array_ocall(ii->second.public_key, 3);   

    }

    tamGravado = fwrite(&keys.pub_size, sizeof(keys.pub_size), 1, arq);
    tamGravado = fwrite(keys.public_key, 1, keys.pub_size, arq);
    cout << "Tamanho Gravado "<< tamGravado << endl;
   


   print_byte_array_ocall(keys1.public_key, 4);

   

   // 1) Assignment using array index notation
   Employees[1] = "Mike C.";
   Employees[2] = "Charlie M.";
   Employees[3] = "David D.";
   Employees[4] = "John A.";
   Employees[5] = "Peter Q.";

   cout << "Employees[3374]=" << Employees[1] << endl << endl;

   cout << "Map size: " << Employees.size() << endl;

   cout << endl << "Natural Order:" << endl;
   for( map<int,string>::iterator ii=Employees.begin(); ii!=Employees.end(); ++ii)
   {
       cout << (*ii).first << ": " << (*ii).second << endl;
       cout << ii->second << endl;
   }

   /*

   cout << endl << "Reverse Order:" << endl;
   for( map<int,string>::reverse_iterator ii=Employees.rbegin(); ii!=Employees.rend(); ++ii)
   {
       cout << (*ii).first << ": " << (*ii).second << endl;
   }

   */
}
