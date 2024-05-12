// Trabajo grupal fase 1 y 2..... THAI
// Perseverando llegaremos a la cima...... Luis

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

// Estructura para almacenar una palabra
struct Palabra {
    string palabra;
    string traduccion;
    string significado;
};

// Función para crear una nueva palabra y almacenarla en el archivo
void crearPalabra() {
    Palabra nuevaPalabra;

    cout << "Ingrese la palabra: ";
    getline(cin, nuevaPalabra.palabra);

    cout << "Ingrese la traduccion: ";
    getline(cin, nuevaPalabra.traduccion);

    cout << "Ingrese la funcionalidad: ";
    getline(cin, nuevaPalabra.significado);

    // Abre el archivo en modo de escritura al final
    ofstream archivo("datos.txt", ios::app);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    // Escribe la nueva palabra en el archivo
    archivo << nuevaPalabra.palabra << "," << nuevaPalabra.traduccion << "," << nuevaPalabra.significado << endl;
    archivo.close();
}

// Función para leer todas las palabras almacenadas en el archivo
void leerPalabras() {
    // Abre el archivo en modo de lectura
    ifstream archivo("datos.txt");
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    // Muestra los títulos de las columnas
    cout << "+----------------------+----------------------+---------------------------------------------------------------------------------------------------+" << endl;
    cout << "|      Palabra         |      Traduccion      |                                  Funcionalidad                                                    |" << endl;
    cout << "+----------------------+----------------------+---------------------------------------------------------------------------------------------------+" << endl;

    // Lee cada palabra del archivo y la muestra en pantalla
    string palabra, traduccion, significado;
    while (getline(archivo, palabra, ',')) {
        getline(archivo, traduccion, ',');
        getline(archivo, significado);
        // Muestra los datos de la palabra en formato de tabla
        cout << "| " << setw(20) << palabra << " | " << setw(20) << traduccion << " | " << setw(20) << significado << endl;
    }

    archivo.close();

    // Agrega una línea horizontal al final
    cout << "+----------------------+----------------------+---------------------------------------------------------------------------------------------------+" << endl;
}

// Función para eliminar una palabra del archivo
void eliminarPalabra(const string& palabraAEliminar) {
    ifstream archivoEntrada("datos.txt");
    ofstream archivoSalida("temp.txt");

    if (!archivoEntrada || !archivoSalida) {
        cerr << "Error al abrir el archivo." << endl;
        return;

    }

    string palabra, traduccion, significado;
    bool eliminada = false;

    // Lee cada palabra del archivo
    while (getline(archivoEntrada, palabra, ',')) {
        getline(archivoEntrada, traduccion, ',');
        getline(archivoEntrada, significado);

        // Si la palabra es diferente a la que se desea eliminar, se escribe en el archivo de salida
        if (palabra != palabraAEliminar) {
            archivoSalida << palabra << "," << traduccion << "," << significado << endl;
        } else {
            eliminada = true;
        }
    }

    archivoEntrada.close();
    archivoSalida.close();

    // Elimina el archivo original y renombra el archivo temporal
    remove("datos.txt");
    rename("temp.txt", "datos.txt");

    if (eliminada) {
        cout << "Palabra eliminada exitosamente." << endl;
    } else {
        cout << "La palabra no fue encontrada." << endl;
    }
}

