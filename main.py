# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
import csv


def main():
    f = open('chess.txt', 'w')
    with open('topchess.csv', newline='') as file:
        reader = csv.DictReader(file)
        for row in reader:
            f.write(row["Name"])
            f.write("\n")


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    main()

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
