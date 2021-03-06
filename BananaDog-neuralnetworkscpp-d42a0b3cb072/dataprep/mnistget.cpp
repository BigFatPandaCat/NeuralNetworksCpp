#include "mnistget.h"

int MnistGet::reverseInt (int i) 
{
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

arma::cube MnistGet::read_mnist(std::string dir)
{
    //corresponds to the batch template in network.cpp/network.h
    arma::cube ret(60000,2,784);
    ret.zeros();

    ifstream file (dir);
    if (file.is_open())
    {
        int magic_number=0;
        int number_of_images=0;
        int n_rows=0;
        int n_cols=0;

        file.read((char*)&magic_number,sizeof(magic_number)); 
        magic_number= reverseInt(magic_number);

        file.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images= reverseInt(number_of_images);

        file.read((char*)&n_rows,sizeof(n_rows));
        n_rows= reverseInt(n_rows);

        file.read((char*)&n_cols,sizeof(n_cols));
        n_cols= reverseInt(n_cols);

        for(int i=0;i<number_of_images;i++)
        {
            for(int r=0;r<n_rows;r++)
            {
                for(int c=0;c<n_cols;c++)
                {
                    unsigned char temp=0;
                    file.read((char*)&temp,sizeof(temp));
		    ret(i,0,r*(n_cols)+c) = (int)temp;
                }
            }
        }
    }
    return ret;
}

/*
std::vector<mattrial> MnistGet::read_mnistimg()
{
    //corresponds to the batch template in network.cpp/network.h
    std::vector<cv::Mat> ret;

    ifstream file ("./data/t10k-images.idx3-ubyte");
    if (file.is_open())
    {
        int magic_number=0;
        int number_of_images=0;
        int n_rows=0;
        int n_cols=0;

        file.read((char*)&magic_number,sizeof(magic_number)); 
        magic_number= reverseInt(magic_number);

        file.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images= reverseInt(number_of_images);

        file.read((char*)&n_rows,sizeof(n_rows));
        n_rows= reverseInt(n_rows);

        file.read((char*)&n_cols,sizeof(n_cols));
        n_cols= reverseInt(n_cols);

        for(int i=0;i<number_of_images;i++)
        {
	    cv::Mat tempimg = cv::Mat::zeros(n_rows,n_cols, CV_8UC1);
            for(int r=0;r<n_rows;r++)
            {
                for(int c=0;c<n_cols;c++)
                {
                    unsigned char temp=0;
                    file.read((char*)&temp,sizeof(temp));
		    tempimg.at<uchar>(r,c) = (int)temp;
                }
            }
	    ret.push_back(tempimg);
        }
    }
    return ret;
}
*/

arma::cube MnistGet::read_labels(std::string dir)
{
    //corresponds to the batch template in network.cpp/network.h
    arma::cube ret(60000,2,784);
    ret.zeros();

    ifstream file (dir);
    if (file.is_open())
    {
        int magic_number=0;
        int number_of_images=0;

        file.read((char*)&magic_number,sizeof(magic_number)); 
        magic_number= reverseInt(magic_number);

        file.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images= reverseInt(number_of_images);

        for(int i=0;i<number_of_images;i++)
        {
            unsigned char temp=0;
            file.read((char*)&temp,sizeof(temp));
            ret(i,1,(unsigned int)temp) = 1;
        }
    }
    return ret;
}
