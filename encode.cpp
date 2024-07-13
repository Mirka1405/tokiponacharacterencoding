#include <fstream>
int main(int argc, char** argv){
    std::ifstream in(argv[1], std::ios::binary);
    std::ofstream out(argv[2], std::ios::binary);
    if(!in||!out) return 1;
    char buffer[84];
    int nontpcounter = 0;
    while(true){
        char i = in.get();
        if(in.eof()) break;
        if(nontpcounter>=3&&buffer[nontpcounter-3]==-13&&buffer[nontpcounter-2]==-79&&(int)(buffer[nontpcounter-1]&0xfc)==164){
            nontpcounter-=3;
            if(nontpcounter>0)out<<(char)(0xaf+nontpcounter);
            for(int i=0;i<nontpcounter;i++) out<<(char)buffer[i];
            out<<(char)(((buffer[nontpcounter+2]&0x3)<<6)+i-128);
            nontpcounter=0;
            continue;
        }
        if(nontpcounter>=83) {
            out<<(char)255;
            for(int i=0;i<80;i++) out<<(char)buffer[i];
            for(int i=80;i<84;i++) buffer[i-80] = buffer[i];
            nontpcounter=4;
            buffer[3]=i;
            continue;
        }
        buffer[nontpcounter]=i;
        nontpcounter++;
    }
    if(!nontpcounter) return 0;
    if(nontpcounter>80){
        out<<(char)255;
        for(int i=0;i<80;i++) out<<(char)buffer[i];
        out<<(char)(0xaf+nontpcounter);
        for(int i=80;i<80+nontpcounter;i++) out<<(char)buffer[i];
        return 0;
    }
    out<<(char)(0xaf+nontpcounter);
    for(int i=0;i<nontpcounter;i++) out<<(char)buffer[i];
    return 0;
}