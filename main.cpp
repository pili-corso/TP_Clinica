#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "C:\Users\UsuarioHI\Downloads\rapidcsv-master\rapidcsv-master\src\rapidcsv.h"

using namespace std;

// ======== ESTRUCTURAS ========

struct Turno {
    string especialidad;
    string practica;
    string medico;
    string consultorio;
    string dia;
    string hora;
    bool ocupado = false;
};

struct Medico {
    string nombre;
    string especialidad;
    string consultorio;
};

// ======== LISTA DE MEDICOS ========

vector<Medico> medicos = {
    {"Dr. Lopez", "Medico Clinico", "Consultorio 1"},
    {"Dra. Garcia", "Medico Clinico", "Consultorio 2"},
    {"Dr. Castro", "Medico Clinico", "Consultorio 3"},
    {"Dra. Silva", "Medico Clinico", "Consultorio 4"},
    {"Dr. Molina", "Medico Clinico", "Consultorio 5"},

    {"Dr. Fernandez", "Cardiologo", "Consultorio 6"},
    {"Dra. Costa", "Cardiologo", "Consultorio 7"},
    {"Dr. Rojas", "Cardiologo", "Consultorio 8"},
    {"Dra. Benitez", "Cardiologo", "Consultorio 9"},
    {"Dr. Herrera", "Cardiologo", "Consultorio 10"},

    {"Dr. Ruiz", "Traumatologo", "Consultorio 11"},
    {"Dra. Soto", "Traumatologo", "Consultorio 12"},
    {"Dr. Aguilar", "Traumatologo", "Consultorio 13"},
    {"Dra. Cabrera", "Traumatologo", "Consultorio 14"},
    {"Dr. Lopez B.", "Traumatologo", "Consultorio 15"},

    {"Dra. Mendez", "Obstetra", "Consultorio 16"},
    {"Dr. Flores", "Obstetra", "Consultorio 17"},
    {"Dra. Alvarez", "Obstetra", "Consultorio 18"},
    {"Dr. Paredes", "Obstetra", "Consultorio 19"},
    {"Dra. Varela", "Obstetra", "Consultorio 20"},

    {"Dr. Torres", "Pediatra", "Consultorio 21"},
    {"Dra. Sanchez", "Pediatra", "Consultorio 22"},
    {"Dr. Gutierrez", "Pediatra", "Consultorio 23"},
    {"Dra. Cabrera", "Pediatra", "Consultorio 24"},
    {"Dr. Ramos", "Pediatra", "Consultorio 25"},

    {"Dra. Diaz", "Dermatologo", "Consultorio 26"},
    {"Dr. Perez", "Dermatologo", "Consultorio 27"},
    {"Dra. Torres", "Dermatologo", "Consultorio 28"},
    {"Dr. Medina", "Dermatologo", "Consultorio 29"},
    {"Dra. Castro", "Dermatologo", "Consultorio 30"},

    {"Dr. Suarez", "Oftalmologo", "Consultorio 31"},
    {"Dra. Lopez A.", "Oftalmologo", "Consultorio 32"},
    {"Dr. Fernandez R.", "Oftalmologo", "Consultorio 33"},
    {"Dra. Rivas", "Oftalmologo", "Consultorio 34"},
    {"Dr. Meza", "Oftalmologo", "Consultorio 35"},

    {"Dr. Bravo", "Gastroenterologo", "Consultorio 36"},
    {"Dra. Alonso", "Gastroenterologo", "Consultorio 37"},
    {"Dr. Cabrera", "Gastroenterologo", "Consultorio 38"},
    {"Dra. Flores M.", "Gastroenterologo", "Consultorio 39"},
    {"Dr. Ruiz C.", "Gastroenterologo", "Consultorio 40"}
};

// ======== FUNCIONES ========

