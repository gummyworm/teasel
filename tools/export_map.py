import sys
from BeautifulSoup import BeautifulSoup

name = sys.argv[1].split('/')
name = name[-1].split('.')[0]

soup = BeautifulSoup(open(sys.argv[1]))

print("uint16_t " + name + "={\n")
print(soup.find('data').string)
print("\n}\n")

