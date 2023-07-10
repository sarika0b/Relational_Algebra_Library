#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include "rdb.h"

using namespace std;


void printRelation(Relation * R){
    for(int i=0;i<R->getNumAttributes();i++){
        cout<<R->getAttributeNames()[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<R->getNumRecords();i++){
        for(int j=0;j<R->getNumAttributes();j++){
            cout<<R->getRecord(i)->getAttribute(j)->toString()<<" ";
        }
        cout<<endl;
    }
}

Relation * union_(Relation * R1, Relation * R2){

    if(R1->getNumAttributes() != R2->getNumAttributes()) {
        printf("Error: Union of relations with different number of attributes is not supported.\n");
        return NULL;
    }
    for(int i=0;i<R1->getNumAttributes();i++){
        if(R1->getAttributeNames()[i] != R2->getAttributeNames()[i]){
            printf("Error: Union of relations with different attributes is not supported.\n");
            return NULL;
        }
    }
    Relation * R = R1->clone();
    for(int i=0; i<R2->getNumRecords();i++){
        int present = 0;
        for(int j=0; j<R1->getNumRecords();j++){

            if(R1->getRecord(j)->compare(*(R2->getRecord(i)),R2->getAttrinds())){
                present=1;
                break;
            }    
        }
        if(present==0){
            R->addRecord(R2->getRecord(i));
        }
    }
    return R;

}


//difference of two relations
Relation * difference (Relation * R1, Relation * R2){
    if(R1->getNumAttributes() != R2->getNumAttributes()) {
        printf("Error: Difference of relations with different number of attributes is not supported.\n");
        return NULL;
    }
    for(int i=0;i<R1->getNumAttributes();i++){
        if(R1->getAttributeNames()[i] != R2->getAttributeNames()[i]){
            printf("Error: Union of relations with different attributes is not supported.\n");
            return NULL;
        }
    }

    Relation * R = new Relation(R1->getAttributeNames());

    for(int i=0; i<R1->getNumRecords();i++){
        int present = 0;
        for(int j=0; j<R2->getNumRecords();j++){
            if(R1->getRecord(i)->compare( *(R2->getRecord(j)),R2->getAttrinds())){
                present=1;
                break;
            }
        }
        if(present==0)
            R->addRecord(R1->getRecord(i));
    }
    return R;
}


//cartesian product of two relations
Relation * cartesianProduct(Relation * R1, Relation * R2){
    for(int i=0;i<R1->getNumAttributes();i++){
        for(int j=0;j<R2->getNumAttributes();j++){
            if(R1->getAttributeNames()[i] == R2->getAttributeNames()[j]){
                printf("Error: Catersian product of relations with same attributes is not supported.\n");
                return NULL;
            }
        }
    }
    vector<string> attr_names;
    for(int i=0;i<R1->getNumAttributes();i++){
        attr_names.push_back(R1->getAttributeNames()[i]);
    }
    for(int i=0;i<R2->getNumAttributes();i++){
        attr_names.push_back(R2->getAttributeNames()[i]);
    }
    Relation * R = new Relation(attr_names);
    for(int i=0;i<R1->getNumRecords();i++){
        for(int j=0;j<R2->getNumRecords();j++){
            Record * r = new Record();
            for(int k=0;k<R1->getNumAttributes();k++){
                r->addAttribute(R1->getRecord(i)->getAttribute(k)->clone());
            }
            for(int k=0;k<R2->getNumAttributes();k++){
                r->addAttribute(R2->getRecord(j)->getAttribute(k)->clone());
            }
            R->addRecord(r);
        }
    }
    return R;
}


//projection of a relation on a set of attributes
Relation * projection(Relation * R1, list<string> projectattrs){
    vector<string> attr_names;
    for(list<string>::iterator it = projectattrs.begin(); it != projectattrs.end(); it++){
        attr_names.push_back(*it);
    }
    Relation * R = new Relation(attr_names);
    for(int i=0;i<R1->getNumRecords();i++){
        Record * r = new Record();
        for(list<string>::iterator it = projectattrs.begin(); it != projectattrs.end(); it++){
            int ind = R1->getAttrind(*it);
            r->addAttribute(R1->getRecord(i)->getAttribute(ind)->clone());
        }
        R->addRecord(r);
    }
    return R;
}



//evaluate a DNF formula on a record
bool evaluate(DNFformula * f, Record * r, vector<string> attr_names){
    for(list <list <tuple <string, char, Attr *> > >::iterator it = f->ops.begin(); it != f->ops.end(); it++){
        int flag = 0;
        for(list <tuple <string, char, Attr *> >::iterator it2 = it->begin(); it2 != it->end(); it2++){
            int ind = -1;
            for(int i=0;i<attr_names.size();i++){
                if(attr_names[i] == get<0>(*it2)){
                    ind = i;
                    break;
                }
            }
            if(ind == -1){
                printf("Error: Attribute not found in record.\n");
                return false;
            }
            if(get<1>(*it2) == '='){
                if(r->getAttribute(ind)->toString() != get<2>(*it2)->toString()){
                    flag = 1;
                    break;
                }
            }
            else if(get<1>(*it2) == '<'){
                if(r->getAttribute(ind)->toString() >= get<2>(*it2)->toString()){
                    flag = 1;
                    break;
                }
            }
            else if(get<1>(*it2) == '>'){
                if(r->getAttribute(ind)->toString() <= get<2>(*it2)->toString()){
                    flag = 1;
                    break;
                }
            }
        }
        if(flag == 0){
            return true;
        }
    }
    return false;
}

//select a relation based on a DNF formula
Relation * selection (Relation * R1, DNFformula * f){
    Relation * R = new Relation(R1->getAttributeNames());
    for(int i=0;i<R1->getNumRecords();i++){
        if(evaluate(f,R1->getRecord(i),R1->getAttributeNames())){
            R->addRecord(R1->getRecord(i));
        }
    }
    return R;
}


//rename an attribute in a relation
Relation * rename (Relation * R1, string s1, string s2){
    for(int i=0;i<R1->getNumAttributes();i++){
        if(R1->getAttributeNames()[i] == s1){
            R1->setAttributeName(i,s2);
        }
    }
    return R1;
}

