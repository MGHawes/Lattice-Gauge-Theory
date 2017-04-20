import numpy as np
import matplotlib.pyplot as plt
sims = 24
dataname = 'lgt22223620000100002p0'

def plotconfig(dataname,sims,silent,residuals):
	inlocation = ".\Debug\\"
	outlocation = ".\outdata\\"
	fname = inlocation + dataname +'.txt'
	outfname = outlocation + 'out' + dataname 
	outcorrelatordata = [[],[],[]]

	#The number of dof is v =n-1 and this is the vth number in the table so by zero based indexing t=ttable[sims-2]
	ttable=[12.71,4.303,3.182,2.776,2.571,2.447,2.365,2.306,2.262,2.228,2.201,2.179,2.16,2.145,2.131,2.12,2.11,2.101,2.093,2.086,2.08,2.074,2.069,2.064,2.06,2.056,2.052,2.048,2.045,2.042]

	t=ttable[sims-2]
	beta = dataname[-3:]
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
				# print('l:'+strippedline+'\n')
				dataline = [float(x.strip()) for x in strippedline.split(',')]
				data[fieldidx][i] = dataline
			else:
				f.readline()
				line = f.readline()
				# print('pl:'+line+'\n')
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
				pointsd = np.sqrt(sum([(data[fieldidx][simno][i]-point)**2 for simno in range(sims)])/(sims-1))
				pointserr = t*pointsd/np.sqrt(sims)
				massy.append(point)
				massyerr.append(pointserr)
			plt.errorbar(massx,massy,yerr=massyerr,linestyle='None',marker='x')
			plt.title(dataname+' '+field)
			plt.xlabel('t')
			plt.ylabel('C(t)')
			plt.gca().set_xlim(left=-1)

			

			outf = open(outfname+field+'.csv','w')
			for i in range(int(lent/2)):
				outf.write(str(i)+','+str(massy[i])+','+str(massyerr[i])+'\n')
			outf.close()

		else:
			point = sum(data[fieldidx])/sims
			pointsd = t*np.sqrt(sum([(pt-point)**2 for pt in data[fieldidx]])/(sims-1))/np.sqrt(sims)
			print(dataname)
			print('val:'+str(point)+' +-'+str(pointsd))
			plt.ticklabel_format(style='sci',axes='x')
			plt.ticklabel_format(useOffset=False)
			plt.errorbar(0,point,yerr=pointsd,linestyle='None',marker='x')
			plt.title(dataname+' '+field)

			if residuals == 1:
				x=[i for i in range(sims)] 
				y=[data[fieldidx][i]-point for i in range(sims)]
				plt.figure(figsize=(6,4))
				plt.scatter(x,y)
				plt.ylabel('$x_i - \\bar{x}$',fontsize='xx-large')
				plt.xlabel('$i$',fontsize='xx-large')
				plt.title('$\\mathrm{Residuals}$',fontsize='xx-large')
				plt.yticks([-0.0002,-0.0001,0,0.0001,0.0002], fontsize='large')
				plt.xticks([0,10,20,30],fontsize='large')
				plt.ylim((-0.0002,0.0002))
				plt.show()
		
		if silent == 1:
			plt.close()
		else:
			plt.savefig(inlocation+dataname+field+'.png')
			plt.show()
		
datalist = [['lgt28284020000100002p3', 30],
			['lgt22223620000100002p3', 30],
			['lgt18182420000100002p3', 30],
			['lgt28284020000100002p2', 29],
			['lgt22223620000100002p2', 30],
			['lgt18182420000100002p2', 30],
			['lgt18182420000100002p0', 30],
			['lgt22223620000100002p0', 30],
			['lgt28284020000100002p0', 28],
			['lgt18182420000100002p1', 30],
			['lgt22223620000100002p1', 30],
			['lgt28284020000100002p1', 28]
			]

for dataname, sims in datalist:
	plotconfig(dataname,sims,1,0)


# plt.figure(figsize=(6,4))
# plt.xlabel('$i$',fontsize='x-large')
# # plt.ylim((0.1,1.1))
# plt.yticks([0.2,0.4,0.6,0.8,1])
# plt.ylabel('$\lambda_i$',fontsize='xx-large')
# plt.title('$\\mathrm{LFR\\ Eigenvalue\\ Spectra}$',fontsize='large')


# w,v = runsim([['ER',100, 0.05]])
# plt.plot(sorted(np.real(w),reverse=True)[0:30],'b',marker='x', linestyle = 'None',label='$\\mathrm{ER\\ }p=0.05$')
