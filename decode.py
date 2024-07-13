from sys import argv
with open(input("Input file: ") if len(argv)<2 else argv[1],"rb") as f:
    with open(input("Output file: ") if len(argv)<3 else argv[2],"wb") as out:
        nontpcounter = 0
        for i in f.read():
            if nontpcounter>0: 
                out.write(i.to_bytes(1))
                nontpcounter-=1
                continue
            if i>0xaf:
                nontpcounter=i-0xaf
                continue
            out.write(b"\xf3\xb1")
            out.write((0xa4+((i&0xc0)>>6)).to_bytes(1))
            out.write(((i&0x3f)+128).to_bytes(1))