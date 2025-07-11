package assignment;
/**
 *
 * CS314H Programming Assignment 1 - Java image processing
 *
 * Included is the Invert effect from the assignment.  Use this as an
 * example when writing the rest of your transformations.  For
 * convenience, you should place all of your transformations in this file.
 *
 * You can compile everything that is needed with
 * javac -d bin src/assignment/*.java
 *
 * You can run the program with
 * java -cp bin assignment.JIP
 *
 * Please note that the above commands assume that you are in the prog1
 * directory.
 */

import java.util.ArrayList;

class Invert extends ImageEffect {
    public int[][] apply(int[][] pixels,
                         ArrayList<ImageEffectParam> params) {
        int width = pixels[0].length;
        int height = pixels.length;

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                pixels[y][x] = ~pixels[y][x];
            }
        }
        return pixels;
    }
}

class Dummy extends ImageEffect {

    public Dummy() {
        super();
        params = new ArrayList<ImageEffectParam>();
        params.add(new ImageEffectParam("ParamName",
                                           "Description of param.",
                                           10, 0, 1000));
    }

    public int[][] apply(int[][] pixels,
                         ArrayList<ImageEffectParam> params) {
        // Use params here.
        return pixels;
    }

}

class NoRed extends ImageEffect {

    /*public NoRed() {
        super();
        params = new ArrayList<ImageEffectParam>();
        params.add(new ImageEffectParam("ParamName",
                                           "Description of param.",
                                           10, 0, 1000));
    } */

    public int[][] apply(int[][] pixels,
                         ArrayList<ImageEffectParam> params) {
        // Use params here.
        int width = pixels[0].length;
        int height = pixels.length;
        
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                //change red to 0 to remove
                pixels[y][x] =  makePixel(0, getGreen(pixels[y][x]), getBlue(pixels[y][x]));
            }
        }
        return pixels;
    }

}

class NoGreen extends ImageEffect {

    /*public NoGreen() {
        super();
        params = new ArrayList<ImageEffectParam>();
        params.add(new ImageEffectParam("ParamName",
                                           "Description of param.",
                                           10, 0, 1000));
    }*/

    public int[][] apply(int[][] pixels,
                         ArrayList<ImageEffectParam> params) {
        // Use params here.
        int width = pixels[0].length;
        int height = pixels.length;
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                //change green to 0 to remove
                pixels[y][x] =  makePixel(getRed(pixels[y][x]), 0, getBlue(pixels[y][x]));
            }
        }
        return pixels;
    }

}

class NoBlue extends ImageEffect {

    /*public NoBlue() {
        super();
        params = new ArrayList<ImageEffectParam>();
        params.add(new ImageEffectParam("ParamName",
                                           "Description of param.",
                                           10, 0, 1000));
    }*/

    public int[][] apply(int[][] pixels,
                         ArrayList<ImageEffectParam> params) {
        // Use params here.
        int width = pixels[0].length;
        int height = pixels.length;
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                //change blue to 0 to remove
                pixels[y][x] =  makePixel(getRed(pixels[y][x]), getGreen(pixels[y][x]), 0);
            }
        }
        return pixels;
    }

}

class RedOnly extends ImageEffect {

    /*public RedOnly() {
        super();
        params = new ArrayList<ImageEffectParam>();
        params.add(new ImageEffectParam("ParamName",
                                           "Description of param.",
                                           10, 0, 1000));
    }*/

    public int[][] apply(int[][] pixels,
                         ArrayList<ImageEffectParam> params) {
        // Use params here.
        int width = pixels[0].length;
        int height = pixels.length;
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                //change blue and green to 0 to remove but keep red
                pixels[y][x] =  makePixel(getRed(pixels[y][x]), 0, 0);
            }
        }
        return pixels;
    }

}

class GreenOnly extends ImageEffect {

    /*public GreenOnly() {
        super();
        params = new ArrayList<ImageEffectParam>();
        params.add(new ImageEffectParam("ParamName",
                                           "Description of param.",
                                           10, 0, 1000));
    }*/

    public int[][] apply(int[][] pixels,
                         ArrayList<ImageEffectParam> params) {
        // Use params here.
        int width = pixels[0].length;
        int height = pixels.length;
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                //change blue and red to 0 to remove but keep green
                pixels[y][x] =  makePixel(0, getGreen(pixels[y][x]), 0);
            }
        }
        return pixels;
    }

}

class BlueOnly extends ImageEffect {

    /*public BlueOnly() {
        super();
        params = new ArrayList<ImageEffectParam>();
        params.add(new ImageEffectParam("ParamName",
                                           "Description of param.",
                                           10, 0, 1000));
    }*/

    public int[][] apply(int[][] pixels,
                         ArrayList<ImageEffectParam> params) {
        // Use params here.
        int width = pixels[0].length;
        int height = pixels.length;
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                //change red and green to 0 to remove but keep blue
                pixels[y][x] =  makePixel(0, 0, getBlue(pixels[y][x]));
            }
        }
        return pixels;
    }

}

class BlackAndWhite extends ImageEffect {

    /*public BlackAndWhite() {
        super();
        params = new ArrayList<ImageEffectParam>();
        params.add(new ImageEffectParam("ParamName",
                                           "Description of param.",
                                           10, 0, 1000));
    }*/

