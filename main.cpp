#include <iostream> //Para entrada/salida
#include <string> //Para manejo de texto
#include <vector> //Para usar listas dinámicas
#include <iomanip> //Para el formato de salida/impresion
#include <algorithm> //Para funciones de busqueda y ordenamiento
#include "C:\Users\Pili\Downloads\rapidcsv-master\rapidcsv-master\src\rapidcsv.h"

using namespace std;


// =================== CLASE PACIENTE ===================
class Paciente {
private:
    string nombre, apellido, dni, obraSocial;

public:
    Paciente() {}
    Paciente(string n, string a, string d, string o)
        : nombre(n), apellido(a), dni(d), obraSocial(o) {
    }

    string getResumen() const {
        return nombre + " " + apellido + " (DNI: " + dni + ", OS: " + obraSocial + ")";
    }
};

// =================== CLASE TURNO ===================
class Turno {
private:
    string medico;
    string especialidad;
    string consultorio;
    string dia;
    string hora;
    string practica;
    bool ocupado;
    Paciente paciente;

public:
    Turno(string m, string e, string c, string d, string h, string p = "", bool o = false)
        : medico(m), especialidad(e), consultorio(c), dia(d), hora(h), practica(p), ocupado(o) {
    }

    string getMedico() const { return medico; }
    string getEspecialidad() const { return especialidad; }
    string getConsultorio() const { return consultorio; }
    string getDia() const { return dia; }
    string getHora() const { return hora; }
    string getPractica() const { return practica; }
    bool estaOcupado() const { return ocupado; }

    void asignarPaciente(const Paciente& p) { paciente = p; ocupado = true; }
    void liberar() { ocupado = false; }

    void mostrar(int i) const {
        cout << setw(4) << i << " | " << dia << " " << hora
            << " | " << consultorio
            << " | " << especialidad
            << " | " << (practica.empty() ? "-" : practica)
            << " | " << (ocupado ? "OCUPADO" : "DISPONIBLE");
        if (ocupado) cout << " | " << paciente.getResumen();
        cout << endl;
    }
    // Devuelve el resumen del paciente si el turno está ocupado, o "-" si está libre
    string getPacienteResumen() const {
        if (estaOcupado())
            return paciente.getResumen();
        else
            return "-";
    }
    // Cargo un resumen de paciente desde el CSV (solo texto, no datos reales)
    void setPacienteResumen(const string& resumen) {
        if (resumen != "-")
            paciente = Paciente(resumen, "", "", ""); // Creo un paciente con el resumen como nombre
    }
};

// =================== CLASE MEDICO ===================
class Medico {
private:
    string nombre;
    string especialidad;
    string consultorio;

public:
    Medico(string n, string e, string c)
        : nombre(n), especialidad(e), consultorio(c) {
    }

    string getNombre() const { return nombre; }
    string getEspecialidad() const { return especialidad; }
    string getConsultorio() const { return consultorio; }
};

// =================== CLASE CLINICA ===================
class Clinica {
private:
    vector<Medico> medicos;
    vector<Turno> turnos;
    string archivoCSV = "turnos.csv"; //defino el nombre (y ruta) del archivo CSV

public:
    // ---------- Constructor ----------
    Clinica() {
        // Verifico si el archivo existe antes de intentar cargarlo
        ifstream fileCheck(archivoCSV);
        if (fileCheck.good()) {
            cargarTurnosDesdeCSV();
            cout << "\nArchivo existente cargado correctamente.\n";
        }
        else {
            cout << "\nArchivo CSV no encontrado. Creando uno nuevo...\n";
            inicializarMedicos();
            guardarTurnosEnCSV();
            cout << "Archivo base creado correctamente.\n";
        }
    }