// Función para editar una palabra del archivo
void editarPalabra(const string& palabraAEditar) {
    ifstream archivoEntrada("datos.txt");
    ofstream archivoSalida("temp.txt");

    if (!archivoEntrada || !archivoSalida) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string palabra, traduccion, significado;
    bool editada = false;

    // Lee cada palabra del archivo
    while (getline(archivoEntrada, palabra, ',')) {
        getline(archivoEntrada, traduccion, ',');
        getline(archivoEntrada, significado);

        // Si la palabra coincide con la que se desea editar, se solicitan los nuevos valores y se escriben en el archivo de salida
        if (palabra == palabraAEditar) {
            editada = true;
            cout << "Ingrese la nueva traduccion para '" << palabraAEditar << "': ";
            getline(cin, traduccion);

            cout << "Ingrese la nueva funcionalidad para '" << palabraAEditar << "': ";
            getline(cin, significado);

            archivoSalida << palabraAEditar << "," << traduccion << "," << significado << endl;
        } else {
            archivoSalida << palabra << "," << traduccion << "," << significado << endl;
        }
    }

    archivoEntrada.close();
    archivoSalida.close();

    // Elimina el archivo original y renombra el archivo temporal
    remove("datos.txt");
    rename("temp.txt", "datos.txt");

    if (editada) {
        cout << "Palabra editada exitosamente." << endl;
    } else {
        cout << "La palabra no fue encontrada." << endl;
    }
}

// Función para traducir las palabras reservadas de C++ en el código ingresado
void traducirPalabrasReservadas(const string& codigo) {
    ifstream archivoPalabras("datos.txt");
    if (!archivoPalabras) {
        cerr << "Error al abrir el archivo de palabras." << endl;
        return;
    }

    map<string, string> traducciones;
    string palabra, traduccion, significado;

    // Lee cada palabra del archivo de palabras y la agrega al mapa de traducciones
    while (getline(archivoPalabras, palabra, ',')) {
        getline(archivoPalabras, traduccion, ',');
        getline(archivoPalabras, significado);
        // Elimina los espacios en blanco al inicio y al final de la palabra
        palabra.erase(0, palabra.find_first_not_of(" \t\n\r"));
        palabra.erase(palabra.find_last_not_of(" \t\n\r") + 1);
        traducciones[palabra] = traduccion;
    }

    archivoPalabras.close();

    istringstream stream(codigo);
    string linea;

    // Lee cada línea del código ingresado
    while (getline(stream, linea)) {
        istringstream palabraStream(linea);
        string palabraCodigo;

        // Lee la primera palabra de la línea
        palabraStream >> palabraCodigo;

        // Verifica si la palabra es una palabra reservada conocida
        if (traducciones.find(palabraCodigo) != traducciones.end()) {
            cout << traducciones[palabraCodigo] << " ";
        } else {
            // Si no es una palabra reservada, imprime la palabra tal cual
            cout << palabraCodigo << " ";
        }

        // Procesa el resto de la línea palabra por palabra
        while (palabraStream >> palabraCodigo) {
            // Si la palabra es una palabra reservada conocida, imprime su traducción
            if (traducciones.find(palabraCodigo) != traducciones.end()) {
                cout << traducciones[palabraCodigo] << " ";
            } else {
                // Si no es una palabra reservada, imprime la palabra tal cual
                cout << palabraCodigo << " ";
            }
        }

        // Muestra un salto de línea después de procesar cada línea
        cout << endl;
    }
}





int main() {
    int opcion;
    string palabraAEditar;
    string palabraAEliminar;
    string codigo;

    do {
        cout << "1. Crear palabra" << endl;
        cout << "2. Leer palabras" << endl;
        cout << "3. Editar palabra" << endl;
        cout << "4. Eliminar palabra" << endl;
        cout << "5. Digitar codigo" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1:
                crearPalabra();
                break;
            case 2:
                leerPalabras();
                break;
            case 3:
                cout << "Ingrese la palabra que desea editar: ";
                getline(cin, palabraAEditar);
                editarPalabra(palabraAEditar);
                break;
            case 4:
                cout << "Ingrese la palabra que desea eliminar: ";
                getline(cin, palabraAEliminar);
                eliminarPalabra(palabraAEliminar);
                break;
            case 5:
                cout << "Ingrese el codigo a traducir (presione Enter dos veces para finalizar):" << endl;
                {
                    stringstream buffer;
                    string linea;
                    while (getline(cin, linea) && !linea.empty()) {
                        buffer << linea << endl;
                    }
                    codigo = buffer.str();
                }
                traducirPalabrasReservadas(codigo);
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida" << endl;
        }
    } while (opcion != 6);

}
