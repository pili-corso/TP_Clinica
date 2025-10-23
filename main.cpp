#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "C:\Users\UsuarioHI\Downloads\rapidcsv-master\rapidcsv-master\src\rapidcsv.h"

using namespace std;

// =================== CLASE TURNO ===================

class Turno {
private:
    string especialidad;
    string practica;
    string medico;
    string consultorio;
    string dia;
    string hora;
    bool ocupado;

public:
    Turno(string e, string p, string m, string c, string d, string h, bool o = false)
        : especialidad(e), practica(p), medico(m), consultorio(c), dia(d), hora(h), ocupado(o) {
    }

    string getEspecialidad() const { return especialidad; }
    string getPractica() const { return practica; }
    string getMedico() const { return medico; }
    string getConsultorio() const { return consultorio; }
    string getDia() const { return dia; }
    string getHora() const { return hora; }
    bool estaOcupado() const { return ocupado; }

    void ocupar() { ocupado = true; }
    void liberar() { ocupado = false; }

    void mostrar(int index) const {
        cout << setw(4) << index << " | " << dia << " " << hora
            << " | " << consultorio
            << " | " << especialidad
            << " | " << practica
            << (ocupado ? " | OCUPADO" : " | DISPONIBLE") << endl;
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

    void inicializarMedicos() {
        medicos = {
            // Medico Clinico
            Medico("Dr. Lopez", "Medico Clinico", "Consultorio 1"),
            Medico("Dra. Garcia", "Medico Clinico", "Consultorio 2"),
            Medico("Dr. Castro", "Medico Clinico", "Consultorio 3"),
            Medico("Dra. Silva", "Medico Clinico", "Consultorio 4"),
            Medico("Dr. Molina", "Medico Clinico", "Consultorio 5"),

            // Cardiologo
            Medico("Dr. Fernandez", "Cardiologo", "Consultorio 6"),
            Medico("Dra. Costa", "Cardiologo", "Consultorio 7"),
            Medico("Dr. Rojas", "Cardiologo", "Consultorio 8"),
            Medico("Dra. Benitez", "Cardiologo", "Consultorio 9"),
            Medico("Dr. Herrera", "Cardiologo", "Consultorio 10"),

            // Traumatologo
            Medico("Dr. Ruiz", "Traumatologo", "Consultorio 11"),
            Medico("Dra. Soto", "Traumatologo", "Consultorio 12"),
            Medico("Dr. Aguilar", "Traumatologo", "Consultorio 13"),
            Medico("Dra. Cabrera", "Traumatologo", "Consultorio 14"),
            Medico("Dr. Lopez B.", "Traumatologo", "Consultorio 15"),

            // Obstetra
            Medico("Dra. Mendez", "Obstetra", "Consultorio 16"),
            Medico("Dr. Flores", "Obstetra", "Consultorio 17"),
            Medico("Dra. Alvarez", "Obstetra", "Consultorio 18"),
            Medico("Dr. Paredes", "Obstetra", "Consultorio 19"),
            Medico("Dra. Varela", "Obstetra", "Consultorio 20"),

            // Pediatra
            Medico("Dr. Torres", "Pediatra", "Consultorio 21"),
            Medico("Dra. Sanchez", "Pediatra", "Consultorio 22"),
            Medico("Dr. Gutierrez", "Pediatra", "Consultorio 23"),
            Medico("Dra. Cabrera", "Pediatra", "Consultorio 24"),
            Medico("Dr. Ramos", "Pediatra", "Consultorio 25"),

            // Dermatologo
            Medico("Dra. Diaz", "Dermatologo", "Consultorio 26"),
            Medico("Dr. Perez", "Dermatologo", "Consultorio 27"),
            Medico("Dra. Torres", "Dermatologo", "Consultorio 28"),
            Medico("Dr. Medina", "Dermatologo", "Consultorio 29"),
            Medico("Dra. Castro", "Dermatologo", "Consultorio 30"),

            // Oftalmologo
            Medico("Dr. Suarez", "Oftalmologo", "Consultorio 31"),
            Medico("Dra. Lopez A.", "Oftalmologo", "Consultorio 32"),
            Medico("Dr. Fernandez R.", "Oftalmologo", "Consultorio 33"),
            Medico("Dra. Rivas", "Oftalmologo", "Consultorio 34"),
            Medico("Dr. Meza", "Oftalmologo", "Consultorio 35"),

            // Gastroenterologo
            Medico("Dr. Bravo", "Gastroenterologo", "Consultorio 36"),
            Medico("Dra. Alonso", "Gastroenterologo", "Consultorio 37"),
            Medico("Dr. Cabrera", "Gastroenterologo", "Consultorio 38"),
            Medico("Dra. Flores M.", "Gastroenterologo", "Consultorio 39"),
            Medico("Dr. Ruiz C.", "Gastroenterologo", "Consultorio 40")
        };
    }

    void crearAgendaBase() {
        vector<string> horas = { "09:00","10:00","11:00","12:00","13:00","14:00","15:00","16:00","17:00" };
        vector<string> dias = { "Lunes","Martes","Miercoles","Jueves","Viernes" };
        for (const auto& med : medicos) {
            vector<string> practicas;
            if (med.getEspecialidad() == "Cardiologo")
                practicas = { "Consulta", "Electrocardiograma", "Ecocardiograma" };
            else if (med.getEspecialidad() == "Traumatologo")
                practicas = { "Consulta", "Control de yeso", "Curacion" };
            else if (med.getEspecialidad() == "Obstetra")
                practicas = { "Consulta", "Ecografia", "Control prenatal" };
            else if (med.getEspecialidad() == "Pediatra")
                practicas = { "Consulta", "Vacunacion", "Control de nino sano" };
            else if (med.getEspecialidad() == "Dermatologo")
                practicas = { "Consulta", "Peeling", "Crioterapia" };
            else if (med.getEspecialidad() == "Oftalmologo")
                practicas = { "Consulta", "Control visual", "Fondo de ojo" };
            else if (med.getEspecialidad() == "Gastroenterologo")
                practicas = { "Consulta", "Endoscopia", "Control post-tratamiento" };
            else
                practicas = { "Consulta" };

            for (auto& d : dias)
                for (auto& h : horas)
                    for (auto& p : practicas)
                        turnos.emplace_back(med.getEspecialidad(), p, med.getNombre(),
                            med.getConsultorio(), d, h, false);
        }
    }

    void guardarTurnosEnCSV() {
        vector<string> dias, horas, consultorios, medicosCol, especialidadesCol, practicasCol, estados;
        for (const auto& t : turnos) {
            dias.push_back(t.getDia());
            horas.push_back(t.getHora());
            consultorios.push_back(t.getConsultorio());
            medicosCol.push_back(t.getMedico());
            especialidadesCol.push_back(t.getEspecialidad());
            practicasCol.push_back(t.getPractica());
            estados.push_back(t.estaOcupado() ? "OCUPADO" : "DISPONIBLE");
        }

        rapidcsv::Document doc("", rapidcsv::LabelParams(-1, -1));
        doc.SetColumn<string>(0, dias);
        doc.SetColumn<string>(1, horas);
        doc.SetColumn<string>(2, consultorios);
        doc.SetColumn<string>(3, medicosCol);
        doc.SetColumn<string>(4, especialidadesCol);
        doc.SetColumn<string>(5, practicasCol);
        doc.SetColumn<string>(6, estados);
        doc.Save(archivoCSV);
        cout << "\nArchivo CSV actualizado correctamente.\n";
    }

    void cargarTurnosDesdeCSV() {
        try {
            rapidcsv::Document doc(archivoCSV, rapidcsv::LabelParams(-1, -1));
            int filas = doc.GetRowCount();
            for (int i = 0; i < filas; i++) {
                string d = doc.GetCell<string>(0, i);
                string h = doc.GetCell<string>(1, i);
                string c = doc.GetCell<string>(2, i);
                string m = doc.GetCell<string>(3, i);
                string e = doc.GetCell<string>(4, i);
                string p = doc.GetCell<string>(5, i);
                string estado = doc.GetCell<string>(6, i);
                bool o = (estado == "OCUPADO");
                turnos.emplace_back(e, p, m, c, d, h, o);
            }
            cout << "\nTurnos cargados desde CSV correctamente.\n";
        }
        catch (...) {
            cout << "\nNo se encontro el archivo CSV. Se creara la agenda completa.\n";
            crearAgendaBase();
            guardarTurnosEnCSV();
        }
    }

    // =================== FUNCIONES DE MENU ===================

    void mostrarEspecialidades() const {
        vector<string> especialidades;
        for (const auto& m : medicos)
            if (find(especialidades.begin(), especialidades.end(), m.getEspecialidad()) == especialidades.end())
                especialidades.push_back(m.getEspecialidad());

        cout << "\n=== ESPECIALIDADES DISPONIBLES ===\n";
        for (size_t i = 0; i < especialidades.size(); i++)
            cout << i + 1 << ". " << especialidades[i] << endl;
    }

    void mostrarMedicosPorEspecialidad() const {
        mostrarEspecialidades();
        cout << "\nSeleccione el numero de la especialidad: ";
        int op; cin >> op; cin.ignore();

        vector<string> especialidades;
        for (const auto& m : medicos)
            if (find(especialidades.begin(), especialidades.end(), m.getEspecialidad()) == especialidades.end())
                especialidades.push_back(m.getEspecialidad());
        if (op < 1 || op >(int)especialidades.size()) return;

        string esp = especialidades[op - 1];
        cout << "\n=== PROFESIONALES DE " << esp << " ===\n";
        for (const auto& m : medicos)
            if (m.getEspecialidad() == esp)
                cout << " - " << m.getNombre() << " (" << m.getConsultorio() << ")\n";
    }

    void menuPrincipal() {
        int opcion;
        do {
            cout << "\n=== SISTEMA DE TURNOS CLINICA CENTRAL ===\n";
            cout << "1. Ver especialidades\n";
            cout << "2. Ver medicos por especialidad\n";
            cout << "3. Guardar y salir\n";
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            cin.ignore();

            switch (opcion) {
            case 1:
                mostrarEspecialidades();
                break;
            case 2:
                mostrarMedicosPorEspecialidad();
                break;
            case 3:
                guardarTurnosEnCSV();
                cout << "\nSaliendo del sistema...\n";
                break;
            default:
                cout << "\nOpcion invalida.\n";
            }

        } while (opcion != 3);
    }
};

// =================== MAIN ===================

int main() {
    Clinica clinica;
    clinica.menuPrincipal();
    return 0;
}