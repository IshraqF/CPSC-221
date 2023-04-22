
#include "stats.h"

stats::stats(PNG& im) {
    vector<vector<long>> columnCumuR;
    vector<vector<long>> columnCumuG;
    vector<vector<long>> columnCumuB;
    vector<vector<long>> sqColCumuR;
    vector<vector<long>> sqColCumuG;
    vector<vector<long>> sqColCumuB;
    RGBAPixel* currPixel;

    for(unsigned int column=0;column<im.width();column++){
        vector<long> columnR;
        vector<long> columnG;
        vector<long> columnB;
        vector<long> columnRsq;
        vector<long> columnGsq;
        vector<long> columnBsq;
        
        for(unsigned int row=0;row<im.height();row++){
            currPixel=im.getPixel(column,row);
            if(!row){
                columnR.push_back(currPixel->r);
                columnG.push_back(currPixel->g);
                columnB.push_back(currPixel->b);
                columnRsq.push_back(pow(currPixel->r,2));
                columnGsq.push_back(pow(currPixel->g,2));
                columnBsq.push_back(pow(currPixel->b,2));
            }else{
                columnR.push_back(currPixel->r+columnR[row-1]);
                columnG.push_back(currPixel->g+columnG[row-1]);
                columnB.push_back(currPixel->b+columnB[row-1]);
                columnRsq.push_back(pow(currPixel->r,2)+columnRsq[row-1]);
                columnGsq.push_back(pow(currPixel->g,2)+columnGsq[row-1]);
                columnBsq.push_back(pow(currPixel->b,2)+columnBsq[row-1]);
            }
        }
        columnCumuR.push_back(columnR);
        columnCumuG.push_back(columnG);
        columnCumuB.push_back(columnB);
        sqColCumuR.push_back(columnRsq);
        sqColCumuG.push_back(columnGsq);
        sqColCumuB.push_back(columnBsq);
    }

    vector<long> columnR;
    vector<long> columnG;
    vector<long> columnB;
    vector<long> columnRsq;
    vector<long> columnGsq;
    vector<long> columnBsq;
    for(unsigned int column=0; column<im.width();column++){
        for(unsigned int row=0; row<im.height();row++){
            currPixel=im.getPixel(column,row);
            if(!column && !row){
                columnR.push_back(currPixel->r);
                columnG.push_back(currPixel->g);
                columnB.push_back(currPixel->b);
                columnRsq.push_back(pow(currPixel->r,2));
                columnGsq.push_back(pow(currPixel->g,2));
                columnBsq.push_back(pow(currPixel->b,2));
            } else if(!column){
                columnR.push_back(currPixel->r+columnR[row-1]);
                columnG.push_back(currPixel->g+columnG[row-1]);
                columnB.push_back(currPixel->b+columnB[row-1]);
                columnRsq.push_back(pow(currPixel->r,2)+columnRsq[row-1]);
                columnGsq.push_back(pow(currPixel->g,2)+columnGsq[row-1]);
                columnBsq.push_back(pow(currPixel->b,2)+columnBsq[row-1]);
            } else{
                columnR.push_back(sumRed[column-1][row]+columnCumuR[column][row]);
                columnG.push_back(sumGreen[column-1][row]+columnCumuG[column][row]);
                columnB.push_back(sumBlue[column-1][row]+columnCumuB[column][row]);
                columnRsq.push_back(sumsqRed[column-1][row]+sqColCumuR[column][row]);
                columnGsq.push_back(sumsqGreen[column-1][row]+sqColCumuG[column][row]);
                columnBsq.push_back(sumsqBlue[column-1][row]+sqColCumuB[column][row]);
            }
        }
        sumRed.push_back(columnR);
        sumGreen.push_back(columnG);
        sumBlue.push_back(columnB);
        sumsqRed.push_back(columnRsq);
        sumsqGreen.push_back(columnGsq);
        sumsqBlue.push_back(columnBsq);
        columnR.clear();
        columnG.clear();
        columnB.clear();
        columnRsq.clear();
        columnGsq.clear();
        columnBsq.clear();
    }
}

long stats::getSum(char channel, pair<int, int> ul, int dim) {
    int width=pow(2, dim)-1;
    vector<vector<long>> * channelSum = nullptr;
    if(channel=='r') channelSum=&sumRed;
    else if(channel=='g') channelSum=&sumGreen;
    else if(channel=='b') channelSum=&sumBlue;
    long sum=0;
    if(ul.first && ul.second) sum+=(*channelSum)[ul.first-1][ul.second-1]-(*channelSum)[ul.first+width][ul.second-1]
        -(*channelSum)[ul.first-1][ul.second+width];
    else if(ul.first) sum-=(*channelSum)[ul.first-1][ul.second+width];
    else if(ul.second) sum-=(*channelSum)[ul.first+width][ul.second-1];
    sum += (*channelSum)[ul.first+width][ul.second+width];
    return sum;
}

long stats::getSumSq(char channel, pair<int, int> ul, int dim) {
    int width=pow(2, dim)-1;
    vector<vector<long>> * channelSum;
    if(channel=='r') channelSum=&sumsqRed;
    else if(channel=='g') channelSum=&sumsqGreen;
    else channelSum=&sumsqBlue;
    long sum=0;
    if(ul.first && ul.second) sum+=(*channelSum)[ul.first-1][ul.second-1]-(*channelSum)[ul.first+width][ul.second-1]
        -(*channelSum)[ul.first-1][ul.second+width];
    else if(ul.first) sum-=(*channelSum)[ul.first-1][ul.second+width];
    else if(ul.second) sum-=(*channelSum)[ul.first+width][ul.second-1];
    sum += (*channelSum)[ul.first+width][ul.second+width];
    return sum;
}

long stats::rectArea(int dim) {
    return pow(pow(2,dim),2);
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int, int> ul, int dim) {
    /* Your code here!! */
    long sqArea=rectArea(dim);
    RGBAPixel avgPixel=getAvg(ul, dim);
    long r=getSum('r', ul, dim);
    long g=getSum('g', ul, dim);
    long b=getSum('b', ul, dim);
    long rSq=getSumSq('r', ul, dim);
    long gSq=getSumSq('g', ul, dim);
    long bSq=getSumSq('b', ul, dim);
    return rSq+gSq+bSq-(pow(r,2)+pow(g,2)+pow(b,2))/sqArea;
}

RGBAPixel stats::getAvg(pair<int, int> ul, int dim) {
    return RGBAPixel(getSum('r',ul,dim)/rectArea(dim),getSum('g',ul,dim)/rectArea(dim),getSum('b',ul,dim)/rectArea(dim));
}
