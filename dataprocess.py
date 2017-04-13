import numpy as np
import matplotlib.pyplot as plt

fname = '.\Debug\lgt28284040001000.txt'
sims = 10
fields = ['m++','m--','avgplq']
data = [[0]*sims,[0]*sims,[0]*sims]

f = open(fname,'r')
_ = f.readline()

for i in range(sims):
	for fieldidx, field in enumerate(fields):
		if field == 'm++' or field == 'm--':
			_ = f.readline()
			line = f.readline()
			line.rstrip()
			strippedline=line[:-3]
			# print(strippedline)
			dataline = [float(x.strip()) for x in strippedline.split(',')]
			data[fieldidx][i] = dataline
		else:
			f.readline()
			line = f.readline()
			dataline = float(line.strip())
			data[fieldidx][i] = dataline

lent=len(data[0][0])
massx = [i for i in range(lent)]

for fieldidx, field in enumerate(fields):
	plt.figure()
	if field == 'm++' or field == 'm--':
		massy = []
		massyerr = []
		for i in range(lent):
			point = sum([data[fieldidx][simno][i] for simno in range(sims)])/sims
			pointsd = 3.25*np.sqrt(sum([(data[fieldidx][simno][i])**2 for simno in range(sims)])/sims-point**2)/np.sqrt(sims)
			massy.append(point)
			massyerr.append(pointsd)
		plt.errorbar(massx,massy,yerr=massyerr,linestyle='None',marker='x')
		plt.title(field)
		plt.xlabel('t')
		plt.ylabel('C(t)')
	else:
		point = sum(data[fieldidx])/sims
		pointsd = 3.25*np.sqrt(sum([pt**2 for pt in data[fieldidx]])/sims-point**2)/np.sqrt(sims)
		print('val:'+str(point)+' +-'+str(pointsd))
		plt.errorbar(0,point,yerr=pointsd,linestyle='None',marker='x')
		plt.title(field)
	plt.show()

