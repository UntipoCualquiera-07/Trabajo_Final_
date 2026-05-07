#include<iostream>
#include<fstream>  
#include<string>  
#include<stdlib.h>  
#include<ctime>

using namespace std;

int dniExiste(int dni);
int dniBaneo(int dni);
void Entrada();
void Menu(int x);
void RegistrarPublicacion();
void RegistrarLector();
void RegistrarPrestamo(int dni);
void ActualizarPublicaciones(string texto, int s);
void RegistrarDevolucion(int dni);
void ReportesMenu();
void Reporte1();
void Reporte2();
void Reporte3();
void Reporte4();
void Reporte5();

int main() {
    srand(time(NULL));
    Entrada();
    return 0;
}
void Entrada() {
    int opcion = 0, dni, valor = 0;
    do {
        system("cls");
        cout << "\tBIENVENIDOS A LA BIBLIOTECA REGIONAL" << endl;
        cout << "1. INICIAR SESION" << endl;
        cout << "2. CREAR CUENTA DE LECTOR" << endl;
        cin >> opcion;
        switch (opcion) {
        case 1:
            do {
                cout << "Ingrese su DNI: ";
                cin >> dni;
                if (dni < 10000000 || dni > 99999999) { // Validación corregida
                    system("cls");
                    cout << "Ingrese un DNI valido" << endl;
                }
            } while (dni < 10000000 || dni > 99999999); // Validación corregida
            if (dniExiste(dni) == 1) {
                cout << "El DNI si esta registrado, puede continuar" << endl;
                system("pause");
                if (dniBaneo(dni) == 1) {
                    cout << "\nPero..." << endl << endl;
                    cout << "El DNI esta baneado del servicio" << endl;
                    cout << "Comuniquese con el bibliotecario" << endl;
                    system("pause");
                    opcion = 0;
                }
                else {
                    Menu(dni);
                    opcion = 0;//opcion = -1; // para salir del bucle luego del menú
                }
            }
            else {
                cout << "EL DNI no esta registrado" << endl;
                system("pause");
                opcion = 0;
            }
            break;
        case 2:
            RegistrarLector();
            opcion = 0;
            break;
        default:
            opcion = 0;
        }
    } while (opcion == 0);
}
int dniBaneo(int dni) {
    fstream baneo;
    int baneado;
    baneo.open("Baneados.txt", ios::in);
    if (baneo.fail()) {
        return 0;
    }
    while (baneo >> baneado) {
        if (baneado == dni) {
            baneo.close();
            return 1;
        }
    }
    baneo.close();
    return 0;
}
int dniExiste(int dni) {
    fstream DNI("DNI.txt", ios::in);
    int existe;
    if (!DNI.is_open()) {
        return 0; // Verifica que el archivo realmente se abrió
    }
    while (DNI >> existe) {
        if (existe == dni) {
            DNI.close();
            return 1;
        }
    }
    DNI.close();
}
void Menu(int x) {
    int opcion, dni = x;
    if (dniBaneo(dni) == 1) {
        return;
    }
    else {
        do {
            system("cls");
            cout << "\nBIENVENIDOS A LA BIBLIOTECA REGIONAL" << endl;
            cout << "1. Registrar una publicacion" << endl;
            cout << "2. Registrar un prestamo" << endl;
            cout << "3. Devolucion de publicacion" << endl;
            cout << "4. Reportes" << endl;
            cout << "5. Salir" << endl;
            cout << "Seleccione una opcion: ";
            cin >> opcion;

            switch (opcion) {
            case 1: RegistrarPublicacion(); break;
            case 2: RegistrarPrestamo(dni); break;
            case 3: RegistrarDevolucion(dni); break;
            case 4: ReportesMenu(); break;
            case 5:
                system("cls");
                cout << "\nGRACIAS POR SU VISITA" << endl; break;
            default:
                system("cls");
                cout << "ERROR, opcion no valida" << endl;
            }
        } while (opcion != 5);
    }
}
void RegistrarPublicacion() {
    int tipo = 0, local = 0, codigo, uni, f = 1;
    fstream publicacion, reporte5;
    string nombre, locales, tipos, linea;
    system("cls");
    cout << "Ingrese el nombre de su publicacion: ";
    cin.ignore();
    getline(cin, nombre);
    do {
        cout << "\nIngrese el tipo de publicacion: " << endl;
        cout << "1. Libro" << endl;
        cout << "2. Revista" << endl;
        cout << "3. Periodico" << endl;cin >> tipo;
        switch (tipo) {
        case 1:
            do {
                cout << "\nIngrese el local de la publicacion: " << endl;
                cout << "1. SJL" << endl;
                cout << "2. Los Olivos" << endl;cin >> local;
                switch (local) {
                case 1:
                    tipos = "Libro";
                    locales = "SJL"; break;
                case 2:
                    tipos = "Libro";
                    locales = "Los Olivos"; break;
                default: local = 0;
                }
            } while (local == 0); break;
        case 2:
            do {
                cout << "\nIngrese el local de la publicacion: " << endl;
                cout << "1. SJL" << endl;
                cout << "2. Los Olivos" << endl;cin >> local;
                switch (local) {
                case 1:
                    tipos = "Revista";
                    locales = "SJL"; break;
                case 2:
                    tipos = "Revista";
                    locales = "Los Olivos"; break;
                default: local = 0;
                }
            } while (local == 0); break;
        case 3:
            do {
                cout << "\nIngrese el local de la publicacion: " << endl;
                cout << "1. SJL" << endl;
                cout << "2. Los Olivos" << endl;cin >> local;
                switch (local) {
                case 1:
                    tipos = "Periodico";
                    locales = "SJL"; break;
                case 2:
                    tipos = "Periodico";
                    locales = "Los Olivos"; break;
                default: local = 0;
                }
            } while (local == 0); break;
        default: tipo = 0;
        }
    } while (tipo == 0);
    do {
        cout << "Cuantas unidades publicara: ";cin >> uni;
        if (uni < 0) {
            system("cls");
            cout << "\nCantidad invalida, reintentar" << endl;
        }
    } while (uni < 0);
    if (uni == 1) {
        do {
            codigo = 1000000 + rand() % (9999999 + 1 - 1000000);
            if (1000000 > codigo and 9999999 < codigo) {
                f = 1;
            }
            publicacion.open("Publicaciones.txt", ios::in);
            if (publicacion.fail()) {
                f = 0;
            }
            while (getline(publicacion, linea)) {
                if (linea.find(codigo) != string::npos) {
                    f = 0;
                }
            }
        } while (f == 1);
        publicacion.close();
        publicacion.open("Publicaciones.txt", ios::app);
        reporte5.open("Reporte_5.txt", ios::app);
        system("cls");
        cout << "     NOMBRE     |    CODIGO    |    TIPO   | LOCAL " << endl;
        cout << nombre << " | " << codigo << " | " << tipos << " | " << locales << endl;
        publicacion << nombre << " | " << codigo << " | " << tipos << " | " << locales << endl;
        reporte5 << nombre << " | " << codigo << " | " << tipos << " | " << locales << endl;
        reporte5.close();
        publicacion.close();
        system("pause");
        system("cls");
    }
    else {
        system("cls");
        cout << "Se registro las " << uni << " publicaciones con exito" << endl;
        cout << "     NOMBRE     |    CODIGO    |    TIPO   | LOCAL " << endl;
        for (int i = 1;i <= uni;i++) {
            do {
                codigo = 1000000 + rand() % (9999999 + 1 - 1000000);
                if (1000000 > codigo and 9999999 < codigo) {
                    f = 1;
                }
                publicacion.open("Publicaciones.txt", ios::in);
                if (publicacion.fail()) {
                    f = 0;
                }
                while (getline(publicacion, linea)) {
                    if (linea.find(codigo) != string::npos) {
                        f = 0;
                    }
                }
            } while (f == 1);
            publicacion.close();
            publicacion.open("Publicaciones.txt", ios::app);
            reporte5.open("Reporte_5.txt", ios::app);
            cout << nombre << " | " << codigo << " | " << tipos << " | " << locales << endl;
            publicacion << nombre << " | " << codigo << " | " << tipos << " | " << locales << endl;
            reporte5 << nombre << " | " << codigo << " | " << tipos << " | " << locales << endl;
            reporte5.close();
            publicacion.close();
        }
        system("pause");
        system("cls");
    }
}
void RegistrarLector() {
    char sexo;
    int dni, edad, celular, l = 0;
    string nombre, apellidos, direccion, linea, dniS;
    fstream lector, DNI;
    bool dni_valido = true;
    lector.open("Lector.txt", ios::app);
    system("cls");
    cin.ignore();
    cout << "Ingrese sus nombres: ";
    getline(cin, nombre);
    cout << "\nIngrese sus apellidos: ";
    getline(cin, apellidos);
    do {
        cout << "\nIngrese su DNI: ";cin >> dni;
        if (dni < 10000000 || dni > 99999999) {
            system("cls");
            cout << "Ingrese un DNI valido" << endl;
            dni_valido = false;
            continue;
        }
        DNI.open("DNI.txt", ios::in);
        if (!DNI.fail()) {
            while (getline(DNI, linea)) {
                if (linea == to_string(dni)) {
                    system("cls");
                    cout << "El DNI ingresado ya esta en uso" << endl;
                    dni_valido = false;
                    break;
                }
            }
            DNI.close();
        }

    } while (!dni_valido);
    do {
        cout << "\nIngrese su edad: ";cin >> edad;
        if (edad < 0) {
            system("cls");
            cout << "Ingrese una edad valida" << endl;
        }
        else if (edad > 100) { // Validación corregida
            system("cls");
            cout << "Mayores de 100 no se pueden registrar" << endl;
        }
    } while (edad < 0 || edad > 100); // Validación corregida
    do {
        cout << "\nIndique su sexo (M o F): ";cin >> sexo;
        if (sexo != 'M' && sexo != 'F') {
            system("cls");
            cout << "Ingrese un sexo valido" << endl;
        }
    } while (sexo != 'M' && sexo != 'F');
    cin.ignore();
    cout << "\nIngrese su direccion: ";
    getline(cin, direccion);
    do {
        cout << "\nIndique su numero de celular: ";cin >> celular;
        if (celular < 900000000 || celular > 999999999) { // Validación corregida
            system("cls");
            cout << "Ingrese un numero de celular valido" << endl;
        }
    } while (celular < 900000000 || celular > 999999999); // Validación corregida
    DNI.open("DNI.txt", ios::app);
    lector << "Nombre: " << nombre << endl;
    lector << "Apellidos: " << apellidos << endl;
    lector << "DNI: " << dni << endl;
    lector << "Edad: " << edad << endl;
    lector << "Sexo: " << sexo << endl;
    lector << "Celular: " << celular << endl;
    lector << "Direccion: " << direccion << endl << endl;
    lector.close();
    DNI << dni << endl;
    DNI.close();
    system("cls");
    cout << "\nREGISTRO CON EXITO EL/LA LECTOR(A)" << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Apellidos: " << apellidos << endl;
    cout << "DNI: " << dni << endl;
    cout << "Edad: " << edad << endl;
    cout << "Sexo: " << sexo << endl;
    cout << "Celular: " << celular << endl;
    cout << "Direccion: " << direccion << endl;
    cout << "\n";
    system("pause");
    system("cls");
}
void RegistrarPrestamo(int dni) {
    fstream publicacion, prestamo;
    int code, s = 0, dia, mes, ano;
    string texto, linea, codigo, SJL, LO;
    publicacion.open("Publicaciones.txt", ios::in);
    system("cls");
    if (publicacion.fail()) {
        cout << "No hay ninguna publicacion habil" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "     NOMBRE     |    CODIGO    |    TIPO   | LOCAL " << endl;
    while (getline(publicacion, texto)) {
        cout << texto << endl;
    }
    cout << "Ingrese un codigo para reservar: ";cin >> code;
    codigo = to_string(code);
    publicacion.close();
    publicacion.open("Publicaciones.txt", ios::in);
    system("cls");
    while (getline(publicacion, texto)) {
        if (texto.find(codigo) != string::npos) {
            cout << "Se encontro el codigo" << endl;
            cout << "     NOMBRE     |    CODIGO    |    TIPO   | LOCAL " << endl;
            cout << texto << endl;
            linea = texto;
            publicacion.close();
            s = 1;
            ActualizarPublicaciones(texto, s);
            system("pause");
            system("cls");
            break;
        }
    }
    if (s == 0) {
        system("cls");
        cout << "No se encontro el codigo" << endl;
        system("pause");
        return;
    }
    do {
        system("cls");
        cout << "Ingrese la fecha actual (dia-mes-anio): " << endl;
        cout << "Ejemplo: 28-6-2025" << endl;cin >> dia;cout << "-";cin >> mes;cout << "-";cin >> ano;
        if (dia < 0 || dia > 31 || mes < 0 || mes > 12 || ano < 0) { // Validación corregida
            cout << "Ingrese una fecha valida" << endl;
            system("pause");
        }
    } while (dia < 0 || dia > 31 || mes < 0 || mes > 12 || ano < 0); // Validación corregida
    prestamo.open("Prestamos.txt", ios::app);
    prestamo << linea << " | " << dia << "-" << mes << "-" << ano << " | ";
    system("cls");
    cout << "Se registro exitosamente su prestamo" << endl;
    cout << "     NOMBRE     |    CODIGO    |    TIPO   |    LOCAL   |   Prestamo   |   Devolucion   |    DNI    " << endl;
    cout << linea << " | " << dia << "-" << mes << "-" << ano << " | ";
    if (linea.find("Libro") != string::npos || linea.find("Revista") != string::npos) {
        dia += 5;
    }
    else if (linea.find("Periodico") != string::npos) {
        dia += 2;
    }
    if (mes == 2 && dia > 28) {
        dia -= 28;
        mes += 1;
    }
    else if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
        dia -= 30;
        mes += 1;
    }
    else if ((mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) && dia > 31) {
        dia -= 31;
        mes += 1;
    }

    if (mes > 12) {
        mes = 1;
        ano += 1;
    }
    cout << dia << "-" << mes << "-" << ano << " | " << dni << endl;
    prestamo << dia << "-" << mes << "-" << ano << " | " << dni << endl;
    prestamo.close();
    system("pause");
    system("cls");
}
void ActualizarPublicaciones(string texto, int s) {
    fstream publicacion, prestamo;
    string relleno, linea;
    switch (s) {
    case 1:
        publicacion.open("Publicaciones.txt", ios::in);
        while (getline(publicacion, linea)) {
            if (linea != texto) {
                relleno += linea + "\n";
            }
        }
        publicacion.close();
        publicacion.open("Publicaciones.txt", ios::out);
        publicacion << relleno;
        publicacion.close();
        break;
    case 2:
        publicacion.open("Publicaciones.txt", ios::app);
        publicacion << texto << endl;
        publicacion.close();
        break;
    case 3:
        prestamo.open("Prestamos.txt", ios::in);
        while (getline(prestamo, linea)) {
            if (linea != texto) {
                relleno += linea + "\n";
            }
        }
        prestamo.close();
        prestamo.open("Publicaciones.txt", ios::out);
        prestamo << relleno;
        prestamo.close();
    }
}
void RegistrarDevolucion(int dni) {
    fstream devolucion, baneo;
    string texto, linea, DNI, codigo, f_devo, fecha_limpia, fe_d, fe_m, fe_a;
    int code, s = 0, dia, mes, ano, diad, mesd, anod, pos1, pos2, devolucion_tardia = 0;
    DNI = to_string(dni);
    devolucion.open("Prestamos.txt", ios::in);
    system("cls");
    cout << "Estas son los prestamos pendientes a devolver" << endl;
    cout << "     NOMBRE     |    CODIGO    |    TIPO   |    LOCAL   |   Prestamo   |   Devolucion   |    DNI    " << endl;
    while (getline(devolucion, linea)) {
        if (linea.find(DNI) != string::npos) {
            cout << linea << endl;
        }
    }
    devolucion.close();
    devolucion.open("Prestamos.txt", ios::in);
    cout << "Ingrese el codigo de la publicacion a devolver: "; cin >> code;
    system("cls");
    codigo = to_string(code);
    while (getline(devolucion, linea)) {
        if (linea.find(codigo) != string::npos) {
            cout << "Se encontro la publicacion" << endl;
            cout << "     NOMBRE     |    CODIGO    |    TIPO   |    LOCAL   |   Prestamo   |   Devolucion   |    DNI    " << endl;
            cout << linea << endl;
            texto = linea;
            s = 2;
            system("pause");
            system("cls");
        }
    }
    if (s == 0) {
        system("cls");
        cout << "No se encontro ningun codigo" << endl;
        system("pause");
        return;
    }
    else if (s == 2) {
        int contador = 0;
        int fecha_inicio = 0, fecha_fin = 0;
        for (int i = 0; i < texto.length(); i++) {
            if (texto[i] == '|') {
                contador++;
                if (contador == 5) {
                    fecha_inicio = i + 1;
                }
                else if (contador == 6) {
                    fecha_fin = i;
                    break;
                }
            }
        }
        if (fecha_inicio == 0 || fecha_fin == 0 || fecha_fin <= fecha_inicio) {
            cout << "Error: no se pudo extraer la fecha de devolucion correctamente." << endl;
            system("pause");
            return;
        }
        f_devo = texto.substr(fecha_inicio, fecha_fin - fecha_inicio);
        fecha_limpia = "";
        for (int i = 0; i < f_devo.length(); i++) {
            if ((f_devo[i] >= '0' && f_devo[i] <= '9') || f_devo[i] == '-') {
                fecha_limpia += f_devo[i];
            }
        }
        pos1 = fecha_limpia.find("-");
        pos2 = fecha_limpia.find("-", pos1 + 1);
        if (fecha_limpia.empty() || pos1 == string::npos || pos2 == string::npos) {
            cout << "Error: la fecha de devolucion no tiene el formato esperado (dia-mes-año)." << endl;
            system("pause");
            return;
        }
        fe_d = fecha_limpia.substr(0, pos1);
        fe_m = fecha_limpia.substr(pos1 + 1, pos2 - pos1 - 1);
        fe_a = fecha_limpia.substr(pos2 + 1);
        diad = stoi(fe_d);
        mesd = stoi(fe_m);
        anod = stoi(fe_a);
    }
    devolucion.close();
    do {
        system("cls");
        cout << "Ingrese la fecha actual de la devolucion (dia-mes-anio): " << endl;
        cout << "Ejemplo: 28-06-2025" << endl; cin >> dia; cout << "-"; cin >> mes; cout << "-"; cin >> ano;
        if (dia < 0 || dia > 31 || mes < 0 || mes > 12 || ano < 0) {
            cout << "\nIngrese una fecha valida" << endl;
            system("pause");
        }
    } while (dia < 0 || dia > 31 || mes < 0 || mes > 12 || ano < 0);
    system("cls");
    cout << "\nFecha limite de devolucion: " << diad << "-" << mesd << "-" << anod << endl;
    cout << "Fecha ingresada por el lector: " << dia << "-" << mes << "-" << ano << endl;
    if (ano > anod || (ano == anod && mes > mesd) || (ano == anod && mes == mesd && dia > diad)) {
        devolucion_tardia = 1;
    }
    if (devolucion_tardia == 1) {
        cout << "\nLa devolucion fue TARDE." << endl;
        cout << "Usted no tendra acceso a la plataforma por 2 semanas" << endl;
        cout << "Una vez cumplidas las semanas indicadas" << endl;
        cout << "Debera comunicarse con el bibliotecario para regresarlo al sistema" << endl;
        baneo.open("Baneados.txt", ios::app);
        baneo << dni << endl;
        baneo.close();
        system("pause");
        system("cls");
        return;
    }
    else {
        cout << "\nLa devolucion fue A TIEMPO." << endl;
        cout << "Gracias por su preferencia" << endl;
        system("pause");
        system("cls");
    }
}
void ReportesMenu() {
    int opcion = 0;
    string contrasena = "admin", ingreso;
    system("cls");
    cout << "Solo el bibliotecario puede ingresar" << endl;
    cout << "Ingrese la contraseña para acceder a los reportes: ";cin >> ingreso;
    if (ingreso == contrasena) {
        cout << "\nContraseña correcta" << endl;
        system("pause");
        do {
            system("cls");
            cout << "\tIngrese el tipo de reporte a ver" << endl;
            cout << "1. Reporte 1" << endl;
            cout << "2. Reporte 2" << endl;
            cout << "3. Reporte 3" << endl;
            cout << "4. Reporte 4" << endl;
            cout << "5. Reporte 5" << endl;
            cout << "6. Salir" << endl;
            cout << "Seleccione una letra: " << endl;cin >> opcion;
            switch (opcion) {
            case 1: Reporte1(); break;
            case 2: Reporte2(); break;
            case 3: Reporte3(); break;
            case 4: Reporte4(); break;
            case 5: Reporte5(); break;
            case 6: system("cls");
                cout << "Esos fueron lo reportes" << endl;
                cout << "Gracias" << endl;
                system("pause"); break;
            default: cout << "ERROR, opcion no valida" << endl;
                system("pause");
            }
        } while (opcion != 6);
    }
    else {
        cout << "Contraseña incorrecta" << endl;
        system("pause");
        return;
    }
}
void Reporte1() {
    string texto, f_devo, fecha_limpia, fe_d, fe_m, fe_a, linea, SJL, LO;
    fstream reporte1, devolucion;
    int dia, mes, ano, pos1, pos2, diad, mesd, anod, devolucion_tardia = 0, count_LO = 0, count_SJL = 0;
    devolucion.open("Prestamos.txt", ios::in);
    reporte1.open("Reporte_1.txt", ios::out);
    system("cls");
    if (devolucion.fail()) {
        system("cls");
        cout << "No hay prestamos a devolver fuera de rango" << endl;
        system("pause");
        system("cls");
        return;
    }
    do {
        system("cls");
        cout << "Ingrese la fecha actual de la devolucion (dia-mes-anio): " << endl;
        cout << "Ejemplo: 28-06-2025" << endl; cin >> dia; cout << "-"; cin >> mes; cout << "-"; cin >> ano;
        if (dia < 0 || dia > 31 || mes < 0 || mes > 12 || ano < 0) {
            cout << "\nIngrese una fecha valida" << endl;
            system("pause");
        }
    } while (dia < 0 || dia > 31 || mes < 0 || mes > 12 || ano < 0);
    system("cls");
    cout << "Estas son las publicaciones pendientes a devolver segun la fecha ingresada" << endl;
    while (getline(devolucion, texto)) {
        devolucion_tardia = 0;
        int contador = 0;
        int fecha_inicio = 0, fecha_fin = 0;
        for (int i = 0; i < texto.length(); i++) {
            if (texto[i] == '|') {
                contador++;
                if (contador == 5) {
                    fecha_inicio = i + 1;
                }
                else if (contador == 6) {
                    fecha_fin = i;
                    break;
                }
            }
        }
        if (fecha_inicio == 0 || fecha_fin == 0 || fecha_fin <= fecha_inicio) {
            cout << "Error: no se pudo extraer la fecha de devolucion correctamente." << endl;
            system("pause");
            return;
        }
        f_devo = texto.substr(fecha_inicio, fecha_fin - fecha_inicio);
        fecha_limpia = "";
        for (int i = 0; i < f_devo.length(); i++) {
            if ((f_devo[i] >= '0' && f_devo[i] <= '9') || f_devo[i] == '-') {
                fecha_limpia += f_devo[i];
            }
        }
        pos1 = fecha_limpia.find("-");
        pos2 = fecha_limpia.find("-", pos1 + 1);
        if (fecha_limpia.empty() || pos1 == string::npos || pos2 == string::npos) {
            cout << "Error: la fecha de devolucion no tiene el formato esperado (dia-mes-año)." << endl;
            system("pause");
            return;
        }
        fe_d = fecha_limpia.substr(0, pos1);
        fe_m = fecha_limpia.substr(pos1 + 1, pos2 - pos1 - 1);
        fe_a = fecha_limpia.substr(pos2 + 1);
        diad = stoi(fe_d);
        mesd = stoi(fe_m);
        anod = stoi(fe_a);
        if (ano > anod || (ano == anod && mes > mesd) || (ano == anod && mes == mesd && dia > diad)) {
            devolucion_tardia = 1;
        }
        if (devolucion_tardia == 1) {
            reporte1 << texto << endl;
        }
    }
    devolucion.close();
    reporte1.close();
    reporte1.open("Reporte_1.txt", ios::in);
    while (getline(reporte1, linea)) {
        if (linea.find("Los Olivos") != string::npos) {
            LO += linea + "\n";
            count_LO++;
        }
        else if (linea.find("SJL") != string::npos) {
            SJL += linea + "\n";
            count_SJL++;
        }
    }
    reporte1.close();
    reporte1.open("Reporte_1.txt", ios::out);
    cout << LO;
    reporte1 << LO;
    cout << SJL;
    reporte1 << SJL;
    reporte1.close();
    cout << "\nLos Olivos: " << count_LO << " registros vencidos" << endl;
    reporte1 << "\nLos Olivos: " << count_LO << " registros vencidos" << endl;
    cout << "San Juan de Lurigancho: " << count_SJL << " registros vencidos" << endl;
    reporte1 << "San Juan de Lurigancho: " << count_SJL << " registros vencidos" << endl;
    system("pause");
    system("cls");
}
void Reporte2() {
    fstream prestamos, lector, reporte2;
    string tipo, linea, dniTemp, dni, texto, dni_p, edadS, edadT;
    int pos, edad, nino = 0, ado = 0, joven = 0, adul = 0, adulMmayor = 0, adul_mayor = 0;
    system("cls");
    cout << "Este reportes es el numero de lectores por rango de edad para un tipo de publicacion" << endl;
    do {
        cout << "Ingrese el tipo de publicacion (Libro, Revista o Periodico): ";cin >> tipo;
        if (tipo != "Libro" and tipo != "Revista" and tipo != "Periodico") {
            cout << "Ingrese una de las opciones indicadas" << endl;
            system("pause");
            system("cls");
        }

    } while (tipo != "Libro" and tipo != "Revista" and tipo != "Periodico");
    lector.open("Lector.txt", ios::in);
    if (lector.fail()) {
        system("cls");
        cout << "No hay lectores registrados" << endl;
        system("pause");
        system("cls");
    }
    prestamos.open("Prestamos.txt", ios::in);
    if (prestamos.fail()) {
        system("cls");
        cout << "No hay prestamos registrados" << endl;
        system("pause");
        return;
        system("cls");
    }
    while (getline(prestamos, linea)) {
        if (linea.find(tipo) != string::npos) {
            pos = linea.rfind("|");
            if (pos != string::npos) {
                dni = "";
                dniTemp = linea.substr(pos + 1);
                for (int i = 0;i < dniTemp.length();i++) {
                    if (dniTemp[i] != ' ') {
                        dni += dniTemp[i];
                    }
                }
                lector.close();
                lector.open("Lector.txt", ios::in);
                while (getline(lector, texto)) {
                    if (texto.find("DNI: " + dni) != string::npos) {
                        dni_p = texto.substr(5);
                    }
                    else if (texto.find("Edad: ") != string::npos and dni_p == dni) {
                        edadT = texto.substr(6);
                        for (int i = 0;i < edadT.length();i++) {
                            if (edadT[i] != ' ') {
                                edadS += edadT[i];
                            }
                        }
                        edad = stoi(edadS);
                        if (1 <= edad and edad <= 10) {
                            nino++;
                        }
                        else if (11 <= edad and edad <= 20) {
                            ado++;
                        }
                        else if (21 <= edad and edad <= 30) {
                            joven++;
                        }
                        else if (31 <= edad and edad <= 40) {
                            adul++;
                        }
                        else if (41 <= edad and edad <= 50) {
                            adulMmayor++;
                        }
                        else if (51 <= edad and edad <= 100) {
                            adul_mayor++;
                        }
                        break;
                    }
                }
            }
        }
    }
    prestamos.close();
    reporte2.open("Reporte_2.txt", ios::out);
    system("cls");
    cout << "\tREPORTE DE LECTORES POR RANGO DE EDAD" << endl;
    cout << "Tipo de publicacion: " << tipo << endl;
    cout << "---------------------------------------------" << endl;
    cout << "De 1 a 10: " << nino << " lectores" << endl;
    cout << "De 11 a 20: " << ado << " lectores" << endl;
    cout << "De 21 a 30: " << joven << " lectores" << endl;
    cout << "De 31 a 40: " << adul << " lectores" << endl;
    cout << "De 41 a 50: " << adulMmayor << " lectores" << endl;
    cout << "De 51 a 100: " << adul_mayor << " lectores" << endl;
    reporte2 << "\tREPORTE DE LECTORES POR RANGO DE EDAD" << endl;
    reporte2 << "Tipo de publicacion: " << tipo << endl;
    reporte2 << "---------------------------------------------" << endl;
    reporte2 << "De 1 a 10: " << nino << " lectores" << endl;
    reporte2 << "De 11 a 20: " << ado << " lectores" << endl;
    reporte2 << "De 21 a 30: " << joven << " lectores" << endl;
    reporte2 << "De 31 a 40: " << adul << " lectores" << endl;
    reporte2 << "De 41 a 50: " << adulMmayor << " lectores" << endl;
    reporte2 << "De 51 a 100: " << adul_mayor << " lectores" << endl;
    reporte2.close();
    system("pause");
    system("cls");
}
void Reporte3() {
    fstream lector, reporte3;
    string linea;
    int contador = 0;
    lector.open("Lector.txt", ios::in);
    reporte3.open("Reporte_3.txt", ios::out);
    system("cls");
    cout << "El registro total de las cuentas de los lectores" << endl;
    while (getline(lector, linea)) {
        cout << linea << endl;
        reporte3 << linea << endl;
        if (linea.find("Nombre: ") != string::npos) {
            contador++;
        }
    }
    cout << "El numero de cuentas registradas son: " << contador << endl;
    reporte3 << "El numero de cuentas registradas son: " << contador << endl;
    system("pause");
    system("cls");
    lector.close();
    reporte3.close();
}
void Reporte4() {
    fstream baneo, reporte4;
    string linea;
    int contador = 0;
    reporte4.open("Reporte_4.txt", ios::out);
    baneo.open("Baneados.txt", ios::in);
    system("cls");
    cout << "Esta es la lista de los DNI baneados: " << endl;
    while (getline(baneo, linea)) {
        cout << linea << endl;
        reporte4 << linea << endl;
        contador++;
    }
    cout << "\nEl numero de baneados son: " << contador << endl;
    reporte4 << "\nEl numero de baneados son: " << contador << endl;
    reporte4.close();
    baneo.close();
    system("pause");
    system("cls");
}
void Reporte5() {
    fstream reporte5;
    string linea;
    int contador = 0;
    reporte5.open("Reporte_5.txt", ios::in);
    system("cls");
    if (reporte5.fail()) {
        system("cls");
        cout << "No se encuentra ninguna publicacion registrada" << endl;
        system("pause");
        return;
    }
    cout << "Este reporte son todas las publicaciones registradas desde las que no estan prestadas hasta las disponibles" << endl;
    while (getline(reporte5, linea)) {
        cout << linea << endl;
        contador++;
    }
    cout << "\nEL numero de publicaciones registradas son: " << contador << endl;
    reporte5.close();
    system("pause");
    system("cls");
}