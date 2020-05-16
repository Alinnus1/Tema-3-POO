#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <typeinfo>
#include <exception>


class Examen {
protected:
    static int numar;
    int id_examen;
    std::string denumire;
    std::string data;
    int nota_scris;
public:
    Examen():id_examen(0),denumire("bla"),data("tba"),nota_scris(1){}
    Examen(int a,std::string b,std::string c, int d):id_examen(a),denumire(b),data(c),nota_scris(d){}
    Examen(const Examen& ob):id_examen(ob.id_examen),denumire(ob.denumire),data(ob.data),nota_scris(ob.nota_scris){}
    virtual ~Examen(){
        numar=-1;
        denumire="";
        data="";
        nota_scris=-1;
    }
    virtual void afisare()=0;
    const Examen& operator =(const Examen&);
    friend std::istream & operator >>(std::istream&, Examen&);
    friend std::ostream & operator <<(std::ostream&, Examen&);
};
int Examen::numar=0;

const Examen & Examen::operator=(const Examen& right){
    this->data=right.data;
    this->id_examen=right.id_examen;
    this->denumire=right.denumire;
    this->nota_scris=right.nota_scris;
    return *this;
}
std::istream & operator >> (std::istream & in, Examen& ob){
    Examen::numar++;
    ob.id_examen=Examen::numar;
    std::cout<<"Introdu numele examenului\n";
    in>>ob.denumire;
    std::cout<<"introdu data\n";
    in>>ob.data;
    std::cout<<"introdu si nota obtinuta la scris\n";
    in>>ob.nota_scris;
    return in;
}
std::ostream & operator << (std::ostream & out, Examen& ob){

    out<<"Id-ul examenului:"<<ob.id_examen<<"\n";
    out<<"Denumirea examenului:"<<ob.denumire<<"\n";
    out<<"Data examenului:"<<ob.data<<"\n";
    out<<"Nota la scris obtinuta:"<<ob.nota_scris<<"\n";
    return out;
}
class Quizz:virtual public Examen {
protected:
    const int nritemi=7;
public:
    Quizz():Examen(){};
    Quizz(int a,std::string b,std::string c, int d,const int e):Examen(a,b,c,d),nritemi(e){}
    Quizz(const Quizz& ob):Examen(ob),nritemi(ob.nritemi){}
    virtual ~Quizz(){}
    void afisare();
    friend std::istream & operator >>(std::istream&, Quizz&);
    friend std::ostream & operator <<(std::ostream&, Quizz&);
};
std::istream & operator >>(std::istream& in, Quizz& ob){
    in>>dynamic_cast<Examen&>(ob);
    std::cout<<"nr de itemi al testului grila este de 7 sa stii\n";
    return in;
}

std::ostream & operator <<(std::ostream & out, Quizz & ob){
    out<<dynamic_cast<Examen&>(ob);
    out<<"nr de itemi:"<< ob.nritemi<<"\n";
    return out;
}
void Quizz::afisare(){
    std::cout<<*this;
}

class Partial: virtual public Examen{
protected:
    int nota_oral;
    bool luat; /// 1 e luat 0 nu e luat
public:
    Partial():Examen(){
    nota_oral=0;
    luat=0;
    }
    Partial(int a,std::string b,std::string c, int d,int e,bool f):Examen(a,b,c,d),nota_oral(e),luat(f){}
    Partial(const Partial& ob):Examen(ob),nota_oral(ob.nota_oral),luat(ob.luat){}
    virtual ~Partial(){
    nota_oral=-1;
    luat=0;
    }
    void afisare();
    friend std::istream & operator >>(std::istream&, Partial&);
    friend std::ostream & operator <<(std::ostream&, Partial&);

};
std::istream & operator >>(std::istream & in, Partial& ob){
    in>>dynamic_cast<Examen&>(ob);
    std::cout<<"Introdu nota la oral obtinuta:\n";
    in>>ob.nota_oral;
    if(ob.nota_oral>=5)
        ob.luat=1;
    else
        ob.luat=0;
    return in;
}
std::ostream& operator<< (std::ostream & out, Partial& ob){
    out<<dynamic_cast<Examen&>(ob);
    out<<"Nota obtinuta la oral:"<<ob.nota_oral<<"\n";
    return out;
}
void Partial::afisare(){
    std::cout<<*this;
}
class ExamenF:virtual public Partial{
protected:
    int extrapct;
    int notarefacuta;
    int notaef;
public:
    ExamenF():Partial(){
    extrapct=0;
    notarefacuta=0;
    }
    ExamenF(int a,std::string b,std::string c, int d,int e,bool f,int g,int h,int i):Partial(a,b,c,d,e,f),extrapct(g),notarefacuta(h),notaef(i){}
    ExamenF(const ExamenF& ob):Partial(ob),extrapct(ob.extrapct),notarefacuta(ob.notarefacuta),notaef(ob.notaef){}
    virtual ~ExamenF(){
    extrapct=-1;
    notarefacuta=-1;
    }
    double mediafin() const{
        if((notarefacuta+notaef)/2+extrapct>10)
            return 10;
        else
            return (notarefacuta+notaef)/2+extrapct;
    }
    void afisare();
    friend std::istream & operator >>(std::istream&, ExamenF&);
    friend std::ostream & operator <<(std::ostream&, ExamenF&);
};


