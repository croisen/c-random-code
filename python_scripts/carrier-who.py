#!/usr/bin/env python3


import sys

smart = [ "0813", "0907", "0908", "0909", "0910", "0911", "0912", "0913", "0914", "0918", "0919",
          "0920", "0921", "0928", "0929", "0930", "0938", "0939", "0946", "0947", "0948", "0949",
          "0950", "0951", "0961", "0963", "0968", "0970", "0981", "0989", "0998", "0999" ]

globe = [ "0817", "0905", "0906", "0915", "0916", "0917", "0926", "0927", "0935", "0936", "0937",
          "0945", "0953", "0954", "0955", "0956", "0965", "0966", "0967", "0975", "0976", "0977",
          "0978", "0979", "0995", "0996", "0997" ]

dito =  [ "0895", "0896", "0897", "0898", "0991", "0992", "0993", "0994" ]

sun =   [ "0922", "0923", "0924", "0925", "0931", "0932", "0933", "0934", "0940", "0941", "0942",
          "0943", "0944", "0973", "0974"]

def main():
    if len(sys.argv) == 1:
        input_num = input("Input the first four numbers in your cp number (09XX): ")
    elif len(sys.argv) > 2:
        print("That is more arguments than I can handle")
        sys.exit(1)
    elif sys.argv[1] == "-h" or sys.argv[1] == "--help":
        print(f'Usage:\n{sys.argv[0]} <<Your cell num (09XX)>>\nOr just use the script without any arguments, you\'ll get prompted to input one anyway')
        sys.exit()
    elif sys.argv[1].isdigit() is False:
        print("Argument is not a valid number, if you put no arguments well, you'll get prompted to input one")
        sys.exit(1)
    elif sys.argv[1] != "":
        if len(sys.argv[1]) > 4:
            print("Argument is too long man, what are you trying to pull?")
            sys.exit(1)
    else:
        print("Well I've tried using if, elif, and else statements for all of the scenarios I can think of, if this appears, you or I probably screwed up")

    input_num = sys.argv[1]

    if input_num in smart:
        print("This is a number from Smart")
        sys.exit()
    elif input_num in globe:
        print("This is a number from Globe")
        sys.exit()
    elif input_num in dito:
        print("This is a number from Dito")
        sys.exit()
    elif input_num in sun:
        print("This is a number from Sun")
        sys.exit()
    else:
        print("This ain't a number in my database sadly...")
        sys.exit()

if __name__ == '__main__':
    main()
