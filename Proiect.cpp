
#include <iostream>
#include <string>
#include <fstream>
#pragma warning (disable: 4996)
using namespace std;
class Teatru {
private:
    char* denumire;
    string locatie;
    int zone;
    int* locuri;
public:
    Teatru() {
        denumire = new char[strlen("Necunoscuta") + 1];
        strcpy(denumire, "Necunoscuta");
        locatie = "Necunoscuta";
        zone = 0;
        locuri = NULL;
    }
    Teatru(char* denumire, string locatie, int zone, int* locuri)
    {
        if (strlen(denumire) > 2) {
            this->denumire = new char[strlen(denumire) + 1];
            strcpy(this->denumire, denumire);
        }
        else {
            this->denumire = new char[strlen("Necunoscuta") + 1];
            strcpy(this->denumire, "Necunoscuta");
        }
        if(size(locatie)>2)
        this->locatie = locatie;
        if (zone >= 0)
            this->zone = zone;
        else this->zone = 0;
        if (this->zone > 0 && locuri != NULL)
        {
            this->locuri = new int[zone];
            for (int i = 0;i < zone;i++)
                this->locuri[i] = locuri[i];
        }
        else this->locuri = NULL;

    }
    Teatru(const Teatru& s) {
        this->denumire = new char[strlen(s.denumire) + 1];
        strcpy(this->denumire, s.denumire);
        this->locatie = s.locatie;
        this->zone = s.zone;
        if (this->zone > 0 && s.locuri != NULL)
        {
            this->locuri = new int[s.zone];
            for (int i = 0;i < s.zone;i++)
                this->locuri[i] = s.locuri[i];
        }
    }
    char* getDenumire() {
        return this->denumire;
    }
    void setDenumire(char* denumire) 
    {
        if (strlen(denumire) > 2)
        {
            delete[] this->denumire;
            this->denumire = new char[strlen(denumire) + 1];
            strcpy(this->denumire, denumire);
        }
    }
    string getLocatie()
    {
        return this->locatie;
    }
    void setLocatie(string locatie)
    {
        if (size(locatie) > 2)
        {
            this->locatie = locatie;
        }
    }
    int getZone() {
        return this->zone;
    }
    void setZone(int zone) 
    {
        if (zone > 0)
        {
            
            int* copie;
            copie = new int[zone];
            for (int j = 0;j <zone;j++)
                copie[j] = 0;
            if (this->locuri != NULL)
            {
                int min;
                if (this->zone < zone) min = this->zone;
                else min = zone;
                for (int i = 0;i <min;i++)
                    copie[i] = this->locuri[i];
            }
            this->locuri = copie; 
            this->zone = zone;
        }

    }
    int getLocuri(int i) {
        return this->locuri[i];
    }
    void setLocuri(int zona, int locuri)
    {
        if (locuri > 0 && zona > 0 && zona <= this->zone)
            this->locuri[zona-1] = locuri;
    }
    Teatru& operator=(const Teatru& s)
    {
        if (this != &s)
        {   delete[] this->denumire;
            delete[] this->locuri;
            this->denumire = new char[strlen(s.denumire) + 1];
            strcpy(this->denumire, s.denumire);
            this->locatie = s.locatie;
            this->zone = s.zone;
            if (this->zone > 0 && s.locuri != NULL)
            {
                this->locuri = new int[s.zone];
                for (int i = 0;i < s.zone;i++)
                    this->locuri[i] = s.locuri[i];
            }
            
        }
        return *this;
    }

