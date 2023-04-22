#include "block.h"
#include <cmath>
#include <iostream>

int Block::height() const {
  if (data.size()){
    return data[0].size();
  }
  return data.size();
}

int Block::width() const {
  return data.size();
}

void Block::render(PNG &im, int x) const {
  HSLAPixel * imPixel;
  for(int i=0;i<this->width();i++){
    for(int y=0;y<this->height();y++){
      imPixel=im.getPixel(x+i,y);
      imPixel->h=data[i][y].h;
      imPixel->s=data[i][y].s;
      imPixel->l=data[i][y].l;
      imPixel->a=data[i][y].a;
    }
  }
}

void Block::build(PNG &im, int x, int width) {
  for(int i=0;i<width;i++){
    vector<HSLAPixel> imageLine;
      for(uint y=0;y<im.height();y++){
        imageLine.push_back(*im.getPixel(x+i,y));
      }
    data.push_back(imageLine);
  }
}

// void Block::renderBlock(string name) const{
//   int w = this->width();
//   int h = this->height();
//   PNG retVal(w, h);
//   render(retVal,0);
//   string fullName="images/"+name;
//   retVal.writeToFile("images/"+name+".png"); 
// }
