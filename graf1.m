%% **************** Archivo para generar las figuras de un archivo .m ***************
clc, clear all, close all;

myPath = 'C:\Users\lau_t\Dropbox\3erSemestre\Tesis\codigo\c++\Observador_c\Imagenes';
keySave = '1';
mySystem = sprintf('exe%ssim',keySave);


Asize = 0.75*[1, 1]; Atype = 3;
LINEWIDTH = 1;
FONTSIZE = 12;
LOCATION = 'Best';
FONTSIZE_legend = 12;

con = 180/pi;
%% ***** Extracción de datos *****

G = load('prueba1.m');
t = G(:,1);
qR1 = G(:,2)*con;
qR2 = G(:,3)*con;
qR3 = G(:,4)*con;
hatQ1 = G(:,5)*con;
hatQ2 = G(:,6)*con;
hatQ3 = G(:,7)*con;
z1 = G(:,8)*con;
z2 = G(:,9)*con;
z3 = G(:,10)*con;
tau1 = G(:,11)*con;
tau2 = G(:,12)*con;
tau3 = G(:,13)*con;
qd1 = G(:,14)*con;
qd2 = G(:,15)*con;
qd3 = G(:,16)*con;
dotHatQ1 = G(:,17)*con;
dotHatQ2 = G(:,18)*con;
dotHatQ3 = G(:,19)*con;
ePos1 = G(:,20)*con;
ePos2 = G(:,21)*con;
ePos3 = G(:,22)*con;

sigma1 = G(:,23);
sigma2 = G(:,24);
sigma3 = G(:,25);

s1 = G(:,26);
s2 = G(:,27);
s3 = G(:,28);

signo1 = G(:,29);
signo2 = G(:,30);
signo3 = G(:,31);

dotS1 = G(:,32);
dotS2 = G(:,33);
dotS3 = G(:,34);

%% Error de observación

%subplot(4,2,3),
figure
plot(t,z1,'-r',t,z2,'-g',t,z3,'-b','Linewidth',LINEWIDTH), grid on
xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
Title = sprintf('Error de Observacion');
title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
h_legend = legend('z1','z2','z3','Location','Northeast');
set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')

%% Error de posición

figure
plot(t,ePos1,'-r',t,ePos2,'-g',t,ePos3,'-b','Linewidth',LINEWIDTH), grid on
xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
Title = sprintf('Error de Posicion');
title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
h_legend = legend('ePos1','ePos2','ePos3','Location','Northeast');
set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')

figure
plot(t,ePos1,'-r','Linewidth',LINEWIDTH), grid on
xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
Title = sprintf('Error de Posicion');
title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
h_legend = legend('ePos1','Location','Northeast');
set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')

figure
plot(t,ePos2,'-g','Linewidth',LINEWIDTH), grid on
xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
Title = sprintf('Error de Posicion');
title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
h_legend = legend('ePos2','Location','Northeast');
set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')

figure
plot(t,ePos3,'-b','Linewidth',LINEWIDTH), grid on
xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
Title = sprintf('Error de Posicion');
title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
h_legend = legend('ePos3','Location','Northeast');
set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')
%% Posición Estimada vs Deseada

figure
subplot(3,1,1),
plot(t,hatQ1,'-r',t,qd1,'-g','Linewidth',LINEWIDTH), grid on
xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
Title = sprintf('Posición Estimada');
title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
h_legend = legend('hatQ1','qd1','Location','Northeast');
set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')

subplot(3,1,2),
plot(t,hatQ2,'-r',t,qd2,'-g','Linewidth',LINEWIDTH), grid on
xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
Title = sprintf('Posición Estimada');
title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
h_legend = legend('hatQ2','qd2','Location','Northeast');
set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')

subplot(3,1,3),
plot(t,hatQ3,'-r',t,qd3,'-g','Linewidth',LINEWIDTH), grid on
xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
Title = sprintf('Posición Estimada');
title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
h_legend = legend('hatQ3','qd3','Location','Northeast');
set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')


%% Integral

figure
plot(t,sigma1,'-r',t,sigma2,'-g',t,sigma3,'-b','Linewidth',LINEWIDTH), grid on
xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
Title = sprintf('Termino integrativo');
title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
h_legend = legend('sig1','sig2','sig3','Location','Northeast');
set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')

%% S

