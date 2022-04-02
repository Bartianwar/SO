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
                        //printf("%s\n", entry->d_name);                                  //(Si un archivo tiene "\" en el nombre, cagamos. Pero son nombres de mascota asique....)                   
                        int fd = open(entry->d_name, O_RDONLY | O_EXCL);
                        char *tipo_animal = (char *)calloc(1, sizeof(char));
                        char *buffer_nom = (char *)malloc(sizeof(char)*255);
                        while(tipo_animal != "\n"){
                            read(fd, tipo_animal, 1);

                            printf("%d",i);
                        }
                        printf("%s \n", tipo_animal);
                        free(tipo_animal);
                        close(fd);
                        
                    }
                }    
            }
        }
    }
    closedir(dir);
    
    return 0;
}