void crearAgendaBase(vector<Turno>& turnos) {
    vector<string> horas = {
        "09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00", "17:00"
    };

    for (const auto& med : medicos) {
        vector<string> dias;
        vector<string> practicas;

        if (med.nombre == "Dr. Lopez" || med.nombre == "Dra. Mendez" || med.nombre == "Dr. Fernandez")
            dias = { "Lunes", "Miercoles", "Viernes" };
        else if (med.nombre == "Dra. Garcia" || med.nombre == "Dr. Torres" || med.nombre == "Dra. Diaz")
            dias = { "Martes", "Jueves" };
        else if (med.nombre == "Dr. Castro" || med.nombre == "Dr. Perez" || med.nombre == "Dra. Costa")
            dias = { "Lunes", "Martes" };
        else if (med.nombre == "Dra. Silva" || med.nombre == "Dr. Rojas" || med.nombre == "Dr. Ruiz")
            dias = { "Miercoles", "Viernes" };
        else if (med.nombre == "Dr. Molina" || med.nombre == "Dr. Medina" || med.nombre == "Dra. Benitez")
            dias = { "Martes", "Viernes" };
        else if (med.nombre == "Dra. Soto" || med.nombre == "Dr. Herrera" || med.nombre == "Dra. Cabrera")
            dias = { "Lunes", "Jueves" };
        else if (med.nombre == "Dr. Bravo" || med.nombre == "Dra. Alonso" || med.nombre == "Dr. Suarez")
            dias = { "Martes", "Miercoles" };
        else if (med.nombre == "Dra. Lopez A." || med.nombre == "Dra. Flores M." || med.nombre == "Dr. Gutierrez")
            dias = { "Jueves", "Viernes" };
        else
            dias = { "Miercoles" };

        if (med.especialidad == "Cardiologo")
            practicas = { "Consulta", "Electrocardiograma", "Ecocardiograma" };
        else if (med.especialidad == "Traumatologo")
            practicas = { "Consulta", "Control de yeso", "Curacion" };
        else if (med.especialidad == "Obstetra")
            practicas = { "Consulta", "Ecografia", "Control prenatal" };
        else if (med.especialidad == "Pediatra")
            practicas = { "Consulta", "Vacunacion", "Control de niño sano" };
        else if (med.especialidad == "Dermatologo")
            practicas = { "Consulta", "Peeling", "Crioterapia" };
        else if (med.especialidad == "Oftalmologo")
            practicas = { "Consulta", "Control visual", "Fondo de ojo" };
        else if (med.especialidad == "Gastroenterologo")
            practicas = { "Consulta", "Endoscopia", "Control post-tratamiento" };
        else
            practicas = { "Consulta" };

        for (const auto& d : dias) {
            for (const auto& h : horas) {
                for (const auto& p : practicas) {
                    Turno t;
                    t.especialidad = med.especialidad;
                    t.practica = p;
                    t.medico = med.nombre;
                    t.consultorio = med.consultorio;
                    t.dia = d;
                    t.hora = h;
                    t.ocupado = false;
                    turnos.push_back(t);
                }
            }
        }
    }
}

void guardarTurnosEnCSV(const vector<Turno>& turnos, const string& archivo) {
    vector<string> dias, horas, consultorios, medicosCol, especialidadesCol, practicasCol, estados;
    for (const auto& t : turnos) {
        dias.push_back(t.dia);
        horas.push_back(t.hora);
        consultorios.push_back(t.consultorio);
        medicosCol.push_back(t.medico);
        especialidadesCol.push_back(t.especialidad);
        practicasCol.push_back(t.practica);
        estados.push_back(t.ocupado ? "OCUPADO" : "DISPONIBLE");
    }

    rapidcsv::Document doc("", rapidcsv::LabelParams(-1, -1));
    doc.SetColumn<string>(0, dias);
    doc.SetColumn<string>(1, horas);
    doc.SetColumn<string>(2, consultorios);
    doc.SetColumn<string>(3, medicosCol);
    doc.SetColumn<string>(4, especialidadesCol);
    doc.SetColumn<string>(5, practicasCol);
    doc.SetColumn<string>(6, estados);
    doc.Save(archivo);
    cout << "\nArchivo CSV actualizado correctamente.\n";
}

