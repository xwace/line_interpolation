Mat globalMat;
void SetPixel(int y,int x, int color){
    globalMat.at<uchar>(y,x) = color;
}

void Line( float x1, float y1, float x2, float y2, const int& color )
{
    globalMat.create(100,100,0);
    globalMat.setTo(0);

    // Bresenham's line algorithm
    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
    if(steep)
    {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if(x1 > x2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    const float dx = x2 - x1;
    const float dy = fabs(y2 - y1);

    float error = dx / 2.0f;
    const int ystep = (y1 < y2) ? 1 : -1;
    int y = (int)y1;

    const int maxX = (int)x2;

    for(int x=(int)x1; x<=maxX; x++)
    {
        if(steep)
        {
            SetPixel(y,x, color);
        }
        else
        {
            SetPixel(x,y, color);
        }

//        namedWindow("mt",2);
        imshow("mt",globalMat*45);
        waitKey();

        error -= dy;
        if(error < 0)
        {
            y += ystep;
            error += dx;
        }
        cout<<"pix: "<<y<<" "<<x<<endl;
    }
}

int main(){
    Line(0,150,55,55,5);
}




/*=============================================*/

struct NodeInfo{int mRow,int mCol;};

std::vector<NodeInfo> interpolate(int x0, int y0, int x1, int y1)
{
    std::vector<NodeInfo> lines;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;
    int e2 = 0;

    NodeInfo point;

    while (true)
    {
        point.mRow = x0;
        point.mCol = y0;
        lines.push_back(point);

        if (x0 == x1 && y0 == y1)
            break;

        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
    return lines;
}
