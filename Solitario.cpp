#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;


//---------------------------------------------- ESTRUCTURA CARTA------------------------------------------------------
struct Carta
{
    int num;
    char color;
    string signo;
    bool bocaArriba;
    Carta* sig;
    Carta* ant;

    Carta(){

    }

    Carta(int numero, char colr, string simbolo, bool arriba, Carta* next, Carta* prev) {
        num = numero;
        color = colr;
        signo = simbolo;
        bocaArriba = arriba;
        sig = next;
        ant = prev;
    }


    string mostrarContenido() {
        if (this == nullptr){
            return "  []  ";
        } else {
            string contenido;
            if (!bocaArriba){
                contenido = "------";
            }else {
                if (num == 1) {
                    contenido += "A ";
                } else if (num == 11) {
                    contenido += "J ";
                } else if (num == 12) {
                    contenido += "Q ";
                } else if (num == 13) {
                    contenido += "K ";
                } else if(num == 10) {
                    contenido += to_string(num);
                } else {
                    contenido += to_string(num) + " ";
                }
                contenido += " " + signo;
                contenido += color;
            }
            return contenido;
        }
    }


public: bool isApilable(Carta* recibir, Carta* colocar){
        if (colocar->num < recibir->num && colocar->color != recibir->color && recibir->bocaArriba == true)
        {
            return true;
        }
        return false;
    }

public: bool isApilableHecho(Carta* recibir, Carta* colocar){
        if (colocar == nullptr){
            return true;
        } else {
            if (colocar->num == recibir->num+1 && colocar->signo == recibir->signo && recibir->bocaArriba == true)
            {
                return true;
            }
            return false;
        }
    }



};


//---------------------------------------------- ESTRUCTURA PILA------------------------------------------------------
struct Pila {
    Carta* tope;
    Carta* base;
    bool finalizada;
    int size = 0, numAceptar = 0;

    Pila() {
        tope = nullptr;
        base = nullptr;
        finalizada = false;
    }
    Pila(int aceptar) {
        tope = nullptr;
        base = nullptr;
        finalizada = false;
        numAceptar = aceptar;
    }

    void push(Carta* carta) {
        if(tope == nullptr ){
            tope = carta;
            size = size +1;
        } else {
            carta->sig = tope;
            tope->ant = carta;
            tope = carta;
            size = size + 1;
        }
    }

    Carta* pop() {
        if (tope == nullptr) {
            return nullptr;
        }
        Carta* carta = tope;
        tope = tope->sig;
        size --;
        if (size <= 0){
            tope = nullptr;
        }
        return carta;
    }

    Carta* popJuego() {
        if (tope == nullptr) {
            return nullptr;
        }
        Carta* carta = tope;
        tope = tope->sig;
        tope->bocaArriba = true;
        size --;
        if (size <= 0){
            tope = nullptr;
        }
        return carta;
    }

    Carta* top() {
        return tope;
    }

    bool isEmpty() {
        return tope == nullptr;
    }

    int tamanoPila(){
        return size;
    }

    Carta* buscarIndice(int num){
        if (num <= size){
            int cont = 1;
            Carta* inicio = tope;
            while (cont != num){
                inicio = inicio->sig;
                cont++;
            }
            size--;
            return inicio;
        }
        return nullptr;
    }

    void dibujarPila(Pila* original){
        Pila* aux = new Pila();
        while (!original->isEmpty()){
            aux->push(original->pop());
        }
        while (!aux->isEmpty()){
            original->push(aux->pop());
            cout<<original->tope->mostrarContenido() + " | ";
        }
        cout<<endl;
    }
};








//---------------------------------------------- ESTRUCTURA COLA------------------------------------------------------
struct Cola {
    Carta* frente;
    Carta* final;
    int numAceptar = 0;

    Cola() {
        frente = nullptr;
        final = nullptr;
    }

    void encolar(Carta* carta) {
        if (final == nullptr) {
            frente = carta;
            final = carta;
            carta->bocaArriba = false;
        } else {
            final->sig = carta;
            carta->ant = final;
            final = carta;
            final->bocaArriba = false;
        }
    }