void cargarTurnosDesdeCSV(vector<Turno>& turnos, const string& archivo) {
    try {
        rapidcsv::Document doc(archivo, rapidcsv::LabelParams(-1, -1));
        int filas = doc.GetRowCount();
        for (int i = 0; i < filas; i++) {
            Turno t;
            t.dia = doc.GetCell<string>(0, i);
            t.hora = doc.GetCell<string>(1, i);
            t.consultorio = doc.GetCell<string>(2, i);
            t.medico = doc.GetCell<string>(3, i);
            t.especialidad = doc.GetCell<string>(4, i);
            t.practica = doc.GetCell<string>(5, i);
            string estado = doc.GetCell<string>(6, i);
            t.ocupado = (estado == "OCUPADO");
            turnos.push_back(t);
        }
        cout << "\nTurnos cargados desde CSV correctamente.\n";
    }
    catch (...) {
        cout << "\nNo se encontro el archivo CSV. Se creara la agenda completa.\n";
        crearAgendaBase(turnos);
        guardarTurnosEnCSV(turnos, archivo);
    }
}

// ===== FUNCIONES DE MENU =====

void cancelarTurno(vector<Turno>& turnos) {
    cout << "\n=== TURNOS OCUPADOS ===\n";
    bool hay = false;
    for (size_t i = 0; i < turnos.size(); i++) {
        if (turnos[i].ocupado) {
            cout << setw(4) << i << " | " << turnos[i].dia << " " << turnos[i].hora
                << " | " << turnos[i].especialidad << " | " << turnos[i].medico
                << " | " << turnos[i].practica << endl;
            hay = true;
        }
    }
    if (!hay) {
        cout << "No hay turnos ocupados.\n";
        return;
    }

    cout << "\nIngrese el numero del turno a cancelar: ";
    int num;
    cin >> num;
    cin.ignore();

    if (num >= 0 && num < (int)turnos.size() && turnos[num].ocupado) {
        turnos[num].ocupado = false;
        cout << "\nTurno cancelado correctamente.\n";
    }
    else {
        cout << "\nNumero invalido o turno ya libre.\n";
    }
}

string elegirEspecialidad() {
    vector<string> especialidades;
    for (const auto& m : medicos)
        if (find(especialidades.begin(), especialidades.end(), m.especialidad) == especialidades.end())
            especialidades.push_back(m.especialidad);

    cout << "\n=== ESPECIALIDADES DISPONIBLES ===\n";
    for (size_t i = 0; i < especialidades.size(); i++)
        cout << i + 1 << ". " << especialidades[i] << endl;

    cout << "\nIngrese el numero de la especialidad: ";
    int op;
    cin >> op;
    cin.ignore();
    if (op < 1 || op >(int)especialidades.size()) {
        cout << "Opcion invalida.\n";
        return "";
    }
    return especialidades[op - 1];
}

// ===== TOMAR TURNO POR MEDICO =====

void tomarTurnoPorMedico(vector<Turno>& turnos) {
    vector<string> medicosUnicos;
    for (const auto& t : turnos)
        if (find(medicosUnicos.begin(), medicosUnicos.end(), t.medico) == medicosUnicos.end())
            medicosUnicos.push_back(t.medico);

    cout << "\n=== MEDICOS DISPONIBLES ===\n";
    for (size_t i = 0; i < medicosUnicos.size(); i++)
        cout << i + 1 << ". " << medicosUnicos[i] << endl;

    cout << "\nIngrese el numero del medico: ";
    int opcion;
    cin >> opcion;
    cin.ignore();

    if (opcion < 1 || opcion >(int)medicosUnicos.size()) {
        cout << "Opcion invalida.\n";
        return;
    }

    string nombre = medicosUnicos[opcion - 1];
    cout << "\n=== TURNOS DE " << nombre << " ===\n";

    bool hay = false;
    for (size_t i = 0; i < turnos.size(); i++) {
        if (turnos[i].medico == nombre && !turnos[i].ocupado) {
            cout << setw(4) << i << " | " << turnos[i].dia << " " << turnos[i].hora
                << " | " << turnos[i].consultorio
                << " | " << turnos[i].especialidad
                << " | " << turnos[i].practica << endl;
            hay = true;
        }
    }
    if (!hay) {
        cout << "\nNo hay turnos disponibles para " << nombre << ".\n";
        return;
    }

    cout << "\nIngrese el numero del turno que desea tomar: ";
    int num;
    cin >> num;
    cin.ignore();

    if (num >= 0 && num < (int)turnos.size() && !turnos[num].ocupado && turnos[num].medico == nombre) {
        turnos[num].ocupado = true;
        cout << "\nTurno tomado con exito con " << turnos[num].medico
            << " (" << turnos[num].especialidad << ") el "
            << turnos[num].dia << " a las " << turnos[num].hora << ".\n";
    }
    else {
        cout << "\nNumero invalido o turno no disponible.\n";
    }
}

