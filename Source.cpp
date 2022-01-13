#include<iostream>
#include<string>
#include<fstream>
#include<conio.h>
using namespace std;
//să se realizeze cel puțin o ierarhie de clase care să implementeze principiile moștenirii(cel puțin 3 clase): cont_client->date_client->comanda

//Exceptiile custom:
class Exceptievarsta : public exception {
public:
    const char* functie() const throw() {
        return "ERROR: Varsta clientului trebuie sa fie >=16. \n";
    }
};

class Exceptietelf : public exception {
public:
    const char* functie() const throw() {
        return "ERROR: Telefonul clientului trebuie sa contina 10 cifre. \n";
    }
};

//Contul clientului pe site:
class cont_client {
protected:
    string nume_cl, prenume_cl, email, username="default";
    int varsta;
public:
    //getteri si setteri:
    string getusername()
    {
        return this->username;
    }
    string getnume()
    {
        return this->nume_cl;
    }
    string getprenume()
    {
        return this->prenume_cl;
    }
    string getemail()
    {
        return this->email;
    }
  
    int getvarsta()
    {
        return this->varsta;
    }

    void setVarsta(int varsta) {
        if (varsta <16) {
            throw new Exceptievarsta();
        }
        else {
            this->varsta = varsta;
        }
    }

    //constructor default
    cont_client() {

        this->nume_cl = "default name value";
        this->prenume_cl = "default name value";
        this->email = "default name value";
        this->username = "default name value";
        this->varsta = 0;
    }
    //constructor cu validari
    cont_client(string nume_cl, string prenume_cl, string email, string username, int varsta)
    {
        if (nume_cl.empty()) {
            throw new exception("Error: numele clientului este empty.");
        }
        else {
            this->nume_cl = nume_cl;
        }

        if (prenume_cl.empty()) {
            throw new exception("Error: prenumele clientului este empty.");
        }
        else {
            this->prenume_cl = prenume_cl;
        }

        if (email.empty()) {
            throw new exception("Error: emailul clientului este empty.");
        }
        else {
            this->email = email;
        }

        if (username.empty()) {
            throw new exception("Error: username-ul clientului este empty.");
        }
        else {
            this->username = username;
        }

        if (varsta < 0) {
            throw new exception("Error: varsta introdusa este gresita.");
        }
        else {
            this->varsta = varsta;
        }
   
    }
    //destructor
    ~cont_client() {}
    //constructor copiere:
    cont_client(const cont_client& cc) {

        this->nume_cl = cc.nume_cl;
        this->prenume_cl = cc.prenume_cl;
        this->email = cc.email;
        this->username = cc.username;
        this->varsta = cc.varsta;
    }
    //operatorul =
    cont_client& operator=(const cont_client& cc)
    {
        if (this != &cc)
        {

            this->nume_cl = cc.nume_cl;
            this->prenume_cl = cc.prenume_cl;
            this->email = cc.email;
            this->username = cc.username;
            this->varsta = cc.varsta;
        }

        return *this;
    }

}cc;

//Datele in plus furnizate pt finalizarea comenzii:
class date_client: public cont_client {
protected:
   string telefon,localitate;
   
public:
    void finalizarecomanda();void scrie(ofstream& iesire); 
    
    string gettelef()
    {
        return this->telefon;
    }
    void settelef(string telefon) 
    {  if (telefon.size() != 10) {
            throw new Exceptietelf();
        }
        else {  
            this->telefon = telefon;
        }
    }

    string getloc()
    {
        return this->localitate;
    }

    //constructor default:
    date_client() : cont_client("Default", "Default", "Default", "Default", 0)
    {
        this->telefon = "default name value";
        this->localitate = "default name value";
    }
    //constructor cu validari:
    date_client(string nume_cl, string prenume_cl, string email, string username, int varsta, string telefon, string localitate) :cont_client(nume_cl, prenume_cl, email, username, varsta)
    {
        if (telefon.empty()) {
            throw new exception("Error: telefonul clientului este empty.");
        }
        else {
            this->telefon = telefon;
        }

        if (localitate.empty()) {
            throw new exception("Error: localitatea este empty.");
        }
        else {
            this->localitate = localitate;
        }
    }
   //destructor:
    ~date_client() {}
    //constructor copiere:
    date_client(const date_client& d) {
        this->telefon = d.telefon;
        this->localitate = d.localitate;
    }
    //operatorul =
    date_client& operator=(const date_client& d)
    {
        if (this != &d)
        {

            this->telefon = d.telefon;
            this->localitate = d.localitate;
        }
        return *this;
    }

}d;

