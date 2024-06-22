import streamlit as st
import cv2
import depthai as dai
import numpy as np
import time
import serial

# Initialize serial connection for motor control
arduino_port = '/dev/ttyACM0'  # Update this based on your system
baud_rate = 9600  # Match the baud rate with the Arduino's

try:
    ser = serial.Serial(arduino_port, baud_rate)
    time.sleep(2)  # Wait for the connection to initialize
    print("Serial connection established.")
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    ser = None

# Create pipeline
pipeline = dai.Pipeline()

# Define sources and outputs
camRgb = pipeline.createColorCamera()
xoutRgb = pipeline.createXLinkOut()

xoutRgb.setStreamName("rgb")

# Properties
camRgb.setPreviewSize(416, 416)
camRgb.setResolution(dai.ColorCameraProperties.SensorResolution.THE_1080_P)
camRgb.setInterleaved(False)
camRgb.setColorOrder(dai.ColorCameraProperties.ColorOrder.BGR)
camRgb.setFps(60)
camRgb.preview.link(xoutRgb.input)

def send_command(command):
    """Send a command to the Arduino."""
    if ser:
        ser.write(command.encode())
        print(f"Sent command: {command}")
    else:
        st.error("Serial connection not established.")

def move_motor_forward():
    send_command('F')

def move_motor_backward():
    send_command('B')

def stop_motor():
    send_command('S')

def rotate_motor_left():
    send_command('L')

def rotate_motor_right():
    send_command('R')

def cam_left():
    send_command('1')

def cam_right():
    send_command('2')

def cam_up():
    send_command('3')

def cam_bottom():
    send_command('4')

def video_disp():
    stop_button_pressed = st.button("Stop")
    frame_placeholder = st.empty()
    with dai.Device(pipeline) as device:
        qRgb = device.getOutputQueue(name="rgb")
        startTime = time.monotonic()
        color2 = (255, 255, 255)
        counter = 0

        while True:
            inRgb = qRgb.get()
            if inRgb is not None:
                frame = inRgb.getCvFrame()
                cv2.putText(frame, "NN fps: {:.2f}".format(counter / (time.monotonic() - startTime)),
                            (2, frame.shape[0] - 4), cv2.FONT_HERSHEY_TRIPLEX, 0.4, color2)

            if frame is not None:
                counter += 1
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            frame_placeholder.image(frame, channels="RGB")
            if cv2.waitKey(1) & 0xFF == ord("q") or stop_button_pressed:
                break


st.header("Ab me kia he kaho tere ko")
def main():
    st.header("Hello bhai")
    st.title("Webcam feed on browser")
    start_button_pressed = st.button("Start")
    
    col1, col2, col3 = st.columns([1, 2, 1])
    with col2:
        if st.button("Forward"):
            move_motor_forward()
            st.write("Car moving forward!")

    col1, col2, col3 = st.columns([3, 5, 5])
    with col1:
        if st.button("Left"):
            rotate_motor_left()
            st.write("Car turning left!")
    with col3:
        if st.button("Right"):
            rotate_motor_right()
            st.write("Car turning right!")
    with col2:
        if st.button("Emergency Stop"):
            stop_motor()
            st.write("Car stopped!")
    
    col1, col2, col3 = st.columns([1, 2, 1])
    with col2:
        if st.button("Backward"):
            move_motor_backward()
            st.write("Car moving backward!")
            
    st.title('Gimbal Control')
    col4, col5, col6, col7 = st.columns([3, 3, 3, 5])
    with col4:
        if st.button("Cam Left"):
            cam_left()
            st.write("Cam is turning left!")
    with col5:
        if st.button("Cam Right"):
            cam_right()
            st.write("Cam is turning right!")
    with col6:
        if st.button("Cam Up"):
            cam_up()
            st.write("Cam is turning up!")
    with col7:
        if st.button("Cam Bottom"):
            cam_bottom()
            st.write("Cam is turning down!")
            
    if start_button_pressed:
        video_disp()

if _name_ == "_main_":
    main()
