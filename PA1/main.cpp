/**
 * @file main.cpp
 * Split an image into k vertical strips (blocks), 
 * rearrange the blocks into a random order,
 * write the concatenation of the blocks into a new image,
 * unscramble the new image back into the original.
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#include "chain.h"
#include <iostream>
#include "cs221util/PNG.h"
using namespace cs221util;
using namespace std;

int main() {
  /**
   * Use your own images and other tests to test your code!
   * Some tests you should write:
   * 1) building and rendering blocks
   * 2) copying a chain
   * 3) assigning one chain to another
   * 4) swapping Nodes in a chain
   * 5) unscrambling an image
   * NOTE: Your code should not be able to correctly unscramble
   * kh.png.  Why not?
   */
  PNG im;
  PNG im1;
  PNG im2;
  PNG im3;

  im.readFromFile("images/ronMueck.png");
  im2.readFromFile("images/terrain.png");
  im1.readFromFile("images/kh.png");
  im3.readFromFile("images/sun.png");
  cout<<im.width();

  Chain c(im, 6);
  Chain c1(im1, 6);
  Chain c2(im2, 6);
  Chain c3(im3, 6);
  // Chain c;

  // Block b;
  // Chain::Node * p=NULL;
  // int k=3;
  // int w=50;
  // for( int i=0; i < k; i++ ) {
  //   Block b;
  //   b.build(im , i*w, w);
  //   p = c.insertAfter(p, b);
  // }

  // randomly scramble the blocks.
  srand(time(NULL));
  c.scramble();
  c1.scramble();
  c2.scramble();
  c3.scramble();
  // or test swapping a few blocks
  //  c.testSwap(3,4); // swap the 3rd and 4th blocks.
  //  c.testSwap(0,1);
  //  c.testSwap(1,0);
  //  c.testSwap(0,4);

  c.render().writeToFile("images/scram.png");  // look at scram.png to debug
  c1.render().writeToFile("images/scram1.png");  // look at scram.png to debug
  c2.render().writeToFile("images/scram2.png");  // look at scram.png to debug
  c3.render().writeToFile("images/scram3.png");  // look at scram.png to debug

  // test unscramble()
  c.unscramble();
  c1.unscramble();
  c2.unscramble();
  c3.unscramble();
  c.render().writeToFile("images/unscram.png");
  c1.render().writeToFile("images/unscram1.png");
  c2.render().writeToFile("images/unscram2.png");
  c3.render().writeToFile("images/unscram3.png");

  /* Check that unscramble works to unscramble a *saved* image too.
  PNG om;
  om.readFromFile("images/scram.png");
  Chain d(om, 5);
  d.unscramble();
  d.render().writeToFile("images/unscram.png");
  */
  return 0;
}
