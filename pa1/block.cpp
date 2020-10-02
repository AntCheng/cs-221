#include "block.h"
#include <cmath>
#include <iostream>

int Block::width() const
{
/* your code here */
    if(data.size()==0){
        return 0;
    }
    return data[0].size();
}

int Block::height() const
{
/* your code here */
    return data.size();
}

void Block::render(PNG &im, int column, int row) const
{
/* your code here */
    if(column <0 || (unsigned) column>im.width() || row<0 || (unsigned) row>im.height()){
        return;
    }

    unsigned int maxWidth = ( (unsigned)column+width()>im.width())? im.width() : (column+width()) ;
    unsigned int maxHeight = ( (unsigned)row+height()>im.height())? im.height() : (row+height()) ;

    for(unsigned int x = row; x < maxHeight; x++){
        for(unsigned int y = column; y < maxWidth; y++){
            HSLAPixel* pixel = im.getPixel(y,x);
            *pixel = data[x-row][y-column]; //is the two thing the same? (x,y) and [x-row][y-column] <<<<<<<<<<<<<<<- BUGGGGGGGGGGG!!!!!!!!!!!!!!!!!
        }
    }
}

void Block::build(PNG &im, int column, int row, int width, int height)
{
/* your code here */
    data.resize(height);
    for(unsigned int x = row; x< (unsigned) row + (unsigned) height; x++){
        data[x-row].resize(width);
        for(unsigned int y = column; y < (unsigned) column + (unsigned) width; y++){
            HSLAPixel* imPixel = im.getPixel(y,x);
            data[x-row][y-column] = * imPixel;
        }
    }
}

void Block::flip()
{
/* your code here */
    vector<vector<HSLAPixel>> copy = data;
    for( int x = 0; x<height(); x++){
        for( int y =0; y<width() ; y++){
            data[x][y] = copy[height()-1-x][y];
        }
    }

}
