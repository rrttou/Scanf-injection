def main():
    fin = open("chessOut.txt", "rt")
    # output file to write the result to
    fout = open("toLow.txt", "wt")
    # for each line in the input file
    tmp = fin.readlines()
    for line in fin:
        fout.write(line[0].lower())


    # close input and output files
    fin.close()
    fout.close()


if __name__ == '__main__':
    main()