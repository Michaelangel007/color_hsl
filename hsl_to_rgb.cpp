/*
By: Michael "Code Poet" Pohoreski, aka, Michaelangel007
Copyright: (C) Copyleft 2016

Generate 16x16 TGA image:   tint16x16.tga

* 12 columns of colors (17 steps but last color <0,0,0> is omitted)
* Gray scale
* Primary Red, Green, Blue (17 steps, again last color is omitted)

Hue:   0  #FFFFFF #FFDFDF #FFBFBF #FF9F9F #FF7F7F #FF5F5F #FF3F3F #FF1F1F #FF0000 #DF0000 #BF0000 #9F0000 #7F0000 #5F0000 #3F0000 #1F0000 
Hue:  30  #FFFFFF #FFEFDF #FFDFBF #FFCF9F #FFBF7F #FFAF5F #FF9F3F #FF8F1F #FF7F00 #DF6F00 #BF5F00 #9F4F00 #7F3F00 #5F2F00 #3F1F00 #1F0F00 
Hue:  60  #FFFFFF #FFFFDF #FFFFBF #FEFF9F #FEFF7F #FEFF5F #FEFF3F #FEFF1F #FEFF00 #DFDF00 #BFBF00 #9F9F00 #7F7F00 #5F5F00 #3F3F00 #1F1F00 
Hue:  90  #FFFFFF #EFFFDF #DFFFBF #CFFF9F #BFFF7F #AFFF5F #9FFF3F #8FFF1F #7FFF00 #6FDF00 #5FBF00 #4F9F00 #3F7F00 #2F5F00 #1F3F00 #0F1F00 
Hue: 120  #FFFFFF #DFFFDF #BFFFBF #9FFF9F #7FFF7F #5FFF5F #3FFF3F #1FFF1F #00FF00 #00DF00 #00BF00 #009F00 #007F00 #005F00 #003F00 #001F00 
Hue: 150  #FFFFFF #DFFFEF #BFFFDF #9FFFCF #7FFFBF #5FFFAF #3FFF9F #1FFF8F #00FF7F #00DF6F #00BF5F #009F4F #007F3F #005F2F #003F1F #001F0F 
Hue: 180  #FFFFFF #DFFFFF #BFFFFF #9FFFFE #7FFFFE #5FFFFE #3FFFFE #1FFFFE #00FFFE #00DFDF #00BFBF #009F9F #007F7F #005F5F #003F3F #001F1F 
Hue: 210  #FFFFFF #DFEFFF #BFDFFF #9FCFFF #7FBFFF #5FAFFF #3F9FFF #1F8FFF #007FFF #006FDF #005FBF #004F9F #003F7F #002F5F #001F3F #000F1F 
Hue: 240  #FFFFFF #DFDFFF #BFBFFF #9F9FFF #7F7FFF #5F5FFF #3F3FFF #1F1FFF #0000FF #0000DF #0000BF #00009F #00007F #00005F #00003F #00001F 
Hue: 270  #FFFFFF #EFDFFF #DFBFFF #CF9FFF #BF7FFF #AF5FFF #9F3FFF #8F1FFF #7F00FF #6F00DF #5F00BF #4F009F #3F007F #2F005F #1F003F #0F001F 
Hue: 300  #FFFFFF #FFDFFF #FFBFFF #FF9FFE #FF7FFE #FF5FFE #FF3FFE #FF1FFE #FF00FE #DF00DF #BF00BF #9F009F #7F007F #5F005F #3F003F #1F001F 
Hue: 330  #FFFFFF #FFDFEF #FFBFDF #FF9FCF #FF7FBF #FF5FAF #FF3F9F #FF1F8F #FF007F #DF006F #BF005F #9F004F #7F003F #5F002F #3F001F #1F000F 
Hue: mono #FFFFFF #EFEFEF #DFDFDF #CFCFCF #BFBFBF #AFAFAF #9F9F9F #8F8F8F #7F7F7F #6F6F6F #5F5F5F #4F4F4F #3F3F3F #2F2F2F #1F1F1F #0F0F0F 
Hue: r    #FF0000 #EF0000 #DF0000 #CF0000 #BF0000 #AF0000 #9F0000 #8F0000 #7F0000 #6F0000 #5F0000 #4F0000 #3F0000 #2F0000 #1F0000 #0F0000 
hue: g    #00FF00 #00EF00 #00DF00 #00CF00 #00BF00 #00AF00 #009F00 #008F00 #007F00 #006F00 #005F00 #004F00 #003F00 #002F00 #001F00 #000F00 
hue: b    #0000FF #0000EF #0000DF #0000CF #0000BF #0000AF #00009F #00008F #00007F #00006F #00005F #00004F #00003F #00002F #00001F #00000F 
          1.0000  0.9375  0.8750  0.8125  0.7500  0.6875  0.6250  0.5625  0.5000  0.4375  0.3750  0.3125  0.2500  0.1875  0.1250  0.0625  

*/

