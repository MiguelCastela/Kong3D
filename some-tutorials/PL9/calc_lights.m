clear all;
clc;

gw = 1024;
gh = 768;
malhaPos = [0 -384 0 1]
Nv = [0 0 1 0];

mview1 = [1 0 0 0; 0 1 0 0; 0 0 1 -665.108; 0 0 0 1];
mview2 = [1 0 0 0 ;0 0.514496 0.857493 0 ; 0 -0.857493 0.514496 -1119.54 ; 0 0 0 1];
mview3 = [0.882353 0.470588 0 0 ;-0.220182 0.412842 0.883788 0 ;0.4159 -0.779813 0.467888 -1231.06 ;0 0 0 1];
mview4 = [0.882353 -0.470588 0 0 ;0.220182 0.412842 0.883788 0 ;-0.4159 -0.779813 0.467888 -1231.06 ;0 0 0 1];
mview5 = [1 0 0 0 ;0 0.8 0.6 0 ;0 -0.6 0.8 -960 ;0 0 0 1];

mview = mview1

view1 = [0 0 665.108 1];
view2 = [0 -gh*1.25 gh*0.75 1];
view3 = [gw*0.5 -gh*1.25 gh*0.75 1];
view4 = [-gw*0.5 -gh*1.25 gh*0.75 1];
view5 = [0 gh*0.75 gh 1];

view = view1

lightPos = [0 0 90 1];
Lamb = [1 1 1 0];
Ldif = [1 1 1 0];
Lspec = [1 1 1 0];
atC = 1.;
atLin = 0.0001;
atQuad = 0.00001;



lightSpotDir = [0 0 0 0];
spotCutoff = 90;
spotCoef = 60;

%bronze
matAmb = [0.2125 0.1275 0.054 0];
matDif = [0.714 0.4284 0.18144 0];
matSpec = [0.393548 0.271906 0.166721 0];
ns = 0.2*128;

% matAmb = [0. 0. 0. 0];
% matDif = [0. 0. 0. 0];
% matSpec = [1. 1. 1. 0];

%Nv = Nv/norm(Nv)

Nv = ((mview*Nv')/norm(mview*Nv'))'
lightPos = (mview*lightPos')'
malhaPos = (mview*malhaPos')'

if (lightPos(end) == 0)
    vlv = lightPos
else
    vlv = (lightPos - malhaPos)
end;
vlv = vlv/norm(vlv)

%localViewer
%true
obs = [0 0 0 1]
vov = (obs - malhaPos)

%false
%obs = malhaPos.*[1 1 0 1]
%vov = (obs - malhaPos)


vov = vov/norm(vov)



Iamb = Lamb.*matAmb

cosTheta = dot(Nv, vlv)/(norm(Nv)*norm(vlv));
theta = acos(cosTheta)
if theta > pi*0.5 | theta < 0
    Idif = [0 0 0 0]
else
    Idif = (Ldif.*matDif)*cosTheta
end;

h = (vlv + vov)/norm(vlv + vov) 
cosBeta = dot(Nv, h)
beta = acos(cosBeta)
if beta > pi*0.5 || beta < 0
    Ispec_h = [0 0 0 0]
else
    Ispec_h = (Lspec.*matSpec)*(cosBeta^ns)
end;

vr = ((2*dot(Nv, vlv)).*Nv) - vlv;
vr = vr/norm(vr)
cosGamma = dot(vov, vr)/(norm(vov)*norm(vr))
gamma = acos(cosGamma)
if gamma > pi*0.5 || gamma < 0
    Ispec = [0 0 0 0]
else
    Ispec = (Lspec.*matSpec)*(cosGamma^ns)
end;


d = norm(lightPos - malhaPos);

if lightPos(end) == 0
    at = 1
else
    at = atC + atLin*d + atQuad*d*d
end;

I_1 = (Iamb + Idif + Ispec)/at
I_2 = (Iamb + Idif + Ispec_h)/at