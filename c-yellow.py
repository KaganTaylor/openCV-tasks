import numpy as np
import cv2 as cv

# Open Camera #
cap = cv.VideoCapture(0)

# Check Successful Camera Opening #
if not cap.isOpened():
    exit()

# Continuously Capture Frames #
capture = True
while capture:
    successful, frame = cap.read()

    ## Check Successful Frame Read ##
    if not successful:
        print("Could not read next frame. Exiting...")
        break
    
    ## Convert frame to HSV (for ease) ##
    hsvFrame = cv.cvtColor(frame, cv.COLOR_BGR2HSV)

    ## Initialise Yellow HSV Boundaries ##
    lower = np.array([20, 100, 100], dtype=np.uint8)
    upper = np.array([30, 255, 255], dtype=np.uint8)

    ## Apply Boundary Thresholds ##
    mask = cv.inRange(hsvFrame, lower, upper)

    ## Apply Mask to Original Frame ##
    output = cv.bitwise_and(frame, frame, mask=mask)

    ## Show Output ##
    cv.imshow('output', output)

    ## Set Exit Conditions ##
    if cv.waitKey(1) == ord('q'):
        capture = False

# Explicit Releases on Exit #
cap.release()
cv.destroyAllWindows()