// Includes
    #include <stdio.h>
    #include <string.h>

// Implementation

    #include "util_hsb.h"
    #include "util_tga.h"


// ========================================================================
void SaveTGA( int width, int height, void *pixels, size_t length, const char * filename )
{
    const bool  bSaved   = TGA_Save32( width, height, pixels, length, filename );
    const char *pMessage = bSaved
        ? "Wrote"
        : "ERROR: Couldn't write"
        ;
    printf( "%s: '%s'\n", pMessage, filename );
}


// ========================================================================
void MakeHues()
{
    int x = 0;
    int y = 0;

    const int W = 16;
    const int H = 16;
    A8R8G8B8 pixels[ H ][ W ]; // [y][x]

    double nHue = 0.0;
    double dHue = 1. / 12.; // 360/30 = 12 hues

    double nSat = 1.0;

    double nLit = 1.0;
    double dLit = 1./16.; // Gradient: White -> Color -> Black

    int nShades = 16; // Pure black cut off

    A8R8G8B8 rgb;
    memset( pixels, 0, sizeof( pixels ) );

    // Chromatic: Gradient: White -> Color -> Black
    nHue = 0.0;
    while (nHue < 1.)
    {
        printf( "Hue: %3.f  ", nHue * 360.0 );

        y = 0;
        nLit = 1.0;

        for( int iShade = 0; iShade < nShades; iShade++ )
        {
            rgb = HSL2RGB( nHue, 1.0, nLit ); // Saturation = 1.0
            pixels[ y ][ x ] = rgb;

            printf( "#%02X%02X%02X "
                , R8G8B8_R8( rgb )
                , R8G8B8_G8( rgb )
                , R8G8B8_B8( rgb )
            );

            y++;
            nLit -= dLit;
        }

        x++;
        nHue += dHue;

        printf( "\n" );
    }

    // Monochromatic: White - Gray - Black
    printf( "Hue: mono " );
    {
        y = 0;
        nLit = 1.0;
        for( int iShade = 0; iShade < nShades; iShade++ )
        {
            rgb = HSL2RGB( 0.0, 0.0, nLit );
            pixels[ y ][ x ] = rgb;

            printf( "#%02X%02X%02X "
                , R8G8B8_R8( rgb )
                , R8G8B8_G8( rgb )
                , R8G8B8_B8( rgb )
            );

            y++;
            nLit -= dLit;
        }
        printf( "\n" );
    }
    x++;

    // Primary: Primary - Black
    nHue = 0.0;
    while (nHue < 1.)
    {
        if( nHue < 3*dHue ) printf( "Hue: r    " );
        else
        if( nHue < 6*dHue ) printf( "hue: g    " );
        else
        if( nHue < 9*dHue ) printf( "hue: b    " );

        y = 0;
        nLit = 0.5;
        for( int iShade = 0; iShade < nShades; iShade++ )
        {
            rgb = HSL2RGB( nHue, 1.0, nLit );
            pixels[ y ][ x ] = rgb;

            printf( "#%02X%02X%02X "
                , R8G8B8_R8( rgb )
                , R8G8B8_G8( rgb )
                , R8G8B8_B8( rgb )
            );

            y++;
            nLit -= (dLit / 2.0);
        }
        printf( "\n" );

        nHue += 4.0/12.0;
        x++;
    }

    //      'Hue: 330  '
    printf( "          " );

    nLit = 1.0;
    for( int iShade = 0; iShade < nShades; iShade++ )
    {
        //      '#RRGGBB '
        printf( "%5.4f  ", nLit );
        nLit -= dLit;
    }
    printf( "\n" );

    SaveTGA( W, H, pixels, sizeof( pixels ), "tint16x16.tga" );
}