//Scrierea datelor personale ale clientului in fisierul binar.
void date_client::scrie(ofstream& iesire)
{ 

    int nr = this->cont_client::getusername().size() + 1;
    iesire.write((char*)&nr, sizeof(nr));
    iesire.write((char*)&username, sizeof(nr));

    int dim1 = this->cont_client::getnume().size() + 1;
    iesire.write((char*)&dim1, sizeof(dim1));
    iesire.write(nume_cl.c_str(), dim1);

    int dim2 = this->cont_client::getprenume().size() + 1;
    iesire.write((char*)&dim2, sizeof(dim2));
    iesire.write(prenume_cl.c_str(), dim2);


    int dim3 = this->cont_client::getemail().size() + 1;
    iesire.write((char*)&dim3, sizeof(dim3));
    iesire.write(email.c_str(), sizeof(email));

    iesire.write((char*)&this->varsta, sizeof(int));

    int dim4 = this->localitate.size() + 1;
    iesire.write((char*)&dim4, sizeof(dim4));
    iesire.write(localitate.c_str(), dim4);

    int dim5 = this->telefon.size() + 1;
    iesire.write((char*)&dim5, sizeof(dim5));
    iesire.write(telefon.c_str(), dim5);
}

//Prelucrarea comenzii de catre magazin prin trimiterea catre firma de curierat.
class comanda : public date_client {
    string AWB; 
    string firma="CARGUS";

public: 
    void scrieAWB(ofstream& iesire);
    void afisarecomanda();
    void comandacurier();
    void citirecomanda(fstream & citire);
    string getfirma()
    {
        return this->firma;
    }
    string getAWB()
    {
        return this->AWB;
    }

    //constructor default:
    comanda() :date_client("Default", "Default", "Default", "Default", 0, "Default", "Default")
    {
        this->AWB = "default name value";
       
    }
    //constructor cu validari:
    comanda(string nume_cl, string prenume_cl, string email, string username, int varsta, string telefon, string localitate, string AWB, string firma) :date_client(nume_cl, prenume_cl, email, username, varsta, telefon, localitate)
    {
        if (AWB.empty()) {
            throw new exception("Error: AWb-ul comenzii este empty.");
        }
        else {
            this->AWB = AWB;
        }

        if (firma.empty()) {
            throw new exception("Error: Firma de curierat este empty.");
        }
        else {
            this->firma = firma;
        }
    }
    //destructor
    ~comanda() {}
    //constructor copiere:
    comanda(const comanda& com) {
        this->AWB = com.AWB;
        this->firma = com.firma;
    }
    //operatorul =
    comanda& operator=(const comanda& com)
    {
        if (this != &com)
        {
            this->AWB = com.AWB;
            this->firma = com.firma;
        }

        return *this;
    }

}com;

//Scrie in fisier binar detaliile comenzii furnizate de firma de curierat.
void comanda::scrieAWB(ofstream& iesire) {
  

    int dim1 = this->getAWB().size() + 1;
    iesire.write((char*)&dim1, sizeof(dim1));
    iesire.write(AWB.c_str(), dim1);

    int dim2 = this->getfirma().size() + 1;
    iesire.write((char*)&dim2, sizeof(dim2));
    iesire.write(firma.c_str(), dim2);

    iesire.close();
}


class produs
{
    string nume, categorie;
    float pret;  //cast float la double
    int cod_produs, cantitate;
    int c;
public:

    void af(fstream& citire);   void aplicareducere(float discount);
    void add();  void scriere(fstream& iesire);  void citire(fstream& citire);
    void scrierelista(fstream& iesire, int c); void citirelista(fstream& citire);
    void stergere(); int fct(string nm);
    void lista(); void getProdus();
    void withd(int c, int& suma);
    void afisare();
    void adaugare_cos(); void valoarecos(string temp, int c, int& sum);
   
    //functie virtuala:
    virtual void arereducere() {
        cout << "\nProdusului nu i-a fost aplicata nicio reducere.\n";
    }

