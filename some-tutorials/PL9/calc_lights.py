import math as m
import numpy as np

gw = 1024
gh = 768
vertexPos = np.array([0, -384, 0, 1])
vertexNormal = np.array([0, 0, 1, 0])

lightPos = np.array([0, 0, 90, 1]);
Lamb = np.array([1, 1, 1, 0]);
Ldif = np.array([1, 1, 1, 0]);
Lspec = np.array([1, 1, 1, 0]);
atC = 1.;
atLin = 0.0;
atQuad = 0.0;

#lightSpotDir = [0 0 0 0];
#spotCutoff = 90;
#spotCoef = 60;

#bronze
# matAmb = np.array([0.2125, 0.1275, 0.054, 0]);
# matDif = np.array([0.714, 0.4284, 0.18144, 0]);
# matSpec = np.array([0.393548, 0.271906, 0.166721, 0]);
# ns = 0.2*128;

#custom
matAmb = np.array([0.15, 0.05, 0.1, 0]);
matDif = np.array([0.5, 0.4, 0.6, 0]);
matSpec = np.array([0, 0, 1, 0]);
ns = 54

mview1 = np.array([(1, 0, 0, 0), (0, 1, 0, 0), (0, 0, 1, -665.108), (0, 0, 0, 1)]);
mview2 = np.array([(1, 0, 0, 0), (0, 0.514496, 0.857493, 0), (0, -0.857493, 0.514496, -1119.54), (0, 0, 0, 1)]);
mview3 = np.array([(0.882353, 0.470588, 0, 0), (-0.220182, 0.412842, 0.883788, 0), (0.4159, -0.779813, 0.467888, -1231.06), (0, 0, 0, 1)]);
mview4 = np.array([(0.882353, -0.470588, 0, 0), (0.220182, 0.412842, 0.883788, 0), (-0.4159, -0.779813, 0.467888, -1231.06), (0, 0, 0, 1)]);
mview5 = np.array([(1, 0, 0, 0), (0, 0.8, 0.6, 0), (0, -0.6, 0.8, -960), (0, 0, 0, 1)]);

mview = mview2
print("modelview = \n", mview)

vertexNormal = np.matmul(mview, vertexNormal)
vertexNormal = vertexNormal/np.linalg.norm(vertexNormal)
print("vertexNormal = ", vertexNormal)

lightPos = np.matmul(mview, lightPos)
vertexPos = np.matmul(mview, vertexPos)

if (lightPos[-1] == 0):
    vlv = lightPos
else:
    vlv = (lightPos - vertexPos)

vlv = vlv/np.linalg.norm(vlv)
print("vlv = ", vlv)

#localViewer
#true
#obs = np.array([0, 0, 0, 1])

#false
obs = vertexPos*np.array([1, 1, 0, 1])

vov = (obs - vertexPos)
vov = vov/np.linalg.norm(vov)
print("vov = ", vov)

Iamb = Lamb*matAmb
print("Iamb = ", Iamb)

cosTheta = np.dot(vertexNormal, vlv);
theta = m.acos(cosTheta);
if (theta > m.pi*0.5):
    Idif = np.array([0, 0, 0, 0])
else:
    Idif = (Ldif*matDif)*cosTheta

print("Idif = ", Idif)

H = (vlv + vov)
H = H/np.linalg.norm(H)
cosBeta = np.dot(vertexNormal, H)
beta = m.acos(cosBeta)
if (beta > m.pi*0.5 or beta < 0):
    Ispec = np.array([0, 0, 0, 0])
else:
    Ispec = (Lspec*matSpec)*(cosBeta**ns)

print("Ispec = ", Ispec)

d = np.linalg.norm(lightPos - vertexPos);

if lightPos[-1] == 0:
    at = 1
else:
    at = atC + atLin*d + atQuad*d*d

I = (Iamb + Idif + Ispec)/at

print("I = ", I)