    void operator[](int index)
    {
        int nr;
        cout << "\nNoul numar de locuri pentru zona " << index << " este:";
        cin >> nr;
        if (index >= 0 && index < this->zone)
            this->locuri[index] = nr;
    }
    bool operator!() {
        if (this->zone == 0) {
            return true;
        }
        return false;
    }
    operator float() {
        float s = 0;
        for (int i = 0;i < this->zone;i++)
        {
            s += locuri[i];
        }
        return s / this->zone;
    }
    Teatru operator++() {
        this->zone=this->zone+1;
        int* copie = new int[this->zone];
        for (int i = 0;i < this->zone-1;i++)
            copie[i] = locuri[i];
        copie[this->zone-1] = 0;
        delete[] this->locuri;
        this->locuri = copie;
        return *this;
         }
    Teatru operator++(int)
    {
        Teatru copie(*this);
        this->zone++;
        delete[] this->locuri;
        this->locuri = new int[this->zone];
        for (int i = 0;i < this->zone - 1;i++)
            this->locuri[i] = copie.locuri[i];
        this->locuri[this->zone - 1] = 0;
        return copie;
    }
    Teatru operator+(int n) {
        for (int i = 0;i < this->zone;i++)
            this->locuri[i] += n;
       return *this;
    }
    bool operator==(Teatru& s) {
        if (*this->denumire != *s.denumire || this->locatie!=s.locatie || this->zone!=s.zone)
            return false; 
        for (int i = 0;i < s.zone;i++)
            if (s.locuri[i] != this->locuri[i]) return false;
        return true;

    }
    bool operator<(Teatru& s) {
        int aux1=0, aux2=0;
        for (int i = 0;i < this->zone;i++)
            aux1 += this->locuri[i];
        for (int  i = 0;i < s.zone;i++)
            aux2 += s.locuri[i];
        if (aux1 < aux2) return true;
        return false;
    }
    ~Teatru() {
        delete[] this->denumire;
        delete[] this->locuri;
    }
    friend istream& operator>>(istream& in, Teatru& s)
    {
        delete[] s.denumire;
        delete[] s.locuri;
        cout << "\nIntroduceti denumire:";
        char aux[100];
        in >> aux;
        s.denumire = new char[strlen(aux) + 1];
        strcpy(s.denumire, aux);
        cout << "Introduceti locatia:";
        in >> s.locatie;
        cout << "Introduceti nr zone:";
        in >> s.zone;
        if (s.zone != 0)
        {
            s.locuri = new int[s.zone];
            for (int i = 0;i < s.zone;i++)
            {
                cout << "Introduceti locuri zona " << i+1<< ":";
                in >> s.locuri[i];
            }
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, const Teatru& s)
    {
        out << "\n------------------------------------";
        out << "\nDenumirea teatrului este:" << s.denumire;
        out << "\nLocatia teatrului este:" << s.locatie;
        out << "\nNumarul de zone ale teatrului:" << s.zone;
        for (int i = 0;i < s.zone;i++)
            out << "\nNumarul de locuri din zona " << i+1 << " este:" << s.locuri[i];
        return out;
    }
    void afisare()
    {
        cout << "\n------------------------------";
        cout << "\nDenumirea teatrului este:" << this->denumire;
        cout << "\nLocatia teatrului este:" << this->locatie;
        cout << "\nNumarun de zone ale teatrului:" << this->zone;
        for(int i=0;i<this->zone;i++)
        cout << "\nNumarul de locuri din zone " << i+1 << " este:" << this->locuri[i];
    }
    void writeToFile(fstream& f)
    {
        int lg1 = strlen(this->denumire) + 1;
        f.write((char*)&lg1, sizeof(int));
        f.write(this->denumire, lg1 * sizeof(char));

        int lg = this->locatie.length() + 1;
        f.write((char*)&lg, sizeof(int));
        f.write(this->locatie.data(), lg * sizeof(char));

        f.write((char*)&this->zone, sizeof(int));
        for (int i = 0; i < this->zone; i++)
            f.write((char*)&this->locuri[i], sizeof(int));

    }
    void readFromFile(fstream& f)
    {
        int lg;
        f.read((char*)&lg, sizeof(int));
        char* copie = new char[lg];
        f.read(copie, lg);
        if (strlen(copie) > 1)
        {
            delete[] this->denumire;
            this->denumire = new char[lg];
            strcpy(this->denumire, copie);

        }
        delete[] copie;
        f.read((char*)&lg, sizeof(int));
        copie = new char[lg];
        f.read(copie, lg);
        this->locatie = copie;
        delete[] copie;
        f.read((char*)&this->zone, sizeof(int));
        delete[] this->locuri;
        this->locuri = new int[this->zone];
        for (int i = 0;i < this->zone;i++)
        {
            f.read((char*)&this->locuri[i], sizeof(int));
        }


    }
    
};
class Abstract
{
public:
    virtual void readFile(fstream& f) = 0;
    virtual void writeFile(fstream& f) = 0;
};
class Angajat
{
protected:
    const int cod;
    string nume;
    string prenume;
    float salariu;
    int zileLucrate;
    float* oreLucrate;
    static int count;
public:
    Angajat() :cod(++count)
    {
        this->nume = "Anonim";
        this->prenume = "Anonim";
        this->salariu = 0;
        this->zileLucrate = 0;
        this->oreLucrate = NULL;

    }
    Angajat(string nume, string prenume, float salariu, int zileLucrate, float* oreLucrate) :cod(++count)
    {
        if (size(nume) > 2) this->nume = nume;
        if (size(prenume) > 2) this->prenume = prenume;
        if (salariu >= 0)   this->salariu = salariu; else this->salariu = 0;
        if (zileLucrate > 0)
        {
            this->zileLucrate = zileLucrate;
            this->oreLucrate = new float[zileLucrate];
            for (int i = 0;i < zileLucrate;i++)
                this->oreLucrate[i] = oreLucrate[i];
        }
        else {
            this->zileLucrate = 0;
            this->oreLucrate = NULL;
        }
    }
    Angajat(const Angajat& s) :cod(++count)
    {
        if (size(s.nume) > 2) this->nume = s.nume;
        if (size(s.prenume) > 2) this->prenume = s.prenume;
        if (s.salariu >= 0) this->salariu = s.salariu; else this->salariu = 0;
        if (s.zileLucrate > 0)
        {
            this->zileLucrate = s.zileLucrate;
            this->oreLucrate = new float[s.zileLucrate];
            for (int i = 0;i < s.zileLucrate;i++)
                this->oreLucrate[i] = s.oreLucrate[i];
        }
        else {
            this->zileLucrate = 0;
            this->oreLucrate = NULL;
        }
    }
    int getCod()
    {
        return this->cod;
    }
    string getNume()
    {
        return this->nume;
    }
    string getPrenume()
    {
        return this->prenume;
    }
    float getSalariu()
    {
        return this->salariu;
    }
    int getZileLucrate()
    {
        return this->zileLucrate;
    }
    float* getOreLucrate()
    {
        return this->oreLucrate;
    }
    void setNume(string nume)
    {
        if (size(nume) > 2) this->nume = nume;
    }
    void setPrenume(string prenume)
    {
        if (size(prenume) > 2) this->prenume = prenume;
    }
    void setSalariu(float salariu)
    {
        if (salariu >= 0) this->salariu = salariu;
    }
    void setLucru(int zile, float* ore)
    {
        delete[] this->oreLucrate;
        if (zile >= 0) {
            this->zileLucrate = zile;
            this->oreLucrate = new float[zile];
            for (int i = 0;i < zile;i++)
                this->oreLucrate[i] = ore[i];
        }
    }
    Angajat& operator=(const Angajat& a)
    {
        if (this != &a)
        {
            delete[] this->oreLucrate;
            this->nume = a.nume;
            this->prenume = a.prenume;
            this->salariu = a.salariu;
            this->zileLucrate = a.zileLucrate;
            this->oreLucrate = new float[a.zileLucrate];
            for (int i = 0;i < this->zileLucrate;i++)
                this->oreLucrate[i] = a.oreLucrate[i];
        }
        return *this;
    }
    Angajat& operator+(float suma) {
        if (this->salariu + suma > 0)
            this->salariu = this->salariu + suma;
        return *this;
    }
    Angajat& operator-(float suma) {
        if (this->salariu - suma > 0)
            this->salariu = this->salariu - suma;
        return *this;
    }
    Angajat& operator++()
    {
        this->salariu += 100;
        return *this;
    }
    Angajat& operator++(int)
    {
        Angajat copie(*this);
        this->salariu = this->salariu + 100;
        return copie;
    }
    Angajat& operator--()
    {
        this->salariu -= 100;
        return *this;
    }
    Angajat& operator--(int)
    {
        Angajat copie(*this);
        this->salariu -= 100;
        return copie;
    }
    operator float() {
        float aux = 0;
        for (int i = 0;i < this->zileLucrate;i++)
            aux += this->oreLucrate[i];
        return aux;
    }
    float operator[](int index) {
        return this->oreLucrate[index];
    }
    bool operator!() {
        if (this->zileLucrate = 0) return true;
        else return false;
    }
    bool operator==(Angajat& s) {
        if (this->prenume != s.prenume || this->nume != s.nume || this->salariu != s.salariu || this->zileLucrate != s.zileLucrate)
            return false;
        for (int i = 0;i < this->zileLucrate;i++)
            if (this->oreLucrate[i] != s.oreLucrate[i]) return false;
        return true;

    }
    bool operator<(Angajat& s) {
        if (this->salariu < s.salariu)
            return true;
        else return false;
    }
    bool operator>(Angajat& s) {
        if (this->salariu > s.salariu)
            return true;
        else return false;
    }
    bool operator<=(Angajat& s) {
        if (this->salariu <= s.salariu)
            return true;
        else return false;
    }
    bool operator>=(Angajat& s) {
        if (this->salariu >= s.salariu)
            return true;
        else return false;
    }
    ~Angajat() {
        count--;
        delete[] this->oreLucrate;
    }
    friend ostream& operator<<(ostream& out, const Angajat a)
    {
        out << "\n----------------------------------";
        out << "\nCodul angajatului este:" << a.cod;
        out << "\nNumele angajatului este:" << a.nume;
        out << "\nPrenumele angsajatului este:" << a.prenume;
        out << "\nSalariul angajatului este:" << a.salariu;
        out << " \nNumarul de zile lucrate este:" << a.zileLucrate;
        out << "\nOrele lucrate zilnic:";
        for (int i = 0;i < a.zileLucrate;i++) cout << a.oreLucrate[i] << " ";
        return out;
    }
    friend istream& operator>>(istream& in, Angajat& a)
    {
        cout << "\nIntroduceti nume:";
        in >> a.nume;
        cout << "Introduceti prenume:";
        in >> a.prenume;
        cout << "Introduceti salariu:";
        in >> a.salariu;
        cout << "Introduceti nr zile lucrate:";
        in >> a.zileLucrate;
        delete[] a.oreLucrate;
        a.oreLucrate = new float[a.zileLucrate];
        for (int i = 0;i < a.zileLucrate;i++)
        {
            cout << "Introduceti nr ore ziua " << i << ":";
            in >> a.oreLucrate[i];
        }
        return in;
    }
    void writeToFile(fstream& f)
    {
        //const int cod;
        //string nume;
        //string prenume;
        //float salariu;
        //int zileLucrate;
        //float* oreLucrate;
        //static int count;
        int lg = this->nume.length() + 1;
        f.write((char*)&lg, sizeof(int));
        f.write(this->nume.data(), lg * sizeof(char));
        int lg2 = this->prenume.length() + 1;
        f.write((char*)&lg2, sizeof(int));
        f.write(this->prenume.data(), lg2 * sizeof(char));
        f.write((char*)&this->salariu, sizeof(float));
        f.write((char*)&this->zileLucrate, sizeof(int));
        for (int i = 0;i < this->zileLucrate; i++)
        {
            f.write((char*)&this->oreLucrate[i], sizeof(float));
        }
    }
    void readFromFile(fstream& f)
    {
        int lg;
        f.read((char*)&lg, sizeof(int));
        f.read((char*)&this->nume, lg * sizeof(char));
        int lg2;
        f.read((char*)&lg2, sizeof(int));
        f.read((char*)&this->prenume, lg2 * sizeof(char));
        f.read((char*)&this->salariu, sizeof(float));
        f.read((char*)&this->zileLucrate, sizeof(int));
        if (this->zileLucrate > 0)
        {
            delete[] this->oreLucrate;
            this->oreLucrate = new float[zileLucrate];
            for (int i = 0;i < this->zileLucrate; i++)
            {
                f.read((char*)&this->oreLucrate[i], sizeof(float));
            }
        }

    }
    virtual float CalculSalariu()
    {
        float suma = 0;
        for (int i = 0;i < this->zileLucrate;i++)
        {
            suma += this->salariu * this->oreLucrate[i];
        }
        return suma;
    }
}
;
int Angajat::count = 0;
class Actor :public Angajat, public Abstract
{
private:
    int nrSpectacole = 0;
    int* Reprezentatii = NULL;
public:
    Actor() :Angajat()
    {}
    Actor(string nume, string prenume, float salariu, int zileLucrate, float* oreLucrate, int nrSpectacole, int* Reprezentatii)
        :Angajat(nume, prenume, salariu, zileLucrate, oreLucrate)
    {
        if (nrSpectacole > 0)
        {
            this->nrSpectacole = nrSpectacole;
            if (Reprezentatii != NULL)
            {
                this->Reprezentatii = new int[this->nrSpectacole];
                for (int i = 0;i < this->nrSpectacole;i++)
                {
                    this->Reprezentatii[i] = Reprezentatii[i];
                }
            }
        }
    }
    Actor(const Angajat& a, int nrSpectacole, int* Reprezentatii) :Angajat(a)
    {
        this->nrSpectacole = nrSpectacole;
        this->Reprezentatii = new int[this->nrSpectacole];
        for (int i = 0;i < this->nrSpectacole;i++)
            this->Reprezentatii[i] = Reprezentatii[i];
    }

