import cv2
import numpy as np
import matplotlib.pyplot as plt

def cv_fft_shift_orig(complexImg):
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
    tmp = q0.copy()
    np.copyto(q0, q3)
    np.copyto(q3, tmp)

    tmp = q1.copy()
    np.copyto(q1, q2)
    np.copyto(q2, tmp)

    # magImg = cv2.normalize(magImg, alpha=0, beta=1, norm_type=cv2.NORM_MINMAX)
    return magImg

def cv_fft_shift(complexImg):
    planes = cv2.split(complexImg)

    for plane in planes:
        shifted = plane
        cx = shifted.shape[1]/2
        cy = shifted.shape[0]/2
        q0 = shifted[0:cy, 0:cx] # top-left
        q1 = shifted[0:cy, cx:] # top-right
        q2 = shifted[cy:, 0:cx] # bottom-left
        q3 = shifted[cy:, cx:] # bottom-right
        tmp = q0.copy()
        np.copyto(q0, q3)
        np.copyto(q3, tmp)
        tmp = q1.copy()
        np.copyto(q1, q2)
        np.copyto(q2, tmp)

    magImg = cv2.magnitude(planes[0], planes[1])
    magImg = magImg + 1
    magImg = cv2.log(magImg)
    
    # magImg = cv2.normalize(magImg, alpha=0, beta=1, norm_type=cv2.NORM_MINMAX)
    return magImg


def np_fft_shift(complexImg):
    shifted = np.fft.fftshift(complexImg)
    magImg = cv2.magnitude(shifted[:,:,0],shifted[:,:,1])
    magImg = np.log(magImg+1)
    return shifted, magImg

def image_fft(img, method='cv'):
    irows,icols = img.shape
    m = cv2.getOptimalDFTSize(irows)
    n = cv2.getOptimalDFTSize(icols)
    right, bottom = n-icols, m-irows

    nimg = cv2.copyMakeBorder(img, 0, bottom, 0, right, cv2.BORDER_CONSTANT, value=0)

    # planes = [ nimg.astype('float32'), np.zeros(nimg.shape).astype('float32') ]
    # complexImg = cv2.merge(planes)
    # complexImg = cv2.dft(complexImg)
    complexImg = cv2.dft(nimg.astype('float32'), flags=cv2.DFT_COMPLEX_OUTPUT)

    if method=='cv':
        magImg = cv_fft_shift(complexImg)
    else:
        magImg = np_fft_shift(complexImg)

    # magImg = cv2.normalize(magImg, alpha=0, beta=1, norm_type=cv2.NORM_MINMAX)

    return magImg


imgR = cv2.imread("imageTextR.png", cv2.IMREAD_GRAYSCALE)
cvMagR = image_fft(imgR, 'cv')
npMagR = image_fft(imgR, 'np')

fig,axes = plt.subplots(1,3,figsize=(10,10))
axes[0].imshow(imgR, cmap='gray')
axes[1].imshow(cvMagR, cmap='gray')
axes[2].imshow(cvInvImgR, cmap='gray')
plt.show()

fig,axes = plt.subplots(1,3,figsize=(10,10))
axes[0].imshow(cvMagN, cmap='gray')
axes[1].imshow(cvMagN, cmap='gray')
axes[2].imshow(npMagN, cmap='gray')
plt.show()



deltaR = npMagR - cvMagR
deltaN = npMagN - cvMagN
print("dN:{}~{}, dR:{}~{}".format(deltaN.max(),deltaN.max(),deltaR.max(),deltaR.max()))
