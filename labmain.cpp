#include "labmain.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

// Estructura opcional
struct ColorConsole
{
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

// Estructura de ConsoleBox (suponiendo que esta ya existe)
struct ConsoleBox
{
    void new_text() {/*...*/}
    void set_text(const string &text) { cout << text << endl; }
};

// Suponemos que ya está inicializado
ConsoleBox *consoleBox = new ConsoleBox;

void load_script(const char* filename, bool show_script)
{
    string script;
    FILE* f = nullptr;
    try
    {
        // Intentar abrir el archivo
        f = fopen(filename, "rb");
        if (!f)
        {
            cerr << "Error: No se pudo abrir el archivo " << filename << endl;
            return;
        }

        // Leer el contenido del archivo
        char buf[4001];
        size_t bytesRead;
        while ((bytesRead = fread(buf, 1, 4000, f)) > 0)
        {
            buf[bytesRead] = 0;  // Terminar la cadena
            script.append(buf);
        }

        // Cerrar el archivo
        fclose(f);
        f = nullptr;

        // Mostrar el script si show_script es verdadero
        if (show_script)
        {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            cout << script << endl;
        }

        consoleBox->new_text();
        consoleBox->set_text(script);
    }
    catch (...)
    {
        // Manejo de errores
        cerr << "Error durante la lectura del archivo" << endl;
        if(f)
            fclose(f);
    }
}

void load_script()
{
    char filename[500];

    // Solicitar al usuario que ingrese el nombre del archivo que desee buscar
    printf("Archivo: ");

    // Leer nombre de archivo con límite de caracteres
    if (scanf("%499s", filename) != 1)
    {
        cerr << "Error al leer el nombre del archivo" << endl;
        return;
    }

    // Llamamos a la función con el nombre del archivo
    load_script(filename, true);
}