    // ---------- Inicializo médicos y creo turnos ----------
    void inicializarMedicos() {
        medicos = {
            // Medico Clinico
            Medico("Dr. Lopez Marcos", "Medico Clinico", "Consultorio 1"),
            Medico("Dra. Garcia Luna", "Medico Clinico", "Consultorio 2"),
            Medico("Dr. Castro Miguel", "Medico Clinico", "Consultorio 3"),
            Medico("Dra. Silva Lucrecia", "Medico Clinico", "Consultorio 4"),
            Medico("Dr. Molina Ricardo", "Medico Clinico", "Consultorio 5"),

            // Cardiologo
            Medico("Dr. Fernandez Francisco", "Cardiologo", "Consultorio 6"),
            Medico("Dra. Costa Silvia", "Cardiologo", "Consultorio 7"),
            Medico("Dr. Rojas Mauro", "Cardiologo", "Consultorio 8"),
            Medico("Dra. Benitez Clara", "Cardiologo", "Consultorio 9"),
            Medico("Dr. Herrera Lucas", "Cardiologo", "Consultorio 10"),

            // Traumatologo
            Medico("Dr. Ruiz Ezequiel", "Traumatologo", "Consultorio 11"),
            Medico("Dra. Soto Ludmila", "Traumatologo", "Consultorio 12"),
            Medico("Dr. Aguilar Maximiliano", "Traumatologo", "Consultorio 13"),
            Medico("Dra. Cabrera Macarena", "Traumatologo", "Consultorio 14"),
            Medico("Dr. Sequeiros Pablo", "Traumatologo", "Consultorio 15"),

            // Obstetra
            Medico("Dra. Mendez Agustina", "Obstetra", "Consultorio 16"),
            Medico("Dr. Flores Ramiro", "Obstetra", "Consultorio 17"),
            Medico("Dra. Alvarez Carolina", "Obstetra", "Consultorio 18"),
            Medico("Dr. Peralta Diego", "Obstetra", "Consultorio 19"),
            Medico("Dra. Varela Silvina", "Obstetra", "Consultorio 20"),

            // Pediatra
            Medico("Dr. Torres Juan", "Pediatra", "Consultorio 21"),
            Medico("Dra. Sanchez Laura", "Pediatra", "Consultorio 22"),
            Medico("Dr. Gutierrez Maximo", "Pediatra", "Consultorio 23"),
            Medico("Dra. Cabrera Lara", "Pediatra", "Consultorio 24"),
            Medico("Dr. Ramos Pablo", "Pediatra", "Consultorio 25"),

            // Dermatologo
            Medico("Dra. Diaz Vera", "Dermatologo", "Consultorio 26"),
            Medico("Dr. Perez Julian", "Dermatologo", "Consultorio 27"),
            Medico("Dra. Torres Paz", "Dermatologo", "Consultorio 28"),
            Medico("Dr. Medina Tomas", "Dermatologo", "Consultorio 29"),
            Medico("Dra. Castro Julieta", "Dermatologo", "Consultorio 30"),

            // Oftalmologo
            Medico("Dr. Suarez Enrique", "Oftalmologo", "Consultorio 31"),
            Medico("Dra. Lopez Andrea", "Oftalmologo", "Consultorio 32"),
            Medico("Dr. Fernandez Nicolas", "Oftalmologo", "Consultorio 33"),
            Medico("Dra. Rivas Karina", "Oftalmologo", "Consultorio 34"),
            Medico("Dr. Meza Damian", "Oftalmologo", "Consultorio 35"),

            // Gastroenterologo
            Medico("Dr. Casanova Saul", "Gastroenterologo", "Consultorio 36"),
            Medico("Dra. Alonso Cristina", "Gastroenterologo", "Consultorio 37"),
            Medico("Dr. Cabrera Luis", "Gastroenterologo", "Consultorio 38"),
            Medico("Dra. Coellar Eduarda", "Gastroenterologo", "Consultorio 39"),
            Medico("Dr. Ruiz Pedro", "Gastroenterologo", "Consultorio 40")
        };

        vector<string> dias = { "Lunes", "Martes", "Miercoles", "Jueves", "Viernes" };
        vector<string> horas = { "09:00","10:00","11:00","12:00","13:00","14:00","15:00","16:00","17:00" };

        for (const auto& m : medicos) {
            vector<string> practicas;
            if (m.getEspecialidad() == "Medico Clinico")
                practicas = { "Consulta", "Control anual Medico Clinico", "Vacunacion mayores de edad"};
            else if (m.getEspecialidad() == "Cardiologo")
                practicas = { "Consulta", "Electrocardiograma" };
            else if (m.getEspecialidad() == "Traumatologo")
                practicas = { "Consulta", "Control de yeso" };
            else if (m.getEspecialidad() == "Obstetra")
                practicas = { "Consulta", "Ecografia obstetrica", "Control prenatal" };
            else if (m.getEspecialidad() == "Pediatra")
                practicas = { "Consulta", "Vacunacion menores de edad" };
            else if (m.getEspecialidad() == "Dermatologo")
                practicas = { "Consulta", "Tratamiento lunares" };
            else if (m.getEspecialidad() == "Oftalmologo")
                practicas = { "Consulta", "Fondo de ojos" };
            else if (m.getEspecialidad() == "Gastroenterologo")
                practicas = { "Consulta", "Endoscopia" };
            else
                practicas = { "Consulta" };

            for (const auto& d : dias)
                for (const auto& h : horas)
                    for (const auto& p : practicas)
                        turnos.push_back(Turno(m.getNombre(), m.getEspecialidad(), m.getConsultorio(), d, h, p, false));
        }
    }