    //SUPRAINCARCARE DE OPERATORI: (pe langa >> si <<)
    
    //1.OPERATORUL +=
    void operator+=(int x) {
        cantitate += x;
    }

    //OPERATORUL FUNCTIE:
    void operator()(int valoare) {
        if (valoare >= 15 && valoare <= 80) 
                pret += valoare;
        else throw new exception("Eroare: valoare < 5 sau valoare > 15");
        
    }

    //OPERATORUL CAST:
    operator double() {
        return pret;
    }

    //GETTERI SI SETTERI:
   string getnume() {
        return nume;
    }

    void setnume(string nume) {
        if (nume.empty()) {
            throw new exception("numele primit ca input este gol.");
        }
        this->nume = nume;
    }

    string getcat() {
        return categorie;
    }

    void setcat(string categorie) {
        if (categorie.empty()) {
            throw new exception("categoria primita ca input este gol.");
        }
        this->categorie = categorie;
    }

    float getpret()
    {
        return this->pret;
    }

    friend ostream& operator<<(ostream& out, produs& p);
    friend ifstream& operator>>(ifstream& citire, produs& p);
    
    //constructor default:
    produs() {

        this->cod_produs = 0;
       
        this->nume= "default name value";
        this->categorie = "default name value";
        this->pret = 0;
        this->cantitate = 0;

    }
    //constructor cu validari:
    produs(int cod_produs, float pret, int cantitate, string nume, string categorie )
    {
        this->cod_produs = cod_produs;

        this->nume = nume;
        this->categorie = categorie;

        this->pret = pret;
        this->cantitate = cantitate;
    }
    //destructor:
    ~produs() {}
    //constructor copiere
    produs(const produs& p) {

        this->cod_produs = p.cod_produs;
        this->nume = p.nume;
        this->categorie = p.categorie;
        this->pret = p.pret;
        this->cantitate = p.cantitate;
    }
    //operatorul =
   produs& operator=(const produs& p)
    {
        if (this != &p) {

            this->cod_produs = p.cod_produs;
            this->nume = p.nume;
            this->categorie = p.categorie;

            this->pret = p.pret;
            this->cantitate = p.cantitate;
        }

        return *this;
    }
}p;

class reducere : public produs
{
    //procentul de discount:
    float procent;
public:
  
    //clasa interfata pt produsul cu reducere: 
    virtual void arereducere() {
        cout << "\nProdusului i-a fost aplicata reducerea.\n";
    }

    //constructor default
    reducere() : produs(0, 0, 0, "Default", "Default") {
        this->procent = 0;
    }

    //constructor cu validari:
    reducere(int cod_produs, float pret, int cantitate, string nume, string categorie, float procent) :produs(cod_produs, pret, cantitate, nume, categorie)
    {
        if (procent<0) {
            throw new exception("Nu ati introdus corect discountul produsului.");
        }
        else
        this->procent = procent;
        
    }
    ~reducere() {}
    //constructor copiere:
    reducere(const reducere& r) {
         this->procent = r.procent;
    }
    //operatorul =
    reducere& operator=(const reducere& r)
    {
        if (this != &r)
        {

            this->procent = r.procent;
        }

        return *this;
    }

    float getDiscount() {
        return this->procent;
        //cout << endl << "The discount is " << this->procent << "%";
    }
}r;

void produs::getProdus()
{
    cin >> cod_produs;
    cin >> pret >> cantitate;
    cin >> nume;
    cin >> categorie;
}
int produs::fct(string nm)
{
    if (nm==nume)
        return 0;
    else
        return 1;
}

//Functia retrage de pe stoc produsele cumparate de client:
void produs::withd(int c, int& suma)
{ 
    suma = 0;
    if (cantitate >= c)
    {
        cantitate -= c;
        cout << "\n\nStoc actualizat.\n";
        suma = pret * c;
    }
    else
        cout << "\n\nStoc insuficient";
}

//Aplicarea reducerii pt anumite produse:
void produs::aplicareducere(float discount)
{  
    pret = pret * (1 - discount);
}

