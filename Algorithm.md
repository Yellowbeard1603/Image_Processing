# 🧠 Leg Detection Algorithm

This document explains the process used to detect and localize small leg-like structures in a set of input images using traditional computer vision techniques.

---

## 📌 Objective

Detect and localize small legs from images using OpenCV-based contour analysis. Ensure robustness across varying lighting and contrast conditions.

---

## 🖼️ Input

- Supported Format: `.jpg`
- Expected Files:
  - `1.jpg`
  - `2.jpg`
  - `3.jpg`
  - `4.jpg`
- Resolution: Automatically resized to `1024x768`

---

## 🧾 Output

- Output Files:
  - `out_1.jpg`
  - `out_2.jpg`
  - `out_3.jpg`
  - `out_4.jpg`
- Description: Images with green bounding boxes and labels like `Leg 1`, `Leg 2`, etc.

---

## ⚙️ Algorithm Steps

### 1. **Image Resizing**
- All input images are resized to 1024×768 for consistent processing.

### 2. **Central Contrast Normalization (Optional but Effective)**
- A circular region at the center is selectively darkened to match the lighting profile of other images.

### 3. **Preprocessing**
- Convert image to grayscale.
- Apply Gaussian blur (`kernel size = 5x5`, `sigma = 4`) to suppress noise.
- Use Otsu’s thresholding to segment potential leg regions.

### 4. **Morphological Filtering**
- **Closing**: Fills small gaps within segmented blobs.
- **Opening**: Removes small background noise.
- **Dilation**: Strengthens and connects disjoint parts of the legs.

### 5. **Contour Detection**
- External contours are extracted.
- For each contour:
  - Area is calculated.
  - Aspect ratio is computed (`height / width`).
  - Distance from the image center is measured.

### 6. **Contour Filtering Criteria**
- A contour is considered a leg if:
  - `500 < area < 15000`
  - `0.2 < aspect_ratio < 2.5`
  - `150 < distance_from_center < 250`

### 7. **Drawing & Labeling**
- Each valid leg candidate is:
  - Enclosed in a green rectangle.
  - Labeled as `Leg 1`, `Leg 2`, etc.
- Final image is saved to disk.

---

## 🛠️ Dependencies

- Language: C++
- Library: OpenCV (version 4 or above)

---

## ✅ Strengths

- Lightweight and fast (no ML or GPU dependency)
- Robust against lighting changes (via contrast normalization)
- Modular and easy to tune for other shape-based tasks

---

## ⚠️ Limitations

- May miss legs with irregular edges or severe occlusion
- Requires consistent framing or position of leg objects

---