    // ---------- Guardar los turnos en CSV ----------
    void guardarTurnosEnCSV() {
        ofstream archivo(archivoCSV, ios::trunc); //Reescribe todo el archivo desde cero
        if (!archivo.is_open()) {
            cerr << "Error al abrir el archivo para guardar.\n";
            return;
        }

        // Escribo la línea de encabezados (opcional, visible en Excel)
        archivo << "Medico;Especialidad;Consultorio;Dia;Hora;Practica;Estado;Paciente\n";

        // Escribo cada turno en una línea
        for (const auto& t : turnos) {
            archivo << t.getMedico() << ";"
                << t.getEspecialidad() << ";"
                << t.getConsultorio() << ";"
                << t.getDia() << ";"
                << t.getHora() << ";"
                << t.getPractica() << ";"
                << (t.estaOcupado() ? "OCUPADO" : "DISPONIBLE") << ";"
                << t.getPacienteResumen() << "\n";
        }

        archivo.close();
        cout << "\nArchivo CSV actualizado correctamente.\n";
    }

    // ---------- Cargar turnos desde CSV ----------
    void cargarTurnosDesdeCSV() {
        try {
            rapidcsv::Document doc(
                archivoCSV,
                rapidcsv::LabelParams(-1, -1),    //SIN encabezados
                rapidcsv::SeparatorParams(';')
            );

            int filas = doc.GetRowCount();
            turnos.clear();

            for (int i = 0; i < filas; i++) {
                string m = doc.GetCell<string>(0, i); // Médico
                string e = doc.GetCell<string>(1, i); // Especialidad
                string c = doc.GetCell<string>(2, i); // Consultorio
                string d = doc.GetCell<string>(3, i); // Día
                string h = doc.GetCell<string>(4, i); // Hora
                string p = doc.GetCell<string>(5, i); // Práctica
                string est = doc.GetCell<string>(6, i); // Estado
                string resumenPaciente = doc.GetCell<string>(7, i); // Paciente

                bool ocupado = (est == "OCUPADO");
                Turno turno(m, e, c, d, h, p, ocupado);
                if (ocupado && resumenPaciente != "-")
                    turno.setPacienteResumen(resumenPaciente);

                turnos.push_back(turno);
            }

            cout << "\nTurnos cargados correctamente desde '" << archivoCSV << "'.\n";
        }
        catch (exception& ex) {
            cerr << "\nError al leer el archivo CSV: " << ex.what() << endl;
        }
    }

    // ---------- Mostrar especialidades ----------
    void mostrarEspecialidades() const {
        vector<string> esp;
        for (const auto& m : medicos)
            if (find(esp.begin(), esp.end(), m.getEspecialidad()) == esp.end())
                esp.push_back(m.getEspecialidad());

        cout << "\n=== ESPECIALIDADES DISPONIBLES ===\n";
        for (size_t i = 0; i < esp.size(); i++)
            cout << i + 1 << ". " << esp[i] << endl;
    }