// Scrierea in fisier binar a stocului din magazin:
void produs::scriere(fstream& iesire)
{

    iesire.write((char*)&this->cod_produs, sizeof(int));

    iesire.write((char*)&this->pret, sizeof(float));

    iesire.write((char*)&this->cantitate, sizeof(int));

    //scriu nr caract al numelui  + \0
    int nr1 = this->nume.size() + 1; 
    iesire.write((char*)&nr1, sizeof(int));
    iesire.write(this->nume.c_str(), nr1* sizeof(char));


    int nr2 = this->categorie.size() + 1;
    iesire.write((char*)&nr2, sizeof(int));
    iesire.write(this->categorie.c_str(), nr2 * sizeof(char));
 
}

//Citirea din fisier binar a stocului din magazin:
void produs::citire(fstream& citire)
{ 
    
    int nr;
    citire.read((char*)&this->cod_produs, sizeof(int));

    citire.read((char*)&this->pret, sizeof(float));
    citire.read((char*)&this->cantitate, sizeof(int));

    //citire dimensiuni si string-uri
    citire.read((char*)&nr, sizeof(int));

    char buffer[100];
    citire.read(buffer, nr*sizeof(char));
    this->nume = string(buffer);
    
    citire.read((char*)&nr, sizeof(int));

    char buffer1[100];
    citire.read(buffer1, nr * sizeof(char));
    this->categorie  = string(buffer1);

}

//Scrierea in fisier binar a listei de cumparaturi a clientului:
void produs::scrierelista(fstream& iesire, int c)//fara cantitate
{ 
    iesire.write((char*)&this->cod_produs, sizeof(int));

    iesire.write((char*)&this->pret, sizeof(float));

    iesire.write((char*)&this->c, sizeof(int));

    //scriu nr caract al numelui  + \0
    int nr1 = this->nume.size() + 1;
    iesire.write((char*)&nr1, sizeof(int));
    iesire.write(this->nume.c_str(), nr1 * sizeof(char));


    int nr2 = this->categorie.size() + 1;
    iesire.write((char*)&nr2, sizeof(int));
    iesire.write(this->categorie.c_str(), nr2 * sizeof(char));

}

//Citirea listei de cumparaturi:
void produs::citirelista(fstream& citire)
{  
    int nr;
    citire.read((char*)&this->cod_produs, sizeof(int));

    citire.read((char*)&this->pret, sizeof(float));
    citire.read((char*)&this->c, sizeof(int));

    //citire dimensiuni si string-uri
    citire.read((char*)&nr, sizeof(int));

    char buffer[100];
    citire.read(buffer, nr * sizeof(char));
    this->nume = string(buffer);

    citire.read((char*)&nr, sizeof(int));

    char buffer1[100];
    citire.read(buffer1, nr * sizeof(char));
    this->categorie = string(buffer1);

}

//supraincarcari de operatori >> <<
ostream& operator<<(ostream& out, produs& p) {
    out << "\n" << "\tCod:\t" << p.cod_produs << "\tPret:\t" << p.pret << "\tCantitate:\t" << p.cantitate << "\tNume:\t" << p.nume << "\tCategorie:\t" << p.categorie;
    return out;
}

ifstream& operator>>(ifstream& citire, produs& p)
{
    citire >> p.cod_produs;
    getline(citire, p.nume);
    getline(citire, p.categorie);
    citire >> p.pret;
    citire >> p.cantitate;
    return citire;
}


//CERINTE SPECIFICE CLIENTULUI:

//1.AFISAREA STOCULUI DISPONIBIL IN MAGAZIN
void afisare()
{ //Afisarea stocului din magazin
    int i = 1;
    cout << "\n==================================================================";
    cout << "\n\n=================\tSTOCUL MAGAZINULUI\t==================";
    cout << "\n\n============================================================\n";
    fstream fisStoc("stoc.dat", ios::binary | ios::in);
    while (!fisStoc.eof())
    {
        p.citire(fisStoc);
        if (!fisStoc.eof())
        {
            if (fisStoc.tellg() < 0)
            {
                i = 0; break;
            }
            cout << p;
        }


    }

    // cout << "\n\n\t\t\t!!   Nu exista produse pe stoc   !!";
    fisStoc.close();

}

