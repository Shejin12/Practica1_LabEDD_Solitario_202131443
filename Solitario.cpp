#include <iostream>
using namespace std;

struct Carta
{
    int num;
    char color;
    char signo[3];
    bool bocaArriba;
    Carta* sig, ant; 

    public char mostrarContenido(){
        char numero;
        if (num == 1)
        {
            numero = 'A';
        } else if (num == 11)
        {
            numero = 'J'
        } else if (num == 12)
        {
            numero = 'Q'
        } else if (num == 13)
        {
            numero = 'K'
        } else {
            numero = num;
        }
        return  numero + ' ' + signo + ' ' + Color;
    }

    public bool isApilable(Carta* recibir, Carta* colocar){
        bool apilable = false;
        if (colocar->num < recibir->num && colocar->color != recibir->color && recibir->bocaArriba == true)
        {
            apilable = true;
        }
        return apilable;
    }



};



/*-----     INICIO    -----------------------------------------------------------------------------------*/

int main()
{
    cout<<"hola mundo"<<endl;
    return 0;
}
