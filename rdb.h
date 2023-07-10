#pragma once
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <iostream>
using namespace std;

class Attr { //Base class for attributes
 // Add operators for different attribute type in derived classes
 public: virtual bool operator== (const Attr & right) = 0;
    virtual bool operator!= (const Attr & right) = 0;
    virtual bool operator< (const Attr & right) = 0;
    virtual bool operator> (const Attr & right) = 0;
    virtual bool operator<= (const Attr & right) = 0;
    virtual bool operator>= (const Attr & right) = 0;

    virtual std::string toString() const = 0; 
    virtual Attr * clone() const = 0;
};

class IntAttr : public Attr{
    int val;
public:
    IntAttr(int v) : val(v) {}
    ~IntAttr() {}
    int getVal() const;
    void setVal(int v);
    bool operator== (const Attr & right);
    bool operator!= (const Attr & right);
    bool operator< (const Attr & right);
    bool operator> (const Attr & right);
    bool operator<= (const Attr & right);
    bool operator>= (const Attr & right);
    Attr * clone() const;
    //toString() method 
    string toString() const;
};

class floatAttr : public Attr{
    float val;
public:
    floatAttr(float v) : val(v) {}
    ~floatAttr() {}
    float getVal() const;
    void setVal(float v);
    bool operator== (const Attr & right);
    bool operator!= (const Attr & right);
    bool operator< (const Attr & right);
    bool operator> (const Attr & right);
    bool operator<= (const Attr & right);
    bool operator>= (const Attr & right);
    Attr * clone() const;
    //toString() method 
    string toString() const;
};

class stringAttr : public Attr{
    string val;
public:
    stringAttr(string v) : val(v) {}
    ~stringAttr() {}
    string getVal() const;
    void setVal(string v);
    bool operator== (const Attr & right);
    bool operator!= (const Attr & right);
    bool operator< (const Attr & right);
    bool operator> (const Attr & right);
    bool operator<= (const Attr & right);
    bool operator>= (const Attr & right);
    Attr * clone() const;
    //toString() method
    string toString() const;
};


class Record { //storing data for each record
 vector <Attr *> attrptr;

 //methods
 public:

    Record() {}
    ~Record() {
        for (auto a : attrptr) delete a;
    }
    void addAttribute(Attr * a) {
        attrptr.push_back(a);
    }
    Attr * getAttribute(int i) const {
        return attrptr[i];
    }

    int size() const {
        return attrptr.size();
    }

    int getAttrind(string attrname) const {
        for (int i = 0; i < attrptr.size(); i++) {
            if (attrptr[i]->toString() == attrname) return i;
        }
        std::cout<<"not found"<<endl;
        return -1;
    }

    //function to compare two records
    bool compare(const Record & right, const vector<int> & attrinds) {
        if (attrinds.size() != right.attrptr.size()) return false;
        for (int i = 0; i < attrinds.size(); i++) {
            if (*attrptr[attrinds[i]] != *right.attrptr[i]) return false;
        }
        return true;
    }
};

class Relation { // storing a relation
 int nattr, nrecs; // number of attributes and records
 vector <string> attrnames; // schema
 vector <int> attrinds; // mapping schema to indices
 list <Record *> recs; // list of records
 // methods
public:
    Relation(const vector<string> & attrs) {
         nattr=attrs.size();
         nrecs=0;
         attrnames=attrs;
         attrinds=vector<int>(nattr);
        for (int i = 0; i < nattr; i++) {
            attrinds[i] = i;
        }
    }
    //relation copy constructor
    Relation(const Relation & r) {
        nattr = r.nattr;
        nrecs = r.nrecs;
        attrnames = r.attrnames;
        attrinds = r.attrinds;
        for (auto rec : r.recs) {
            Record * newrec = new Record();
            for (int i = 0; i < nattr; i++) {
                newrec->addAttribute(rec->getAttribute(attrinds[i])->clone());
            }
            recs.push_back(newrec);
        }
    }
    Relation(){
        nattr=0;
        nrecs=0;
    }
    ~Relation() {
        for (auto r : recs) delete r;
    }

    //add a record to the relation
    void addRecord(Record * rec) {
        if (rec->size() != nattr) {
            cout<<"Error: record size does not match schema size."<<endl;
            return;
        };
        recs.push_back(rec);
        nrecs++;
    }

    //getters
    int getNumAttributes() const {
        return nattr;
    }
    int getNumRecords() const {
        return nrecs;
    }
    vector<int> getAttrinds(){
        return attrinds;
    }
    vector<string> getAttributeNames() const {
        return attrnames;
    }

    void setAttributeName(int i, string name) {
        attrnames[i] = name;
    }

    //getAttrind()
    int getAttrind(string attrname) const {
        for (int i = 0; i < nattr; i++) {
            if (attrnames[i] == attrname) return i;
        }
        cout<<"Attribute not found"<<endl;
        return -1;
    }

    //copy operator
    Relation & operator= (const Relation & right) {
        if (this == &right) return *this;
        for (auto r : recs) delete r;
        nattr = right.nattr;
        nrecs = right.nrecs;
        attrnames = right.attrnames;
        attrinds = right.attrinds;
        for (auto rec : right.recs) {
            Record * newrec = new Record();
            for (int i = 0; i < nattr; i++) {
                newrec->addAttribute(rec->getAttribute(attrinds[i])->clone());
            }
            recs.push_back(newrec);
        }
        return *this;
    }

    //get a record from the relation
    Record * getRecord(int i) const {
        auto it = recs.begin();
        advance(it, i);
        return *it;
    }    


    //clone a relation
    Relation * clone() const {
        Relation * r = new Relation(attrnames);
        r->attrinds = attrinds;
        for (auto rec : recs) {
            Record * newrec = new Record();
            for (int i = 0; i < nattr; i++) {
                newrec->addAttribute(rec->getAttribute(attrinds[i])->clone());
            }
            r->addRecord(newrec);
        }
        return r;
    }

    //create a new relation with the same schema
    Relation * empty() const {
        Relation * r = new Relation(attrnames);
        r->attrinds = attrinds;
        return r;
    }

    //delete a relation
    void deleteRelation() {
        for (auto r : recs) delete r;
        recs.clear();
        nrecs = 0;
    }
};

struct DNFformula { 
    list <list <tuple <string, char, Attr *> > > ops; 
};

Relation * union_(Relation * R1, Relation * R2);
Relation * difference (Relation * R1, Relation * R2);
Relation * cartesianProduct(Relation * R1, Relation * R2);
Relation * projection(Relation * R1, list<string> projectattrs);
Relation * selection (Relation * R1, DNFformula * f);
Relation * rename (Relation * R1, string s1, string s2);
Relation * naturaljoin(Relation * R1, Relation * R2, list<string> joinattr);
void printRelation(Relation * R);

