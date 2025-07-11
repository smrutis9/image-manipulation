# Image Manipulation Project

## Overview
A Java-based image processing application that implements twelve transformation algorithms to apply various visual effects to images. Supports JPEG, PNG, and GIF formats.

## Features

### Color Filters
- **Remove Colors**: NoRed, NoGreen, NoBlue - Removes specific color channels
- **Isolate Colors**: RedOnly, GreenOnly, BlueOnly - Displays only one color channel

### Image Effects
- **BlackAndWhite**: Converts images to pure black and white based on pixel brightness
- **Threshold**: Binarizes pixel values based on user-defined parameters

### Geometric Transformations
- **HorizontalReflect**: Creates a horizontal mirror image
- **VerticalReflect**: Creates a vertical mirror image
- **Grow**: Doubles the image size
- **Shrink**: Reduces the image size by half

## Technical Approach
- Object-oriented design with inheritance from a base Transformations class
- Pixel-by-pixel manipulation using 2D arrays
- RGB value modifications for color transformations
- Coordinate mapping for geometric transformations

## Testing
- Comprehensive unit testing with custom test cases
- Visual verification through GUI
- Edge case handling for various image dimensions

## Results
Successfully implemented all twelve transformations with interesting visual outcomes, including unexpected artistic effects when combining multiple transformations.

## Author
Smruti Sannabhadti