    Actor(const Actor& a) :Angajat(a)
    {
        this->nrSpectacole = a.nrSpectacole;
        this->Reprezentatii = new int[this->nrSpectacole];
        for (int i = 0;i < this->nrSpectacole;i++)
            this->Reprezentatii[i] = a.Reprezentatii[i];
    }
    Actor& operator=(const Actor& a)
    {
        if (this != &a)
        {
            Actor::operator=(a);
            this->nrSpectacole = a.nrSpectacole;
            delete[] this->Reprezentatii;
            this->Reprezentatii = new int[this->nrSpectacole];
            for (int i = 0;i < this->nrSpectacole;i++)
                this->Reprezentatii[i] = a.Reprezentatii[i];
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Actor& a)
    {
        out << (Angajat)a;
        out << "\nNumarul de spectacole:" << a.nrSpectacole;
        for (int i = 0;i < a.nrSpectacole;i++)
        {
            out << "\nNumarul de reprezentatii al spectacolului " << i << " :" << a.Reprezentatii[i];
        }
        return out;
    }
    float CalculSalariu()
    {
        float suma = 0;
        suma = Angajat::CalculSalariu();
        for (int i = 0;i < this->nrSpectacole;i++)
        {
            suma += this->Reprezentatii[i] * 200;
        }
        return suma;
    }
    void writeFile(fstream& f)
    {
        int lg = this->nume.length() + 1;
        f.write((char*)&lg, sizeof(int));
        f.write(this->nume.data(), lg * sizeof(char));
        int lg2 = this->prenume.length() + 1;
        f.write((char*)&lg2, sizeof(int));
        f.write(this->prenume.data(), lg2 * sizeof(char));
        f.write((char*)&this->salariu, sizeof(float));
        f.write((char*)&this->zileLucrate, sizeof(int));
        for (int i = 0;i < this->zileLucrate; i++)
        {
            f.write((char*)&this->oreLucrate[i], sizeof(float));
        }
        f.write((char*)&this->nrSpectacole, sizeof(int));
        for (int i = 0;i < this->nrSpectacole;i++)
            f.write((char*)&this->Reprezentatii[i], sizeof(int));
    }
    void readFile(fstream& f)
    {
        int lg;
        f.read((char*)&lg, sizeof(int));
        f.read((char*)&this->nume, lg * sizeof(char));
        int lg2;
        f.read((char*)&lg2, sizeof(int));
        f.read((char*)&this->prenume, lg2 * sizeof(char));
        f.read((char*)&this->salariu, sizeof(float));
        f.read((char*)&this->zileLucrate, sizeof(int));
        if (this->zileLucrate > 0)
        {
            
            for (int i = 0;i < this->zileLucrate; i++)
            {
                f.read((char*)&this->oreLucrate[i], sizeof(float));
            }
        }
        f.read((char*)&this->nrSpectacole, sizeof(int));
       
        for (int i = 0;i < this->nrSpectacole;i++)
            f.read((char*)&this->Reprezentatii[i], sizeof(int));
    }

    ~Actor()
    {
        delete[] this->Reprezentatii;
    }
};
class Spectacol
{
private:
    char* nume;
    char* data;
    Teatru locatie;
public:
    Spectacol()
    {
        this->nume = new char[15];
        this->data = new char[15];
        strcpy(this->nume, "Necunoscut");
        strcpy(this->data, "Necunoscut");
    }
    Spectacol(char* nume, char* data, Teatru locatie)
    {
        if (strlen(nume) > 2)
        {
            this->nume = new char[strlen(nume)+ 1];
            strcpy(this->nume, nume);
        }
        if (strlen(data) > 2)
        {
            this->data = new char[strlen(nume) + 1];
            strcpy(this->data, data);
        }
        this->locatie = locatie;
    }
    Spectacol(const Spectacol& s)
    {
        this->nume = new char[strlen(s.nume) + 1];
        strcpy(this->nume, s.nume);
        this->data = new char[strlen(s.data) + 1];
        strcpy(this->data, s.data);
        this->locatie = s.locatie;
    }
    char* getNume()
    {
        return this->nume;
    }
    char* getData()
    {
        return this->data;
    }
    Teatru getLocatie()
    {
        return this->locatie;
    }
    void setNume(char nume[])
    {
        if (strlen(nume) > 2)
        {
            delete[] this->nume;
            this->nume = new char[strlen(nume) + 1];
            strcpy(this->nume, nume);
        }
    }
    void setData(char data[])
    {
        if (strlen(data) > 2)
        {
            delete[] this->data;
            this->data = new char[strlen(data) + 1];
            strcpy(this->data, data);
        }
    }
    void setLocatie(Teatru t)
    {
            this->locatie = t;
    }
    Spectacol& operator=(const Spectacol& s)
    {
        if (this != &s)
        {
            delete[] this->nume;
            delete[] this->data;
            this->nume = new char[strlen(s.nume) + 1];
            strcpy(this->nume, s.nume);
            this->data = new char[strlen(s.data) + 1];
            strcpy(this->data, s.data);
            this->locatie = s.locatie;
        }
        return *this;
    }
    Spectacol operator++() {
        int zone = this->locatie.getZone();
        this->locatie.setZone(zone + 1);
        this->locatie.setLocuri(zone + 1, 0);
        return *this;
    }
    Spectacol operator++(int)
    {
        Spectacol copie(*this);
        int zone = this->locatie.getZone();
        this->locatie.setZone(zone + 1);
        this->locatie.setLocuri(zone + 1, 0);
        return copie;
    }
    int operator[](int index) {
        return this->locatie.getLocuri(index);
    }
    operator float() {
        float s = 0;
        for (int i = 0;i < this->locatie.getZone();i++)
        {
            s += this->locatie.getLocuri(i);
        }
        return s / this->locatie.getZone();
    }
    Spectacol operator+(int n)
    {
        for (int i = 0;i < this->locatie.getZone();i++)
        {
            this->locatie.setLocuri(i, this->locatie.getLocuri(i) + n);
        }
        return *this;
    }
    bool operator==(Spectacol& s) 
    {
        if (*this->data != *s.data || *this->nume!=*s.nume|| this->locatie!=s.locatie)return false; 
        return true;
    }
    bool operator!() {
        if (this->locatie.getZone() == 0) {
            return true;
        }
        return false;
    }
    bool operator<(Spectacol& s) {
        int aux1 = 0, aux2 = 0;
        for (int i = 0;i < this->locatie.getZone();i++)
            aux1 += this->locatie.getLocuri(i);
        for (int i = 0;i < s.locatie.getZone();i++)
            aux2 += s.locatie.getLocuri(i);
        if (aux1 < aux2) return true;
        return false;
    }
    bool operator>(Spectacol& s) {
        int aux1 = 0, aux2 = 0;
        for (int i = 0;i < this->locatie.getZone();i++)
            aux1 += this->locatie.getLocuri(i);
        for (int i = 0;i < s.locatie.getZone();i++)
            aux2 += s.locatie.getLocuri(i);
        if (aux1 > aux2) return true;
        return false;
    }
    ~Spectacol()
    {
        delete[] this->data;
        delete[] this->nume;
    }
    friend ostream& operator<<(ostream& out, const Spectacol& s)
    {
        out << "\n---------------------------------------";
        out << "\nNume spectacol:" << s.nume;
        out << "\nData spectacol:" << s.data;
        out << "\nLocatia spectacolului este:" << s.locatie;
        return out;
    }
    friend istream& operator>>(istream& in, Spectacol& s)
    {
        char aux[100];
        cout << "Introduceti numele spectacolului:";
        in >> aux;
        if(strlen(aux)>2)
        {
            delete[] s.nume;
            s.nume = new char[strlen(aux) + 1];
            strcpy(s.nume, aux);
        }
        cout << "Introduceti data spectacolului:";
        in >> aux;
        if (strlen(aux) > 2)
        {
            delete[] s.data;
            s.data = new char[strlen(aux) + 1];
            strcpy(s.data, aux);
        }
        cout << "Introduceti locatia specatcolului:";
        in >> s.locatie;
        return in;
    }
};
class Comanda
{ 
private:
    string numeSpectacol = "Necunoscut";
    int clasa=1;  // clasa=popularitate(pt determinarea pretului comenzii)
    int randuri=0;
    int* locuri;
    bool **bilete;
public:
    Comanda() {
        this->locuri = NULL;
        this->bilete = NULL;
    }
    Comanda(string numeSpectacol, int clasa, int randuri, int* locuri, bool** bilete)
    {
        if (size(numeSpectacol) > 2)
            this->numeSpectacol = numeSpectacol;
        else numeSpectacol = "Necunoscut";
        if (clasa > 0 && clasa < 6) this->clasa = clasa;
        else this->clasa = 1;
        if (randuri > 0)
        {
            this->randuri = randuri;
        }
        if (locuri != NULL)
        {
            this->locuri = new int[this->randuri];
            this->bilete = new bool* [this->randuri];
            for (int i = 0;i < this->randuri;i++)
            {
                this->locuri[i] = locuri[i];
                this->bilete[i] = new bool[locuri[i]];
            }
            if (bilete != NULL)
                for (int i = 0;i < this->randuri;i++)
                    for (int j = 0;j < this->locuri[i];j++)
                        this->bilete[i][j] = bilete[i][j];
        }
        else {
            this->locuri = NULL;
            this->bilete = NULL;
        }

    }
    Comanda(const Comanda& c) {
        this->numeSpectacol = c.numeSpectacol;
        this->clasa = c.clasa;
        this->randuri = c.randuri;
        this->locuri = new int[this->randuri];
        this->bilete = new bool*[this->randuri];
        for (int i = 0;i < this->randuri;i++)
        {
            this->locuri[i] = c.locuri[i];
            this->bilete[i] = new bool[c.locuri[i]];
        }
        for (int i = 0;i < this->randuri;i++)
            for (int j = 0;j <this->locuri[i];j++)
                this->bilete[i][j] = c.bilete[i][j];

    }
    string getNumeSpectacol()
    {
        return this->numeSpectacol;
    }
    int getClasa()
    {
        return this->clasa;
    }
    int getRanduri()
    {
        return this->randuri;
    }
    int getLocuri(int rand)
    {
        return this->locuri[rand];
    }
    bool getBilet(int rand, int loc)
    {
        return this->bilete[rand][loc];
    }
    void setNumeSpectacol(string nume)
    {
        this->numeSpectacol = nume;
    }
    void setClasa(int clasa)
    {
        this->clasa = clasa;
    }
    
