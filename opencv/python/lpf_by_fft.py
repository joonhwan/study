'''
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
int main(int argc, char ** argv)
{
    const char* filename = argc >=2 ? argv[1] : "lena.jpg";

    Mat I = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
    if( I.empty())
        return -1;

    Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize( I.rows );
    int n = getOptimalDFTSize( I.cols ); // on the border add zero values
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

'''
import cv2
import numpy as np
import matplotlib.pyplot as plt

# img = cv2.imread("imageTextR.png", cv2.IMREAD_GRAYSCALE)
img = cv2.imread("imageTextN.png", cv2.IMREAD_GRAYSCALE)
irows,icols = img.shape
m = cv2.getOptimalDFTSize(irows)
n = cv2.getOptimalDFTSize(icols)
right, bottom = n-icols, m-irows

nimg = cv2.copyMakeBorder(img, 0, bottom, 0, right, cv2.BORDER_CONSTANT, value=0)

'''

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

    dft(complexI, complexI);            // this way the result may fit in the source matrix
'''
# planes = [ nimg.astype('float32'), np.zeros(nimg.shape).astype('float32') ]
# complexImg = cv2.merge(planes)
# complexImg = cv2.dft(complexImg)
complexImg = cv2.dft(nimg.astype('float32'), flags=cv2.DFT_COMPLEX_OUTPUT)


'''
    // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];

    magI += Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);

    // crop the spectrum, if it has an odd number of rows or columns
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magI.cols/2;
    int cy = magI.rows/2;

    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right
'''
planes = cv2.split(complexImg)
magImg = cv2.magnitude(planes[0], planes[1])
magImg = magImg + 1
magImg = cv2.log(magImg)

cx = magImg.shape[1]/2
cy = magImg.shape[0]/2

q0 = magImg[0:cy, 0:cx] # top-left
q1 = magImg[0:cy, cx:] # top-right
q2 = magImg[cy:, 0:cx] # bottom-left
q3 = magImg[cy:, cx:] # bottom-right

'''
    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
                                            // viewable image form (float between values 0 and 1).

    imshow("Input Image"       , I   );    // Show the result
    imshow("spectrum magnitude", magI);
    waitKey();

    return 0;
}
'''
tmp = q0.copy()
np.copyto(q0, q3)
np.copyto(q3, tmp)

tmp = q1.copy()
np.copyto(q1, q2)
np.copyto(q2, tmp)

cv2.normalize(magImg, alpha=0, beta=1, norm_type=cv2.NORM_MINMAX)

fig = plt.figure(figsize=(10,10))
axis = fig.add_subplot(1,1,1)
axis.imshow(magImg, cmap='gray')
plt.show()