std::istream & operator >>(std::istream& in , ExamenF & ob){
    in>>dynamic_cast<Partial&>(ob);
    std::cout<<"introdu extra punctaju:\n";
    in>>ob.extrapct;
    if(!ob.luat)
    {
        std::cout<<"se pare ca nu s=a luat o nota buna, care e nota noua?\n";
        in>>ob.notarefacuta;
    }
    else
        ob.notarefacuta=(ob.nota_oral+ob.nota_scris)/2;
    std::cout<<"care e nota la examenul final\n";
    in>>ob.notaef;
    return in;

}
std::ostream & operator <<(std::ostream & out, ExamenF& ob){
    out<<dynamic_cast<Partial&>(ob);
    out<<"Punctajul extra este :"<<ob.extrapct<<"\n";
    out<<"Punctajul refacut este:"<<ob.notarefacuta<<"\n";
    out<<"Nota la examenul ifnal este:"<<ob.notaef<<"\n";
    return out;
}
void ExamenF::afisare(){
    std::cout<<*this;
}

class Student {
protected:
    int nrexamene;
    std::vector<Examen*> examenele;
public:
    Student(){nrexamene=0;}
    Student(const int a,std::vector<Examen*>& examenele_other):nrexamene(a){
        for(int i=0; i<examenele_other.size(); i++){
            if(typeid(examenele_other[i]).name() == typeid(Partial).name()){
                examenele.push_back(new Partial(*dynamic_cast<Partial*>(examenele_other[i])));
            }
            else if(typeid(examenele_other[i]).name() == typeid(ExamenF).name()){
                examenele.push_back(new ExamenF(*dynamic_cast<ExamenF*>(examenele_other[i])));
            }
            else{
            examenele.push_back(new Quizz(*dynamic_cast<Quizz*>(examenele_other[i])));
            }
        }
    }
    ~Student(){
    nrexamene=-1;
    examenele.clear();
    }
    int getnr(){return nrexamene;}
    friend std::istream& operator>>(std::istream & , Student&);
    friend std::ostream& operator<<(std::ostream &, Student&);

};
std::istream & operator>>(std::istream & in, Student& ob){
    std::cout<<"care este numarul de examene al acestui student????\n";
    in>>ob.nrexamene;
    int x;
    x=ob.nrexamene;
    ob.examenele.clear();
    while(x--){
        int y;
        std::cout<<"Apasa 1 pentru partial,2 pentru examenF,3 pentru quizz\n";
        in>>y;
        if(y==1){
            Partial *temp=new Partial();
            in>>*temp;
            ob.examenele.push_back(temp);
        }else if(y==2){
            ExamenF *temp=new ExamenF();
            in>>*temp;
            ob.examenele.push_back(temp);
        }else if(y==3){
            Quizz *temp=new Quizz();
            in>>*temp;
            ob.examenele.push_back(temp);
        }
    }
    return in;
}
std::ostream & operator <<(std::ostream & out, Student & ob){
    out<<"numarul de examene este"<<ob.nrexamene<<"\n";
    for (int i=0;i<ob.examenele.size();i++)
    {
        out<< *(ob.examenele[i]);
    }
    return out;
}

template <class T> class CatalogIndividual{
    T* s;
    static int nr_matricol;
    int nr_matr;
    int nr_examenee;
    std::vector<int> informatie{3};
public:
    CatalogIndividual():s(nullptr),nr_matr(0),nr_examenee(0){}
    CatalogIndividual(T* a):s(a){
        this->nr_examenee=a->getnr();
        CatalogIndividual::nr_matricol++;
        nr_matr=CatalogIndividual::nr_matricol;
        for(int i=0; i<a->examenele.size(); i++){
            if(typeid(a->examenele[i]).name() == typeid(Partial).name()){
                informatie[0]++;
            }
            else if(typeid(a->examenele[i]).name() == typeid(ExamenF).name()){
                informatie[1]++;
            }
            else{
                informatie[2]++;
            }
        }

    }
    ~CatalogIndividual()=default;

};



class Probelma : public std::exception {
public:
    const char* what(){
        return "am aruncat eroarea caa sa fie";
    }
};

int main()
{

    std::vector<Student> vectoru;
    std::cout<<"cati studenti vrei?\n";
    int n;
    std::cin>>n;
    while(n--)
    {
        try{
            Student temp;
            std::cin>>temp;
            if(temp.getnr()==0)
                throw Probelma();
            vectoru.push_back(temp);
            }catch (Probelma e){
        std::cout<<e.what();
        n++;
            }
    }


    return 0;
}