//2.INTRODUCEREA DE PRODUSE IN COSUL ELECTRONIC:
void produs::valoarecos(string temp, int c, int& sum)
{
    int i = 0;
    long pos = 0;
    fstream listacos("lista.dat", ios::out | ios::binary | ios::app );
    fstream fisStoc("stoc.dat", ios::in | ios::out | ios::binary);
    while (!fisStoc.eof())
    {
        pos = fisStoc.tellp();
        p.citire(fisStoc);
        if (p.fct(temp) == 0)
        {

            p.withd(c, sum);

            fisStoc.seekp(pos);
            p.scriere(fisStoc);
            this->c = c;
            p.scrierelista(listacos, this->c);
            cout << "\n\nProdus adaugat in cos!";

            i++;
            break;


        }

    }
    if (i != 1)
        cout << "\nProdusul nu a fost gasit";

    fisStoc.close();
    listacos.close();

}

//2.1CALCUL SUMA TOTALA DE PLATIT 
void adaugare_cos(int& n)
{
    char temp[100]; int c;
    int  id_comanda = 0;
    id_comanda++;
    int i = 0, suma = 0, SUM = 0;
    long pos = 0;
    afisare();
    cout << "\nComanda cu id-ul: " << id_comanda;

    if (n)
    {
        bool ok = 1;
        do
        {
            cout << "\n\nIntrodu numele produsului:  \n" << "\n";
            cin >> temp;
            cout << "\n\nCantitatea pe care doresti sa o cumperi: \n" << "\n";
            cin >> c;
            p.valoarecos(temp, c, suma);
            SUM += suma;

            cout << "\nPentru a mai adauga produse in cos introdu 1, altfel pentru a finaliza 0:   ";
            cin >> ok;
        } while (ok);
    }
    else cout << "Nu ai ales nimic de adaugat in cos!";

    cout << "\nTotal de plata: " << SUM;

    p.lista();


}

//AFISAREA LISTEI DE CUMPARATURI:
void produs::lista()
{
    int i = 1;
    cout << "\n==================================================================";
    cout << "\n\n=================\tLISTA CUMPARATURILOR\t==================";
    cout << "\n\n==================================================================\n";
    fstream lista("lista.dat", ios::binary | ios::in);
    while (!lista.eof())
    {
        p.citirelista(lista);
        if (!lista.eof())
        {
            if (lista.tellg() < 0)
            {
                i = 0; break;
            }
            cout << "\n" << " Cod: " << cod_produs << " Pret:  " << pret << " Cantitate cumparata:  " << c << "  Nume:  " << nume << " Categorie:  " << categorie << endl;
        }
    }

    lista.close();

}

//4.COMPLETAREA DATELOR PERSONALE ALE CLIENTULUI SI FINALIZAREA COMENZII:
void date_client::finalizarecomanda()
{
    ofstream raport("comanda.dat", ios::app | ios::binary | ios::out);
    bool ok;
    cout << "\nComanda dvs:";
    p.lista();

    cout << "\nDoresti sa finalizezi comanda? 1 pt DA 0 pt NU:\t";
    cin >> ok;
    if (ok)
    {

        cout << "\nIntroduceti datele personale:";
        cout << "\nUsername: "; cin >> this->username;
        cout << "\nNume: "; cin >> this->nume_cl;
        cout << "\nPrenume: "; cin >> this->prenume_cl;
        cout << "\nEmail: "; cin >> this->email;
        cout << "\nTelefon: "; cin >> this->telefon;
        cout << "\nLocalitate: "; cin >> this->localitate;

        cout << "\nVarsta: "; cin >> this->varsta;


        //adaugarea datelor in fisier binar nou:
        d.scrie(raport);
        com.scrieAWB(raport);
    }
    cout << "\n\nDate adaugate!";
    raport.close();
}


//CERINTE SPECIFICE MAGAZINULUI:

//1. ADAUGAREA DE PRODUSE
void add()
{
    int n;
    cout << "\nNr de produse de adaugat: ";
    cin >> n;

    if (n != 0)
    {
        fstream fisStoc("stoc.dat", ios::binary | ios::app | ios::out);
        for (int i = 0; i < n; i++)

        {
            cout << "\n\nIntroduceti codul, pretul, cantitatea , numele si categoria produsului pe care vreti sa-l adaugati:\n\n";
            p.getProdus();
            p.scriere(fisStoc);

        }
        cout << "\n\nStoc reactualizat!!";

        fisStoc.close();
        //cin.get();
        afisare();
    }
}


