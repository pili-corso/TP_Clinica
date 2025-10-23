#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
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

        // === Asignar practicas y crear turnos ===
        vector<string> dias = { "Lunes", "Martes", "Miercoles", "Jueves", "Viernes" };
        vector<string> horas = { "09:00","10:00","11:00","12:00","13:00","14:00","15:00","16:00","17:00" };

        for (auto& m : medicos) {
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
                practicas = { "Consulta", "Vacunacion", "Control de nino sano" };
            else if (m.getEspecialidad() == "Dermatologo")
                practicas = { "Consulta", "Control de tratamiento" };
            else if (m.getEspecialidad() == "Oftalmologo")
                practicas = { "Consulta", "Fondo de ojo" };
            else if (m.getEspecialidad() == "Gastroenterologo")
                practicas = { "Consulta", "Endoscopia" };
            else
                practicas = { "Consulta" };

            // Crear turnos del medico (9:00–17:00 cada dia)
            for (const auto& d : dias)
                for (const auto& h : horas)
                    for (const auto& p : practicas)
                        turnos.push_back(Turno(
                            m.getNombre(),
                            m.getEspecialidad(),
                            m.getConsultorio(),
                            d,
                            h,
                            p,
                            false
                        ));
        }
    }


    // =================== CREAR Y GUARDAR TURNOS ===================

    void crearAgendaBase() {
        vector<string> horas = { "09:00","10:00","11:00","12:00","13:00","14:00","15:00","16:00","17:00" };
        vector<string> dias = { "Lunes","Martes","Miercoles","Jueves","Viernes" };

        for (const auto& med : medicos) {
            vector<string> practicas;
            if (med.getEspecialidad() == "Medico Clinico")
                practicas = { "Consulta general", "Control anual" };
            else if (med.getEspecialidad() == "Cardiologo")
                practicas = { "Consulta", "Electrocardiograma" };
            else if (med.getEspecialidad() == "Traumatologo")
                practicas = { "Consulta", "Control de yeso" };
            else if (med.getEspecialidad() == "Obstetra")
                practicas = { "Consulta", "Ecografia obstetrica", "Control prenatal" };
            else if (med.getEspecialidad() == "Pediatra")
                practicas = { "Consulta", "Vacunacion", "Control de nino sano" };
            else if (med.getEspecialidad() == "Dermatologo")
                practicas = { "Consulta", "Control de tratamiento" };
            else if (med.getEspecialidad() == "Oftalmologo")
                practicas = { "Consulta", "Fondo de ojo" };
            else if (med.getEspecialidad() == "Gastroenterologo")
                practicas = { "Consulta", "Endoscopia" };
            else
                practicas = { "Consulta" };

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
    // =================== MENUS Y FUNCIONES ===================
    void mostrarEspecialidades() const {
        vector<string> especialidades;
        for (const auto& m : medicos)
            if (find(especialidades.begin(), especialidades.end(), m.getEspecialidad()) == especialidades.end())
                especialidades.push_back(m.getEspecialidad());

        cout << "\n=== ESPECIALIDADES DISPONIBLES ===\n";
        for (size_t i = 0; i < especialidades.size(); i++)
            cout << i + 1 << ". " << especialidades[i] << endl;
    }

    string elegirEspecialidad() const {
        vector<string> especialidades;
        for (const auto& m : medicos)
            if (find(especialidades.begin(), especialidades.end(), m.getEspecialidad()) == especialidades.end())
                especialidades.push_back(m.getEspecialidad());

        cout << "\nSeleccione el numero de la especialidad: ";
        int op; cin >> op; cin.ignore();

        if (op < 1 || op >(int)especialidades.size()) return "";
        return especialidades[op - 1];
    }

    void mostrarMedicosPorEspecialidad() const {
        vector<string> especialidades;

        for (const auto& m : medicos)
            if (find(especialidades.begin(), especialidades.end(), m.getEspecialidad()) == especialidades.end())
                especialidades.push_back(m.getEspecialidad());

        cout << "\n=== ESPECIALIDADES DISPONIBLES ===\n";
        for (size_t i = 0; i < especialidades.size(); i++)
            cout << i + 1 << ". " << especialidades[i] << endl;

        cout << "\nSeleccione el numero de la especialidad: ";
        int op;
        cin >> op;
        cin.ignore();

        if (op < 1 || op >(int)especialidades.size()) {
            cout << "\nOpcion invalida.\n";
            return;
        }

        string esp = especialidades[op - 1];
        cout << "\n=== PROFESIONALES DE " << esp << " ===\n";

        int contador = 1;
        for (const auto& m : medicos)
            if (m.getEspecialidad() == esp)
                cout << contador++ << ". " << m.getNombre()
                << " (" << m.getConsultorio() << ")\n";

        if (contador == 1)
            cout << "No hay medicos registrados para esta especialidad.\n";
    }


    void tomarTurnoPorMedico() {
        // Crear lista única de médicos disponibles
        vector<string> nombres;
        for (const auto& m : medicos)
            if (find(nombres.begin(), nombres.end(), m.getNombre()) == nombres.end())
                nombres.push_back(m.getNombre());

        // Mostrar los médicos disponibles
        cout << "\n=== MEDICOS DISPONIBLES ===\n";
        for (size_t i = 0; i < nombres.size(); i++)
            cout << i + 1 << ". " << nombres[i] << endl;

        // Pedir la selección
        cout << "\nSeleccione el numero del medico: ";
        int op;
        cin >> op;
        cin.ignore();

        if (op < 1 || op >(int)nombres.size()) {
            cout << "\nOpcion invalida.\n";
            return;
        }

        string elegido = nombres[op - 1];

        cout << "\n=== TURNOS DISPONIBLES DE " << elegido << " ===\n";
        bool hayTurnos = false;

        // Mostrar los turnos libres del médico elegido
        for (size_t i = 0; i < turnos.size(); i++) {
            if (turnos[i].getMedico() == elegido && !turnos[i].estaOcupado()) {
                turnos[i].mostrar(i);
                hayTurnos = true;
            }
        }

        if (!hayTurnos) {
            cout << "\nNo hay turnos disponibles para " << elegido << ".\n";
            return;
        }

        cout << "\nIngrese el numero del turno que desea tomar: ";
        int num;
        cin >> num;
        cin.ignore();

        if (num >= 0 && num < (int)turnos.size() &&
            !turnos[num].estaOcupado() &&
            turnos[num].getMedico() == elegido) {
            turnos[num].ocupar();
            cout << "\nTurno tomado con exito con " << turnos[num].getMedico()
                << " (" << turnos[num].getEspecialidad() << ") el "
                << turnos[num].getDia() << " a las " << turnos[num].getHora() << ".\n";
        }
        else {
            cout << "\nNumero invalido o turno no disponible.\n";
        }
    }


    void tomarTurnoPorEspecialidad() {
        // Mostrar lista de especialidades
        vector<string> especialidades;
        for (const auto& m : medicos)
            if (find(especialidades.begin(), especialidades.end(), m.getEspecialidad()) == especialidades.end())
                especialidades.push_back(m.getEspecialidad());

        cout << "\n=== ESPECIALIDADES DISPONIBLES ===\n";
        for (size_t i = 0; i < especialidades.size(); i++)
            cout << i + 1 << ". " << especialidades[i] << endl;

        cout << "\nSeleccione el numero de la especialidad: ";
        int op;
        cin >> op;
        cin.ignore();

        if (op < 1 || op >(int)especialidades.size()) {
            cout << "\nOpcion invalida.\n";
            return;
        }

        string esp = especialidades[op - 1];

        // Mostrar medicos de esa especialidad
        cout << "\n=== PROFESIONALES DE " << esp << " ===\n";
        vector<string> medicosEsp;
        for (const auto& m : medicos)
            if (m.getEspecialidad() == esp)
                medicosEsp.push_back(m.getNombre());

        for (size_t i = 0; i < medicosEsp.size(); i++)
            cout << i + 1 << ". " << medicosEsp[i] << endl;

        cout << "\nSeleccione el numero del medico: ";
        int opMed;
        cin >> opMed;
        cin.ignore();

        if (opMed < 1 || opMed >(int)medicosEsp.size()) {
            cout << "\nOpcion invalida.\n";
            return;
        }

        string medicoElegido = medicosEsp[opMed - 1];
        cout << "\n=== TURNOS DISPONIBLES DE " << medicoElegido << " ===\n";

        bool hayTurnos = false;
        for (size_t i = 0; i < turnos.size(); i++) {
            if (turnos[i].getMedico() == medicoElegido && !turnos[i].estaOcupado()) {
                turnos[i].mostrar(i);
                hayTurnos = true;
            }
        }

        if (!hayTurnos) {
            cout << "\nNo hay turnos disponibles para " << medicoElegido << ".\n";
            return;
        }

        cout << "\nIngrese el numero del turno que desea tomar: ";
        int num;
        cin >> num;
        cin.ignore();

        if (num >= 0 && num < (int)turnos.size() &&
            !turnos[num].estaOcupado() &&
            turnos[num].getMedico() == medicoElegido) {
            turnos[num].ocupar();
            cout << "\nTurno tomado con exito con " << turnos[num].getMedico()
                << " (" << turnos[num].getEspecialidad() << ") el "
                << turnos[num].getDia() << " a las " << turnos[num].getHora() << ".\n";
        }
        else {
            cout << "\nNumero invalido o turno no disponible.\n";
        }
    }

    void tomarTurnoPorPractica() {
        vector<pair<string, string>> practicas; // (nombre practica, especialidad)

        // Extraer lista de practicas unicas desde los turnos
        for (const auto& t : turnos) {
            pair<string, string> p = { t.getPractica(), t.getEspecialidad() };
            bool existe = false;
            for (const auto& pr : practicas)
                if (pr.first == p.first) { existe = true; break; }
            if (!existe) practicas.push_back(p);
        }

        if (practicas.empty()) {
            cout << "\nNo hay practicas disponibles en este momento.\n";
            return;
        }

        // Mostrar la lista de practicas disponibles
        cout << "\n=== PRACTICAS DISPONIBLES ===\n";
        for (size_t i = 0; i < practicas.size(); i++)
            cout << i + 1 << ". " << practicas[i].first
            << " (" << practicas[i].second << ")\n";

        // Pedir al usuario que elija una
        cout << "\nSeleccione el numero de la practica: ";
        int op;
        cin >> op;
        cin.ignore();

        if (op < 1 || op >(int)practicas.size()) {
            cout << "\nOpcion invalida.\n";
            return;
        }

        string practicaElegida = practicas[op - 1].first;
        string especialidadElegida = practicas[op - 1].second;

        // Mostrar medicos que realizan esa practica
        vector<string> medicosDisp;
        for (const auto& t : turnos)
            if (t.getPractica() == practicaElegida &&
                t.getEspecialidad() == especialidadElegida &&
                !t.estaOcupado() &&
                find(medicosDisp.begin(), medicosDisp.end(), t.getMedico()) == medicosDisp.end())
                medicosDisp.push_back(t.getMedico());

        if (medicosDisp.empty()) {
            cout << "\nNo hay medicos disponibles para la practica seleccionada.\n";
            return;
        }

        cout << "\n=== MEDICOS QUE REALIZAN " << practicaElegida << " (" << especialidadElegida << ") ===\n";
        for (size_t i = 0; i < medicosDisp.size(); i++)
            cout << i + 1 << ". " << medicosDisp[i] << endl;

        cout << "\nSeleccione el numero del medico: ";
        int opm;
        cin >> opm;
        cin.ignore();

        if (opm < 1 || opm >(int)medicosDisp.size()) {
            cout << "\nOpcion invalida.\n";
            return;
        }

        string elegido = medicosDisp[opm - 1];

        cout << "\n=== TURNOS DISPONIBLES PARA " << practicaElegida
            << " CON " << elegido << " ===\n";
        bool hayTurnos = false;

        for (size_t i = 0; i < turnos.size(); i++) {
            if (turnos[i].getMedico() == elegido &&
                turnos[i].getPractica() == practicaElegida &&
                !turnos[i].estaOcupado()) {
                turnos[i].mostrar(i);
                hayTurnos = true;
            }
        }

        if (!hayTurnos) {
            cout << "\nNo hay turnos disponibles para esta practica.\n";
            return;
        }

        cout << "\nIngrese el numero del turno a tomar: ";
        int num;
        cin >> num;
        cin.ignore();

        if (num >= 0 && num < (int)turnos.size() &&
            !turnos[num].estaOcupado() &&
            turnos[num].getPractica() == practicaElegida &&
            turnos[num].getMedico() == elegido) {
            turnos[num].ocupar();
            cout << "\nTurno tomado con exito para " << practicaElegida
                << " con " << turnos[num].getMedico() << " el "
                << turnos[num].getDia() << " a las " << turnos[num].getHora() << ".\n";
        }
        else {
            cout << "\nNumero invalido o turno no disponible.\n";
        }
    }

    void cancelarTurno() {
        cout << "\n=== TURNOS OCUPADOS ===\n";
        for (size_t i = 0; i < turnos.size(); i++)
            if (turnos[i].estaOcupado()) turnos[i].mostrar(i);

        cout << "\nIngrese el numero del turno a cancelar: ";
        int num; cin >> num; cin.ignore();
        if (num >= 0 && num < (int)turnos.size() && turnos[num].estaOcupado()) {
            turnos[num].liberar();
            cout << "\nTurno cancelado correctamente.\n";
        }
        else cout << "\nNumero invalido o turno ya libre.\n";
    }

    void menuPrincipal() {
        int op;
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
            cin >> op; cin.ignore();

            switch (op) {
            case 1: mostrarEspecialidades(); break;
            case 2: mostrarMedicosPorEspecialidad(); break;
            case 3: tomarTurnoPorEspecialidad(); break;
            case 4: tomarTurnoPorMedico(); break;
            case 5: tomarTurnoPorPractica(); break;
            case 6: cancelarTurno(); break;
            case 7: guardarTurnosEnCSV(); cout << "\nSaliendo del sistema...\n"; break;
            default: cout << "\nOpcion invalida.\n";
            }
        } while (op != 7);
    }
};

// =================== MAIN ===================

int main() {
    Clinica clinica;
    clinica.menuPrincipal();
    return 0;
}