// ===== TOMAR TURNO POR ESPECIALIDAD =====

void tomarTurnoPorEspecialidad(vector<Turno>& turnos) {
    string esp = elegirEspecialidad();
    if (esp.empty()) return;

    cout << "\n=== PROFESIONALES DE " << esp << " ===\n";
    vector<string> medicosEsp;
    for (const auto& m : medicos)
        if (m.especialidad == esp)
            medicosEsp.push_back(m.nombre);

    for (size_t i = 0; i < medicosEsp.size(); i++)
        cout << i + 1 << ". " << medicosEsp[i] << endl;

    cout << "\nSeleccione el numero del medico: ";
    int opcion;
    cin >> opcion;
    cin.ignore();

    if (opcion < 1 || opcion >(int)medicosEsp.size()) {
        cout << "Opcion invalida.\n";
        return;
    }

    string nombre = medicosEsp[opcion - 1];
    cout << "\n=== TURNOS DE " << nombre << " ===\n";

    bool hay = false;
    for (size_t i = 0; i < turnos.size(); i++) {
        if (turnos[i].medico == nombre && !turnos[i].ocupado) {
            cout << setw(4) << i << " | " << turnos[i].dia << " " << turnos[i].hora
                << " | " << turnos[i].consultorio
                << " | " << turnos[i].especialidad
                << " | " << turnos[i].practica << endl;
            hay = true;
        }
    }

    if (!hay) {
        cout << "\nNo hay turnos disponibles para " << nombre << ".\n";
        return;
    }

    cout << "\nIngrese el numero del turno que desea tomar: ";
    int num;
    cin >> num;
    cin.ignore();

    if (num >= 0 && num < (int)turnos.size() && !turnos[num].ocupado && turnos[num].medico == nombre) {
        turnos[num].ocupado = true;
        cout << "\nTurno tomado con exito con " << turnos[num].medico
            << " (" << turnos[num].especialidad << ") el "
            << turnos[num].dia << " a las " << turnos[num].hora << ".\n";
    }
    else {
        cout << "\nNumero invalido o turno no disponible.\n";
    }
}

// ===== TOMAR TURNO POR PRACTICA =====

