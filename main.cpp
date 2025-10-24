#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "C:\Users\Pili\Downloads\rapidcsv-master\rapidcsv-master\src\rapidcsv.h"
using namespace std;

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
    string archivoCSV = "turnos.csv";

public:
    Clinica() {
        inicializarMedicos();
        cargarTurnosDesdeCSV();
    }

    // ---------- Inicializar médicos y crear turnos ----------
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
                practicas = { "Consulta general", "Control anual" };
            else if (m.getEspecialidad() == "Cardiologo")
                practicas = { "Consulta", "Electrocardiograma" };
            else if (m.getEspecialidad() == "Traumatologo")
                practicas = { "Consulta", "Control de yeso" };
            else if (m.getEspecialidad() == "Obstetra")
                practicas = { "Consulta", "Ecografia obstetrica", "Control prenatal" };
            else if (m.getEspecialidad() == "Pediatra")
                practicas = { "Consulta", "Vacunacion" };
            else if (m.getEspecialidad() == "Dermatologo")
                practicas = { "Consulta", "Control de tratamiento" };
            else if (m.getEspecialidad() == "Oftalmologo")
                practicas = { "Consulta", "Fondo de ojo" };
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

    // ---------- Guardar / Cargar CSV ----------
    void guardarTurnosEnCSV() {
        vector<string> med, esp, cons, dia, hora, prac, estado;

        for (const auto& t : turnos) {
            med.push_back(t.getMedico());
            esp.push_back(t.getEspecialidad());
            cons.push_back(t.getConsultorio());
            dia.push_back(t.getDia());
            hora.push_back(t.getHora());
            prac.push_back(t.getPractica());
            estado.push_back(t.estaOcupado() ? "OCUPADO" : "DISPONIBLE");
        }

        rapidcsv::Document doc("", rapidcsv::LabelParams(-1, -1));
        doc.SetColumn<string>(0, med);
        doc.SetColumn<string>(1, esp);
        doc.SetColumn<string>(2, cons);
        doc.SetColumn<string>(3, dia);
        doc.SetColumn<string>(4, hora);
        doc.SetColumn<string>(5, prac);
        doc.SetColumn<string>(6, estado);
        doc.Save(archivoCSV);
    }

    void cargarTurnosDesdeCSV() {
        try {
            rapidcsv::Document doc(archivoCSV, rapidcsv::LabelParams(-1, -1));
            int filas = doc.GetRowCount();
            for (int i = 0; i < filas; i++) {
                string m = doc.GetCell<string>(0, i);
                string e = doc.GetCell<string>(1, i);
                string c = doc.GetCell<string>(2, i);
                string d = doc.GetCell<string>(3, i);
                string h = doc.GetCell<string>(4, i);
                string p = doc.GetCell<string>(5, i);
                string est = doc.GetCell<string>(6, i);
                bool o = (est == "OCUPADO");
                turnos.emplace_back(m, e, c, d, h, p, o);
            }
        }
        catch (...) {
            guardarTurnosEnCSV();
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

    }

    // ---------- Tomar turno por práctica ----------
    void tomarTurnoPorPractica() {
        vector<string> practicas;
        for (const auto& t : turnos)
            if (find(practicas.begin(), practicas.end(), t.getPractica()) == practicas.end())
                practicas.push_back(t.getPractica());

        cout << "\n=== PRACTICAS DISPONIBLES ===\n";
        for (size_t i = 0; i < practicas.size(); i++)
            cout << i + 1 << ". " << practicas[i] << endl;

        cout << "\nSeleccione el numero de la practica: ";
        int opp; cin >> opp; cin.ignore();
        if (opp < 1 || opp >(int)practicas.size()) return;

        string practicaElegida = practicas[opp - 1];
        vector<string> medDisp;
        for (const auto& t : turnos)
            if (t.getPractica() == practicaElegida && !t.estaOcupado()
                && find(medDisp.begin(), medDisp.end(), t.getMedico()) == medDisp.end())
                medDisp.push_back(t.getMedico());

        cout << "\n=== MEDICOS QUE REALIZAN " << practicaElegida << " ===\n";
        for (size_t i = 0; i < medDisp.size(); i++)
            cout << i + 1 << ". " << medDisp[i] << endl;

        cout << "\nSeleccione el numero del medico: ";
        int opm; cin >> opm; cin.ignore();
        if (opm < 1 || opm >(int)medDisp.size()) return;
        string elegido = medDisp[opm - 1];

        cout << "\n=== TURNOS DISPONIBLES DE " << elegido << " ===\n";
        vector<int> disp;
        for (int i = 0; i < (int)turnos.size(); i++)
            if (turnos[i].getMedico() == elegido && turnos[i].getPractica() == practicaElegida && !turnos[i].estaOcupado()) {
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
        cout << "Practica: " << turnos[num].getPractica() << endl;
        cout << "Profesional: " << turnos[num].getMedico()
            << " (" << turnos[num].getEspecialidad() << ")\n";
        cout << "Dia: " << turnos[num].getDia()
            << " - Hora: " << turnos[num].getHora() << "\n";
        cout << "Consultorio: " << turnos[num].getConsultorio() << endl;
        cout << "\nTurno reservado correctamente.\n";
    }

    // ---------- Cancelar turno ----------
    void cancelarTurno() {
        cout << "\n=== TURNOS OCUPADOS ===\n";
        vector<int> ocup;
        for (int i = 0; i < (int)turnos.size(); i++)
            if (turnos[i].estaOcupado()) {
                turnos[i].mostrar(i);
                ocup.push_back(i);
            }
        if (ocup.empty()) { cout << "No hay turnos ocupados.\n"; return; }

        cout << "\nIngrese el numero del turno a cancelar: ";
        int num; cin >> num; cin.ignore();
        if (find(ocup.begin(), ocup.end(), num) == ocup.end()) { cout << "Numero invalido.\n"; return; }

        turnos[num].liberar();
        cout << "\nTurno cancelado correctamente.\n";
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
            cout << "6. Guardar y salir\n";
            cout << "Seleccione una opcion: ";
            cin >> op; cin.ignore();

            switch (op) {
            case 1: mostrarEspecialidades(); break;
            case 2: tomarTurnoPorMedico(); break;
            case 3: tomarTurnoPorEspecialidad(); break;
            case 4: tomarTurnoPorPractica(); break;
            case 5: cancelarTurno(); break;
            case 6: guardarTurnosEnCSV(); cout << "\nSaliendo del sistema...\n"; break;
            default: cout << "\nOpcion invalida.\n";
            }
        } while (op != 5);
    }
};

// =================== MAIN ===================
int main() {
    Clinica c;
    c.menuPrincipal();
    return 0;
}