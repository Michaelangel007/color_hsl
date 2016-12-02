// Macros

    #define R8G8B8_R8(r8g8b8) ((r8g8b8 >> 16) & 0xFF)
    #define R8G8B8_G8(r8g8b8) ((r8g8b8 >>  8) & 0xFF)
    #define R8G8B8_B8(r8g8b8) ((r8g8b8 >>  0) & 0xFF)

// Types
    typedef unsigned int A8R8G8B8;

// Utility

    // See: 
    //   http://en.wikipedia.org/wiki/HSL_color_space
    //   https://github.com/mjackson/mjijackson.github.com/blob/master/2008/02/rgb-to-hsl-and-rgb-to-hsv-color-model-conversion-algorithms-in-javascript.txt
    double
    hue2rgb( double p, double q, double t)
    // ========================================================================
    {
        if (t < 0.0 ) t += 1.0;
        if (t > 1.0 ) t -= 1.0;
        if (t < 1/6.) return p + (q - p) * t           * 6.;
        if (t < 3/6.) return q;
        if (t < 4/6.) return p + (q - p) * (2./3. - t) * 6.;

        return p;
    }

    // @param double hue - [0,1] Hue
    // @param double sat - [0,1] Saturation
    // @param double lit - [0,1] Lightness
    // @return 0xAARRGGBB where Alpha is 255
    A8R8G8B8
    HSL2RGB( double hue, double sat, double lit )
    // ========================================================================
    {
        double r, g, b;

        if (sat == 0)
        {
            r = g = b = lit; // achromatic
        }
        else
        {
            double q = lit < 0.5 
                ?              lit * (1. + sat) 
                : lit + sat - (lit *       sat);
            double p = 2.0 * lit - q;

            r = hue2rgb( p, q, hue + 1/3.);
            g = hue2rgb( p, q, hue       );
            b = hue2rgb( p, q, hue - 1/3.);
        }

        return  0
        | ((A8R8G8B8 (r * 255.0)) << 16)
        | ((A8R8G8B8 (g * 255.0)) <<  8)
        | ((A8R8G8B8 (b * 255.0)) <<  0)
        | ((A8R8G8B8 (    255  )) << 24)
        ;
    }