figure
plot(t,s1,'-r',t,s2,'-g',t,s3,'-b','Linewidth',LINEWIDTH), grid on
xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
Title = sprintf('Superficie');
title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
h_legend = legend('s1','s2','s3','Location','Northeast');
set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')


%% Signo

% figure
% plot(t,signo1,'-r',t,signo2,'-g',t,signo3,'-b','Linewidth',LINEWIDTH), grid on
% xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
% ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
% set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
% Title = sprintf('Signo');
% title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
% h_legend = legend('signo1','signo2','signo3','Location','Northeast');
% set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')

figure
plot(t,signo1,'-r','Linewidth',LINEWIDTH), grid on
xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
Title = sprintf('Signo');
title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
h_legend = legend('signo1','Location','Northeast');
set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')

figure
plot(t,signo2,'-g','Linewidth',LINEWIDTH), grid on
xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
Title = sprintf('Signo');
title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
h_legend = legend('signo2','Location','Northeast');
set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')

figure
plot(t,signo3,'-b','Linewidth',LINEWIDTH), grid on
xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
Title = sprintf('Signo');
title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
h_legend = legend('signo3','Location','Northeast');
set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')



%% dotSigma

figure
plot(t,dotS1,'-r',t,dotS2,'-g',t,dotS3,'-b','Linewidth',LINEWIDTH), grid on
xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
Title = sprintf('dotSigma');
title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
h_legend = legend('dotS1','dotS2','dotS3','Location','Northeast');
set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')


%% Posición Leida

figure
%subplot(3,2,1),
plot(t,qR1,'-r',t,qR2,'-g',t,qR3,'-b','Linewidth',LINEWIDTH), grid on
xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
Title = sprintf('Posición Leida');
title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
h_legend = legend('q1','q2','q3','Location','Northeast');
set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')

%% %% Posición Deseada

%subplot(4,2,5),
figure
plot(t,qd1,'-r',t,qd2,'-g',t,qd3,'-b','Linewidth',LINEWIDTH), grid on
xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
Title = sprintf('Posición deseada');
title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
h_legend = legend('qd1','qd2','qd3','Location','Northeast');
set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')


%% Par

%subplot(4,2,4),
figure
plot(t,tau1,'-r',t,tau2,'-g',t,tau3,'-b','Linewidth',LINEWIDTH), grid on
xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
Title = sprintf('Par');
title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
h_legend = legend('tau1','tau2','tau3','Location','Northeast');
set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')


%% Velocidad Estimada

%subplot(4,2,6),
figure
plot(t,dotHatQ1,'-r',t,dotHatQ2,'-g', t, dotHatQ3,'-b','Linewidth',LINEWIDTH), grid on
xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
Title = sprintf('Velocidad Estimada');
title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
h_legend = legend('dotHatQ1','dotHatQ2','dotHatQ3','Location','Northeast');
set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')




%% Termino Exponencial

% %subplot(4,2,8),
% figure
% plot(t,sd1,'-r',t,sd2,'-g',t,sd3,'-b','Linewidth',LINEWIDTH), grid on
% xlabel('Tiempo [s]', 'FontSize', FONTSIZE,'FontWeight','Bold')
% ylabel('Amplitud','FontSize', FONTSIZE,'FontWeight','Bold')
% set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
% Title = sprintf('Sd');
% title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
% h_legend = legend('sd1','sd2','sd3','Location','Northeast');
% set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')
% 




%% ***** Guardar Gráficas *****

% fig_eObs = figure('NumberTitle','off', 'Color','white','Units','Norm','Resize','on','outerposition',[0 0 1 1]);
% set(gcf,'Name', sprintf('Ejercicio %s',keySave),'Visible','off')
% plot(t, z1, '-r', t, z2, '-g', t, z3, '-b', 'Linewidth',LINEWIDTH), hold on
% grid on
% xlabel('Tiempo[s]','FontSize',FONTSIZE,'FontWeight','Bold')
% ylabel('Amplitud','FontSize',FONTSIZE,'FontWeight','Bold')
% set(gca,'FontWeight','Bold','FontSize',FONTSIZE)
% Title = sprintf('Error de Observación');
% title(Title,'FontSize',FONTSIZE,'FontWeight','Bold')
% h_legend = legend('z1','z2','z3','Location',LOCATION);
% set(h_legend,'FontSize',FONTSIZE_legend,'FontWeight','Bold')
% 
% SAVEFIG(fig_eObs,keySave,'s', myPath)

