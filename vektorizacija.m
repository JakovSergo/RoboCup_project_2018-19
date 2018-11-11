syms ax ay omega;
alfa=[pi/4,pi/4+ pi/2,pi/4+pi,pi/4+3*pi/2];
f=[-1;-1;1;1];
koef=zeros(3,4);
beta=zeros(1,4);
M=0.685;
R=0.09;
I=M*R^2*0.5; %approximation of inertion of robot with inertion of cylinder
a=zeros(3);

for i = 1 : 4
    beta(i)=alfa(i)+pi/2;
    koef(1,i)=-sin(alfa(i));
    koef(2,i)=cos(alfa(i));
    koef(3,i)=M*R/I;
    
end

a=[ax;ay;omega];

f=M*pinv(koef)*a;