    public int[][] apply(int[][] pixels,
                         ArrayList<ImageEffectParam> params) {
        // Use params here.
        // assumption: the method will print out an image with pixels that are exclusively Black and White
        // grey pixels are not considered Black and White
        int width = pixels[0].length;
        int height = pixels.length;
        int num;
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                // add up RGB values
                num= getRed(pixels[y][x]) + getBlue(pixels [y][x]) + getGreen(pixels[y][x]);
                // 383 = 255*3/2 rounded up
                if (num>=383)
                {
                    pixels[y][x] =  makePixel(255, 255, 255);
                }
                if (num<383)
                {
                    pixels[y][x] =  makePixel(0, 0, 0);
                }
            }
        }
        return pixels;
    }

}

class HorizontalReflect extends ImageEffect {

    /*public VerticalReflect() {
        super();
        params = new ArrayList<ImageEffectParam>();
        params.add(new ImageEffectParam("ParamName",
                                           "Description of param.",
                                           10, 0, 1000));
    }*/

    public int[][] apply(int[][] pixels,
                         ArrayList<ImageEffectParam> params) {
        // Use params here.
        int width = pixels[0].length;
        int height = pixels.length;
        int[][] pixels2 = new int[height][width];
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                // change y values of image
                pixels2 [height-1-y][x] = pixels[y][x];
            }
        }
        return pixels2;
    }

}

class VerticalReflect extends ImageEffect {

    /*public HorizontalReflect() {
        super();
        params = new ArrayList<ImageEffectParam>();
        params.add(new ImageEffectParam("ParamName",
                                           "Description of param.",
                                           10, 0, 1000));
    }*/

    public int[][] apply(int[][] pixels,
                         ArrayList<ImageEffectParam> params) {
        // Use params here.
        int width = pixels[0].length;
        int height = pixels.length;
        int[][] pixels2 = new int[height][width];
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                // change x values of image
                pixels2 [y][width-1-x] = pixels[y][x] ;
            }
        }
        return pixels2;
    }

}

class Grow extends ImageEffect {

    /*public Grow() {
        super();
        params = new ArrayList<ImageEffectParam>();
        params.add(new ImageEffectParam("ParamName",
                                           "Description of param.",
                                           10, 0, 1000));
    }*/

    public int[][] apply(int[][] pixels,
                         ArrayList<ImageEffectParam> params) {
        // Use params here.
        int width = pixels[0].length;
        int height = pixels.length;
        int[][] pixels2 = new int [height*2][width*2];
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                // change one pixel in old image to quad of pixels in new image
                pixels2 [y*2][x*2] = pixels[y][x];
                pixels2 [y*2+1][x*2] = pixels[y][x];
                pixels2 [y*2][x*2+1] = pixels[y][x];
                pixels2 [y*2+1][x*2+1] = pixels[y][x];
            }
        }
        return pixels2;
    }

}

class Shrink extends ImageEffect {

    /*public Shrink() {
        super();
        params = new ArrayList<ImageEffectParam>();
        params.add(new ImageEffectParam("ParamName",
                                           "Description of param.",
                                           10, 0, 1000));
    }*/

    public int[][] apply(int[][] pixels,
                         ArrayList<ImageEffectParam> params) {
        // Use params here.
        // if odd number ignore last row/column
        int width = pixels[0].length;
        int height = pixels.length;
        int red;
        int green;
        int blue;
        int[][] pixels2 = new int [height/2][width/2];
        // ignore last row/column if odd rows/columns
        if (height%2==1)
        {
            height-=1;
        }
        if (width%2==1)
        {
            width -=1;
        }
        for (int x = 0; x < width; x+=2)
        {
            for (int y = 0; y < height; y+=2)
            {
                //average rgb vals to one pixel
                red = getRed(pixels[y][x]) + getRed(pixels[y+1][x]) + getRed (pixels[y][x+1]) + getRed (pixels[y+1][x+1]);
                red/=4;
                green = getGreen(pixels[y][x]) + getGreen(pixels[y+1][x]) + getGreen (pixels[y][x+1]) + getGreen (pixels[y+1][x+1]);
                green/=4;
                blue = getBlue(pixels[y][x]) + getBlue(pixels[y+1][x]) + getBlue (pixels[y][x+1]) + getBlue (pixels[y+1][x+1]);
                blue /=4;
                // divide to half indices and assign new averaged pixel
                pixels2[y/2][x/2] = makePixel(red, green, blue);
            }
        }

        return pixels2;
    }

}

class Threshold extends ImageEffect {

    public Threshold() {
        super();
        params = new ArrayList<ImageEffectParam>();
        params.add(new ImageEffectParam("ParamName",
                                           "Description of param.",
                                           127, 0, 255));
    }

    public int[][] apply(int[][] pixels,
                         ArrayList<ImageEffectParam> params) {
        // Use params here.
        int width = pixels[0].length;
        int height = pixels.length;
        int red;
        int green;
        int blue;
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                // get red val to determine if it is above threshold, make 255 if so, 0 if under
                if (getRed(pixels[y][x])>=params.get(0).getValue())
                {
                    red=255;
                }
                else
                {
                    red=0;
                }

                // get green val to determine if it is above threshold, make 255 if so, 0 if under
                if (getGreen(pixels[y][x])>=params.get(0).getValue())
                {
                    green=255;
                }
                else
                {
                    green=0;
                }

                // get blue val to determine if it is above threshold, make 255 if so, 0 if under
                if (getBlue(pixels[y][x])>=params.get(0).getValue())
                {
                    blue=255;
                }
                else
                {
                    blue=0;
                }

                // assign rgb values to new pixel based on threshold
                pixels[y][x] =  makePixel(red, green, blue);

            }
        }
        return pixels;
    }

   

    
}