    // ---------- Tomar turno por medico ----------
    void tomarTurnoPorMedico() {
        cout << "\n=== SELECCIONE UN MEDICO ===\n";
        for (size_t i = 0; i < medicos.size(); i++)
            cout << setw(2) << i + 1 << ". " << medicos[i].getNombre()
            << " (" << medicos[i].getEspecialidad() << ")\n";

        cout << "\nNumero del medico: ";
        int opm;
        cin >> opm;
        cin.ignore();

        if (opm < 1 || opm >(int)medicos.size()) {
            cout << "\nNumero invalido.\n";
            return;
        }

        string elegido = medicos[opm - 1].getNombre();

        cout << "\n=== TURNOS DISPONIBLES DE " << elegido << " ===\n";
        vector<int> disponibles;
        for (int i = 0; i < (int)turnos.size(); i++) {
            if (turnos[i].getMedico() == elegido && !turnos[i].estaOcupado()) {
                turnos[i].mostrar(i);
                disponibles.push_back(i);
            }
        }

        if (disponibles.empty()) {
            cout << "\nNo hay turnos disponibles para este medico.\n";
            return;
        }

        cout << "\nIngrese el numero del turno a tomar: ";
        int num;
        cin >> num;
        cin.ignore();

        if (find(disponibles.begin(), disponibles.end(), num) == disponibles.end()) {
            cout << "\nNumero de turno invalido.\n";
            return;
        }

        // Datos del paciente
        string nombre, apellido, dni, obraSocial;
        cout << "\nIngrese los datos del paciente:\n";
        cout << "Nombre: ";
        getline(cin, nombre);
        cout << "Apellido: ";
        getline(cin, apellido);
        cout << "DNI: ";
        getline(cin, dni);
        cout << "Obra social: ";
        getline(cin, obraSocial);

        Paciente p(nombre, apellido, dni, obraSocial);
        turnos[num].asignarPaciente(p);

        cout << "\nTurno reservado con exito!\n";
        cout << "Paciente: " << p.getResumen() << endl;
        cout << "Profesional: " << turnos[num].getMedico()
            << " (" << turnos[num].getEspecialidad() << ")\n";
        cout << "Dia: " << turnos[num].getDia()
            << " - Hora: " << turnos[num].getHora() << "\n";
        cout << "Consultorio: " << turnos[num].getConsultorio() << endl;
        guardarTurnosEnCSV();
    }


    // ---------- Tomar turno por especialidad ----------
    void tomarTurnoPorEspecialidad() {
        mostrarEspecialidades();
        cout << "\nSeleccione el numero de la especialidad: ";
        int op; cin >> op; cin.ignore();

        vector<string> esp;
        for (const auto& m : medicos)
            if (find(esp.begin(), esp.end(), m.getEspecialidad()) == esp.end())
                esp.push_back(m.getEspecialidad());

        if (op < 1 || op >(int)esp.size()) return;
        string e = esp[op - 1];

        cout << "\n=== MEDICOS DE " << e << " ===\n";
        vector<string> medEsp;
        for (const auto& m : medicos)
            if (m.getEspecialidad() == e)
                medEsp.push_back(m.getNombre());

        for (size_t i = 0; i < medEsp.size(); i++)
            cout << i + 1 << ". " << medEsp[i] << endl;

        cout << "\nSeleccione el numero del medico: ";
        int opm; cin >> opm; cin.ignore();

        if (opm < 1 || opm >(int)medEsp.size()) return;
        string elegido = medEsp[opm - 1];

        cout << "\n=== TURNOS DISPONIBLES DE " << elegido << " ===\n";
        vector<int> disp;
        for (int i = 0; i < (int)turnos.size(); i++)
            if (turnos[i].getMedico() == elegido && !turnos[i].estaOcupado()) {
                turnos[i].mostrar(i);
                disp.push_back(i);
            }

        if (disp.empty()) { cout << "No hay turnos disponibles.\n"; return; }

        cout << "\nIngrese el numero del turno: ";
        int num; cin >> num; cin.ignore();

        if (find(disp.begin(), disp.end(), num) == disp.end()) { cout << "Numero invalido.\n"; return; }

        string n, a, d, o;
        cout << "\nIngrese los datos del paciente:\n";
        cout << "\nNombre: "; getline(cin, n);
        cout << "Apellido: "; getline(cin, a);
        cout << "DNI: "; getline(cin, d);
        cout << "Obra social: "; getline(cin, o);

        Paciente p(n, a, d, o);
        turnos[num].asignarPaciente(p);
        cout << "\nTurno reservado con exito!\n";
        cout << "Paciente: " << p.getResumen() << endl;
        cout << "Profesional: " << turnos[num].getMedico()
            << " (" << turnos[num].getEspecialidad() << ")\n";
        cout << "Dia: " << turnos[num].getDia()
            << " - Hora: " << turnos[num].getHora() << "\n";
        cout << "Consultorio: " << turnos[num].getConsultorio() << endl;
        guardarTurnosEnCSV();

    }

