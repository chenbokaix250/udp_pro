import numpy as np 
import cv2 

#img = cv2.imread('a.png')
img = cv2.imread('b.jpg')
img_encode = cv2.imencode('.jpg',img)[1]
data_encode = np.array(img_encode)
str_encode = data_encode.tobytes()
print(len(str_encode))

# a.png 813611
# b.jpg 62470

#nparr = np.fromstring(str_encode,np.uint8)
nparr = np.frombuffer(str_encode,np.uint8)
img_decode = cv2.imdecode(nparr,cv2.IMREAD_COLOR)
cv2.imshow('result',img_decode)
cv2.waitKey()
cv2.destroyAllWindows()