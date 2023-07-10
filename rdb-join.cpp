#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include "rdb.h"

using namespace std;

//natural join of two relations
Relation * naturaljoin(Relation * R1, Relation * R2, list<string> joinattr){

    for(list<string>::iterator it = joinattr.begin(); it != joinattr.end(); it++){
        int ind1 = -1, ind2 = -1;
        for(int i=0;i<R1->getNumAttributes();i++){
            if(R1->getAttributeNames()[i] == *it){
                ind1 = i;
                break;
            }
        }
        for(int i=0;i<R2->getNumAttributes();i++){
            if(R2->getAttributeNames()[i] == *it){
                ind2 = i;
                break;
            }
        }
        if(ind1 == -1 || ind2 == -1){
            printf("Error: Attribute not found in relation.\n");
            return NULL;
        }
        int flag=0;
        for(int i=0;i<R1->getNumRecords();i++){
            for(int j=0;j<R2->getNumRecords();j++){
                if(R1->getRecord(i)->getAttribute(ind1)->toString() != R2->getRecord(j)->getAttribute(ind2)->toString()){
                    flag=0;
                }
                else {flag=1;break;}
            }
            if(flag==1) break;
        }
        if(flag==0){
            printf("Error: Natural join not possible.\n");
            return NULL;
        }
    }

    vector<int> R1indices;
    vector<int> R2indices;

    for(auto it: joinattr){
        int ind1 = -1, ind2 = -1;
        for(int i=0;i<R1->getNumAttributes();i++){
            if(R1->getAttributeNames()[i] == it){
                ind1 = i;
                break;
            }
        }
        for(int i=0;i<R2->getNumAttributes();i++){
            if(R2->getAttributeNames()[i] == it){
                ind2 = i+ R1->getNumAttributes();
                break;
            }
        }

        R1indices.push_back(ind1);
        R2indices.push_back(ind2);
    }
    Relation * Rtemp=R1;


    //rename all attributes in rindices from r1
    for(int i=0;i<R1indices.size();i++){
       Relation * rn= rename(Rtemp,R1->getAttributeNames()[R1indices[i]],R1->getAttributeNames()[R1indices[i]]+"1");
         Rtemp=rn;
    }
    Relation * Rc=cartesianProduct(Rtemp,R2);


    Relation * Rc2= new Relation(Rc->getAttributeNames());
    for(int i=0;i<Rc->getNumRecords();i++){
        int flag=0;
        for(int j=0;j<R1indices.size();j++){
            if(Rc->getRecord(i)->getAttribute(R1indices[j])->toString() != Rc->getRecord(i)->getAttribute(R2indices[j])->toString()){
                flag=1;
                break;
            }
        }
        if(flag==0){
            Rc2->addRecord(Rc->getRecord(i));
        }
    }
    list<string> project_attrs;
    for(int i=0;i<Rc2->getNumAttributes();i++){
        //dont take attribute if present in r1indices
        int flag=0;
        for(int j=0;j<R1indices.size();j++){
            if(i==R1indices[j]){
                flag=1;
                break;
            }
        }
        if(flag==0){
            project_attrs.push_back(Rc2->getAttributeNames()[i]);
        }
    }
    Relation * R = projection(Rc2,project_attrs);
    return R;
}