    // ---------- Tomar turno por práctica ----------
    void tomarTurnoPorPractica() {
        vector<string> practicas;

        // Cargo prácticas únicas, excluyendo "Consulta"
        for (const auto& t : turnos) {
            string pract = t.getPractica();
            if (pract == "Consulta") continue; //ignorar "Consulta"

            if (find(practicas.begin(), practicas.end(), pract) == practicas.end())
                practicas.push_back(pract);
        }

        if (practicas.empty()) {
            cout << "\nNo hay practicas disponibles en este momento.\n";
            return;
        }

        cout << "\n=== PRACTICAS DISPONIBLES ===\n";
        for (size_t i = 0; i < practicas.size(); i++)
            cout << i + 1 << ". " << practicas[i] << endl;

        cout << "\nSeleccione el numero de la practica: ";
        int opp;
        cin >> opp;
        cin.ignore();
        if (opp < 1 || opp >(int)practicas.size()) return;

        string practicaElegida = practicas[opp - 1];

        // Médicos disponibles para esa práctica
        vector<string> medDisp;
        for (const auto& t : turnos)
            if (t.getPractica() == practicaElegida && !t.estaOcupado()
                && find(medDisp.begin(), medDisp.end(), t.getMedico()) == medDisp.end())
                medDisp.push_back(t.getMedico());

        if (medDisp.empty()) {
            cout << "\nNo hay medicos disponibles para esta practica.\n";
            return;
        }

        cout << "\n=== MEDICOS QUE REALIZAN " << practicaElegida << " ===\n";
        for (size_t i = 0; i < medDisp.size(); i++)
            cout << i + 1 << ". " << medDisp[i] << endl;

        cout << "\nSeleccione el numero del medico: ";
        int opm;
        cin >> opm;
        cin.ignore();
        if (opm < 1 || opm >(int)medDisp.size()) return;

        string elegido = medDisp[opm - 1];

        cout << "\n=== TURNOS DISPONIBLES DE " << elegido << " ===\n";
        vector<int> disp;
        for (int i = 0; i < (int)turnos.size(); i++)
            if (turnos[i].getMedico() == elegido && turnos[i].getPractica() == practicaElegida && !turnos[i].estaOcupado()) {
                turnos[i].mostrar(i);
                disp.push_back(i);
            }

        if (disp.empty()) {
            cout << "No hay turnos disponibles.\n";
            return;
        }

        cout << "\nIngrese el numero del turno: ";
        int num;
        cin >> num;
        cin.ignore();

        if (find(disp.begin(), disp.end(), num) == disp.end()) {
            cout << "Numero invalido.\n";
            return;
        }

        // Datos del paciente
        string n, a, d, o;
        cout << "\nIngrese los datos del paciente:\n";
        cout << "Nombre: "; getline(cin, n);
        cout << "Apellido: "; getline(cin, a);
        cout << "DNI: "; getline(cin, d);
        cout << "Obra social: "; getline(cin, o);

        Paciente p(n, a, d, o);
        turnos[num].asignarPaciente(p);

        cout << "\nTurno reservado con exito!\n";
        cout << "Paciente: " << p.getResumen() << endl;
        cout << "Profesional: " << turnos[num].getMedico()
            << " (" << turnos[num].getEspecialidad() << ")\n";
        cout << "Dia: " << turnos[num].getDia()
            << " - Hora: " << turnos[num].getHora() << "\n";
        cout << "Consultorio: " << turnos[num].getConsultorio() << endl;
        guardarTurnosEnCSV();
    }

