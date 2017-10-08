clf;
n=1:1:10;
p=[0.25 0.6 0.9];
hold on;
for i=1:3
    y=1-p(i).^n;
    plot(n,y);
end
hold off;
xlabel('n');
ylabel('CPU utilisation');
legend('p=25%','p=60%','p=90%');
saveas(gcf, 'ex1.png');