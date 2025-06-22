# Image_Processing

# Leg Detection Algorithm - Submission

## 📌 Overview
This project implements a leg detection algorithm using OpenCV in C++. It processes a series of input images to detect and highlight small leg-like structures based on shape and position.

The final results are saved as images with bounding boxes around each detected leg.

---

## 🧠 Algorithm Summary
- Resizes input image to a fixed resolution (1024x768).
- Optionally darkens the central circular region to match contrast across images.
- Applies preprocessing (grayscale, Gaussian blur, Otsu thresholding).
- Uses morphological operations to refine segmented blobs.
- Extracts and filters contours based on:
  - Area
  - Aspect ratio
  - Distance from image center
- Draws bounding boxes around valid leg candidates and saves the result.

---

## 📁 Files Included
- `opencvtest.cpp` – main C++ source code
- `ImageProcessing.ipynb` - Test python code
- `out_1.jpg`, `out_2.jpg`, `out_3.jpg`, `out_4.jpg`, `debug_output_1.jpg` – final output images with detected legs
- `Documentation.txt` – detailed explanation of the algorithm
- `README.txt` – this file

---

## 🛠 Requirements
- OpenCV 4.x or newer
- C++ compiler (e.g., g++)

---