//3.STERGEREA DE PRODUSE DE PE STOC:
void stergere()
{

    fstream fistemp("temp.dat", ios::out| ios::binary | ios::app);
    fstream fisStoc("stoc.dat", ios::binary|ios::in);
    int i = 0;
    string aux;
    cout << "\n\t\t\t\tSTERGEREA UNUI PRODUS";
    cout << "\n\nEnter the name of the product:";
    cin >> aux;
    while (!fisStoc.eof())
    {

        p.citire(fisStoc);
        if (!fisStoc.eof())
        {
            if (p.fct(aux) == 0)// TRB SA MODIFICAM SA SE FACA STERGEREA IN FUNCTIE DE CODUL PRODUSULUI
            {
                cout << p;
                cout << "\n\n\t\tRecord deleted";
                i++;
            }
            else
                p.scriere(fistemp);
        }

    }
    if (i == 0)
        cout << "\n\n!!Record not found!!";
    fistemp.close();
    fisStoc.close();
    remove("stoc.dat");
    rename("temp.dat", "stoc.dat");
    afisare();

    cout << '\n' << '\n';
}

//2. EDITAREA DE PRODUSE:
void editare()
{
    string temp;
    bool ok = 1;
    int i = 0;  float discount;
    long pos = 0;
    fstream fisStoc("stoc.dat", ios::in | ios::out | ios::binary);
    do
    {
        cout << "\nNumele produsului pe care il reduceti: "; cin >> temp;
        while (!fisStoc.eof())
        {

        
            pos = fisStoc.tellp();
            p.citire(fisStoc);
            if (p.fct(temp) == 0)
            {
                cout << "\nProcentul de reducere aplicat este:  "; cin >> discount;
                p.aplicareducere(discount);

                fisStoc.seekp(pos);
                p.scriere(fisStoc);


                cout << "\n\nProdus modificat!";

                i++;
                break;
            }


        }
        cout << "\nPentru a continua editarea de produse scrieti 1, pt iesire 0"; cin >> ok;
    } while (ok);
   


    if (i != 1)
        cout << "\nProdusul nu a fost gasit";

    fisStoc.close();
}

