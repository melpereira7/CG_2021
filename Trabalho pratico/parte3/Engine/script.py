import re
import math


def calculaRaio(x,y):
	return math.sqrt(x*x+y*y)



f = open("config.xml",'r')
e = open("config2.xml",'w')

tempo = 20

for line in f:
	#placeholder = '<translate time="' + str(tempo) + '" >\n'
	i = 0
	

	if(linha :=	re.search(r'\<translate X\=\"(-?\d+)\"\/\>', line)):
		tempo += 5
		placeholder = '<translate time="' + str(tempo) + '" >\n'
		if float(linha.group(1)) > 0:
			r = math.log(float(linha.group(1)))-8			
		else:
			r = float(linha.group(1))
			print(r)

		while(i<(2*math.pi)):
				
			x = 0.9*r * round(math.cos(i), 6)
		
			z = 1.1*r * round(math.sin(i), 6)

			i += math.pi / 6
			placeholder += '\t\t <point X="' + str(x) + '" Y="0" Z="' + str(z) + '"/>\n'

		placeholder += "\t</translate>\n"
		line = re.sub(rf'{linha.group(0)}', rf'{placeholder}', line)

	elif(linha := re.search(r'\<translate X\=\"(-?\d+)\" Y=\"(-?\d+)\"\/\>', line)):
		tempo += 5
		xInit = float(linha.group(1))
		yInit = float(linha.group(2))

		r = calculaRaio(xInit, yInit)

		if tempo == 95:
			r = math.log(float(linha.group(1)))-8	
			placeholder = '<translate time="' + str(0.5) + '" >\n'
			while(i<(2*math.pi)):
				x = 2*r * round(math.cos(i), 6)
				y = 0
				z = 1.5*r * round(math.sin(i), 6)
				i += math.pi / 6
				placeholder += '\t\t <point X="' + str(x) + '" Y="' + str(y) + '" Z="' + str(z) + '"/>\n'
		else:	
			placeholder = '<translate time="' + str(tempo) + '" >\n'
			while(i<(2*math.pi)):
				x = r * round(math.cos(i), 6)
				y = 0
				z = r * round(math.sin(i), 6)
				i += math.pi / 6
				placeholder += '\t\t <point X="' + str(x) + '" Y="' + str(y) + '" Z="' + str(z) + '"/>\n'

		placeholder += "\t</translate>\n"
		line = re.sub(rf'{linha.group(0)}', rf'{placeholder}', line)

	e.write(line)
