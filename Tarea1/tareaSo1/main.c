#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

int main(){
    DIR *dir;                                                   // Tipo de archivo dir
    struct dirent *entry;                                       // Estructura definida para utilizar opendir, readdir, etc que contiene el nombre y el tipo de archivo en una cola que se va limpiando al usar readdir
    

    if ((dir = opendir(".")) == NULL)                           //Checkea que se abrio correctamente el arhivo
        perror("opendir() error");
    else {    
        while((entry = readdir(dir)) != NULL){                  //Lopea por todos los archivos con nombre, fijandose si la extencion es .txt.
            if(entry->d_type == DT_REG){                        //Se fija si el archivo es de tipo normal (No un directorio, por ejemplo).
                const char *ext = strrchr(entry->d_name,'.');   // Define y guarda la extension del archivo que se este mirando.
                if((!ext) || (ext == entry->d_name))            // Si la extension no existe o la ext es el nombre del arhivo, entonces no nos sirve.(Podemos no usar strmp por que son punteros a algo)
                    continue;
                else{
                    if (strcmp(ext, ".txt") == 0 && !strstr(entry->d_name, "\\")){      //Terrible solucion, pero funciona. Se fija si la extension del archivo es de tipo txt
                        printf("%s\n", entry->d_name);                                  //(Si un archivo tiene "\" en el nombre, cagamos. Pero son nombres de mascota asique....)                   
                        /*
                        int fd = open(entry->d_name, O_RDONLY | O_EXCL);                //Hasta ahora, he accedido al loop, leido el nombre de cada uno de los archivos e imprimi el nombre de cada uno por pantalla 
                        char *tipo_animal = (char *)calloc(1, sizeof(char));            //En este loop se puede acceder tambien a la informacion dentro de cada uno de los archivos, por lo que no deberia se tan
                        char *buffer_nom = (char *)malloc(sizeof(char)*255);            //complejo accder a que tipo de animal son y el estado en el que se encuentran. Me imagino que la mejor forma de hacerlo
                        while(tipo_animal != "\n"){                                     //sera leer por byte hasta encontrar un cambio de linea o algo por el estilo.
                            read(fd, tipo_animal, 1);

                            printf("%d",i);                                             //Este comentario de codigo grande es un intento de solucion para leer la primera linea del archivo, el cual es el nombre de la mascota
                        }                                                               //Probablemente deberiamos intentar crear una funcion estilo "leerLinea(str nombreArchivo, int lineaQueSe);" para poder usarla de manera mas generia
                        printf("%s \n", tipo_animal);
                        free(tipo_animal);
                        close(fd);
                        */
                        
                    }
                }    
            }
        }
    }
    closedir(dir);
    
    return 0;
}