//4.PRELUCRAREA COMENZILOR:
void comanda::comandacurier()
{
    ofstream raport("comanda.txt", ios::app);
    cout << "\n\n\n Firma de curierat:";
    cout << getfirma();
    cout << "\n\n\n Completeaza comanda cu AWB:";
    cin >> this->AWB;
    if (!raport.eof())
    {
        raport << getfirma() << " " << getAWB();
    }
    raport.close();
}



 void comanda::citirecomanda(fstream& citire)
 {
     int nr;
     fstream raport("comanda.dat", ios::binary | ios::in);
     char buffer[100];

     citire.read((char*)&this->varsta, sizeof(varsta));

     //citire dimensiuni si string-uri
     citire.read((char*)&nr, sizeof(int));

    
     citire.read(buffer, nr * sizeof(char));
     this->username = string(buffer);
     //........neterminat
     raport.close();

 }
 void comanda::afisarecomanda() 
 {     int i = 1;
     cout << "\n==================================================================";
     cout << "\n\n=================\tCOMANDA CLIENTULUI\t==================";
     cout << "\n\n==================================================================\n";
     fstream raport("comanda.dat", ios::binary|ios::in);
     while (!raport.eof())
     {
         
      
         com.citirecomanda(raport);
             cout << "\nDatele personale:";
             cout << "\nUsername: " << username<<"\tNume: "<<nume_cl<< "\tPrenume: "<<prenume_cl<< "\tEmail: "<<email << "\tTelefon: "<<telefon << "\tLocalitate: "<< localitate;
             cout << "\nVarsta: " << varsta;
             cout << "\nFirma curierat aleasa:" << getfirma() << "\nAWB:" << getAWB();
         
     }

     raport.close();

 }
 int main()
 {
  

     char parola[20] = "p";
     int x; int n;
     cout << "\n\t\t  ADMINISTRARE MAGAZIN DE PARFUMURI \n";
     cout << "\n=============================================================";
     cout << "\n\n\t\t   1. Meniul Angajatului \n\n\t\t   2. Meniul Clientului \n";
     cout << "\n\n=============================================================\n";
     cout << "\n\nAlegerea dumneavoastra:\t";
     cin >> x;
     bool conditie = 1;
         switch (x) {
         case 1: if (x == 1)
         {
             cout << "Introduceti parola pentru a continua:(parola este p)";
             char passw[20];  cin >> passw;
             if (strcmp(parola, passw) == 0)
             {
                 cout << "\n\n\n!!Conectarea s-a efectuat cu succes!!\n\n";
                 cout << "\n=================================================================";
                 meniumagz:
                 cout << "\n\n\t\t\t    Meniul Angajatului\n1. Adauga produse noi\n2. Afiseaza stocul magazinului\n3. Editarea de produse. Aplicarea de reduceri. \n4. Sterge produse din stoc\n5. Prelucrarea comenzilor.\n6. Iesire";
                 cout << "\n\n\n=======================================================";
                 cout << "\n\nAlegerea dumneavoastra:\t";
                 int i;
                 cin >> i;

                 if (i == 1)
                 {
                     add();
                     goto meniumagz;

                 }
                 else if (i == 2)
                 {
                     afisare();
                     goto meniumagz;
                 }
                 else if (i == 3)
                 {
                     editare();
                     afisare();
                     goto meniumagz;
                 }
                 else if (i == 4)
                 {
                     stergere();
                     goto meniumagz;
                 }
                 else if (i == 5)
                 {
                     com.comandacurier();
                     goto meniumagz;
                 }
                 else if (i==6)
                 {
                     exit(0);
                 }


             }
         }
         case 2: if (x == 2)
         {
         meniuclient:
             int j;
             cout << "\n=================================================================";
             cout << "\n\n\t\t\t    Meniul Clientului \n1. Adauga in cos\n2. Afiseaza stocul magazinului\n3. Completarea datelor personale si Finalizarea si trimiterea comenzii.\n4.Afiseaza lista de cumparaturi\n5.Afisare detalii comanda\n6.Iesire";
             cout << "\n\n\n=======================================================";
             cout << "\n\n Alegerea dumneavoastra:\t";
             cin >> j;

             if (j == 1)
             {
                 cout << "\n\n\n=======================================================";
                 cout << "\n\nNR de produse diferite de cumparat:\n" << "\n";
                 cin >> n;
                 adaugare_cos(n);
                 //p.lista();
                 goto meniuclient;
             }
             else if (j == 2)
             {
                 cout << "\n\n\n=======================================================";
                 afisare();
                 goto meniuclient;
             }
             else if (j == 3)
             {
               
                 cout << "\n\n\n=======================================================";
                 d.finalizarecomanda();
                 goto meniuclient;
             }
             else if (j == 4)
             {
                 cout << "\n\n\n=======================================================";
                 p.lista();
                 goto meniuclient;
             }
             else if (j == 5)
             {
                 cout << "\n\n\n=======================================================";
                 com.afisarecomanda();
                 goto meniuclient;
                
             }
             else if (j == 6)
             {
                 cout << "\n\n\n=======================================================";
                 exit(0);
             }

         }
         }
     

     
    //polimorfism:
         //pointeri la obiecte:
     produs* p1 = new reducere(1,930,51,"Dior","Dama", 130);
     produs p2(19, 392, 20, "Chanel", "Barbat");
    
     cont_client* c1 = new date_client("mirceaionescu13","Ionescu","Mircea","ion.mircea@gmail.com",19,"0726345891","Slobozia");
     date_client* c2 = new date_client("mihaii19", "Alexandrescu", "Mihai", "ion.mihaia@gmail.com", 35, "0726465891", "Bucuresti");
    
     //clasa interfata:
     p1->produs::arereducere();
     //operatori supraincarcati:
     //op +=
     p2 += 2;
     //operatorul functie:
     p2(25);
     //operatorul cast:
     cout << "\n(double)a3=" << (double)p2 << endl;
     //exceptiile custom:
     try {
         c2->settelef("0725231511");

         c1->setVarsta(16);
     }
     catch (Exceptievarsta* e) { 
         cout << e->functie() << "Eroare nu este fatala. Programul poate sa mearga mai departe" << endl;
     }
     catch (Exceptietelf* e) {
         cout << e->functie() << "Eroare nu este fatala. Programul poate sa mearga mai departe" << endl;
     }
 }