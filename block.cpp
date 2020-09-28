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
    if(column <0 || column>im.width() || row<0 || row>im.height()){
        return;
    }

    int maxWidth = (row+width()>im.width())? im.width() : (row+width()) ;
    int maxHeight = (column+height()>im.height())? im.height() : (column+height()) ;

    for(unsigned x = row; x <= maxHeight; x++){
        for(unsigned y = column; y <= maxWidth; y++){
            HSLAPixel* pixel = im.getPixel(x,y);
            *pixel = data[x-row][y-column];
        }
    }
}

void Block::build(PNG &im, int column, int row, int width, int height)
{
/* your code here */

    data.resize(im.height());
    for(unsigned x = row; x<row + height; x++){
        data[x-row].resize(im.width());
        for(unsigned y = column; y < column + width; y++){
            HSLAPixel* imPixel = im.getPixel(x,y);
            data[x-row][y-column] = * imPixel;
        }
    }
}

void Block::flip()
{
/* your code here */
    vector<vector<HSLAPixel>> copy = data;
    for(unsigned x = 0; x<height(); x++){
        for(unsigned y =0; y<width() ; y++){
            data[x][y] = copy[height()-x][y];
        }
    }

}