    Carta* decolar() {
        if (frente == nullptr) {
            return nullptr;
        }
        Carta* carta = frente;
        frente = frente->sig;
        if (frente == nullptr) {
            final = nullptr;
        }
        return carta;
    }

    Carta* decolarFinal(){
        if (final == nullptr) {
            return nullptr;
        }
        Carta* carta = final;
        final = final->ant;
        final->ant->bocaArriba = true;
        final->ant->sig = nullptr;
        return carta;
    }

    void regresarCartas(Cola* baraja) {
        while (!baraja->isEmpty()) {
            this->encolar(baraja->decolar());
        }
    }

    bool isEmpty() {
        return frente == nullptr;
    }
};

//---------------------------------------------- creacion de lista de cartas -----------------------------------------

Pila* listaCartas = new Pila();
Pila* listaAleatoria = new Pila();

void crearCartas(){
    string signo = "<>";
    char color = 'R';
    for (int i = 0; i <= 3; ++i) {
        if(i==0){
            color = 'R';
            signo = "<>";
        }else if (i == 1){
            color = 'N';
            signo = "!!";
        } else if (i == 2){
            color = 'R';
            signo = "<3";
        } else if(i == 3){
            color = 'N';
            signo = "E3";
        }
        for (int j = 1; j <= 13; j++) {
            Carta *creada = new Carta(j, color, signo, false, nullptr, nullptr);
            listaCartas->push(creada);
        }
    }
}

void repartirCartas(Cola* Mazo, Pila* ListaMazo[]){
    for (int i = 1; i < 25; ++i) {
        Mazo->encolar(listaCartas->pop());
    }
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < ListaMazo[i]->numAceptar; ++j) {
            ListaMazo[i]->push(listaCartas->pop());
        }
        ListaMazo[i]->tope->bocaArriba = true;
    }
}

void aleatorizar() {
    int indiceAleatorio;
    while (!listaCartas->isEmpty()){
        indiceAleatorio = rand() % listaCartas->tamanoPila() + 1;
        Carta* temp = listaCartas->buscarIndice(indiceAleatorio);
        listaAleatoria->push(temp);
    }
}

void revelarCarta(Cola* inicial, Cola* final){
    if (inicial->isEmpty()){
        inicial->regresarCartas(final);
    } else {
        final->encolar(inicial->decolar());
        final->final->bocaArriba = true;
    }
}

void moverAbiertoJuego(Cola* inicial, Pila* colocar){
    if (inicial->final->isApilable(colocar->tope, inicial->final)){
        colocar->push(inicial->decolarFinal());
    } else {
        cout<<"Movimiento Invalido"<<endl;
        cout<<"Presione Enter para Continuar"<<endl;
        string pres;
        cin>>pres;
    }
}

void moverJuegoAJuego(Pila* colocar, Pila* recibir){
    if (colocar->tope->isApilable(recibir->tope, colocar->tope)){
        recibir->push(colocar->popJuego());
    } else {
        cout<<"Movimiento Invalido"<<endl;
        cout<<"Presione Enter para Continuar"<<endl;
        string pres;
        cin>>pres;
    }
}

void moverJuegoAHecho(Pila* inicial, Pila* hecha){
    if (inicial->tope->isApilableHecho(inicial->tope, hecha->tope)){
        hecha->push(inicial->popJuego());
    } else {
        cout<<"Movimiento Invalido"<<endl;
        cout<<"Presione Enter para Continuar"<<endl;
        string pres;
        cin>>pres;
    }
}








