% [fname, fpath, fltidx]  = uigetfile({'*.txt; *.csv'}, 'File Chooser', 'C:/Users/Gueg/Desktop');
% path = strcat(fpath,fname,fltidx);
% path = path(1:end-1);
csv = load('C:/Users/Gueg/Desktop/noise.txt');
subplot
scatter3(csv(:,1), csv(:,2), csv(:,4), 100, csv(:,4));