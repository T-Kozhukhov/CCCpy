import numpy as np  
import matplotlib.pyplot as plt 
import numpy.random 

Lx = 30
Ly = 8
phi_in = 0.5
phi_border = 2.0

rmean = 0.25
rvar =  0.15

Nglued = 2*int(phi_border*Lx/(2*rmean))
Ninside = int(Lx*Ly/(np.pi*rmean**2))

particles = np.zeros((Nglued+Ninside,9))

# border particles
for k in range(Nglued):
    if k<Nglued/2:
        xpos = 2*rmean*k/phi_border
        ypos = 0
    else:
        xpos = 2*rmean*(k-Nglued/2)/phi_border
        ypos =  Ly
    particles[k,0]=k
    particles[k,1]=xpos
    particles[k,2]=ypos
    particles[k,3]=0
    particles[k,4]=0
    particles[k,5]=0
    particles[k,6]=rmean
    particles[k,7]=rmean
    particles[k,8]=1

# inside particles
for k in range(Nglued,Nglued+Ninside):
    xpos = np.random.uniform(0,Lx,1)
    ypos = np.random.uniform(2*rmean,Ly-2*rmean,1)
    particles[k,0]=k
    particles[k,1]=xpos
    particles[k,2]=ypos
    particles[k,3]=np.random.uniform(-np.pi,np.pi,1)
    particles[k,4]=0
    particles[k,5]=0
    particles[k,6]=np.random.uniform(rmean*(1-rvar),rmean*(1+rvar),1)
    particles[k,7]=rmean
    particles[k,8]=0

# write to text file. Not pretty, but this one does not read header ...
numpy.savetxt("corridor.csv", particles, delimiter=",",fmt=['%d','%8.6f','%8.6f','%8.6f','%8.6f','%8.6f','%8.6f','%8.6f','%d'])




