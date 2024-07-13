#include <fstream>
#include <iostream>
int main(int argc, char** argv){
    std::ifstream in(argv[1], std::ios::binary);
    std::ofstream out(argv[2], std::ios::binary);
    char nontpcounter = 0;
    while(true){
        unsigned char i = in.get();
        std::cout<<(int)i<<" ";
        if(in.eof()) break;
        if(nontpcounter>0){out<<i;nontpcounter--;continue;}
        if(i>0xaf) {nontpcounter=i-0xaf;continue;}
        out<<(char)0xf3<<(char)0xb1<<(char)(0xa4+((i&0xc0)>>6))<<(char)((i&0x3f)+128);
    }
}