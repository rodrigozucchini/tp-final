#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estructura
struct Contacto {
    int id;
    char nombre[50];
    char apellido[50];
    char telefono[20];
};

// Prototipos de las funciones
void agregarContacto(FILE *archivo);
void mostrarContactos(FILE *archivo);
void convertirMayusculas(char *cadena);

int main() {
    FILE *archivo;
    int opcion;

    // ABRO ARCHIVO
    archivo = fopen("contactos.bin", "ab+");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    do {
        // Opciones
        printf("\nMenu: !\n");
        printf("1. Agregar contacto\n");
        printf("2. Mostrar contactos\n");
        printf("3. Salir\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                agregarContacto(archivo);
                break;
            case 2:
                mostrarContactos(archivo);
                break;
            case 3:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion no valida. Pruebe.\n");
        }
    } while (opcion != 3);

    // Cierro
    fclose(archivo);

    return 0;
}

// Agrego pero a binario
void agregarContacto(FILE *archivo) {
    struct Contacto contacto;

    fseek(archivo, 0, SEEK_END);
    contacto.id = ftell(archivo) / sizeof(struct Contacto);

    printf("Ingrese nombre: ");
    scanf("%s", contacto.nombre);
    convertirMayusculas(contacto.nombre);
    printf("Ingrese apellido: ");
    scanf("%s", contacto.apellido);
    convertirMayusculas(contacto.apellido);
    printf("Ingrese telefono: ");
    scanf("%s", contacto.telefono);

    // Escribir en binario
    fwrite(&contacto, sizeof(struct Contacto), 1, archivo);
    printf("Contacto agregado con éxito. ID asignado: %d\n", contacto.id);
}

// muestro datos en binario
void mostrarContactos(FILE *archivo) {
    struct Contacto contacto;
    rewind(archivo);
    printf("Lista de contactos:\n");
    while (fread(&contacto, sizeof(struct Contacto), 1, archivo) == 1) {
        printf("ID: %d\t Nombre: %s\t Apellido: %s\t Telefono: %s\n", contacto.id, contacto.nombre, contacto.apellido, contacto.telefono);
    }
}

// A MAYUSCULA
void convertirMayusculas(char *cadena) {
    for (int i = 0; cadena[i] != '\0'; i++) {
        cadena[i] = toupper(cadena[i]);
    }
}