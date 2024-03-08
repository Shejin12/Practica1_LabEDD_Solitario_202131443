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
        string contenido;
        if (num == 1) {
            contenido += 'A';
        } else if (num == 11) {
            contenido += 'J';
        } else if (num == 12) {
            contenido += 'Q';
        } else if (num == 13) {
            contenido += 'K';
        } else {
            contenido += to_string(num);
        }
        contenido += " " + signo;
        contenido += color;
        return contenido;
    }


public: bool isApilable(Carta* recibir, Carta* colocar){
        if (colocar->num < recibir->num && colocar->color != recibir->color && recibir->bocaArriba == true)
        {
            return true;
        }
        return false;
    }



};


//---------------------------------------------- ESTRUCTURA PILA------------------------------------------------------
struct Pila {
    Carta* tope;
    bool finalizada;
    int size = 0;

    Pila() {
        tope = nullptr;
        finalizada = false;
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
            }
            size--;
            return inicio;
        }
        return nullptr;
    }
};

//---------------------------------------------- ESTRUCTURA COLA------------------------------------------------------
struct Cola {
    Carta* frente;
    Carta* final;

    Cola() {
        frente = nullptr;
        final = nullptr;
    }

    void encolar(Carta* carta) {
        if (final == nullptr) {
            frente = carta;
            final = carta;
        } else {
            final->sig = carta;
            final = carta;
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
            signo = "^^";
        } else if (i == 2){
            color = 'R';
            signo = "<3";
        } else if(i == 3){
            color = 'N';
            signo = "E3";
        }
        for (int j = 1; j <= 13; j++) {
            Carta *creada = new Carta(j, color, signo, true, nullptr, nullptr);
            listaCartas->push(creada);
        }
    }
}

void aleatorizar() {
    int indiceAleatorio = rand() % listaCartas->tamanoPila();
    while (!listaCartas->isEmpty()){
        Carta* temp = listaCartas->buscarIndice(indiceAleatorio);
        temp->sig->ant = temp->ant;
        temp->ant->sig = temp->sig;
        listaAleatoria->push(temp);
    }
}








//---------------------------------------------- INICIO ------------------------------------------------------
int main() {

    crearCartas();

    /* Probando si funciona la creacion de Cartas
    cout << "Pila:" << endl;
    while (!listaCartas->isEmpty()) {
        Carta* carta = listaCartas->pop();
        cout << carta->mostrarContenido() << endl;
    }*/

    cout<<"---------------------------------------------------------------"<<endl;
    aleatorizar();

    cout << "Pila: aleatoria" << endl;
    while (!listaAleatoria->isEmpty()) {
        Carta* carta = listaAleatoria->pop();
        cout << carta->mostrarContenido() << endl;
    }

    return 0;
}