// ========================================================================
void MakeCheckerboards()
{
    double nHue;
    double nSat;
    double nLit;

    double dHue = 1. / 12.; // 360/30 = 12 hues

    int x = 0;
    int y = 0;

    const int W = 32;
    const int H =  4;
    A8R8G8B8 checkerboard[ H ][ W ]; // [y][x]
    A8R8G8B8 rgb;

    memset( checkerboard, 0, sizeof( checkerboard ) );

    // Checkerboard: Chromatic

    nSat = 1.0;

    for( nHue = 0.0, x = 0; x < 12; x++, nHue += dHue )
    {
        y = 0;
        nLit = 0.5; // Primary

        // Top 2 rows
        rgb = HSL2RGB( nHue, nSat, 0.5 ); // Light
        checkerboard[ y+0 ][ 2*x+0 ] = rgb;
        checkerboard[ y+1 ][ 2*x+1 ] = rgb;

        rgb = HSL2RGB( nHue, nSat, 2./3.* 0.5 ); // Dark // // HSB: Brightness = 66% -> HSL: Lightness: 33%
        checkerboard[ y+0 ][ 2*x+1 ] = rgb;
        checkerboard[ y+1 ][ 2*x+0 ] = rgb;

        // Bottom 2 rows
        rgb = HSL2RGB( nHue, nSat, 0.50 * 0.5 ); // Light
        checkerboard[ y+2 ][ 2*x+0 ] = rgb;
        checkerboard[ y+3 ][ 2*x+1 ] = rgb;

        rgb = HSL2RGB( nHue, nSat, 1./3.* 0.5 ); // Dark
        checkerboard[ y+2 ][ 2*x+1 ] = rgb;
        checkerboard[ y+3 ][ 2*x+0 ] = rgb;
    }

    // Checkerboard: Monochromatic
    nHue = 0.0; // Doesn't matter
    nSat = 0.0; // Monochrome

    /*
        Checkoards  Steps   Delta (%)   Greys (%)
        1           2       100         100, 0
                    3        50         100,50     0
        2           4        33         100,66    33, 0
                    5        25         100,75    50,25     0
        3           6        20         100,80    60,40    20, 0
                    7        16.66      100,83    66,50    33,16    0
        ~4          8        15         100,85    70,55    40,25   10, 0
        4           8        14.28      100,~85  ~71,~57  ~42,~28 ~14, 0
                    9        12.5       100,87.5  75,62.5  50,37.5 25,12.5  0
        5           10
        Delta = 1/(steps - 1)
    */


    // Top checkerboards: 4 or 2 look good
    int    nTiles = 2;
    double nSteps = nTiles * 2.0;
    double dLit   = 1.0 / (nSteps - 1.0);

    double checkerboardLite = 1.0; // Start white
    double checkerboardDark ;

    int colBeg = 12; // Start in Col 12
    int colEnd = colBeg + nTiles;

#if 1
    for( x = colBeg; x < colEnd; x++ )
    {
        checkerboardDark = checkerboardLite - dLit;

        // if darker than black then roll over to white for Black & White checkerboard
        if( checkerboardDark < 0.0)
            checkerboardDark = 1.0;

        // Top checkerboards
        rgb = HSL2RGB( 0.0, 0.0, checkerboardLite );
        checkerboard[ y+0 ][ 2*x+0 ] = rgb;
        checkerboard[ y+1 ][ 2*x+1 ] = rgb;

        rgb = HSL2RGB( 0.0, 0.0, checkerboardDark );
        checkerboard[ y+0 ][ 2*x+1 ] = rgb;
        checkerboard[ y+1 ][ 2*x+0 ] = rgb;

        checkerboardLite -= 2.0*dLit; // HSB: Brightness 2*B -> HSL: Lightness: B
    }
#endif

    // Bot checkerboards: 3
    y += 2;

    nTiles = 3;
    nSteps = nTiles * 2.0;
    dLit   = 1.0 / (nSteps - 1.0);

    checkerboardLite = 1.0; // Start white

    colEnd = colBeg + nTiles;

    for( x = colBeg; x < colEnd; x++ )
    {
        checkerboardDark = checkerboardLite - dLit;

//printf( "[%d]  Delta: %5.4f  Lit: %5.3f  Dark: %5.3f\n", x - colBeg, dLit, checkerboardLite, checkerboardDark );

        // Bot checkerboards
        rgb = HSL2RGB( 0.0, 0.0, checkerboardLite );
        checkerboard[ y+0 ][ 2*x+0 ] = rgb;
        checkerboard[ y+1 ][ 2*x+1 ] = rgb;

        rgb = HSL2RGB( 0.0, 0.0, checkerboardDark );
        checkerboard[ y+0 ][ 2*x+1 ] = rgb;
        checkerboard[ y+1 ][ 2*x+0 ] = rgb;

        checkerboardLite -= 2.0*dLit;
    }

    // Black & White checkerboard
    y -= 2;

    checkerboardLite = 0.0;
    checkerboardDark = 1.0;

    rgb = HSL2RGB( 0.0, 0.0, checkerboardLite );
    checkerboard[ y+0 ][ 2*x+0 ] = rgb;
    checkerboard[ y+1 ][ 2*x+1 ] = rgb;

    rgb = HSL2RGB( 0.0, 0.0, checkerboardDark );
    checkerboard[ y+0 ][ 2*x+1 ] = rgb;
    checkerboard[ y+1 ][ 2*x+0 ] = rgb;


    SaveTGA( W, H, checkerboard, sizeof( checkerboard ), "checkerboard32x4.tga" );
}


// ========================================================================
int main( const int nArg, const char* aArg[] )
{
    MakeHues();
    MakeCheckerboards();

    return 0;
}