    void setLocuri(int rand, int locuri)
    {
        this->locuri[rand] = locuri;
    }
    void setBilete(int rand, int loc, bool bilet)
    {   
        this->bilete[rand][loc] = bilet;
    }
    Comanda& operator=(const Comanda& c)
    {
        if (this != &c)
        {
            for (int i = 0;i < this->randuri;i++)
                delete[] this->bilete[i];
            delete[] this->bilete;
            delete[] this->locuri;
            this->numeSpectacol = c.numeSpectacol;
            this->clasa = c.clasa;
            this->randuri = c.randuri;
            this->locuri = new int[this->randuri];
            this->bilete = new bool* [this->randuri];
            for (int i = 0;i < this->randuri;i++)
            {
                this->locuri[i] = c.locuri[i];
                this->bilete[i] = new bool[c.locuri[i]];
            }
            for (int i = 0;i < this->randuri;i++)
                for (int j = 0;j < this->locuri[i];j++)
                    this->bilete[i][j] = c.bilete[i][j];
        }
        return *this;
    }
    operator float() 
    {
        float ocupate = 0;
        float totale = 0;
        for (int i = 0;i < this->randuri;i++)
            for (int j = 0;j < this->locuri[i];j++)
            {
                totale++;
                if (this->bilete[i][j]) ocupate++;
            }
        return ocupate / totale*100;
    }
    Comanda operator++()
    {
        int ok = 0,i=0,j=0;
        while (i < this->randuri && ok==0)
        {
            j = 0;
            while (j < this->locuri[i] && ok == 0)
            {
                if (!this->bilete[i][j]) {
                    ok = 1;
                    this->bilete[i][j] = 1;
                }
                j++;
            }
            i++;
        }
        return *this;
    }
    Comanda operator++(int)
    {
        Comanda copie(*this);
        int ok = 0, i = 0, j = 0;
        while (i < this->randuri && ok == 0)
        {
            j = 0;
            while (j < this->locuri[i] && ok == 0)
            {
                if (this->bilete[i][j] == 0) {
                    ok = 1;
                    this->bilete[i][j] = 1;
                }
                j++;
            }
            i++;
        }
        return copie;
    }
    Comanda operator+(int nr)
    {
        if (this->clasa + nr <= 6 && this->clasa+nr >= 1)
            this->clasa += nr;
        return *this;
    }
    Comanda operator-(int nr)
    {
        if (this->clasa - nr <= 6 && this->clasa - nr >= 1)
            this->clasa -= nr;
        return *this;
    }
    int operator[](int index) 
    {
        int suma = 0;
        if (index < this->randuri)
        {
            for (int i = 0;i < this->locuri[index];i++)
                if (this->bilete[index][i]) suma++;
        }
        return suma;
    }
    bool operator<(Comanda& c)
    {
        int b1 = 0, b2 = 0;
        for (int i = 0;i < this->randuri;i++)
            for (int j = 0;j < this->locuri[i];j++)
                if (this->bilete[i][j]) b1++;
        for (int i = 0;i < c.randuri;i++)
            for (int j = 0;j < c.locuri[i];j++)
                if (c.bilete[i][j]) b2++;
        if (b1 < b2) return true;
        else return false;
    }
    bool operator>(Comanda& c)
    {
        int b1 = 0, b2 = 0;
        for (int i = 0;i < this->randuri;i++)
            for (int j = 0;j < this->locuri[i];j++)
                if (this->bilete[i][j]) b1++;
        for (int i = 0;i < c.randuri;i++)
            for (int j = 0;j < c.locuri[i];j++)
                if (c.bilete[i][j]) b2++;
        if (b1 > b2) return true;
        else return false;
    }
    bool operator==(Comanda& c)
    {
        if (this->numeSpectacol != c.numeSpectacol || this->clasa != c.clasa || this->randuri != c.randuri)
            return false;
        for (int i = 0;i < this->randuri;i++)
            if (this->locuri[i] != c.locuri[i]) return false;
        for (int i = 0;i < this->randuri;i++)
        {
            for (int j = 0;j < this->locuri[i];j++)
                if (this->bilete[i][j] != c.bilete[i][j]) return false;
        }
        return true;
    }bool operator!() 
    {
        for (int i = 0;i < this->randuri;i++)
            for (int j = 0;j < this->locuri[i];j++)
                if (this->bilete[i][j]) return false;
        return true;
    }
    ~Comanda() {
        for (int i = 0;i < this->randuri;i++)
            delete[] this->bilete[i];
        delete[] this->bilete;
        delete[] this->locuri;
    }
    friend ostream& operator<<(ostream& out, const Comanda c)
    {
        out << "\n---------------------------------------";
        out << "\nNumele spectacolului este:" <<c.numeSpectacol;
        out << "\nClasa spectacolui este:"<<c.clasa;
        out << "\nNumarul de randuri este:" << c.randuri;
        for(int i=0;i<c.randuri;i++)
        out << "\nNumarul locuri pe randul "<<i<<" este:" <<c.locuri[i];
        out << "\nLocurile sunt:";
            for (int i = 0;i < c.randuri;i++)
            {
                out <<"\n";
                for (int j = 0;j < c.locuri[i];j++)
                    out <<c.bilete[i][j] << " ";
            }
        return out;
    }
    friend istream& operator>>(istream& in, Comanda& c)
    {
        for (int i = 0;i <c.randuri;i++)
            delete[] c.bilete[i];
        delete[] c.bilete;
        delete[] c.locuri;
        cout << "\nIntroduceti nume spectacol: ";
        in >>c.numeSpectacol;
        cout << "Introduceti clasa spectacolului:";
        in >>c.clasa;
        cout << "Introduceti numarul de randuri:";
        in >> c.randuri;
        c.locuri = new int[c.randuri];
        c.bilete = new bool*[c.randuri];
        for (int i = 0;i < c.randuri;i++)
        {
            cout << "Introduceti numarul de locuri pe randul " << i<<":";
            in >> c.locuri[i];
            c.bilete[i] = new bool[c.locuri[i]];
        }
        for (int i = 0;i < c.randuri;i++)
            for (int j = 0;j < c.locuri[i];j++)
            {
                cout << "Este locul " << j << " de pe randul " << i << " ocupat?(1=da,0=nu)";
                in >> c.bilete[i][j];
            }
        return in;
    }
    void writeToFile(fstream& f)
    {
        //string numeSpectacol = "Necunoscut";
        //int clasa = 1;  // clasa=popularitate(pt determinarea pretului comenzii)
        //int randuri = 0;
        //int* locuri;
        //bool** bilete;
        int lg = this->numeSpectacol.length() + 1;
        f.write((char*)&lg, sizeof(int));
        f.write((char*)&this->numeSpectacol, lg * sizeof(char));
        f.write((char*)&this->clasa, sizeof(int));
        f.write((char*)&this->randuri, sizeof(int));
        for (int i = 0;i < this->randuri;i++)
            f.write((char*)&this->locuri[i], sizeof(int));
        for (int i = 0;i < this->randuri;i++)
            for (int j = 0;j < this->locuri[i];j++)
                f.write((char*)&bilete[i][j], sizeof(bool));
    }
    void readFromFile(fstream& f)
    {
        int lg;
        f.read((char*)&lg, sizeof(int));
        f.read((char*)&this->numeSpectacol, lg);
        f.read((char*)&this->clasa, sizeof(int));
        f.read((char*)&this->randuri, sizeof(int));
        if (this->randuri > 0)
        {

            for (int i = 0;i < this->randuri;i++)
            {
                f.read((char*)&this->locuri[i], sizeof(int));

            }
            for (int k = 0;k < this->randuri;k++)
                for (int j = 0;j < this->locuri[k];j++)
                    f.read((char*)&this->bilete[k][j], sizeof(bool));
        }
    }
};
class Decor
{
private:
    int elemente;
    string* recuzita;
    int cantitate[10];
public:
    Decor()
    {
        this->elemente = 0;
        this->recuzita = NULL;
        for (int i = 0;i < 10;i++)
            this->cantitate[i] = 0;
    }
    Decor(int elemente, string* recuzita, int cantitate[])
    {
        if (elemente > 0)
        {
            this->elemente = elemente;
            for (int i = 0;i < this->elemente;i++)
                this->cantitate[i] = cantitate[i];
            if (recuzita != NULL)
            {
                this->recuzita = new string[this->elemente];
                for (int i = 0;i < this->elemente;i++)
                    this->recuzita[i] = recuzita[i];
            }
            else this->recuzita = NULL;

        }
        else {
            this->elemente = 0;
            for (int i = 0;i < 10;i++)
                this->cantitate[i] = 0;
            this->recuzita = NULL;
        }

    }
    Decor(const Decor& d)
    {
        this->elemente = d.elemente;
        if (d.elemente != 0)
        {
            this->recuzita = new string[this->elemente];
            for (int i = 0;i < this->elemente;i++)
            {
                this->recuzita[i] = d.recuzita[i];
                this->cantitate[i] = d.cantitate[i];
            }
        }
        else
        {
            this->elemente = 0;
            for (int i = 0;i < 10;i++)
                this->cantitate[i] = 0;
            this->recuzita = NULL;
        }
    }
    int getElemente()
    {
        return this->elemente;
    }
    void setElemente(int elemente)
    {
        if (elemente > 0 && elemente < 10)
        {
            string* copie;
            copie = new string[elemente];
            for (int j = 0;j < elemente;j++)
                copie[j] = "Indisponibil";
            if (this->recuzita != NULL)
            {
                int min;
                if (this->elemente < elemente) min = this->elemente;
                else min = elemente;
                for (int i = 0;i < min;i++)
                    copie[i] = this->recuzita[i];
            }
            if (elemente > this->elemente)
                for (int i = this->elemente;i < elemente;i++)
                    this->cantitate[i] = 0;
            this->recuzita = copie;
            this->elemente = elemente;
        }
    }
    int getCantitate(int i)
    {
        return this->cantitate[i];
    }
    void setCantitate(int i, int x)
    {
        if (i < 10 && i >= 0 && x >= 0)
            this->cantitate[i] = x;
    }
    string getRecuzita(int i)
    {
        return this->recuzita[i];
    }
    void setRecuzita(int i, string s)
    {
        if (i < 10 && i >= 0 && size(s)>2)
            this->recuzita[i] = s;
    }
    Decor& operator=(const Decor& d)
    {
        if (this != &d)
        {
            this->elemente = d.elemente;
            delete[] this->recuzita;
            this->recuzita = new string[this->elemente];
            for (int i = 0;i < this->elemente;i++)
            {
                this->recuzita[i] = d.recuzita[i];
                this->cantitate[i] = d.cantitate[i];
            }
        }
        return *this;
    }
  /*  Decor& operator+(const Decor d)
    {
        if (this->elemente + d.elemente <= 10)
        {
            int count = 0;
            Decor copie;
            copie = *this;
            delete[] this->recuzita;
            for (int i = 0;i < copie.elemente;i++)
            {
                int ok = 1;
                for (int j = 0;j < d.elemente;j++)
                    if (copie.recuzita[i] == d.recuzita[j] && d.cantitate[j] > 0)
                    {
                        ok = 0;
                        copie.cantitate[i] += d.cantitate[j];
                    }
                if (ok == 1) count++;
            }
            this->recuzita = new string[count];
            for (int i = 0;i < this->elemente;i++)
            {
                this->recuzita[i] = copie.recuzita[i];
                this->cantitate[i] = copie.cantitate[i];
            }
            int a = this->elemente;
            for (int i = 0;i < d.elemente;i++)
            {
                int ok = 1;
                for (int j = 0;j < this->elemente;j++)
                {
                    if (this->recuzita[i] == d.recuzita[j])
                        ok = 0;
                }
                if (ok == 1)
                {
                    this->recuzita[a] = d.recuzita[i];
                    this->cantitate[a] = d.cantitate[i];
                    a++;
                }
            }
            this->elemente = count;
        }
        return *this;
    }
    */
    int operator[](int index) {
        return this->cantitate[index];
    }

