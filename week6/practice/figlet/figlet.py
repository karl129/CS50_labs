import sys
from pyfiglet import Figlet


if len(sys.argv) == 1:
    font = "slant"
elif len(sys.argv) == 3 and (sys.argv[1] in ["-f", "--font"]):
    font = sys.argv[2]
else:
    print("Invalid usage")
    sys.exit(1)

f = Figlet(font=font)
text = input("Input: ")
print(f.renderText(text))
sys.exit(0)