   // ---------- Cancelar turno ----------
    void cancelarTurno() {
        cout << "\n=== CANCELAR TURNO ===\n";
        string nombre, apellido;
        cout << "Ingrese el nombre del paciente: ";
        getline(cin, nombre);
        cout << "Ingrese el apellido del paciente: ";
        getline(cin, apellido);

        string buscado = nombre + " " + apellido;
        vector<int> turnosPaciente;

        cout << "\n=== TURNOS RESERVADOS DE " << buscado << " ===\n";
        for (int i = 0; i < (int)turnos.size(); i++) {
            // Busco los turnos donde figure este paciente
            if (turnos[i].estaOcupado() && turnos[i].getPacienteResumen().find(buscado) != string::npos) {
                cout << setw(3) << i << " | " << turnos[i].getDia() << " " << turnos[i].getHora()
                    << " | " << turnos[i].getMedico() << " (" << turnos[i].getEspecialidad() << ")"
                    << " | " << turnos[i].getPractica()
                    << " | " << turnos[i].getConsultorio() << endl;
                turnosPaciente.push_back(i);
            }
        }

        if (turnosPaciente.empty()) {
            cout << "\nNo se encontraron turnos registrados para " << buscado << ".\n";
            return;
        }

        cout << "\nIngrese el numero del turno que desea cancelar: ";
        int num;
        cin >> num;
        cin.ignore();

        // Verificar que el número sea válido
        if (find(turnosPaciente.begin(), turnosPaciente.end(), num) == turnosPaciente.end()) {
            cout << "\nNumero invalido o ese turno no pertenece a este paciente.\n";
            return;
        }

        // Confirmación
        cout << "\n¿Confirma que desea cancelar este turno? (s/n): ";
        char conf;
        cin >> conf;
        cin.ignore();

        if (conf == 's' || conf == 'S') {
            turnos[num].liberar();
            guardarTurnosEnCSV();
            cout << "\nTurno cancelado correctamente.\n";
        }
        else {
            cout << "\nOperacion cancelada.\n";
        }
    }


    // ---------- Ver turnos del paciente ----------
    void verTurnosDePaciente() {
        string nombre, apellido;
        cout << "\n=== CONSULTAR TURNOS DEL PACIENTE ===\n";
        cout << "Nombre del paciente: ";
        getline(cin, nombre);
        cout << "Apellido del paciente: ";
        getline(cin, apellido);

        string buscado = nombre + " " + apellido;

        bool encontrado = false;
        cout << "\n=== TURNOS RESERVADOS DE " << buscado << " ===\n";

        for (const auto& t : turnos) {
            // Compara el nombre y apellido dentro del resumen del paciente
            if (t.getPacienteResumen().find(buscado) != string::npos && t.estaOcupado()) {
                cout << "Profesional: " << t.getMedico()
                    << " (" << t.getEspecialidad() << ")\n";
                cout << "Practica: " << t.getPractica() << endl;
                cout << "Dia: " << t.getDia()
                    << " - Hora: " << t.getHora() << endl;
                cout << "Consultorio: " << t.getConsultorio() << endl;
                cout << "----------------------------------------\n";
                encontrado = true;
            }
        }

        if (!encontrado)
            cout << "\nNo se encontraron turnos registrados para " << buscado << ".\n";
    }

    // ---------- Menú principal ----------
    void menuPrincipal() {
        int op;
        do {
            cout << "\n=== SISTEMA DE TURNOS CLINICA MAIPU ===\n";
            cout << "1. Ver especialidades\n";
            cout << "2. Tomar turno por medico\n";
            cout << "3. Tomar turno por especialidad\n";
            cout << "4. Tomar turno por practica\n";
            cout << "5. Cancelar turno\n";
            cout << "6. Ver mis turnos\n";
            cout << "7. Guardar y salir\n";
            cout << "Seleccione una opcion: ";
            cin >> op; cin.ignore();

            switch (op) {
            case 1: mostrarEspecialidades(); break;
            case 2: tomarTurnoPorMedico(); break;
            case 3: tomarTurnoPorEspecialidad(); break;
            case 4: tomarTurnoPorPractica(); break;
            case 5: cancelarTurno(); break;
            case 6: verTurnosDePaciente(); break;
            case 7: guardarTurnosEnCSV(); cout << "\nSaliendo del sistema...\n"; break;
            default: cout << "\nOpcion invalida.\n";
            }
        } while (op != 7);
    }
};

// =================== MAIN ===================
int main() {
    Clinica c;
    c.menuPrincipal();
    return 0;
}