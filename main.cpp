#include <iostream>
#include <string>
#include <locale>

using namespace std;

class SocioClub
{
private:
    int NumeroSocio;
    string NombreSocio;
    string Domicilio;
    int AnoIngreso;

public:
    SocioClub() : NumeroSocio(0), NombreSocio(""), Domicilio(""), AnoIngreso(0) {}

    SocioClub(int numerosocio, const string &nombresocio, const string &domicilio, int anoingreso)
        : NumeroSocio(numerosocio), NombreSocio(nombresocio), Domicilio(domicilio), AnoIngreso(anoingreso) {}

    int getNumeroSocio() const
    {
        return NumeroSocio;
    }

    string getNombreSocio() const
    {
        return NombreSocio;
    }

    string getDomicilio() const
    {
        return Domicilio;
    }

    void imprimir() const
    {
        cout << "Número de socio: " << NumeroSocio << endl;
        cout << "Nombre: " << NombreSocio << endl;
        cout << "Domicilio: " << Domicilio << endl;
        cout << "Año de ingreso: " << AnoIngreso << endl;
        cout << "-------------------------" << endl;
    }


    bool operator<(const SocioClub &socio) const
    {
        return NumeroSocio < socio.NumeroSocio;
    }


    bool operator==(const SocioClub &socio) const
    {
        return NumeroSocio == socio.NumeroSocio;
    }
};


template<class T>
class LSLSE
{
private:


public:
    LSLSE() : lista(nullptr) {}

    struct node
    {
        T data;
        node* sig;
    };
    node* lista;

    bool vacia() const
    {
        return lista == nullptr;
    }

    void insertar(T elem)
    {
        node* nuevo = new node;
        nuevo->data = elem;

        if (vacia() || elem < lista->data)
        {
            nuevo->sig = lista;
            lista = nuevo;
        }
        else
        {
            node* actual = lista;
            while (actual->sig != nullptr && !(elem < actual->sig->data))
            {
                actual = actual->sig;
            }
            nuevo->sig = actual->sig;
            actual->sig = nuevo;
        }
    }

    bool eliminar(int numerosocio)
    {
        if (vacia())
        {
            return false;
        }

        node* actual = lista;
        node* anterior = nullptr;

        while (actual != nullptr && actual->data.getNumeroSocio() != numerosocio)
        {
            anterior = actual;
            actual = actual->sig;
        }

        if (actual == nullptr)
        {
            return false;
        }

        if (anterior == nullptr)
        {
            lista = actual->sig;
        }
        else
        {
            anterior->sig = actual->sig;
        }

        delete actual;
        return true;
    }

    void imprimir() const
    {
        node* actual = lista;
        while (actual != nullptr)
        {
            actual->data.imprimir();
            actual = actual->sig;
        }
    }


    node* getLista() const
    {
        return lista;
    }
};

int main()
{
    LSLSE<SocioClub> listaSocios;
    int opc;

    setlocale(LC_ALL,"");

    do
    {
        cout << "\t**********[Menu]**********" << endl;
        cout << "\t1. Agregar socio" << endl;
        cout << "\t2. Eliminar socio" << endl;
        cout << "\t3. Reporte socios" << endl;
        cout << "\t4. Buscar socio por nombre y domicilio" << endl;
        cout << "\t5. Mostrar total de socios registrados" << endl;
        cout << "\t6. Salir" << endl;
        cout << "\tIngrese una opcion: ";
        cin >> opc;

        switch (opc)
        {
        case 1:
        {
            int numerosocio, anoingreso;
            string nombresocio, domicilio;
            cout<<"------------------------------"<<endl;
            cout << " Numero de socio: ";
            cin >> numerosocio;
            cout << " Nombre del socio: ";
            cin.ignore();
            getline(cin, nombresocio);
            cout << " Domicilio del socio: ";
            getline(cin, domicilio);
            cout << " Año de ingreso: ";
            cin >> anoingreso;
            cout<<"------------------------------"<<endl;
            SocioClub nuevoSocio(numerosocio, nombresocio, domicilio, anoingreso);
            listaSocios.insertar(nuevoSocio);
            cout << " Se agrego el socio con exito " << endl;
            cout<<"------------------------------"<<endl;
            break;
        }
        case 2:
        {
            int numerosocio;
            cout << "Ingrese el número del socio a dar de baja: ";
            cin >> numerosocio;
            cout<<"------------------------------"<<endl;

            if (listaSocios.eliminar(numerosocio))
            {
                cout<<"------------------------------"<<endl;
                cout << "¡Se eliminó el socio con éxito!" << endl;
                cout<<"------------------------------"<<endl;
            }
            else
            {
                cout<<"-----------------------------"<<endl;
                cout << "No se pudo eliminar el socio." << endl;
                cout<<"------------------------------"<<endl;
            }
            break;
        }
        case 3:
        {
            cout << " ************ LISTA SOCIOS ***************** " << endl;
            cout<<"-------------------------"<<endl;
            listaSocios.imprimir();
            break;
        }
        case 4:
        {
            string nombreBuscado, domicilioBuscado;
            cout<<"-------------------------"<<endl;
            cout << "Ingrese el nombre del socio a buscar: ";
            cin.ignore();
            getline(cin, nombreBuscado);
            cout << "Ingrese el domicilio del socio a buscar: ";
            getline(cin, domicilioBuscado);
            cout<<"-------------------------"<<endl;

            bool encontrado = false;
            typename LSLSE<SocioClub>::node* actual = listaSocios.getLista();
            while (actual != nullptr)
            {
                if (actual->data.getNombreSocio() == nombreBuscado && actual->data.getDomicilio() == domicilioBuscado)
                {
                    actual->data.imprimir();
                    encontrado = true;
                }
                actual = actual->sig;
            }

            if (!encontrado)
            {
                cout<<"-------------------------"<<endl;
                cout << "No se encontró ningún socio con ese nombre y domicilio." << endl;
                cout<<"-------------------------"<<endl;
            }
            break;
        }
        case 5:
        {
            int totalSocios = 0;
            typename LSLSE<SocioClub>::node* actual = listaSocios.getLista();
            while (actual != nullptr)
            {
                totalSocios++;
                actual = actual->sig;
            }
            cout<<"-------------------------"<<endl;
            cout << "El total de socios registrados es: " << totalSocios << endl;
            cout<<"-------------------------"<<endl;
            break;
        }
        }
    }
    while (opc != 6);

    return 0;
}