    Decor& operator--() {
        Decor copie;
        copie.elemente = this->elemente;
        copie.recuzita = new string[this->elemente];
        for (int i = 0;i < this->elemente;i++)
            copie.recuzita[i] = this->recuzita[i];
        if (this->elemente > 0)
        {
            this->elemente--;
            delete[] this->recuzita;
            this->recuzita = new string[this->elemente];
            for (int i = 0;i < this->elemente;i++)
                this->recuzita[i] = copie.recuzita[i];
            this->cantitate[this->elemente] = 0;
        }
        return *this;
    }
    Decor operator--(int) {
        Decor copie;
        copie.elemente = this->elemente;
        copie.recuzita = new string[this->elemente];
        for (int i = 0;i < this->elemente;i++)
            copie.recuzita[i] = this->recuzita[i];
        if (this->elemente > 0)
        {
            this->elemente--;
            delete[] this->recuzita;
            this->recuzita = new string[this->elemente];
            for (int i = 0;i < this->elemente;i++)
                this->recuzita[i] = copie.recuzita[i];
            this->cantitate[this->elemente] = 0;
        }
        return copie;
    }
    Decor operator++(int) {
        Decor copie = *this;
        if (this->elemente < 10)
        {

            this->elemente++;
            delete[] this->recuzita;
            this->recuzita = new string[this->elemente];
            for (int i = 0;i < copie.elemente;i++)
                this->recuzita[i] = copie.recuzita[i];
            this->recuzita[copie.elemente] = "Indisponibil";
            this->cantitate[copie.elemente] = 0;
        }
        return copie;

    }
    operator float() {
        float x = 0;
        for (int i = 0;i < this->elemente;i++)
        {
            x += this->cantitate[i];
        }
        return x / this->elemente;
    }
    bool operator!()
    {
        if (this->elemente == 0) {
            return true;
        }
        return false;
    }
    bool operator>(Decor& d) {
        if (this->elemente > d.elemente)
            return true;
        else return false;
    }
    bool operator<(Decor& d) {
        if (this->elemente < d.elemente)
            return false;
        else return true;
    }
    bool operator==(Decor& d) {
        if (this->elemente != d.elemente)
            return false;
        for (int i = 0;i < d.elemente;i++)
            if (this->recuzita[i] != d.recuzita[i] || this->cantitate[i] != d.cantitate[i]) return false;
        return true;
    }
    ~Decor() {}
    friend ostream& operator<<(ostream& out, const Decor d)
    {
        out << "\n-------------------";
        out << "\nNumarul de elemente este:" << d.elemente;
        for (int i = 0;i < d.elemente;i++)
            out << "\nElementul " << i + 1 << " este:" << d.recuzita[i];
        for (int i = 0;i < d.elemente;i++)
            out << "\nCantitatea elementului " << i + 1 << " este:" << d.cantitate[i];
        return out;
    }
    friend istream& operator>>(istream& in, Decor& d)
    {
        cout << "\n------------------";
        cout << "\nIntroduceti numarul de elemente:";
        in >> d.elemente;
        if (d.elemente > 0)
        {
            d.recuzita = new string[d.elemente];
            for (int i = 0;i < d.elemente;i++)
            {
                cout << "Introduceti elementul " << i + 1 << " :";
                in >> d.recuzita[i];
            }
            for (int i = 0;i < d.elemente;i++)
            {
                cout << "Introduceti cantitatea elementului " << i + 1 << " :";
                in >> d.cantitate[i];
            }

        }
        return in;
    }
    void writeToFile(fstream& f)
    {
        // int elemente;
         //string* recuzita;
         //int cantitate[10];
        int lg;
        f.write((char*)&this->elemente, sizeof(int));
        for (int i = 0;i < this->elemente;i++)
        {
            lg = this->recuzita[i].length() + 1;
            f.write((char*)&lg, sizeof(int));
            f.write(this->recuzita[i].data(), lg);
        }
        for (int i = 0;i < this->elemente;i++)
        {
            f.write((char*)&this->cantitate[i], sizeof(int));
        }

    }
    void readFromFile(fstream& f)
    {
        f.read((char*)&this->elemente, sizeof(int));
        if (this->elemente > 0) {
            delete[] this->recuzita;
            this->recuzita = new string[this->elemente];
            for (int i = 0;i < this->elemente;i++)
            {
                int lg;
                f.read((char*)&lg, sizeof(int));
                f.read((char*)&this->recuzita[i], lg);
            }
            for (int i = 0;i < this->elemente;i++)
                f.read((char*)&this->cantitate[i], sizeof(int));
        }
    }

};
int main()
{ //Administrarea unei comapanii de teatru
    char* aux1 = new char[20];
    strcpy(aux1, "Elisabeta");
    int* v = new int[3];
    for (int i = 0;i < 3;i++) v[i] = (i + 1) * 10;
    Teatru t1;
    cout << t1;
    Teatru t2(aux1, "Bv. Regina Elisabeta", 3, v);
    cout << t2;
    Teatru t3(t1);
    strcpy(aux1, "TNB");
    t3.setDenumire(aux1);
    t3.setLocatie("Universitate");
    t3.setZone(2);
    t3.setLocuri(0, 30);
    t3.setLocuri(1, 15);
    cout << t3;
    cout << "\nAfisam acelasi obiect, utilizand getteri";
    cout << "\n" << t3.getDenumire();
    cout << "\n" << t3.getLocatie();
    cout << "\n" << t3.getZone();
    for (int i = 0;i < t3.getZone();i++)
        cout << "\n" << t3.getLocuri(i);
    if (t3 == t2) cout << "\nElementele t3 si t2 sunt la fel";
    else cout << "\nElementele t2 si t3 sunt diferite";
    t3 = t2;
    if (t3 == t2) cout << "\nElementele t3 si t2 sunt la fel";
    else cout << "\nElementele t2 si t3 sunt diferite";
    cout << "\nNumarul mediu de locuri pentru zonele t2 este:" << (float)t2;
    if (t2 < t3) cout << "\nCapacitatea teatrului t2 este mai mica decat cea a teatrului t3";
    else cout << "\nCapacitatea teatrului t2 este mai mare decat cea a teatrului t3";
    cout << t2 + 10;
    if (!t1) cout << "\nT1 nu are zone";
    if (!t2) cout << "\nT2 nu are zone";
    cout << "\nPreincerementam si afisam t1" << ++t1;
    //t1[0];
    cout << "\nPostincrementam si afisam t1" << t1++;
    cout << "\nAfisam din nou t1" << t1;
    //cin >> t1;
    cout << t1;
    float* ore = new float[2]; ore[0] = 8.2; ore[1] = 7;
    Angajat a1;
    cout << a1;
    Angajat a2("David", "Cristian", 1000, 2, ore);
    cout << a2;
    Angajat a3(a1);
    a3.setNume("Petre");
    a3.setPrenume("Mihai");
    a3.setSalariu(1500);
    delete[] ore;
    ore = new float[3]; ore[0] = 10; ore[1] = 8.3; ore[2] = 2;
    a3.setLucru(3, ore);
    cout << a3;
    cout << "\nAfisam acelasi obiect utilizant getteri";
    cout << "\n" << a3.getCod();
    cout << "\n" << a3.getNume();
    cout << "\n" << a3.getPrenume();
    cout << "\n" << a3.getSalariu();
    cout << "\n" << a3.getZileLucrate() << endl;
    ore = a3.getOreLucrate();
    for (int i = 0;i < a3.getZileLucrate();i++)
        cout << ore[i] << " ";

    cout << "\nNumarul total de ore lucrate de angajatul a2 este " << (float)a2;
    if (!a1) cout << "\nAngajatul a1 a muncit";
    else cout << "\nAngajatul a1 nu a muncit";
    cout << "\nAngajatul a2 a muncit " << a2[1] << " ore in ziua 1";
    cout << "\nSalariul anagajatului a2 este " << a2.getSalariu();
    cout << "\nSalariul anagajatului a3 este " << a3.getSalariu();
    cout << "\nPreincrementam salariu angajatului a2 si il afisam" << ++a2;
    float salariu;
    salariu = 500;
    a2 = a2 + salariu;
    cout << "\nNoul salariu este " << a2.getSalariu();
    salariu = 200;
    a2 = a2 - salariu;
    cout << "\nNoul salariu este " << a2.getSalariu();
    if (a2 < a3) cout << "\nAngajatul a2 are salariul mai mic decat angajatul a3";
    else cout << "\nAngajatul a3 are salariu mai mic decat anagajatul a2";
    a2.setSalariu(a3.getSalariu());
    if (a2 >= a3) cout << "\nAngajatul a2 are salariul mai mare sau egal cu angajatul a3";
    else cout << "\nAngajatul a3 are salariu mai mic decat anagajatul a2";
    if (a2 == a3) cout << "\nObiectele a3 si a2 sunt la fel";
    else cout << "\nObiectele a2 si a3 sunt diferite";
    a3 = a2;
    if (a3 == a2) cout << "\nObiectele a3 si a2 sunt la fel";
    else cout << "\nObiectele a2 si a3 sunt diferite";
    //cin >> a2;
    cout << a2;
    int* locuri = new int[2];  locuri[1] = 2;locuri[0] = 2;
    bool** bil = new bool* [2];bil[0] = new bool[2]; bil[1] = new bool[2]; bil[0][0] = 1;bil[0][1] = 1;bil[1][0] = 0;bil[1][1] = 0;
    Comanda c;
    cout << c;
    Comanda c2("Aladdin", 4, 2, locuri, bil);
    cout << c2;
    Comanda c3(c2);
    c3.setClasa(3);
    c3.setNumeSpectacol("Micul Print");
    c3.setBilete(1, 1, 1);
    c3.setBilete(0, 0, 0);
    cout << c3;
    if (!c) cout << "\nComandan c nu are bilete";
    else cout << "\nComanda c are bilete";
    if (!c2) cout << "\nComandan c2 nu are bilete";
    else cout << "\nComanda c2 are bilete";
    cout << "\nComanda c2 ocupa " << (float)c2 << " procente din sala.";
    cout << "\nPreincrementam si afisam c2" << ++c2;
    cout << "\nPostincrementam si afisam c2" << c2++;
    cout << "\nAfisam din nou c2" << c2;
    cout << "\nComanda c2 are " << c2[1] << " bilete pe randul 1.";
    if (c2 > c3) cout << "\nComanda c2 are mai multe bilete decat comanda c3";
    else cout << "\nComanda c3 are mai multe bilete decat comanda c2";
    if (c2 == c3) cout << "\nComenzile sunt la fel";
    else cout << "\nComenzile sunt diferite";
    c2 = c3;
    if (c2 == c3) cout << "\nComenzile sunt la fel";
    else cout << "\nComenzile sunt diferite";
    Comanda c4;
    //cin >> c4;
    cout << c4;
    Spectacol s;
    cout << s;
    strcpy(aux1, "Aladdin");
    char* aux2 = new char[20];
    strcpy(aux2, "22 oct");
    Spectacol s2(aux1,aux2,t3);
    cout << s2;
    Spectacol s3(s2);
    cout << s3;
    strcpy(aux1, "Omul");
    strcpy(aux2, " 14 nov");
    s3.setNume(aux1);
    s3.setData(aux2);
    s3.setLocatie(t2);
    cout << s3;
    cout << "\nAfisam obiecul cu ajutorul getterilor";
    cout << "\n" << s3.getNume();
    cout << "\n" << s3.getData();
    cout << "\n" << s3.getLocatie();
    if (!s) cout << "\nSpectacolul s nu are zone locatia valida";
    else cout << "\nSpectacolul s  are zone locatia valida";
    cout << "\nNumarul mediu de locuri in zonele teatrului spectacolului s2 este " << (float)s2;
    s2=s2 + 10;
    if (s2 > s3) cout << "\nSpectacolul s2 are capacitatea mai mare ca s3";
    else  cout << "\nSpectacolul s2 nu are capacitatea mai mare ca s3";
    cout <<"\nPreincrementam s2 si il afisam"<< ++s2;
    cout << "\nPostincrementam s2 si il afisam" << s2++;
    cout <<"\nAfisam din nou s2"<< s2;
    if (s2 == s3) cout << "\nSpectacolele sunt la fel";
    else cout << "\nSpectacolele sunt diferite";
    s3 = s2;
    if (s2 == s3) cout << "\nSpectacolele sunt la fel";
    else cout << "\nSpectacolele sunt diferite";
    Spectacol s4;
    //cin >> s4;
    cout << s4;
    Decor d;
    cout << d;
    int* vv = new int[2];
    vv[0] = 2;
    vv[1] = 3;
    Angajat aa;
    cin >> aa;
    Actor ac2(aa, 2, vv);
    fstream fout("fisiere.txt", ios::out | ios::binary);
    ac2.writeFile(fout);
    fout.close();
    return 0;
}