//---------------------------------------------- INICIO ------------------------------------------------------
int main() {
    Cola* ListaCerradas = new Cola();
    Cola* ListaAbiertas = new Cola();
    Pila* Mazos[7];
    bool finJuego = false;
    for (int i = 0; i < 7; ++i) {
        Mazos[i]  = new Pila(i+1);
    }
    Pila* Colocadas[4];
    for (int i = 0; i <= 3; ++i) {
        Colocadas[i] = new Pila();
    }

    crearCartas();
    repartirCartas(ListaCerradas, Mazos);

    while (!finJuego){
        cout<<"                     SOLITARIO"<<endl;
        cout<<"     CARTAS"<<endl;
        cout<<"Mazo Cerradas:   "<<ListaCerradas->frente->mostrarContenido()<<endl;
        cout<<"Mazo Abiertas:   "<<ListaAbiertas->final->mostrarContenido()<<endl;
        cout<<""<<endl;

        cout<<"     MAZOS en JUEGO"<<endl;
        for (int i = 0; i < 7; ++i) {
            cout<<"Mazo "<< i+1 << ":          | "; Mazos[i]->dibujarPila(Mazos[i]);
        }
        cout<<endl;

        cout<<"     HECHOS"<<endl;
        for (int i = 0; i < 4; ++i) {
            cout<<"Mazo "<< i+1 << ":          "<<Colocadas[i]->tope->mostrarContenido()<<endl;
        }
        cout<<endl;

        int opcion;
        cout<<"Elija su movimiento"<<endl;
        cout<<"1.   Revelar Carta"<<endl;
        cout<<"2.   Mover de Mazo Abierto a un Mazo en Juego "<<endl;
        cout<<"3.   Mover de un Mazo en Juego a otro Mazo en Juego"<<endl;
        cout<<"4.   Mover de un Mazo en Juego a un Mazo Hecho"<<endl;
        cout<<"5.   Salir"<<endl;

        cout<<"Ingrese su opcion :";
        cin>>opcion;

        switch (opcion) {


            case 1:
                revelarCarta(ListaCerradas, ListaAbiertas);
                break;


            case 2:
                cout<<"Ingrese el indice del Mazo para moverlo :";
                int mazo;
                cin>> mazo;
                if (mazo < 1 || mazo > 7){
                    cout<<"Movimiento Invalido"<<endl;
                    cout<<"Presione Enter para Continuar"<<endl;
                    string pres;
                    cin>>pres;
                } else {
                    moverAbiertoJuego(ListaAbiertas, Mazos[mazo-1]);
                }
                break;


            case 3:
                int mazoSalir, mazoRecibe;
                cout<<"Ingrese el indice del Mazo del que quitar la carta :";
                cin>> mazoSalir;
                cout<<endl;
                cout<<"Ingrese el indice del Mazo donde colocar la carta :";
                cin>> mazoRecibe;
                cout<<endl;
                if (mazoSalir < 1 || mazoSalir > 7 || mazoRecibe < 1 || mazoRecibe > 7){
                    cout<<"Movimiento Invalido"<<endl;
                    cout<<"Presione Enter para Continuar"<<endl;
                    string pres;
                    cin>>pres;
                } else {
                    moverJuegoAJuego(Mazos[mazoSalir-1], Mazos[mazoRecibe-1]);
                }
                break;


            case 4:
                int mazoSacar, hechoRecibe;
                cout<<"Ingrese el indice del Mazo del que quitar la carta :";
                cin>> mazoSacar;
                cout<<endl;
                cout<<"Ingrese el indice del Mazo donde colocar la carta :";
                cin>> hechoRecibe;
                cout<<endl;
                if (hechoRecibe < 1 || hechoRecibe > 4 || mazoSacar < 1 || mazoSacar > 7){
                    cout<<"Movimiento Invalido"<<endl;
                    cout<<"Presione Enter para Continuar"<<endl;
                    string pres;
                    cin>>pres;
                } else {
                    moverJuegoAHecho(Mazos[mazoSacar-1], Colocadas[hechoRecibe-1]);
                }
                break;

            case 5:
                finJuego = true;
                break;
        }
        cout<<""<<endl;
        cout<<"**********************************************************************************************************"<<endl;
        cout<<""<<endl;
    }


    /*
                                            Probando si funciona la creacion de Cartas, funciona correctamente :)
    cout << "Pila:" << endl;
    while (!listaCartas->isEmpty()) {
        Carta* carta = listaCartas->pop();
        cout << carta->mostrarContenido() << endl;
    }

                                            FUNCION PARA ALEATORIZAR LAS CARTAS Y MOSTRARLAS, NO FUNCIONA TODAVÍA :c
    aleatorizar();

    cout << "Pila: aleatoria" << endl;
    while (!listaAleatoria->isEmpty()) {
        Carta* carta = listaAleatoria->pop();
        cout << carta->mostrarContenido() << endl;
    }
    */

    return 0;
}