#include "Draw.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Draw::Draw()
{
    //ctor
}

Draw::~Draw()
{
    //dtor
}

void Draw::drawDFS(){
    // Cargamos el header para imprimirlo
    string header_dir = "./art/dfs_header.txt";
    string line;
    ifstream header(header_dir.c_str());
    // Abrimos el header
    if(header){
        // Imprimimos el header
        while(getline(header,line)){
            cout<<line<<endl;
        }
    }else{
        cout<<"\t----------Dummy File System----------\n";
        cout<<"\t-----------by Penserbjorne-----------\n\n";
    }
}
