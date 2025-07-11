package assignment;
import static assignment.ImageEffect.*;

import java.util.ArrayList;

public class Tester{
    public static void main(String[] args) {
        int[][] image = new int [2][2];
        image[0][0] = makePixel(0, 255, 0);
        image[1][0] = makePixel(255, 0, 0);
        image[0][1] = makePixel(0, 0, 255);
        image[1][1] = makePixel(110, 230, 230);
        
        System.out.println("Image Before No Red:");
        for (int i=0; i<2;i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(image[i][j]) + "; green: "+ getGreen(image[i][j]) +"; blue: "+ getBlue(image[i][j]));
            }
        }
        System.out.println("Image After No Red:");
        //testing NoRed
        NoRed test = new NoRed();
        image[0][0] = makePixel(0, 255, 0);
        image[1][0] = makePixel(255, 0, 0);
        image[0][1] = makePixel(0, 0, 255);
        image[1][1] = makePixel(110, 230, 230);
        int[][] nored = test.apply(image, null);
        
        for (int i=0; i<2; i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(nored[i][j]) + "; green: "+ getGreen(nored[i][j]) +"; blue: "+ getBlue(nored[i][j]));
            }
        }
        System.out.println();
        System.out.println("Image Before No Green:");
        for (int i=0; i<2;i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(image[i][j]) + "; green: "+ getGreen(image[i][j]) +"; blue: "+ getBlue(image[i][j]));
            }
        }
        System.out.println("Image After No Green:");
        //testing NoGreen
        NoGreen test1 = new NoGreen();
        image[0][0] = makePixel(0, 255, 0);
        image[1][0] = makePixel(255, 0, 0);
        image[0][1] = makePixel(0, 0, 255);
        image[1][1] = makePixel(110, 230, 230);
        int[][] nogreen = test1.apply(image, null);
        
        for (int i=0; i<2; i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(nogreen[i][j]) + "; green: "+ getGreen(nogreen[i][j]) +"; blue: "+ getBlue(nogreen[i][j]));
            }
        }
        
        System.out.println();
        System.out.println("Image Before No Blue:");
        for (int i=0; i<2;i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(image[i][j]) + "; green: "+ getGreen(image[i][j]) +"; blue: "+ getBlue(image[i][j]));
            }
        }
        System.out.println("Image After No Blue:");
        //testing NoBlue
        NoBlue test2 = new NoBlue();

        image[0][0] = makePixel(0, 255, 0);
        image[1][0] = makePixel(255, 0, 0);
        image[0][1] = makePixel(0, 0, 255);
        image[1][1] = makePixel(110, 230, 230);
        int[][] noblue = test2.apply(image, null);
        for (int i=0; i<2; i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(noblue[i][j]) + "; green: "+ getGreen(noblue[i][j]) +"; blue: "+ getBlue(noblue[i][j]));
            }
        }
        System.out.println();

        System.out.println("Image Before Red Only:");
        for (int i=0; i<2;i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(image[i][j]) + "; green: "+ getGreen(image[i][j]) +"; blue: "+ getBlue(image[i][j]));
            }
        }
        System.out.println("Image After Red Only:");
        //testing RedOnly
        RedOnly test3 = new RedOnly();
        image[0][0] = makePixel(0, 255, 0);
        image[1][0] = makePixel(255, 0, 0);
        image[0][1] = makePixel(0, 0, 255);
        image[1][1] = makePixel(110, 230, 230);
        int[][] redonly = test3.apply(image, null);
        
        for (int i=0; i<2; i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(redonly[i][j]) + "; green: "+ getGreen(redonly[i][j]) +"; blue: "+ getBlue(redonly[i][j]));
            }
        }
        System.out.println();

        System.out.println("Image Before Green Only:");
        for (int i=0; i<2;i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(image[i][j]) + "; green: "+ getGreen(image[i][j]) +"; blue: "+ getBlue(image[i][j]));
            }
        }
        System.out.println("Image After Green Only:");
        //testing GreenOnly
        GreenOnly test4 = new GreenOnly();
        image[0][0] = makePixel(0, 255, 0);
        image[1][0] = makePixel(255, 0, 0);
        image[0][1] = makePixel(0, 0, 255);
        image[1][1] = makePixel(110, 230, 230);
        int[][] greenonly = test4.apply(image, null);
        
        for (int i=0; i<2; i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(greenonly[i][j]) + "; green: "+ getGreen(greenonly[i][j]) +"; blue: "+ getBlue(greenonly[i][j]));
            }
        }
        System.out.println();

        System.out.println("Image Before Blue Only:");
        for (int i=0; i<2;i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(image[i][j]) + "; green: "+ getGreen(image[i][j]) +"; blue: "+ getBlue(image[i][j]));
            }
        }
        System.out.println("Image After Blue Only:");
        //testing BlueOnly
        BlueOnly test5 = new BlueOnly();
        image[0][0] = makePixel(0, 255, 0);
        image[1][0] = makePixel(255, 0, 0);
        image[0][1] = makePixel(0, 0, 255);
        image[1][1] = makePixel(110, 230, 230);
        int[][] blueonly = test5.apply(image, null);
        
        for (int i=0; i<2; i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(blueonly[i][j]) + "; green: "+ getGreen(blueonly[i][j]) +"; blue: "+ getBlue(blueonly[i][j]));
            }
        }
        System.out.println();

        System.out.println("Image Before Black and White:");
        for (int i=0; i<2;i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(image[i][j]) + "; green: "+ getGreen(image[i][j]) +"; blue: "+ getBlue(image[i][j]));
            }
        }
        System.out.println("Image After Black and White:");
        //testing Black and White
        BlackAndWhite test6 = new BlackAndWhite();
        image[0][0] = makePixel(0, 255, 0);
        image[1][0] = makePixel(255, 0, 0);
        image[0][1] = makePixel(0, 0, 255);
        image[1][1] = makePixel(110, 230, 230);
        int[][] blackandwhite = test6.apply(image, null);
        
        for (int i=0; i<2; i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(blackandwhite[i][j]) + "; green: "+ getGreen(blackandwhite[i][j]) +"; blue: "+ getBlue(blackandwhite[i][j]));
            }
        }
        System.out.println();
        image[0][0] = makePixel(0, 255, 0);
        image[1][0] = makePixel(255, 0, 0);
        image[0][1] = makePixel(0, 0, 255);
        image[1][1] = makePixel(110, 230, 230);
        System.out.println("Image Before Vertical Reflect:");
        for (int i=0; i<2;i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(image[i][j]) + "; green: "+ getGreen(image[i][j]) +"; blue: "+ getBlue(image[i][j]));
            }
        }
        System.out.println("Image After Vertical Reflect:");
        //testing Vertical Reflect
        
        VerticalReflect test7 = new VerticalReflect();
        image[0][0] = makePixel(0, 255, 0);
        image[1][0] = makePixel(255, 0, 0);
        image[0][1] = makePixel(0, 0, 255);
        image[1][1] = makePixel(110, 230, 230);
        int[][] vert = test7.apply(image, null);
        
        for (int i=0; i<2; i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(vert[i][j]) + "; green: "+ getGreen(vert[i][j]) +"; blue: "+ getBlue(vert[i][j]));
            }
        }
        System.out.println();

        System.out.println("Image Before Horizontal Reflect:");
        for (int i=0; i<2;i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(image[i][j]) + "; green: "+ getGreen(image[i][j]) +"; blue: "+ getBlue(image[i][j]));
            }
        }
        System.out.println("Image After Horizontal Reflect:");
        //testing Horizontal Reflect
        HorizontalReflect test8 = new HorizontalReflect();
        image[0][0] = makePixel(0, 255, 0);
        image[1][0] = makePixel(255, 0, 0);
        image[0][1] = makePixel(0, 0, 255);
        image[1][1] = makePixel(110, 230, 230);
        int[][] horiz = test8.apply(image, null);
        image[0][0] = makePixel(0, 255, 0);
        image[1][0] = makePixel(255, 0, 0);
        image[0][1] = makePixel(0, 0, 255);
        image[1][1] = makePixel(110, 230, 230);
        
        
        for (int i=0; i<2; i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(horiz[i][j]) + "; green: "+ getGreen(horiz[i][j]) +"; blue: "+ getBlue(horiz[i][j]));
            }
        }
        System.out.println();

        System.out.println("Image Before Grow:");
        for (int i=0; i<2;i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(image[i][j]) + "; green: "+ getGreen(image[i][j]) +"; blue: "+ getBlue(image[i][j]));
            }
        }
        System.out.println("Image After Grow:");
        
        //testing Grow
        Grow test9 = new Grow();
        image[0][0] = makePixel(0, 255, 0);
        image[1][0] = makePixel(255, 0, 0);
        image[0][1] = makePixel(0, 0, 255);
        image[1][1] = makePixel(110, 230, 230);
        int[][] grow = test9.apply(image, null);
        
        for (int i=0; i<grow.length; i++)
        {
            for (int j=0; j< grow[i].length;j++)
            {
                System.out.println("red: "+ getRed(grow[i][j]) + "; green: "+ getGreen(grow[i][j]) +"; blue: "+ getBlue(grow[i][j]));
            }
        }
        System.out.println();

        System.out.println("Image Before Shrink:");
        for (int i=0; i<2;i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(image[i][j]) + "; green: "+ getGreen(image[i][j]) +"; blue: "+ getBlue(image[i][j]));
            }
        }
        System.out.println("Image After Shrink:");
        //testing Shrink
        Shrink test10 = new Shrink();
        int[][] shrink = test10.apply(image, null);
        image[0][0] = makePixel(0, 255, 0);
        image[1][0] = makePixel(255, 0, 0);
        image[0][1] = makePixel(0, 0, 255);
        image[1][1] = makePixel(110, 230, 230);
        int count =0;
        
        for (int i=0; i< shrink.length; i++)
        {
            count++;
            for (int j=0; j<count;j++)
            {
                System.out.println("red: "+ getRed(shrink[i][j]) + "; green: "+ getGreen(shrink[i][j]) +"; blue: "+ getBlue(shrink[i][j]));
            }
        }
        //testing shrink with edge case:
        System.out.println("Image Before Shrink:");
        for (int i=0; i<2;i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(image[i][j]) + "; green: "+ getGreen(image[i][j]) +"; blue: "+ getBlue(image[i][j]));
            }
        }
        System.out.println("Image After Shrink:");
        //testing Shrink edge case
        int[][] image2 = new int [3][3];
        image2[0][0] = makePixel(0, 255, 0);
        image2[1][0] = makePixel(255, 0, 0);
        image2[0][1] = makePixel(0, 0, 255);
        image2[1][1] = makePixel(110, 230, 230);
        image2[1][2] = makePixel(0, 250, 150);
        image2[2][2]= makePixel(110, 130, 112);
        image2[0][2]= makePixel(110, 130, 112);
        image2[2][0]= makePixel(110, 130, 112);
        image2[2][1]= makePixel(110, 130, 112);
        Shrink test12 = new Shrink();
        int[][] shrink2 = test12.apply(image2, null);
        
        for (int i=0; i< shrink2.length; i++)
        {
            for (int j=0; j<shrink2[i].length;j++)
            {
                System.out.println("red: "+ getRed(shrink[i][j]) + "; green: "+ getGreen(shrink[i][j]) +"; blue: "+ getBlue(shrink[i][j]));
            }
        }
        System.out.println();

        System.out.println("Image Before Threshold:");
        for (int i=0; i<2;i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(image[i][j]) + "; green: "+ getGreen(image[i][j]) +"; blue: "+ getBlue(image[i][j]));
            }
        }
        System.out.println("Image After Threshold:");
        //testing Threshold
        Threshold test11 = new Threshold();
        image[0][0] = makePixel(0, 255, 0);
        image[1][0] = makePixel(255, 0, 0);
        image[0][1] = makePixel(0, 0, 255);
        image[1][1] = makePixel(110, 230, 230);
        ArrayList<ImageEffectParam> params2 = new ArrayList<>();
        ImageEffectParam obj2 = new ImageEffectParam(null, null, 110 ,0 ,255);
        params2.add(obj2);
        
        int[][] threshold = test11.apply(image, params2);
        
        for (int i=0; i<2; i++)
        {
            for (int j=0; j<2;j++)
            {
                System.out.println("red: "+ getRed(threshold[i][j]) + "; green: "+ getGreen(threshold[i][j]) +"; blue: "+ getBlue(threshold[i][j]));
            }
        }
    }
}