void tomarTurnoPorPractica(vector<Turno>& turnos) {
    cout << "\n=== PRACTICAS DISPONIBLES ===\n";

    vector<string> practicas;
    for (const auto& t : turnos) {
        if (find(practicas.begin(), practicas.end(), t.practica) == practicas.end())
            practicas.push_back(t.practica);
    }

    for (size_t i = 0; i < practicas.size(); i++)
        cout << i + 1 << ". " << practicas[i] << endl;

    cout << "\nSeleccione el numero de la practica: ";
    int opcion;
    cin >> opcion;
    cin.ignore();

    if (opcion < 1 || opcion >(int)practicas.size()) {
        cout << "Opcion invalida.\n";
        return;
    }

    string practicaElegida = practicas[opcion - 1];
    cout << "\n=== MEDICOS QUE REALIZAN " << practicaElegida << " ===\n";

    vector<string> medicosDisponibles;
    for (const auto& t : turnos) {
        if (t.practica == practicaElegida && !t.ocupado) {
            if (find(medicosDisponibles.begin(), medicosDisponibles.end(), t.medico) == medicosDisponibles.end())
                medicosDisponibles.push_back(t.medico);
        }
    }

    for (size_t i = 0; i < medicosDisponibles.size(); i++) {
        string especialidad, consultorio;
        for (const auto& t : turnos)
            if (t.medico == medicosDisponibles[i]) {
                especialidad = t.especialidad;
                consultorio = t.consultorio;
                break;
            }
        cout << i + 1 << ". " << medicosDisponibles[i]
            << " (" << especialidad << ", " << consultorio << ")\n";
    }

    if (medicosDisponibles.empty()) {
        cout << "\nNo hay medicos disponibles para esa practica.\n";
        return;
    }

    cout << "\nSeleccione el numero del medico: ";
    int opcionMed;
    cin >> opcionMed;
    cin.ignore();

    if (opcionMed < 1 || opcionMed >(int)medicosDisponibles.size()) {
        cout << "Opcion invalida.\n";
        return;
    }

    string nombre = medicosDisponibles[opcionMed - 1];
    cout << "\n=== TURNOS DISPONIBLES PARA " << practicaElegida << " CON " << nombre << " ===\n";
    bool hayTurnos = false;

    for (size_t i = 0; i < turnos.size(); i++) {
        if (turnos[i].medico == nombre && turnos[i].practica == practicaElegida && !turnos[i].ocupado) {
            cout << setw(4) << i << " | " << turnos[i].dia << " " << turnos[i].hora
                << " | " << turnos[i].consultorio
                << " | " << turnos[i].especialidad << endl;
            hayTurnos = true;
        }
    }

    if (!hayTurnos) {
        cout << "\nNo hay turnos disponibles para esa practica.\n";
        return;
    }

    cout << "\nIngrese el numero del turno que desea tomar: ";
    int num;
    cin >> num;
    cin.ignore();

    if (num >= 0 && num < (int)turnos.size() && !turnos[num].ocupado &&
        turnos[num].practica == practicaElegida && turnos[num].medico == nombre) {
        turnos[num].ocupado = true;
        cout << "\nTurno tomado con exito para " << practicaElegida
            << " con " << turnos[num].medico
            << " el " << turnos[num].dia
            << " a las " << turnos[num].hora << ".\n";
    }
    else {
        cout << "\nNumero invalido o turno no disponible.\n";
    }
}

// ===== MAIN =====

int main() {
    vector<Turno> turnos;
    string archivoCSV = "turnos.csv";
    cargarTurnosDesdeCSV(turnos, archivoCSV);

    int opcion;
    do {
        cout << "\n=== SISTEMA DE TURNOS CLINICA CENTRAL ===\n";
        cout << "1. Ver especialidades\n";
        cout << "2. Ver medicos por especialidad\n";
        cout << "3. Tomar turno por especialidad\n";
        cout << "4. Tomar turno por medico\n";
        cout << "5. Tomar turno por practica\n";
        cout << "6. Cancelar turno\n";
        cout << "7. Guardar y salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: {
            vector<string> especialidades;
            for (const auto& m : medicos)
                if (find(especialidades.begin(), especialidades.end(), m.especialidad) == especialidades.end())
                    especialidades.push_back(m.especialidad);
            cout << "\n=== ESPECIALIDADES DISPONIBLES ===\n";
            for (size_t i = 0; i < especialidades.size(); i++)
                cout << i + 1 << ". " << especialidades[i] << endl;
            break;
        }
        case 2: {
            string esp = elegirEspecialidad();
            if (!esp.empty()) {
                cout << "\n=== PROFESIONALES DE " << esp << " ===\n";
                for (const auto& m : medicos)
                    if (m.especialidad == esp)
                        cout << " - " << m.nombre << " (" << m.consultorio << ")\n";
            }
            break;
        }
        case 3:
            tomarTurnoPorEspecialidad(turnos);
            break;
        case 4:
            tomarTurnoPorMedico(turnos);
            break;
        case 5:
            tomarTurnoPorPractica(turnos);
            break;
        case 6:
            cancelarTurno(turnos);
            break;
        case 7:
            guardarTurnosEnCSV(turnos, archivoCSV);
            cout << "\nSaliendo del sistema...\n";
            break;
        default:
            cout << "\nOpcion invalida.\n";
        }

    } while (opcion != 7);

    return 0;
}