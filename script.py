
import csv

def main():
    fin = open ("chess.txt","rt")
    fout =open("chessOut.txt","wt")
    tmp =[ ]
    tmp1 = []
    for line in fin:
        tmp1=line.replace("\n",'')
        tmp=tmp1.split(" ")
        str=""
        for i in reversed(tmp):
            str=str+i
            str.replace(',','\n')
            res=str[0].lower()+str[1:-1]
            res.replace(',','\n')
        fout.write(res)
        fout.write("\n")


if __name__ == '__main__':
    main()

    # def main():
    # fin = open("chess.txt", "rt")
    # output file to write the result to
    # fout = open("chessOut.txt", "wt")
    # for each line in the input file
    # tmp = fin.readlines()
    # for line in tmp:
    # foo = line.strip("\n")
    # foo = foo.split(",")
    # for i in list(reversed(foo)):
    # fout.write(i)
    # close input and output files
    # fin.close()
    # fout.close()