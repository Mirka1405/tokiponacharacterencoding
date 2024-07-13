from sys import argv
with open(input("Input file: ") if len(argv)<2 else argv[1],"rb") as f:
    with open(input("Output file: ") if len(argv)<3 else argv[2],"wb") as out:
        nontpcounter = 0
        last3bytes = 0
        nontpbuffer = b""
        for i in f.read():
            if last3bytes&0xfffffc==0xf3b1a4: # sitelen pona block range is f3b1a480 to f3b1a6a3
                nontpcounter-=3
                last = (((nontpbuffer[-1]&0b11)<<6)+i-128).to_bytes(1)
                while nontpcounter>0:
                    out.write(((0xaf+nontpcounter) if (0xaf+nontpcounter)<=0xff else 0xff).to_bytes(1))
                    out.write(nontpbuffer[:80] if nontpcounter>80 else nontpbuffer[:-3])
                    nontpbuffer=nontpbuffer[80:]
                    nontpcounter-=80
                out.write(last)
                nontpbuffer = b""
                nontpcounter = 0
                last3bytes = 0
                continue
            last3bytes = ((last3bytes&0xffffff)<<8)+i
            nontpcounter+=1
            nontpbuffer+=i.to_bytes(1)
        while nontpcounter>0: # finish the job if the last character wasnt tp
            out.write(((0xaf+nontpcounter) if (0xaf+nontpcounter)<=0xff else 0xff).to_bytes(1))
            out.write(nontpbuffer[:80])
            nontpbuffer=nontpbuffer[80:]
            nontpcounter-=80
