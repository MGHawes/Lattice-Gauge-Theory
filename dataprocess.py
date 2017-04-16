import numpy as np
import matplotlib.pyplot as plt

dataname = 'lgt28284040001000'
location = ".\Debug\\"
fname = location + dataname + '.txt'
sims = 10
fields = ['m++','m--','wilson','avgplq']
data = [[0]*sims,[0]*sims,[0]*sims,[0]*sims]

f = open(fname,'r')
_ = f.readline()

for i in range(sims):
	for fieldidx, field in enumerate(fields):
		if field == 'm++' or field == 'm--' or field == 'wilson':
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
	if field == 'm++' or field == 'm--' or field == 'wilson':
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
		plt.ticklabel_format(style='plain',axes='x')
		plt.ticklabel_format(useOffset=False)
		plt.errorbar(0,point,yerr=pointsd,linestyle='None',marker='x')
		plt.title(field)

	plt.savefig(location+dataname+field+'.png')
	plt.show()
	

